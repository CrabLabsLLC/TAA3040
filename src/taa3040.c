#include "taa3040.h"
#include "taa3040_registers.h"
#include <stddef.h>
#include <string.h> // For memcpy if needed

/* === Internal Helper Functions === */

static bool taa3040_write(const taa3040_t *const dev, const uint8_t reg, const uint8_t value) {
    return dev->hal.i2c_write(dev->address, reg, value);
}

static bool taa3040_read(const taa3040_t *const dev, const uint8_t reg, uint8_t* const value) {
    return dev->hal.i2c_read(dev->address, reg, value);
}

static bool taa3040_write_multi(const taa3040_t *const dev, uint8_t start_reg, const void* const data, uint8_t len) {
    for (uint8_t i = 0; i < len; ++i) {
        if (!taa3040_write(dev, start_reg + i, ((uint8_t*)data)[i])) return false;
    }
    return true;
}

static bool taa3040_read_multi(const taa3040_t *const dev, const uint8_t start_reg, uint8_t *data, uint8_t len) {
    for (uint8_t i = 0; i < len; ++i) {
        if (!taa3040_read(dev, start_reg + i, &data[i])) return false;
    }
    return true;
}

/* === Core Device Management === */

bool taa3040_init(taa3040_t *const dev, const taa3040_hal_t *const hal, const uint8_t address) {
    if (!dev || !hal) return false;
    dev->hal = *hal;
    dev->address = address;
    return true;
}

bool taa3040_reset(const taa3040_t *const dev) {
    return taa3040_write(dev, TAA3040_REG_SW_RESET, TAA3040_SW_RESET_MASK);
}

bool taa3040_sleep(const taa3040_t *const dev) {
    return taa3040_write(dev, TAA3040_REG_SLEEP_CFG, TAA3040_SLEEP_ENABLE_MASK);
}

bool taa3040_wake(const taa3040_t *const dev) {
    return taa3040_write(dev, TAA3040_REG_SLEEP_CFG, 0x00);
}

bool taa3040_power_on(const taa3040_t *const dev) {
#ifndef TAA3040_REDUCED_HAL
    if (dev->hal.enable_write) dev->hal.enable_write(true);
#endif
    return true;
}

bool taa3040_power_off(const taa3040_t *const dev) {
#ifndef TAA3040_REDUCED_HAL
    if (dev->hal.enable_write) dev->hal.enable_write(false);
#endif
    return true;
}

/* === ASI Configuration === */

bool taa3040_set_asi_config(const taa3040_t *const dev, const taa3040_asi_config_t *const asi) {
    if (!dev || !asi) return false;
    bool success = true;

    uint8_t cfg = (asi->mode & TAA3040_ASI_MODE_MASK)
                | ((asi->word_length << TAA3040_ASI_WORD_LENGTH_SHIFT) & TAA3040_ASI_WORD_LENGTH_MASK);

    if (asi->slave_mode) cfg |= TAA3040_ASI_SLAVE_MODE_ENABLE_MASK;
    if (asi->auto_clock_enabled) cfg |= TAA3040_ASI_AUTO_CLOCK_DETECT_MASK;

    success &= taa3040_write(dev, TAA3040_REG_ASI_CONFIG, cfg);

    uint8_t adv = 0;
    if (asi->transmit_lsb_hiz) adv |= TAA3040_ASI_LSB_TRANSMIT_HIZ_ENABLE_MASK;
    adv |= ((asi->keeper_mode << TAA3040_ASI_KEEPER_MODE_SHIFT) & TAA3040_ASI_KEEPER_MODE_MASK);
    adv |= ((asi->transmission_offset_cycles << TAA3040_ASI_TRANSMIT_OFFSET_SHIFT) & TAA3040_ASI_TRANSMIT_OFFSET_MASK);

    success &= taa3040_write(dev, TAA3040_REG_ASI_ADVANCED, adv);

    return success;
}

/* === Channel Configuration === */

