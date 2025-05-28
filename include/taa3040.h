/**
 * @file taa3040.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#ifndef TAA3040_H
#define TAA3040_H

#ifdef __cplusplus
extern "C" {
#endif

#include "taa3040_types.h"

/* === Core Device Management === */

/**
 * @brief Initialize a TAA3040 device instance.
 *
 * @param[out] dev Pointer to device structure to initialize.
 * @param[in] hal Pointer to constant HAL structure (I2C, GPIO).
 * @param[in] address 7-bit I2C device address.
 * @return true on success, false on failure.
 */
bool taa3040_init(taa3040_t *const dev, const taa3040_hal_t *const hal, const uint8_t address);

/**
 * @brief Perform a software reset to factory default register settings.
 *
 * @param[in] dev Device handle.
 * @return true if successful, false otherwise.
 */
bool taa3040_reset(const taa3040_t *const dev);

/**
 * @brief Put the device into low-power sleep mode.
 *
 * @param[in] dev Device handle.
 * @return true if successful, false otherwise.
 */
bool taa3040_sleep(const taa3040_t *const dev);

/**
 * @brief Wake the device from sleep mode.
 *
 * @param[in] dev Device handle.
 * @return true if successful, false otherwise.
 */
bool taa3040_wake(const taa3040_t *const dev);

/**
 * @brief Enable the device using external control (if available).
 *
 * @param[in] dev Device handle.
 * @return true if successful, false otherwise.
 */
bool taa3040_startup(const taa3040_t*const dev);

/**
 * @brief Disable the device using external control (if available).
 *
 * @param[in] dev Device handle.
 * @return true if successful, false otherwise.
 */
bool taa3040_shutdown(const taa3040_t* const dev);

/* === Global Device Configuration === */

/**
 * @brief Apply a full device configuration snapshot.
 *
 * @param[in] dev Device handle.
 * @param[in] config Pointer to constant configuration data.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_device_config(const taa3040_t* const dev, const taa3040_config_t *const config);

/**
 * @brief Read the current full device configuration.
 *
 * @param[in] dev Device handle.
 * @param[out] config Pointer to configuration structure to fill.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_device_config(const taa3040_t* const dev, taa3040_config_t *const config);

/* === ASI (Audio Serial Interface) Configuration === */

/**
 * @brief Configure the audio output serial interface.
 *
 * @param[in] dev Device handle.
 * @param[in] asi_config Pointer to constant ASI configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_asi_config(const taa3040_t *const dev, const taa3040_asi_config_t *const asi_config);

/**
 * @brief Read back the current ASI configuration.
 *
 * @param[in] dev Device handle.
 * @param[out] asi_config Pointer to ASI configuration structure to fill.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_asi_config(const taa3040_t *const dev, taa3040_asi_config_t *const asi_config);

/* === Per-Channel Input Configuration === */

/**
 * @brief Configure a single input channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Channel index (0–7).
 * @param[in] ch_config Pointer to constant channel configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_channel_config(const taa3040_t *const dev, uint8_t channel, const taa3040_channel_config_t *const ch_config);

/**
 * @brief Read the configuration of a single input channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Channel index (0–7).
 * @param[out] ch_config Pointer to channel configuration structure to fill.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_channel_config(const taa3040_t *const dev, uint8_t channel, taa3040_channel_config_t *const ch_config);

/* === Mixer Configuration === */

/**
 * @brief Set mixer coefficients for a specific output channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Output channel index (0–7).
 * @param[in] mixer_config Pointer to constant mixer configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_mixer_channel_config(const taa3040_t *const dev, uint8_t channel, const taa3040_mixer_channel_config_t *const mixer_config);

/**
 * @brief Read mixer coefficients for a specific output channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Output channel index (0–7).
 * @param[out] mixer_config Pointer to mixer configuration structure to fill.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_mixer_channel_config(const taa3040_t *const dev, uint8_t channel, taa3040_mixer_channel_config_t *const mixer_config);

/**
 * @brief Set the full mixer matrix.
 *
 * @param[in] dev Device handle.
 * @param[in] mixer_config Pointer to constant mixer matrix.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_mixer_config(const taa3040_t *const dev, const taa3040_mixer_config_t *const mixer_config);

/**
 * @brief Read the full mixer matrix.
 *
 * @param[in] dev Device handle.
 * @param[out] mixer_config Pointer to mixer matrix structure to fill.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_mixer_config(const taa3040_t *const dev, taa3040_mixer_config_t *const mixer_config);

bool taa3040_set_system_config(const taa3040_t* const dev, const taa3040_system_config_t* const config);

/**
 * @brief 
 * 
 * @param dev 
 * @param dsp_config 
 * @return true 
 * @return false 
 */
