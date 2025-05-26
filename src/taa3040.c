/**
 * @file taa3040.c
 * @author Orion Serup (orion@crablabs.io)
 * @brief The implementation of the TAA3040 driver functionality
 * @version 0.1
 * @date 2025-04-29
 * 
 * @license MIT
 * @copyright Copyright (c) Crab Labs LLC 2025
 * 
 */

#include "taa3040.h"
#include "taa3040_registers.h"
#include <string.h>

/* --- Internal Helpers --- */
static bool taa3040_select_page(const taa3040_t *const dev, uint8_t page) 
{
    if(!dev->hal.i2c_write(dev->address, TAA3040_REG_PAGE_SELECT, &page, 1))
        return false;
}

static bool taa3040_write_reg(const taa3040_t *const dev, uint8_t reg, uint8_t val) 
{
    return dev->hal.i2c_write(dev->address, reg, &val, 1);
}

static bool taa3040_read_reg(const taa3040_t *const dev, uint8_t reg, uint8_t *val) 
{
    return dev->hal.i2c_read(dev->address, reg, &val, 1);
}

static bool taa3040_write_i32(const taa3040_t *const dev, uint8_t reg, int32_t v) 
{
    uint8_t b[4] = { (uint8_t)(v >> 24), (uint8_t)(v >> 16), (uint8_t)(v >> 8), (uint8_t)v };
    if(!dev->hal.i2c_write(dev->address, reg, b, 1))
        return false;
    return true;
}

static bool taa3040_read_i32(const taa3040_t *const dev, uint8_t reg, int32_t *v) 
{    
    uint8_t b[4];
    if (!dev->hal.i2c_read(dev->address, reg, b, 4)) 
        return false;

    *v = (int32_t)((b[0]<<24)|(b[1]<<16)|(b[2]<<8)|b[3]);

    return true;
}

/* === Core Device Management === */
bool taa3040_init(taa3040_t *const dev, const taa3040_hal_t *const hal, const uint8_t address) 
{
    if (!dev || !hal) return false;
    dev->hal = *hal;
    dev->address = address;
#ifndef TAA3040_MINIMAL_RAM
    memcpy(&dev->config, &TAA3040_DEFAULT_CONFIG, sizeof(dev->config));
#endif
    return taa3040_select_page(dev, 0);
}

bool taa3040_reset(const taa3040_t *const dev) 
{
    return taa3040_select_page(dev, 0) && taa3040_write_reg(dev, TAA3040_REG_SW_RESET, TAA3040_SW_RESET_MASK);
}

bool taa3040_sleep(const taa3040_t *const dev) 
{
    return taa3040_select_page(dev,0) && taa3040_write_reg(dev, TAA3040_REG_SLEEP_CFG, TAA3040_SLEEP_ENABLE_MASK);
}

bool taa3040_wake(const taa3040_t *const dev) 
{
    uint8_t cfg;
    return taa3040_select_page(dev, 0)
        && taa3040_read_reg(dev, TAA3040_REG_SLEEP_CFG, &cfg)
        && taa3040_write_reg(dev, TAA3040_REG_SLEEP_CFG, cfg & ~TAA3040_SLEEP_ENABLE_MASK);
}

bool taa3040_startup(const taa3040_t *const dev) 
{
#ifndef TAA3040_REDUCED_HAL
    if (dev->hal.enable_write) 
    dev->hal.enable_write(true);
#endif
    uint8_t cfg;
    bool stat = taa3040_select_page(dev,0)
        && taa3040_read_reg(dev, TAA3040_REG_SHUTDOWN_CFG, &cfg)
        && taa3040_write_reg(dev, TAA3040_REG_SHUTDOWN_CFG, cfg & ~TAA3040_SHDNZ_CFG_MASK);

    return stat && taa3040_write_reg(dev, TAA3040_REG_POWER_CONFIG, 0xff); // powers up everything
}

bool taa3040_shutdown(const taa3040_t *const dev) 
{
#ifndef TAA3040_REDUCED_HAL
    if (dev->hal.enable_write) dev->hal.enable_write(false);
#endif
    uint8_t cfg;
    bool stat = taa3040_write_reg(dev, TAA3040_REG_POWER_CONFIG, 0x00);
    return stat 
        && taa3040_select_page(dev,0)
        && taa3040_read_reg(dev, TAA3040_REG_SHUTDOWN_CFG, &cfg)
        && taa3040_write_reg(dev, TAA3040_REG_SHUTDOWN_CFG, cfg | TAA3040_SHDNZ_CFG_MASK);
}