bool taa3040_set_channel_config(const taa3040_t *const dev, const uint8_t ch, const taa3040_channel_config_t *const ch_cfg) {
    if (!dev || !ch_cfg || ch >= TAA3040_NUM_CHANNELS) return false;
    bool success = true;

    success &= taa3040_set_gain_db(dev, ch, ch_cfg->gain_db);
    success &= taa3040_set_digital_volume(dev, ch, ch_cfg->digital_volume_setting);
    success &= taa3040_enable_agc(dev, ch, ch_cfg->automatic_gain_control);

    return success;
}

bool taa3040_get_channel_config(const taa3040_t *const dev, const uint8_t ch, taa3040_channel_config_t *const ch_cfg) {
    if (!dev || !ch_cfg || ch >= TAA3040_NUM_CHANNELS) return false;
    bool success = true;

    success &= taa3040_get_gain_db(dev, ch, &ch_cfg->gain_db);
    success &= taa3040_get_digital_volume(dev, ch, &ch_cfg->digital_volume_setting);
    success &= taa3040_is_agc_enabled(dev, ch, &ch_cfg->automatic_gain_control);

    return success;
}

/* === Full Device Configuration === */

bool taa3040_set_system_config(const taa3040_t *const dev, const taa3040_system_config_t *const sys_cfg) {
    if (!dev || !sys_cfg) return false;
    bool success = true;

    uint8_t sleep_cfg = 0;
    success &= taa3040_read(dev, TAA3040_REG_SLEEP_CFG, &sleep_cfg);

    sleep_cfg &= ~TAA3040_VREF
    // Set VREF Quick Charge Time
    success &= taa3040_write(dev, TAA3040_REG_SLEEP_CFG, sys_cfg->vref_qc_time);

    // Set Fixed I2C Address if applicable
    success &= taa3040_write(dev, TAA3040_REG_FIXED_I2C_ADDR, sys_cfg->fixed_i2c_address ? 0x01 : 0x00);

    return success;
}

bool taa3040_get_system_config(const taa3040_t *const dev, taa3040_system_config_t *const sys_cfg) {
    if (!dev || !sys_cfg) return false;
    uint8_t value;

    // Get VREF Quick Charge Time
    if (!taa3040_read(dev, TAA3040_REG_VREF_QC_TIME, &value)) return false;
    sys_cfg->vref_qc_time = (taa3040_vref_qc_t)value;

    // Get Input Quick Charge Time
    if (!taa3040_read(dev, TAA3040_REG_INPUT_QC_TIME, &value)) return false;
    sys_cfg->input_qc_time = (taa3040_input_qc_t)value;

    // Get Fixed I2C Address
    if (!taa3040_read(dev, TAA3040_REG_FIXED_I2C_ADDR, &value)) return false;
    sys_cfg->fixed_i2c_address = (value == 0x01);

    return true;
}

/* === GPIO Configuration === */

bool taa3040_set_gpio_config(const taa3040_t *const dev, const taa3040_gpio_config_t *const gpio_cfg) {
    if (!dev || !gpio_cfg) return false;
    bool success = true;

    // Configure GPI pins
    for (uint8_t i = 0; i < TAA3040_NUM_GPI; ++i) {
        success &= taa3040_write(dev, TAA3040_REG_GPI_CONFIG_BASE + i, gpio_cfg->gpi_modes[i]);
    }

    // Configure GPO pins
    for (uint8_t i = 0; i < TAA3040_NUM_GPO; ++i) {
        success &= taa3040_write(dev, TAA3040_REG_GPO_CONFIG_BASE + i, gpio_cfg->gpo_configs[i].mode);
        success &= taa3040_write(dev, TAA3040_REG_GPO_CONFIG_BASE + i + TAA3040_GPO_DRIVE_SHIFT, gpio_cfg->gpo_configs[i].drive);
    }

    return success;
}