bool taa3040_set_dsp_config(const taa3040_t* const dev, const taa3040_dsp_config_t* const dsp_config);

/**
 * @brief 
 * 
 * @param dev 
 * @param dsp_config 
 * @return true 
 * @return false 
 */
bool taa3040_get_dsp_config(const taa3040_t* const dev, taa3040_dsp_config_t* const dsp_config);

/**
 * @brief Set GPIO pin modes and drive types.
 *
 * @param[in] dev Device handle.
 * @param[in] gpio_config Pointer to constant GPIO configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_gpio_config(const taa3040_t *const dev, taa3040_gpio_config_t *const gpio_config);

/**
 * @brief Set GPIO pin modes and drive types.
 *
 * @param[in] dev Device handle.
 * @param[in] gpio_config Pointer to constant GPIO configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_gpio_config(const taa3040_t *const dev, const taa3040_gpio_config_t *const gpio_config);

/**
 * @brief Configure interrupt polarity, edge trigger, and latch behavior.
 *
 * @param[in] dev Device handle.
 * @param[in] int_config Pointer to constant interrupt configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_set_interrupt_config(const taa3040_t *const dev, const taa3040_interrupt_config_t *const int_config);

/**
 * @brief Configure interrupt polarity, edge trigger, and latch behavior.
 *
 * @param[in] dev Device handle.
 * @param[in] int_config Pointer to constant interrupt configuration.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_interrupt_config(const taa3040_t* const dev, taa3040_interrupt_config_t *const int_config);

/* === Gain, Volume, and AGC === */

/**
 * @brief Set analog front-end gain for a channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Channel index (0–7).
 * @param[in] gain_db Gain value (0–63).
 * @return true if successful, false otherwise.
 */
bool taa3040_set_gain_db(const taa3040_t *const dev, uint8_t channel, uint8_t gain_db);

/**
 * @brief Read analog front-end gain setting for a channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Channel index (0–7).
 * @param[out] gain_db Pointer to receive gain value.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_gain_db(const taa3040_t *const dev, uint8_t channel, uint8_t *const gain_db);

/**
 * @brief Set digital output volume for a channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Channel index (0–7).
 * @param[in] volume_code Volume code (0–255).
 * @return true if successful, false otherwise.
 */
bool taa3040_set_digital_volume(const taa3040_t *const dev, uint8_t channel, uint8_t volume_code);

/**
 * @brief Read digital output volume for a channel.
 *
 * @param[in] dev Device handle.
 * @param[in] channel Channel index (0–7).
 * @param[out] volume_code Pointer to receive volume code.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_digital_volume(const taa3040_t *const dev, uint8_t channel, uint8_t *const volume_code);

/**
 * @brief 
 * 
 * @param dev 
 * @param index 
 * @param filter 
 * @return true 
 * @return false 
 */
bool taa3040_get_filter(const taa3040_t* const dev, const uint8_t index, taa3040_biquad_filter_t* const filter);

/**
 * @brief 
 * 
 * @param dev 
 * @param index
 * @param filter 
 * @return true 
 * @return false 
 */
bool taa3040_set_filter(const taa3040_t* const dev, const uint8_t index, taa3040_biquad_filter_t* const filter);


/**
 * @brief 
 * 
 * @param dev 
 * @param channel 
 * @return true 
 * @return false 
 */
bool taa3040_enable_channel(const taa3040_t* const dev, const uint8_t channel);

/**
 * @brief 
 * 
 * @param dev 
 * @param channel 
 * @return true 
 * @return false 
 */
bool taa3040_disable_channel(const taa3040_t* const dev, const uint8_t channel);

/* === GPIO and Interrupt Configuration === */

/* === Device Status === */

/**
 * @brief Read the device's current operational status.
 *
 * @param[in] dev Device handle.
 * @param[out] status Pointer to receive status value.
 * @return true if successful, false otherwise.
 */
bool taa3040_get_status(const taa3040_t *const dev, taa3040_status_t *const status);

#ifdef __cplusplus
}
#endif

#endif /* TAA3040_H */