/* === ASI Configuration === */
bool taa3040_set_asi_config(const taa3040_t *const dev, const taa3040_asi_config_t *const a) 
{
    if (!dev || !a) 
        return false;

    taa3040_select_page(dev,0);
    const uint8_t config0 = ((a->mode<<TAA3040_ASI_FORMAT_SHIFT) & TAA3040_ASI_FORMAT_MASK)
                          | ((a->word_length << TAA3040_ASI_WORD_LENGTH_SHIFT) & TAA3040_ASI_WORD_LENGTH_MASK)
                          | (a->fsync_polarity? TAA3040_FSYNC_POLARITY_MASK : 0)
                          | (a->bclk_polarity? TAA3040_BLCK_POLARITY_MASK : 0)
                          | (a->transmit_edge? TAA3040_TRANSMIT_EDGE_MASK : 0)
                          | (a->fill_zeros? TAA3040_TRANSMIT_FILL_MASK : 0);
    if (!taa3040_write_reg(dev, TAA3040_REG_ASI_CONFIG0, config0)) 
        return false;

    const uint8_t config1 = (a->advanced.transmit_lsb_hiz ? TAA3040_TRANSMIT_LSB_MASK : 0)
                          | ((a->advanced.keeper_mode << TAA3040_TRANSMIT_KEEPER_SHIFT) & TAA3040_TRANSMIT_KEEPER_MASK)
                          | ((a->advanced.transmission_offset_cycles << TAA3040_TRANSMIT_OFFSET_SHIFT) & TAA3040_TRANSMIT_OFFSET_MASK);
    if (!taa3040_write_reg(dev, TAA3040_REG_ASI_CONFIG1, config1)) 
        return false;

    uint8_t config2 = (a->advanced.daisy_chain_connection? TAA3040_ASI_DAISY_MASK : 0)
                    | (a->advanced.error_detection? TAA3040_ASI_ERROR_MASK : 0)
                    | (a->advanced.error_recovery? TAA3040_ASI_ERROR_RECOVERY_MASK : 0);
    if (!taa3040_write_reg(dev, TAA3040_REG_ASI_CONFIG2, config2))
        return false;

    uint8_t master0 = (a->slave_mode? 0: TAA3040_MASTER_SLAVE_CONFIG_MASK)
                    | ((a->master_mode.sample_rate << TAA3040_SAMPLE_RATE_SHIFT) & TAA3040_SAMPLE_RATE_MASK)
                    | ((a->master_mode.mclk_fsync_ratio << TAA3040_FSYNC_BCLK_RATIO_SHIFT) & TAA3040_FSYNC_BCLK_RATIO_MASK)
                    | (a->master_mode.sample_rate_48khz? TAA3040_SAMPLE_RATE_MASK : 0)
                    | (a->master_mode.automatic_clock_config? TAA3040_AUTO_CLOCK_CONFIG_MASK : 0)
                    | (a->master_mode.pll_disabled_autoclock? TAA3040_AUTO_MODE_PLL_MASK : 0)
                    | (a->master_mode.gate_clocks? TAA3040_BCLK_FSYNC_GATE_MASK : 0);
    if (!taa3040_write_reg(dev, TAA3040_REG_MASTER_CONFIG0, master0))
        return false;

    uint8_t master1 = ((a->master_mode.mclk_fsync_ratio << TAA3040_FSYNC_BCLK_RATIO_SHIFT) & TAA3040_FSYNC_BCLK_RATIO_MASK)
                    | ((a->master_mode.sample_rate << TAA3040_FSYNC_RATE_SHIFT) & TAA3040_FSYNC_RATE_MASK);
    if (!taa3040_write_reg(dev, TAA3040_REG_MASTER_CONFIG1, master1)) 
        return false;

    uint8_t channel_en = 0;
    for(uint8_t channel = 0; channel < TAA3040_NUM_CHANNELS; ++channel)
    {
        const taa3040_asi_channel_config_t* cc = &a->channel_configs[channel];
        const uint8_t v   = ((cc->slot << TAA3040_ASI_CHANNEL_SLOT_SHIFT) & TAA3040_ASI_CHANNEL_SLOT_MASK)
                    |  (cc->gpio_output? TAA3040_ASI_CHANNEL_OUTPUT_MASK : 0);

        if (cc->enabled)
            channel_en |= (1 << (TAA3040_NUM_CHANNELS - channel - 1));
        
        if(!taa3040_write_reg(dev, TAA3040_REG_ASI_CHANNEL_BASE + channel, v))
            return false;
    }

    if (!taa3040_write_reg(dev, TAA3040_REG_ASI_OUT_CHANNEL_EN, channel_en))
        return false;

    return true;
}

