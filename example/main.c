/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../include/taa3040.h"

// main.c
#include <stdio.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// Stub HAL – in your real code, wire these up to your platform’s I²C & GPIO
// -----------------------------------------------------------------------------

// Example 7-bit I²C address for your device
#define TAA3040_I2C_ADDR  0x1A

// These stubs just print–in real use, implement bus transactions!
bool my_i2c_write(uint8_t address, uint8_t reg, const uint8_t *data, size_t len) {
    // TODO: send [reg,data[0],data[1]…] over I²C to (address<<1)|0
    printf("[I2C WRITE] 0x%02X @ 0x%02X (%u bytes)\n", address, reg, (unsigned)len);
    return true;
}

bool my_i2c_read(uint8_t address, uint8_t reg, uint8_t *data, size_t len) {
    // TODO: write reg, then read len bytes into data
    printf("[I2C READ ] 0x%02X @ 0x%02X (%u bytes)\n", address, reg, (unsigned)len);
    // for demo just zero them
    for(size_t i=0; i<len; ++i) data[i] = 0;
    return true;
}

void my_gpio_enable(bool state) {
    // TODO: drive your shutdown (SHDNZ) or enable pin
    printf("[GPIO      ] EN_PIN = %s\n", state ? "HIGH" : "LOW");
}

// -----------------------------------------------------------------------------
// Example usage
// -----------------------------------------------------------------------------

int main(void) 
{
    // 1) Build our HAL descriptor
    taa3040_hal_t hal = 
    {
        .i2c_write    = my_i2c_write,
        .i2c_read     = my_i2c_read,
        .enable_write = my_gpio_enable
    };
    
    // 2) Create device instance
    taa3040_t dev;
    if (!taa3040_init(&dev, &hal, TAA3040_I2C_ADDR)) 
    {
        printf("ERROR: taa3040_init failed\n");
        return -1;
    }
    
    // 3) Reset to known state
    taa3040_reset(&dev);
    
    // 4) Configure ASI for I2S, 24-bit, master @48 kHz
    taa3040_asi_config_t asi = default_asi_config;
    asi.mode         = TAA3040_ASI_MODE_I2S;
    asi.word_length  = TAA3040_ASI_WORD_LENGTH_24BITS;
    asi.slave_mode    = false;    // we drive BCLK/FSYNC
    taa3040_set_asi_config(&dev, &asi);
    
    // 5) Configure channel 0: single-ended analog, 12 dB gain, AGC off
    taa3040_channel_config_t ch0 = TAA3040_DEFAULT_CHANNEL_CONFIG;
    ch0.enabled                 = true;
    ch0.is_microphone           = false;
    ch0.mode                    = TAA3040_CHANNEL_MODE_ANALOG_SE;
    ch0.gain_db                 = 12;
    ch0.automatic_gain_control  = false;
    taa3040_set_channel_config(&dev, 0, &ch0);
    
    // 6) Enable channel 0 in the output enable register
    taa3040_enable_channel(&dev, 0);
    
    // 7) Read back status
    taa3040_status_t status;
    if (taa3040_get_status(&dev, &status)) 
    {
        printf("Device status = %u\n", (unsigned)status.device_status);
        printf("Channel 0 powered up = %s\n",
            status.channel_powered_up[0] ? "YES" : "NO");
    } else {
        printf("ERROR: could not read status\n");
    }
    
    return 0;
}