bool taa3040_get_gpio_config(const taa3040_t *const dev, taa3040_gpio_config_t *const gpio_cfg) {
    if (!dev || !gpio_cfg) return false;
    bool success = true;

    // Read GPI pins
    for (uint8_t i = 0; i < TAA3040_NUM_GPI; ++i) {
        success &= taa3040_read(dev, TAA3040_REG_GPI_CONFIG_BASE + i, &gpio_cfg->gpi_modes[i]);
    }

    // Read GPO pins
    for (uint8_t i = 0; i < TAA3040_NUM_GPO; ++i) {
        success &= taa3040_read(dev, TAA3040_REG_GPO_CONFIG_BASE + i, &gpio_cfg->gpo_configs[i].mode);
        success &= taa3040_read(dev, TAA3040_REG_GPO_CONFIG_BASE + i + TAA3040_GPO_DRIVE_SHIFT, &gpio_cfg->gpo_configs[i].drive);
    }

    return success;
}

/* === Full Device Configuration === */

bool taa3040_set_device_config(const taa3040_t *const dev, const taa3040_config_t *const config) {
    if (!dev || !config) return false;
    bool success = true;

    // Set system config
    success &= taa3040_set_system_config(dev, &config->system_config);

    // Set ASI config
    success &= taa3040_set_asi_config(dev, &config->asi_config);

    // Set channel configs
    for (uint8_t i = 0; i < TAA3040_NUM_CHANNELS; ++i) {
        success &= taa3040_set_channel_config(dev, i, &config->channel_configs[i]);
    }

    // Set GPIO config
    success &= taa3040_set_gpio_config(dev, &config->gpio_config);

    // Set filter config (IIR/Biquad filters)
    success &= taa3040_set_filter_config(dev, &config->filter_config);

    // Set mixer config
    success &= taa3040_set_mixer_config(dev, &config->mixer_config);

    return success;
}

bool taa3040_get_device_config(const taa3040_t *const dev, taa3040_config_t *const config) {
    if (!dev || !config) return false;
    bool success = true;

    // Get system config
    success &= taa3040_get_system_config(dev, &config->system_config);

    // Get ASI config
    success &= taa3040_get_asi_config(dev, &config->asi_config);

    // Get channel configs
    for (uint8_t i = 0; i < TAA3040_NUM_CHANNELS; ++i) {
        success &= taa3040_get_channel_config(dev, i, &config->channel_configs[i]);
    }

    // Get GPIO config
    success &= taa3040_get_gpio_config(dev, &config->gpio_config);

    // Get filter config
    success &= taa3040_get_filter_config(dev, &config->filter_config);

    // Get mixer config
    success &= taa3040_get_mixer_config(dev, &config->mixer_config);

    return success;
}

/* === Fine Channel Controls === */

bool taa3040_set_gain_db(const taa3040_t *const dev, const uint8_t ch, const uint8_t gain_db) {
    if (!dev || ch >= TAA3040_NUM_CHANNELS) return false;
    return taa3040_write(dev, TAA3040_REG_CH_GAIN_BASE + ch, gain_db & TAA3040_CH_GAIN_MASK);
}

bool taa3040_get_gain_db(const taa3040_t *const dev, const uint8_t ch, uint8_t *const gain_db) {
    if (!dev || !gain_db || ch >= TAA3040_NUM_CHANNELS) return false;
    uint8_t val = 0;
    if (!taa3040_read(dev, TAA3040_REG_CH_GAIN_BASE + ch, &val)) return false;
    *gain_db = val & TAA3040_CH_GAIN_MASK;
    return true;
}

bool taa3040_set_digital_volume(const taa3040_t *const dev, const uint8_t ch, const uint8_t vol) {
    if (!dev || ch >= TAA3040_NUM_CHANNELS) return false;
    return taa3040_write(dev, TAA3040_REG_CH_DIG_VOL_BASE + ch, vol);
}

bool taa3040_get_digital_volume(const taa3040_t *const dev, const uint8_t ch, uint8_t *const vol) {
    if (!dev || !vol || ch >= TAA3040_NUM_CHANNELS) return false;
    return taa3040_read(dev, TAA3040_REG_CH_DIG_VOL_BASE + ch, vol);
}

bool taa3040_enable_agc(const taa3040_t *const dev, const uint8_t ch, const bool enable) {
    if (!dev || ch >= TAA3040_NUM_CHANNELS) return false;
    return taa3040_write(dev, TAA3040_REG_CH_AGC_BASE + ch, enable ? TAA3040_AGC_ENABLE_MASK : 0);
}