bool taa3040_get_asi_config(const taa3040_t *const dev, taa3040_asi_config_t *const a) 
{
    if (!dev || !a) 
        return false;
    
    taa3040_select_page(dev,0);
    
    uint8_t config0; 
    if(!taa3040_read_reg(dev, TAA3040_REG_ASI_CONFIG0, &config0))
        return false;
    
    a->mode = (config0 & TAA3040_ASI_FORMAT_MASK) >> TAA3040_ASI_FORMAT_SHIFT;
    a->word_length = (config0 & TAA3040_ASI_WORD_LENGTH_MASK) >> TAA3040_ASI_WORD_LENGTH_SHIFT;
    a->fsync_polarity = !!(config0 & TAA3040_FSYNC_POLARITY_MASK);
    a->bclk_polarity = !!(config0 & TAA3040_BLCK_POLARITY_MASK);
    a->transmit_edge = !!(config0 & TAA3040_TRANSMIT_EDGE_MASK);
    a->fill_zeros = !!(config0 & TAA3040_TRANSMIT_FILL_MASK);
    
    uint8_t config1;
    if(!taa3040_read_reg(dev, TAA3040_REG_ASI_CONFIG1, &config1))
        return false;
    
    a->advanced.transmit_lsb_hiz = !!(config1 & TAA3040_TRANSMIT_LSB_MASK);
    a->advanced.keeper_mode = (config1 & TAA3040_TRANSMIT_KEEPER_MASK) >> TAA3040_TRANSMIT_KEEPER_SHIFT;
    a->advanced.transmission_offset_cycles = (config1 & TAA3040_TRANSMIT_OFFSET_MASK) >> TAA3040_TRANSMIT_OFFSET_SHIFT;
    
    uint8_t config2; 
    if(!taa3040_read_reg(dev, TAA3040_REG_ASI_CONFIG2, &config2))
        return false;

    a->advanced.daisy_chain_connection= !!(config2 & TAA3040_ASI_DAISY_MASK);
    a->advanced.error_detection= !!(config2 & TAA3040_ASI_ERROR_MASK);
    a->advanced.error_recovery= !!(config2 & TAA3040_ASI_ERROR_RECOVERY_MASK);

    uint8_t master0; 
    if(!taa3040_read_reg(dev,TAA3040_REG_MASTER_CONFIG0, &master0))
        return false;

    a->slave_mode = !(master0 & TAA3040_MASTER_SLAVE_CONFIG_MASK);
    a->master_mode.sample_rate = (master0 & TAA3040_SAMPLE_RATE_MASK) >> TAA3040_SAMPLE_RATE_SHIFT;
    a->master_mode.mclk_fsync_ratio = (master0 & TAA3040_FSYNC_BCLK_RATIO_MASK) >> TAA3040_FSYNC_BCLK_RATIO_SHIFT;
    a->master_mode.automatic_clock_config = !!(master0 & TAA3040_AUTO_CLOCK_CONFIG_MASK);
    a->master_mode.pll_disabled_autoclock = !!(master0 & TAA3040_AUTO_MODE_PLL_MASK);
    a->master_mode.gate_clocks = !!(master0 & TAA3040_BCLK_FSYNC_GATE_MASK);

    uint8_t master1; 
    if(!taa3040_read_reg(dev,TAA3040_REG_MASTER_CONFIG1,&master1))
        return false;

    a->master_mode.sample_rate = ((master1 & TAA3040_FSYNC_RATE_MASK) >> TAA3040_FSYNC_RATE_SHIFT);
    a->master_mode.mclk_fsync_ratio = ((master1 & TAA3040_FSYNC_BCLK_RATIO_MASK) >> TAA3040_BCLK_FSYNC_GATE_SHIFT);
    
    for(uint8_t channel=0; channel < TAA3040_NUM_CHANNELS; ++channel)
    {
        uint8_t v; 
        if(!taa3040_read_reg(dev, TAA3040_REG_ASI_CHANNEL_BASE + channel, &v))
            return false;

        a->channel_configs[channel].gpio_output = !!(v & TAA3040_ASI_CHANNEL_OUTPUT_MASK);
        a->channel_configs[channel].slot = (v & TAA3040_ASI_CHANNEL_SLOT_MASK) >> TAA3040_ASI_CHANNEL_SLOT_SHIFT;
    }

    uint8_t channel_en;
    if(!taa3040_read_reg(dev, TAA3040_REG_ASI_OUT_CHANNEL_EN, &channel_en))
        return false;

    for(uint8_t i = 0; i < TAA3040_NUM_CHANNELS; i++)
    {
        a->channel_configs[i].enabled = !!(channel_en & (1 << (TAA3040_NUM_CHANNELS - i - 1)));
    }

    return true;
}

