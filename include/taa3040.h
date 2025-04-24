/**
 * @file taa3040.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TAA3040_H
#define TAA3040_H

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "taa3040_types.h"

/** Initialize TAA3040 device
 *  @param dev Device context
 *  @return true if successful, false otherwise
 */
bool taa3040_init(const taa3040_config_t* const config, taa3040_t *const dev);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool taa3040_enable(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool taa3040_disable(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool taa3040_reset(void);

/** Configure all channel settings at once
 *  @param dev Device context
 *  @param config Channel configuration settings
 *  @return true if successful, false otherwise
 */
bool taa3040_configure_all_channels(taa3040_t *const dev, const taa3040_channel_config_t *const config);

/** Configure single channel fully
 *  @param dev Device context
 *  @param channel Channel number (0-3)
 *  @param config Channel configuration settings
 *  @return true if successful, false otherwise
 */
bool taa3040_configure_channel(taa3040_t *const dev, const uint8_t channel, const taa3040_channel_config_t *const config);

/** Read channel configuration from the device
 *  @param dev Device context
 *  @param channel Channel number (0-3)
 *  @param config Pointer to store channel configuration settings
 *  @return true if successful, false otherwise
 */
bool taa3040_get_channel_config(taa3040_t *const dev, const uint8_t channel, taa3040_channel_config_t *const config);

/** Set gain for specified channel
 *  @param dev Device context
 *  @param channel Channel number (0-3)
 *  @param gain_db Gain in dB (-12 to +32)
 *  @return true if successful, false otherwise
 */
bool taa3040_set_gain(taa3040_t *const dev, const uint8_t channel, const int gain_db);

/** Get gain for specified channel
 *  @param dev Device context
 *  @param channel Channel number (0-3)
 *  @param gain_db Pointer to store gain in dB
 *  @return true if successful, false otherwise
 */
bool taa3040_get_gain(taa3040_t *const dev, const uint8_t channel, int *const gain_db);

/** Write to a device register
 *  @param dev Device context
 *  @param reg Register address
 *  @param value Value to write
 *  @return true if successful, false otherwise
 */
bool taa3040_write_register(taa3040_t *const dev, const uint8_t reg, const uint8_t value);

/** Read from a device register
 *  @param dev Device context
 *  @param reg Register address
 *  @param value Pointer to store read value
 *  @return true if successful, false otherwise
 */
bool taa3040_read_register(taa3040_t *const dev, const uint8_t reg, uint8_t *const value);

#endif // TAA3040_H