bool taa3040_is_agc_enabled(const taa3040_t *const dev, const uint8_t ch, bool *const enabled) {
    if (!dev || !enabled || ch >= TAA3040_NUM_CHANNELS) return false;
    uint8_t val;
    if (!taa3040_read(dev, TAA3040_REG_CH_AGC_BASE + ch, &val)) return false;
    *enabled = (val & TAA3040_AGC_ENABLE_MASK) != 0;
    return true;
}

/* === Mixer Matrix === */

bool taa3040_set_mixer_channel_config(const taa3040_t *const dev, const uint8_t ch, const taa3040_mixer_channel_config_t *const mix_cfg) {
    if (!dev || !mix_cfg || ch >= TAA3040_NUM_CHANNELS) return false;
    return taa3040_write_multi(dev, TAA3040_REG_MIXER_MATRIX_BASE + ch * TAA3040_MIXER_CHANNEL_STRIDE,
                               (const uint8_t *)mix_cfg->coefficients, TAA3040_NUM_MIXERS);
}

/* === Filters === */

bool taa3040_set_custom_iir_filter(const taa3040_t *const dev, const taa3040_iir_filter_t *const iir) {
    if (!dev || !iir) return false;

    uint8_t coeffs[9] = {
        (uint8_t)(iir->n0 >> 16), (uint8_t)(iir->n0 >> 8), (uint8_t)(iir->n0),
        (uint8_t)(iir->n1 >> 16), (uint8_t)(iir->n1 >> 8), (uint8_t)(iir->n1),
        (uint8_t)(iir->d1 >> 16), (uint8_t)(iir->d1 >> 8), (uint8_t)(iir->d1)
    };

    if (!taa3040_write(dev, TAA3040_REG_PAGE_SELECT, TAA3040_PAGE_IIR_COEFF))
        return false;

    return taa3040_write_multi(dev, TAA3040_REG_IIR_COEFF_START, coeffs, 9);
}

bool taa3040_set_biquad_filter(const taa3040_t *const dev, const uint8_t idx, const taa3040_biquad_filter_t *const biquad) {
    if (!dev || !biquad || idx >= TAA3040_NUM_BIQUADS) return false;

    uint8_t page = TAA3040_PAGE_BIQUAD_FILTER_1 + (idx / 4);
    uint8_t offset = (idx % 4) * 5 * 3;

    uint8_t coeffs[15] = {
        (uint8_t)(biquad->n0 >> 16), (uint8_t)(biquad->n0 >> 8), (uint8_t)(biquad->n0),
        (uint8_t)(biquad->n1 >> 16), (uint8_t)(biquad->n1 >> 8), (uint8_t)(biquad->n1),
        (uint8_t)(biquad->n2 >> 16), (uint8_t)(biquad->n2 >> 8), (uint8_t)(biquad->n2),
        (uint8_t)(biquad->d1 >> 16), (uint8_t)(biquad->d1 >> 8), (uint8_t)(biquad->d1),
        (uint8_t)(biquad->d2 >> 16), (uint8_t)(biquad->d2 >> 8), (uint8_t)(biquad->d2)
    };

    if (!taa3040_write(dev, TAA3040_REG_PAGE_SELECT, page))
        return false;

    return taa3040_write_multi(dev, TAA3040_REG_BIQUAD_COEFF_BASE + offset, coeffs, sizeof(coeffs));
}

/* === Device Status === */

bool taa3040_get_status(const taa3040_t *const dev, taa3040_status_t *const status) {
    if (!dev || !status) return false;
    uint8_t val;
    if (!taa3040_read(dev, TAA3040_REG_DEV_STS0, &val)) return false;

    uint8_t mode = (val & TAA3040_STATUS_MODE_MASK) >> TAA3040_STATUS_MODE_SHIFT;
    switch (mode) {
        case 0x4: *status = TAA3040_STATUS_SLEEP; break;
        case 0x6: *status = TAA3040_STATUS_ACTIVE_OFF; break;
        case 0x7: *status = TAA3040_STATUS_ACTIVE_ON; break;
        default: return false;
    }

    return true;
}