/* === Channel Configuration === */
bool taa3040_set_channel_config(const taa3040_t *const dev, uint8_t ch, const taa3040_channel_config_t *const c) 
{
    if(!dev || !c || ch >= TAA3040_NUM_CHANNELS) 
        return false;
    
    taa3040_select_page(dev, 0);
    
    const uint8_t config_reg = TAA3040_REG_CH_CONFIG(ch);
    const uint8_t cfg0 = (c->automatic_gain_control? TAA3040_CHANNEL_AGC_EN_MASK : 0)
                        | ((c->input_impedance << TAA3040_CHANNEL_IMPEDANCE_SHIFT) & TAA3040_CHANNEL_IMPEDANCE_MASK)
                        | (c->dc_coupled? TAA3040_CHANNEL_COUPLING_MASK : 0)
                        | ((c->mode << TAA3040_CHANNEL_SOURCE_SHIFT) & TAA3040_CHANNEL_SOURCE_MASK);
    if(!taa3040_write_reg(dev, config_reg, cfg0))
        return false;

    const uint8_t gain_reg = TAA3040_REG_CH_GAIN(ch);
    const uint8_t cfg1 = (c->gain_db << TAA3040_CHANNEL_GAIN_SHIFT) & TAA3040_CHANNEL_GAIN_MASK;
    if(!taa3040_write_reg(dev, gain_reg, cfg1))
        return false;

    const uint8_t volume_reg = TAA3040_REG_CH_VOLUME(ch);
    const uint8_t cfg2 = (c->digital_volume_setting << TAA3040_CHANNEL_VOLUME_SHIFT) & TAA3040_CHANNEL_VOLUME_MASK;
    if(!taa3040_write_reg(dev, volume_reg, cfg2))
        return false;
    
    const uint8_t gain_cal_reg = TAA3040_REG_CH_GAIN_CAL(ch);
    const uint8_t cfg3 = (c->advanced.gain_calibration << TAA3040_CHANNEL_GAIN_CAL_SHIFT) & TAA3040_CHANNEL_GAIN_CAL_MASK;
    if(!taa3040_write_reg(dev, gain_cal_reg, cfg3))
        return false;
    
    const uint8_t phase_cal_reg = TAA3040_REG_CH_PHASE_CAL(ch);
    const uint8_t cfg4 = (c->advanced.phase_calibration << TAA3040_CHANNEL_PHASE_CAL_SHIFT) & TAA3040_CHANNEL_PHASE_CAL_MASK;
    if(!taa3040_write_reg(dev, phase_cal_reg, cfg4))
        return false;

    return c->enabled? taa3040_enable_channel(dev, ch): true;
}
bool taa3040_get_channel_config(const taa3040_t *const dev, uint8_t ch, taa3040_channel_config_t *const c) 
{
    if(!dev||!c||ch>=TAA3040_NUM_CHANNELS) 
        return false;
    
    memset(c, 0, sizeof(*c)); 
    
    taa3040_select_page(dev,0);
    
    uint8_t v;
    if(!taa3040_read_reg(dev, TAA3040_REG_CH_CONFIG(ch),&v)) 
        return false;

    c->automatic_gain_control= !!(v & TAA3040_CHANNEL_AGC_EN_MASK);
    c->input_impedance = (v & TAA3040_CHANNEL_IMPEDANCE_MASK) >> TAA3040_CHANNEL_IMPEDANCE_SHIFT;
    c->dc_coupled = !!(v & TAA3040_CHANNEL_COUPLING_MASK);
    c->mode = (v & TAA3040_CHANNEL_SOURCE_MASK) >> TAA3040_CHANNEL_SOURCE_SHIFT;

    if(!taa3040_read_reg(dev, TAA3040_REG_CH_GAIN(ch), &v)) 
        return false; 

    c->gain_db = (v & TAA3040_CHANNEL_GAIN_MASK) >> TAA3040_CHANNEL_GAIN_SHIFT;
    
    if(!taa3040_read_reg(dev, TAA3040_REG_CH_VOLUME(ch), &v)) 
        return false; 
    
    c->digital_volume_setting = (v & TAA3040_CHANNEL_VOLUME_MASK) >> TAA3040_CHANNEL_VOLUME_SHIFT;

    if(!taa3040_read_reg(dev,TAA3040_REG_CH_GAIN_CAL(ch), &v))
        return false; 
    
    c->advanced.gain_calibration = (v & TAA3040_CHANNEL_GAIN_CAL_MASK) >> TAA3040_CHANNEL_GAIN_CAL_SHIFT;
    
    if(!taa3040_read_reg(dev, TAA3040_REG_CH_PHASE_CAL(ch), &v))
        return false; 
    
    c->advanced.phase_calibration = (v & TAA3040_CHANNEL_PHASE_CAL_MASK) >> TAA3040_CHANNEL_PHASE_CAL_SHIFT;

    return true;
}

/* === Mixer Configuration === */
bool taa3040_set_mixer_channel_config(const taa3040_t *const dev, uint8_t ch, const taa3040_mixer_channel_config_t *const m) 
{
    if(!dev || !m || ch >= TAA3040_NUM_CHANNELS) 
        return false;

    taa3040_select_page(dev,TAA3040_PAGE_MIXER_CONTROL);
    
    const uint8_t base = TAA3040_REG_MIXER_MATRIX_BASE + ch * TAA3040_MIXER_CHANNEL_STRIDE;
    
    dev->hal.i2c_write(dev->address, base, m->coefficients, TAA3040_NUM_CHANNELS);
 
    return taa3040_select_page(dev, 0);
}
bool taa3040_get_mixer_channel_config(const taa3040_t *const dev, uint8_t ch, taa3040_mixer_channel_config_t *const m) 
{
    if(!dev || !m || ch >= TAA3040_NUM_CHANNELS) 
        return false;

    taa3040_select_page(dev,TAA3040_PAGE_MIXER_CONTROL);
    
    const uint8_t base = TAA3040_REG_MIXER_MATRIX_BASE + ch * TAA3040_MIXER_CHANNEL_STRIDE;
    dev->hal.i2c_read(dev->address, base, m->coefficients, TAA3040_NUM_CHANNELS); 
    
    return taa3040_select_page(dev, 0);
}
bool taa3040_set_mixer_config(const taa3040_t *const dev, const taa3040_mixer_config_t *const M) 
{
    for(int ch = 0; ch < TAA3040_NUM_CHANNELS; ++ch)
    {
        if(!taa3040_set_mixer_channel_config(dev, ch, &M->channels[ch]))
            return false;
    }
    return true;
}
bool taa3040_get_mixer_config(const taa3040_t *const dev, taa3040_mixer_config_t *const M) 
{
    for(int ch = 0; ch < TAA3040_NUM_CHANNELS; ++ch)
    {
        if(!taa3040_get_mixer_channel_config(dev, ch, &M->channels[ch]))
            return false;
    }
    return true;
}

/* === GPIO & Interrupt Configuration === */
bool taa3040_set_gpio_config(const taa3040_t *const dev, const taa3040_gpio_config_t *const g) 
{
    if(!dev || !g) 
        return false;

    taa3040_select_page(dev, 0);
    
    for(int i = 0; i < TAA3040_NUM_GPO; ++i)
    {
        const uint8_t v = ((g->gpo_configs[i].mode << TAA3040_GPO_CONFIG_SHIFT) & TAA3040_GPO_CONFIG_MASK)
                        | ((g->gpo_configs[i].drive << TAA3040_GPO_DRIVE_MODE_SHIFT) & TAA3040_GPO_DRIVE_MODE_MASK);
        if(!taa3040_write_reg(dev,TAA3040_REG_GPO_CONFIG_BASE + i,v))
            return false;
    }
    for(int i = 0; i < TAA3040_NUM_GPI; ++i)
    {
        const uint8_t addr = TAA3040_REG_GPI_CONFIG_BASE + (i/2);
        uint8_t v; 
        if(!taa3040_read_reg(dev, addr, &v))
            return false;

        const uint8_t shift = (i % 2)? TAA3040_GPI1_CONFIG_SHIFT: TAA3040_GPI2_CONFIG_SHIFT;
        const uint8_t mask = (i % 2)? TAA3040_GPI1_CONFIG_MASK: TAA3040_GPI2_CONFIG_MASK;

        v &= ~mask; // clear the mask bits
        v |= ((g->gpi_modes[i] << shift) & mask);

        if(!taa3040_write_reg(dev,addr,v))
            return false;
    }
    return true;
}
bool taa3040_get_gpio_config(const taa3040_t* const dev, taa3040_gpio_config_t* const g) 
{
    if(!dev || !g) 
        return false;

    taa3040_select_page(dev, 0);
    
    for(int i = 0; i < TAA3040_NUM_GPO; ++i)
    { 
        uint8_t v; 
        if(!taa3040_read_reg(dev, TAA3040_REG_GPO_CONFIG_BASE + i, &v))
            return false;

        g->gpo_configs[i].mode = (v & TAA3040_GPO_CONFIG_MASK) >> TAA3040_GPO_CONFIG_SHIFT;
        g->gpo_configs[i].drive =(v & TAA3040_GPO_DRIVE_MODE_MASK) >> TAA3040_GPO_DRIVE_MODE_SHIFT;
    }
    for(int i = 0;  i < TAA3040_NUM_GPI; ++i)
    { 
        const uint8_t addr = TAA3040_REG_GPI_CONFIG_BASE+(i/2);
        
        uint8_t v;
        if(!taa3040_read_reg(dev,addr,&v))
            return false;
        
        const uint8_t shift = (i % 2)? TAA3040_GPI1_CONFIG_SHIFT: TAA3040_GPI2_CONFIG_SHIFT;
        const uint8_t mask = (i % 2)? TAA3040_GPI1_CONFIG_MASK: TAA3040_GPI2_CONFIG_MASK;
        
        g->gpi_modes[i]=(v & mask) >> shift;
    }
    return true;
}
bool taa3040_set_interrupt_config(const taa3040_t* const dev, const taa3040_interrupt_config_t* const i) 
{
    if(!dev || !i) 
        return false;

    taa3040_select_page(dev,0);

    uint8_t cfg=((i->polarity << TAA3040_INTERRUPT_POLARITY_SHIFT) & TAA3040_INTERRUPT_POLARITY_MASK)
              | ((i->event << TAA3040_INTERRUPT_EVENT_SHIFT) & TAA3040_INTERRUPT_EVENT_MASK)
              | (i->latch_enable? TAA3040_INTERRUPT_LATCH_MASK : 0);
    
    if(!taa3040_write_reg(dev, TAA3040_REG_INTERRUPT_CONFIG, cfg))
        return false;

    uint8_t m = (i->mask_pll_interrupt? TAA3040_INTERRUPT_PLL_ERROR_MASK: 0)
            |   (i->mask_asi_interrupt? TAA3040_INTERRUPT_ASI_ERROR_MASK : 0);

    if(!taa3040_write_reg(dev,TAA3040_REG_INTERRUPT_MASK,m))
        return false;
    
    uint8_t l = (i->latch_pll_interrupt? TAA3040_INTERRUPT_PLL_ERROR_MASK: 0)
            |   (i->latch_asi_interrupt? TAA3040_INTERRUPT_ASI_ERROR_MASK: 0);
    
            return taa3040_write_reg(dev,TAA3040_REG_INTERRUPT_LATCH,l);
}

bool taa3040_get_interrupt_config(const taa3040_t* const dev, taa3040_interrupt_config_t* const i) 
{
    if(!dev||!i) 
        return false;

    taa3040_select_page(dev,0);
    
    uint8_t v; 
    if(!taa3040_read_reg(dev, TAA3040_REG_INTERRUPT_CONFIG, &v))
        return false;

    i->polarity = (v & TAA3040_INTERRUPT_POLARITY_MASK) >> TAA3040_INTERRUPT_POLARITY_SHIFT;
    i->event = (v & TAA3040_INTERRUPT_EVENT_MASK) >> TAA3040_INTERRUPT_EVENT_SHIFT;
    i->latch_enable = !!(v & TAA3040_INTERRUPT_LATCH_MASK);
    
    if(!taa3040_read_reg(dev, TAA3040_REG_INTERRUPT_MASK, &v))
        return false;

    i->mask_pll_interrupt = !!(v & TAA3040_INTERRUPT_PLL_ERROR_MASK);
    i->mask_asi_interrupt = !!(v & TAA3040_INTERRUPT_ASI_ERROR_MASK);
    
    if(!taa3040_read_reg(dev,TAA3040_REG_INTERRUPT_LATCH,&v))
        return false;

    i->latch_pll_interrupt = !!(v & TAA3040_INTERRUPT_PLL_ERROR_MASK);
    i->latch_asi_interrupt = !!(v & TAA3040_INTERRUPT_ASI_ERROR_MASK);

    return true;
}

/* === Gain & Volume === */
bool taa3040_set_dsp_config(const taa3040_t* const dev, const taa3040_dsp_config_t* const dsp) 
{
    if (!taa3040_select_page(dev, 0)) 
        return false;
    // DSP_CONFIG0: DECIMATION_FILTER (7-6), CHANNEL_SUMMING (5-4), HPF (1-0)
    const uint8_t cfg0 =  ((dsp->decimation_filter << TAA3040_DECIMATION_FILTER_SHIFT) & TAA3040_DECIMATION_FILTER_MASK)
                        | ((dsp->channel_summing    << TAA3040_CHANNEL_SUM_MODE_SHIFT) & TAA3040_CHANNEL_SUM_MODE_MASK)
                        | ((dsp->high_pass_filter  << TAA3040_HIGH_PASS_FILTER_SHIFT) & TAA3040_HIGH_PASS_FILTER_MASK);
    if (!taa3040_write_reg(dev, TAA3040_REG_DSP_CONFIG0, cfg0)) 
        return false;

    // DSP_CONFIG1: VOLUME_GANGED (7), BIQUADS (6-5), SOFT_SWEEP (4), AGC_SELECT (3)
    const uint8_t cfg1 =  (dsp->volume_ganged ? (1 << 7) : 0)
                        | ((dsp->biquads_per_channel << 5) & 0x60)
                        | (dsp->advanced.soft_stepping ? 0 : (1 << 4))
                        | (dsp->automatic_gain_control ? (1 << 3) : 0);
    if (!taa3040_write_reg(dev, TAA3040_REG_DSP_CONFIG1, cfg1)) 
        return false;

    // AGC config
    uint8_t agc_val = ((dsp->advanced.automatic_gain_control_level  << TAA3040_AGC_LEVEL_SHIFT) & TAA3040_AGC_LEVEL_MASK)
                    | ((dsp->advanced.automatic_gain_control_max_gain << TAA3040_AGC_MAX_GAIN_SHIFT) & TAA3040_AGC_MAX_GAIN_MASK);
    
    if (!taa3040_write_reg(dev, TAA3040_REG_AGC_CONFIG, agc_val)) 
        return false;
    // Custom HPF
    if (dsp->high_pass_filter == TAA3040_HIGH_PASS_FILTER_CUSTOM) 
    {
        if (!taa3040_select_page(dev, TAA3040_PAGE_IIR_COEFF)) 
            return false;
        if (!taa3040_write_i32(dev, TAA3040_REG_IIR_N0, dsp->advanced.custom_high_pass_filter.n0)) return false;
        if (!taa3040_write_i32(dev, TAA3040_REG_IIR_N1, dsp->advanced.custom_high_pass_filter.n1)) return false;
        if (!taa3040_write_i32(dev, TAA3040_REG_IIR_D1, dsp->advanced.custom_high_pass_filter.d1)) return false;
        if (!taa3040_select_page(dev, 0)) 
            return false;
    }
    return true;
}
bool taa3040_get_dsp_config(const taa3040_t* const dev, taa3040_dsp_config_t* const dsp) 
{
    if (!taa3040_select_page(dev, 0)) 
        return false;

    uint8_t cfg0;
    if (!taa3040_read_reg(dev, TAA3040_REG_DSP_CONFIG0, &cfg0)) 
        return false;
    
    dsp->decimation_filter = (taa3040_decimation_filter_t)((cfg0 & TAA3040_DECIMATION_FILTER_MASK) >> TAA3040_DECIMATION_FILTER_SHIFT);
    dsp->channel_summing   = (taa3040_channel_summing_mode_t)((cfg0 & TAA3040_CHANNEL_SUM_MODE_MASK) >> TAA3040_CHANNEL_SUM_MODE_SHIFT);
    dsp->high_pass_filter  = (taa3040_high_pass_filter_t)((cfg0 & TAA3040_HIGH_PASS_FILTER_MASK) >> TAA3040_HIGH_PASS_FILTER_SHIFT);

    uint8_t cfg1;
    if (!taa3040_read_reg(dev, TAA3040_REG_DSP_CONFIG1, &cfg1)) 
        return false;

    dsp->volume_ganged            = !!(cfg1 & TAA3040_VOLUME_GANGED_MASK);
    dsp->biquads_per_channel      = (cfg1 & TAA3040_BIQUAD_COUNT_MASK) >> TAA3040_BIQUAD_COUNT_SHIFT;
    dsp->advanced.soft_stepping   = !(cfg1 & TAA3040_SOFT_STEP_MASK);
    dsp->automatic_gain_control   = !!(cfg1 & TAA3040_AGC_SELECT_MASK);

    uint8_t agc_val;
    if (!taa3040_read_reg(dev, TAA3040_REG_AGC_CONFIG, &agc_val)) 
        return false;
    
    dsp->advanced.automatic_gain_control_level    = (agc_val & TAA3040_AGC_LEVEL_MASK) >> TAA3040_AGC_LEVEL_SHIFT;
    dsp->advanced.automatic_gain_control_max_gain =  agc_val & TAA3040_AGC_MAX_GAIN_MASK;
    if (dsp->high_pass_filter == TAA3040_HIGH_PASS_FILTER_CUSTOM) 
    {
        if (!taa3040_select_page(dev, TAA3040_PAGE_IIR_COEFF)) 
            return false;
        
        if (!taa3040_read_i32(dev, TAA3040_REG_IIR_N0, &dsp->advanced.custom_high_pass_filter.n0)) return false;
        if (!taa3040_read_i32(dev, TAA3040_REG_IIR_N1, &dsp->advanced.custom_high_pass_filter.n1)) return false;
        if (!taa3040_read_i32(dev, TAA3040_REG_IIR_D1, &dsp->advanced.custom_high_pass_filter.d1)) return false;
        
        if (!taa3040_select_page(dev, 0)) 
            return false;
    }
    return true;
}


bool taa3040_get_filter(const taa3040_t* const dev, const uint8_t index, taa3040_biquad_filter_t* const filter)
{
    if (!dev || index > TAA3040_NUM_BIQUADS || !filter)
        return 0;

    const uint8_t page = index > 6? TAA3040_PAGE_BIQUAD_FILTER_2: TAA3040_PAGE_BIQUAD_FILTER_1;
    const uint8_t base_address = TAA3040_REG_BIQUAD_COEFF_BASE + TAA3040_BIQUAD_COEFF_WORDS_PER_SECTION * sizeof(int32_t) * (index % 6);

    if(!taa3040_select_page(dev, page))
        return false;

    if(!taa3040_read_i32(dev, base_address, &filter->n0)) return false;
    if(!taa3040_read_i32(dev, base_address + sizeof(int32_t), &filter->n1)) return false;
    if(!taa3040_read_i32(dev, base_address + 2 * sizeof(int32_t), &filter->n2)) return false;
    if(!taa3040_read_i32(dev, base_address + 3 * sizeof(int32_t), &filter->d1)) return false;
    if(!taa3040_read_i32(dev, base_address + 4 * sizeof(int32_t), &filter->d2)) return false;

    return true;
}

bool taa3040_set_filter(const taa3040_t* const dev, const uint8_t index, taa3040_biquad_filter_t* const filter)
{
    if (!dev || index > TAA3040_NUM_BIQUADS || !filter)
        return 0;
        
    const uint8_t page = index > 6? TAA3040_PAGE_BIQUAD_FILTER_2: TAA3040_PAGE_BIQUAD_FILTER_1;
    const uint8_t base_address = TAA3040_REG_BIQUAD_COEFF_BASE + TAA3040_BIQUAD_COEFF_WORDS_PER_SECTION * sizeof(int32_t) * (index % 6);

    if(!taa3040_select_page(dev, page))
        return false;

    if(!taa3040_write_i32(dev, base_address, filter->n0)) return false;
    if(!taa3040_write_i32(dev, base_address + sizeof(int32_t), filter->n1)) return false;
    if(!taa3040_write_i32(dev, base_address + 2 * sizeof(int32_t), filter->n2)) return false;
    if(!taa3040_write_i32(dev, base_address + 3 * sizeof(int32_t), filter->d1)) return false;
    if(!taa3040_write_i32(dev, base_address + 4 * sizeof(int32_t), filter->d2)) return false;

    return true;
}

/* === Gain & Volume === */
bool taa3040_set_gain_db(const taa3040_t *const dev, uint8_t ch, uint8_t g) 
{
    if(!dev || ch >= TAA3040_NUM_CHANNELS)
        return false;

    const uint8_t v = (g << TAA3040_CHANNEL_GAIN_SHIFT) & TAA3040_CHANNEL_GAIN_MASK;
    return taa3040_write_reg(dev, TAA3040_REG_CH_GAIN(ch), v);
}
bool taa3040_get_gain_db(const taa3040_t *const dev, uint8_t ch, uint8_t *g) 
{
    if(!dev || !g || ch >= TAA3040_NUM_CHANNELS) 
        return false;
    uint8_t v; 
    if(!taa3040_read_reg(dev, TAA3040_REG_CH_GAIN(ch), &v))
        return false;
    *g = (v & TAA3040_CHANNEL_GAIN_MASK) >> TAA3040_CHANNEL_GAIN_SHIFT;
    return true;
}
bool taa3040_set_digital_volume(const taa3040_t *const dev, uint8_t ch, uint8_t vcode) 
{
    if(!dev || ch >= TAA3040_NUM_CHANNELS) 
        return false;

    return taa3040_write_reg(dev, TAA3040_REG_CH_VOLUME(ch), vcode & TAA3040_CHANNEL_VOLUME_MASK);
}
bool taa3040_get_digital_volume(const taa3040_t *const dev, uint8_t ch, uint8_t *vcode) 
{
    if(!dev || !vcode || ch >= TAA3040_NUM_CHANNELS) 
        return false;

    uint8_t v; 
    if(!taa3040_read_reg(dev, TAA3040_REG_CH_VOLUME(ch), &v))
        return false;

    *vcode = v & TAA3040_CHANNEL_VOLUME_MASK;
    return true;
}
bool taa3040_enable_channel(const taa3040_t* const dev, const uint8_t ch) 
{
    if(!dev || ch >= TAA3040_NUM_CHANNELS)
        return false;
    
    uint8_t v; 
    if(!taa3040_read_reg(dev, TAA3040_REG_IN_CHANNEL_EN, &v))
        return false;
    
    v |= (1 << (TAA3040_NUM_CHANNELS - ch - 1));
    return taa3040_write_reg(dev, TAA3040_REG_IN_CHANNEL_EN, v);
}

/* === Device Status & Config Snapshot === */
bool taa3040_get_status(const taa3040_t *const dev, taa3040_status_t *status) 
{
    if(!dev || !status)
        return false;

    taa3040_select_page(dev, 0);

    uint8_t v; 
    if(!taa3040_read_reg(dev, TAA3040_REG_DEV_STS0, &v))
        return false;
    
    status->device_status = (taa3040_device_status_t)((v & TAA3040_MODE_STATUS_MASK) >> TAA3040_MODE_STATUS_SHIFT);
    
    if(!taa3040_read_reg(dev, TAA3040_REG_STATUS1, &v))
        return false;
    
    for(int i = 0; i < TAA3040_NUM_CHANNELS; ++i)
        status->channel_powered_up[i] = !!(v & (1 << (TAA3040_NUM_CHANNELS - i - 1)));
    
    return true;
}
bool taa3040_set_device_config(const taa3040_t* const dev, const taa3040_config_t *const cfg) 
{
    if(!dev||!cfg)
        return false;

    for(uint8_t i = 0; i < TAA3040_NUM_CHANNELS; ++i) 
        if(!taa3040_set_channel_config(dev, i, &cfg->channel_configs[i])) 
            return false;

    return taa3040_set_asi_config(dev,&cfg->asi_config)    
        && taa3040_set_gpio_config(dev,&cfg->gpio_config)
        && taa3040_set_dsp_config(dev,&cfg->dsp_config)
        && taa3040_set_mixer_config(dev,&cfg->mixer_config)
        && taa3040_set_interrupt_config(dev,&cfg->interrupt_config);
}
bool taa3040_get_device_config(const taa3040_t* const dev, taa3040_config_t *cfg) 
{
    if(!dev || !cfg)
        return false;

    for(uint8_t i = 0; i < TAA3040_NUM_CHANNELS; ++i) 
        if(!taa3040_get_channel_config(dev, i, &cfg->channel_configs[i])) 
            return false;

    return taa3040_get_asi_config(dev,&cfg->asi_config)
        && taa3040_get_gpio_config(dev,&cfg->gpio_config)
        && taa3040_get_dsp_config(dev,&cfg->dsp_config)
        && taa3040_get_mixer_config(dev,&cfg->mixer_config)
        && taa3040_get_interrupt_config(dev,&cfg->interrupt_config);
}
