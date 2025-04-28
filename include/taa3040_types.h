

#include <stdint.h>
#include <stdbool.h>

#define TAA3040_NUM_CHANNELS    8   ///< 8 Input and Output channels
#define TAA3040_NUM_GPI         4   ///< 4 Digital Inputs (multipupose pins)
#define TAA3040_NUM_GPO         4   ///< 4 Digital Outputs (multipurpose pins)
#define TAA3040_NUM_BIQUADS     12  ///< 
#define TAA3040_NUM_MIXERS      8

/* === Enumerations === */

/** @brief Audio Output Modes */
typedef enum {
    TAA3040_ASI_MODE_TDM = 0x0,      ///< Time-Division Multiplexed (TDM) output
    TAA3040_ASI_MODE_I2S = 0x1,      ///< Standard I2S output format
    TAA3040_ASI_MODE_LJ  = 0x2,      ///< Left-Justified audio format
    TAA3040_ASI_MODE_RESERVED = 0x3  ///< Reserved (do not use)
} taa3040_asi_mode_t;

/** @brief Audio Word Lengths */
typedef enum {
    TAA3040_ASI_WORD_LENGTH_16BITS = 0x0, ///< 16-bit audio words
    TAA3040_ASI_WORD_LENGTH_20BITS = 0x1, ///< 20-bit audio words
    TAA3040_ASI_WORD_LENGTH_24BITS = 0x2, ///< 24-bit audio words (typical)
    TAA3040_ASI_WORD_LENGTH_32BITS = 0x3  ///< 32-bit audio words
} taa3040_asi_word_length_t;

/** @brief Output Transmission Keeper Options */
typedef enum {
    TAA3040_KEEPER_MODE_DISABLED = 0x0,           ///< Keeper disabled (no data hold after LSB)
    TAA3040_KEEPER_MODE_ENABLED = 0x1,            ///< Keeper always enabled after LSB
    TAA3040_KEEPER_MODE_ONE_CYCLE = 0x2,          ///< Keeper enabled for 1 BCLK cycle after LSB
    TAA3040_KEEPER_MODE_THREE_HALF_CYCLE = 0x3    ///< Keeper enabled for 1.5 BCLK cycles after LSB
} taa3040_keeper_mode_t;

/** @brief Supported Audio Sampling Rates */
typedef enum {
    TAA3040_SAMPLING_RATE_8KHZ  = 0x0, ///< 8 kHz sample rate
    TAA3040_SAMPLING_RATE_16KHZ = 0x1, ///< 16 kHz sample rate
    TAA3040_SAMPLING_RATE_24KHZ = 0x2, ///< 24 kHz sample rate
    TAA3040_SAMPLING_RATE_32KHZ = 0x3, ///< 32 kHz sample rate
    TAA3040_SAMPLING_RATE_48KHZ = 0x4, ///< 48 kHz sample rate
    TAA3040_SAMPLING_RATE_96KHZ = 0x5, ///< 96 kHz sample rate
    TAA3040_SAMPLING_RATE_192KHZ = 0x6, ///< 192 kHz sample rate
    TAA3040_SAMPLING_RATE_384KHZ = 0x7, ///< 384 kHz sample rate
    TAA3040_SAMPLING_RATE_768KHZ = 0x8  ///< 768 kHz sample rate
} taa3040_sampling_rate_t;

/** @brief Master Clock Frequency Options */
typedef enum {
    TAA3040_MCLK_FREQ_12000KHZ = 0x0, ///< 12.000 MHz
    TAA3040_MCLK_FREQ_12288KHZ = 0x1, ///< 12.288 MHz (48kHz x 256)
    TAA3040_MCLK_FREQ_13000KHZ = 0x2, ///< 13.000 MHz
    TAA3040_MCLK_FREQ_16000KHZ = 0x3, ///< 16.000 MHz
    TAA3040_MCLK_FREQ_19200KHZ = 0x4, ///< 19.200 MHz
    TAA3040_MCLK_FREQ_19680KHZ = 0x5, ///< 19.680 MHz
    TAA3040_MCLK_FREQ_24000KHZ = 0x6, ///< 24.000 MHz
    TAA3040_MCLK_FREQ_24576KHZ = 0x7  ///< 24.576 MHz (48kHz x 512)
} taa3040_mclk_freq_t;

/** @brief MCLK Ratio Settings */
typedef enum {
    TAA3040_MCLK_RATIO_64   = 0x0, ///< MCLK = 64 × FSYNC
    TAA3040_MCLK_RATIO_256  = 0x1, ///< MCLK = 256 × FSYNC
    TAA3040_MCLK_RATIO_384  = 0x2, ///< MCLK = 384 × FSYNC
    TAA3040_MCLK_RATIO_512  = 0x3, ///< MCLK = 512 × FSYNC
    TAA3040_MCLK_RATIO_768  = 0x4, ///< MCLK = 768 × FSYNC
    TAA3040_MCLK_RATIO_1024 = 0x5, ///< MCLK = 1024 × FSYNC
    TAA3040_MCLK_RATIO_1536 = 0x6, ///< MCLK = 1536 × FSYNC
    TAA3040_MCLK_RATIO_2304 = 0x7  ///< MCLK = 2304 × FSYNC
} taa3040_mclk_ratio_t;

/** @brief PDM Clock Divider Settings */
typedef enum {
    TAA3040_PDM_CLOCK_3072KHZ = 0x0, ///< 3.072 MHz PDM clock
    TAA3040_PDM_CLOCK_1536KHZ = 0x1, ///< 1.536 MHz PDM clock
    TAA3040_PDM_CLOCK_768KHZ  = 0x2, ///< 768 kHz PDM clock
    TAA3040_PDM_CLOCK_6144KHZ = 0x3  ///< 6.144 MHz PDM clock
} taa3040_pdm_clock_t;

/** @brief GPIO Output Drive Strength Options */
typedef enum {
    TAA3040_GPO_DRIVE_FLOATING = 0x0,   ///< High impedance (floating output)
    TAA3040_GPO_DRIVE_PUSH_PULL,        ///< Push-pull full drive
    TAA3040_GPO_DRIVE_OPEN_DRAIN_PU,    ///< Open-drain with weak pull-up
    TAA3040_GPO_DRIVE_OPEN_DRAIN,       ///< Open-drain output (floating when high)
    TAA3040_GPO_DRIVE_OPEN_SOURCE_PD,   ///< Open-source with weak pull-down
    TAA3040_GPO_DRIVE_OPEN_SOURCE,      ///< Open-source output (strong high)
    TAA3040_GPO_DRIVE_RESERVED          ///< Reserved
} taa3040_gpo_drive_t;

/** @brief GPO Output Functional Modes */
typedef enum {
    TAA3040_GPO_MODE_DISABLED = 0x0,    ///< Output pin disabled
    TAA3040_GPO_MODE_OUTPUT,            ///< General-purpose digital output
    TAA3040_GPO_MODE_IRQ,               ///< Output interrupt signal
    TAA3040_GPO_MODE_SDOUT,             ///< Secondary I2S/ASI data output
    TAA3040_GPO_MODE_PDMCLK             ///< PDM clock output
} taa3040_gpo_mode_t;

/** @brief GPI Input Functional Modes */
typedef enum {
    TAA3040_GPI_MODE_DISABLED = 0x0,///< Pin disabled
    TAA3040_GPI_MODE_INPUT,         ///< General digital input
    TAA3040_GPI_MODE_MCLK,          ///< Master clock input
    TAA3040_GPI_MODE_SDIN,          ///< Secondary I2S/ASI data input
    TAA3040_GPI_MODE_PDM_12,        ///< PDM inputs for Channels 1 and 2
    TAA3040_GPI_MODE_PDM_34,        ///< PDM inputs for Channels 3 and 4
    TAA3040_GPI_MODE_PDM_56,        ///< PDM inputs for Channels 5 and 6
    TAA3040_GPI_MODE_PDM_78         ///< PDM inputs for Channels 7 and 8
} taa3040_gpi_mode_t;

/** @brief Channel Input Modes */
typedef enum {
    TAA3040_CHANNEL_MODE_ANALOG_DIFF = 0x0, ///< Differential analog input
    TAA3040_CHANNEL_MODE_ANALOG_SE,         ///< Single-ended analog input
    TAA3040_CHANNEL_MODE_DIGITAL_PDM,       ///< Digital PDM input
    TAA3040_CHANNEL_MODE_RESERVED           ///< Reserved
} taa3040_channel_mode_t;

/** @brief Input Impedance Settings for Analog Inputs */
typedef enum {
    TAA3040_CHANNEL_IMPEDANCE_2K5 = 0x0,    ///< 2.5 kOhm input impedance
    TAA3040_CHANNEL_IMPEDANCE_10K,          ///< 10 kOhm input impedance
    TAA3040_CHANNEL_IMPEDANCE_20K,          ///< 20 kOhm input impedance
    TAA3040_CHANNEL_IMPEDANCE_RESERVED      ///< Reserved
} taa3040_channel_impedance_t;

/** @brief Internal Reference Voltage Options */
typedef enum {
    TAA3040_REFERENCE_VOLTAGE_2V75 = 0x0,   ///< 2.75V internal reference
    TAA3040_REFERENCE_VOLTAGE_2V5,          ///< 2.5V internal reference
    TAA3040_REFERENCE_VOLTAGE_1V375,        ///< 1.375V internal reference
    TAA3040_REFERENCE_VOLTAGE_RESERVED      ///< Reserved
} taa3040_reference_voltage_t;

/** @brief Microphone Bias Settings */
typedef enum {
    TAA3040_MIC_BIAS_VREF = 0x0,    ///< Mic bias tied to internal reference voltage
    TAA3040_MIC_BIAS_VREF_SCALED,   ///< Mic bias = VREF × 1.096
    TAA3040_MIC_BIAS_AVDD,          ///< Mic bias tied to AVDD
    TAA3040_MIC_BIAS_RESERVED       ///< Reserved
} taa3040_mic_bias_t;

/** @brief Quick Charge Timing for Internal VREF */
typedef enum {
    TAA3040_VREF_QC_3500US = 0x0,   ///< 3.5 ms quick charge time
    TAA3040_VREF_QC_10MS,           ///< 10 ms quick charge time
    TAA3040_VREF_QC_50MS,           ///< 50 ms quick charge time
    TAA3040_VREF_QC_100MS           ///< 100 ms quick charge time
} taa3040_vref_qc_t;

/** @brief Input Capacitor Quick Charge Times */
typedef enum {
    TAA3040_INPUT_QC_2500US = 0x0,  ///< 2.5 ms input quick charge
    TAA3040_INPUT_QC_12500US,       ///< 12.5 ms input quick charge
    TAA3040_INPUT_QC_25MS,          ///< 25 ms input quick charge
    TAA3040_INPUT_QC_50MS           ///< 50 ms input quick charge
} taa3040_input_qc_t;

/**
 * @brief Dynamic power mode channel settings
 * 
 */
typedef enum 
{
    TAA3040_DYNAMIC_MODE_CHANNELS_1_2 = 0x0,    ///< Channels 1-2 can be dynamically powered
    TAA3040_DYNAMIC_MODE_CHANNELS_1_4,          ///< Channels 1-4 can be dynamically powered
    TAA3040_DYNAMIC_MODE_CHANNELS_1_6,          ///< Channels 1-6 can be dynamically powered
    TAA3040_DYNAMIC_MODE_CHANNELS_ALL,          ///< Channels 1-8 can be dynamically powered
} taa3040_dynamic_mode_channels_t;

/**
 * @brief Channel summing mode, which can increase SNR
 * 
 */
typedef enum 
{
    TAA3040_CHANNEL_SUMMING_MODE_NONE = 0x0,
    TAA3040_CHANNEL_SUMMING_MODE_DUAL,          ///< CH1 + CH2 / 2 ...
    TAA3040_CHANNEL_SUMMING_MODE_QUAD,          ///< CH1 + CH2 + CH3 + CH4 / 4 ...
    TAA3040_CHANNEL_SUMMING_MODE_RESERVED
} taa3040_channel_summing_mode_t;

/**
 * @brief Filter type for initial decimation and filtering per channel
 * 
 */
typedef enum 
{
    TAA3040_DECIMATION_FILTER_LIN_PHASE = 0x0,  ///< FIR Filter
    TAA3040_DECIMATION_FILTER_LOW_LATENCY,      ///< Low Latency IIR Filter
    TAA3040_DECIMATION_FILTER_ULTRA_LOW_LATENCY,///< Ultra Low Latency IIR Filter
    TAA3040_DECIMATION_FILTER_RESERVED          
} taa3040_decimation_filter_t;

/**
 * @brief Filter cutoff for the high pass filter after the decimation filter
 * 
 */
typedef enum
{
    TAA3040_HIGH_PASS_FILTER_CUSTOM = 0x0,      ///< User defined IIR Filter 
    TAA3040_HIGH_PASS_FILTER_FS_4000,           ///< Cutoff at Sampling Frequency / 5000
    TAA3040_HIGH_PASS_FILTER_FS_500,            ///< Cutoff at Sampling Frequency / 500
    TAA3040_HIGH_PASS_FILTER_FS_125,            ///< Cutoff at Sampling Frequency / 125
} taa3040_high_pass_filter_t;


/**
 * @brief Behavior for DREG after shutdown
 * 
 */
typedef enum 
{
    TAA3040_SHUTDOWN_DREG_MODE_OFF = 0x0,   ///< DREG turns off with the device
    TAA3040_SHUTDOWN_DREG_MODE_WAIT,        ///< DREG waits for a timer after device shutoff
    TAA3040_SHUTDOWN_DREG_MODE_ON,          ///< DREG stays on after shutdown
} taa3040_shutdown_dreg_mode_t;

/**
 * @brief 
 * 
 */
typedef enum 
{
    TAA3040_DREG_SHUTDOWN_TIME_30MS = 0x0,  ///< DREG stays on for 30ms after shutdown
    TAA3040_DREG_SHUTDOWN_TIME_25MS,        ///< DREG stays on for 25ms after shutdown
    TAA3040_DREG_SHUTDOWN_TIME_10MS,        ///< DREG stays on for 10ms after shutdown
    TAA3040_DREG_SHUTDOWN_TIME_5MS          ///< DREG stays on for 5ms after shutdown 
} taa3040_dreg_shutdown_time_t;

/** @brief Interrupt Signal Polarity */
typedef enum {
    TAA3040_INTERRUPT_POLARITY_ACTIVE_LOW = 0x0, ///< Interrupt active low
    TAA3040_INTERRUPT_POLARITY_ACTIVE_HIGH = 0x1 ///< Interrupt active high
} taa3040_interrupt_polarity_t;

/** @brief Interrupt Triggering Types */
typedef enum {
    TAA3040_INTERRUPT_EVENT_ASSERT = 0x0,   ///< Asserts on interrupt
    TAA3040_INTERRUPT_EVENT_BLINK = 0x2,    ///< Blinks after an assertion
    TAA3040_INTERRUPT_EVENT_PULSE = 0x3,    ///< Assert, Hold and Release
} taa3040_interrupt_event_t;

/**
 * @brief Device status modes.
 */
typedef enum 
{
    TAA3040_STATUS_SLEEP        = 0x4, ///< Device is in Sleep or Shutdown mode
    TAA3040_STATUS_ACTIVE_OFF   = 0x6, ///< Device is Active but all channels are off
    TAA3040_STATUS_ACTIVE_ON    = 0x7, ///< Device is Active and at least one channel is on
} taa3040_status_t;

/**
 * @brief Defines a biquad filter
 * 
 * H(z) = (n0 + 2*n1*z^-1 + n2*z^-2) / (2^31 - 2*d1*z^-1 - d2*z^-2)
 */
typedef struct 
{
    int32_t n0; ///< Numerator coefficient b0
    int32_t n1; ///< Numerator coefficient b1
    int32_t n2; ///< Numerator coefficient b2
    int32_t d1; ///< Denominator coefficient a1
    int32_t d2; ///< Denominator coefficient a2
} taa3040_biquad_filter_t;

/**
 * @brief First-order IIR filter structure.
 * 
 *  H(z) = (n0 + n1*z^-1) / (2^31 - d1*z^-1)
 */
typedef struct {
    int32_t n0; ///< Forward coefficient n0
    int32_t n1; ///< Forward coefficient n1
    int32_t d1; ///< Feedback coefficient d1
} taa3040_iir_filter_t;

/* === Configuration Structures === */

/**
 * @brief Output channel slot configuration.
 */
typedef struct {
    bool enabled;
    bool gpio_output;   ///< If true, output via GPIO instead of ASI/TDM
    uint8_t slot: 6;    ///< Slot assignment (0–63) for TDM/ASI/I2S bus
} taa3040_asi_channel_config_t;

/**
 * @brief GPO (General Purpose Output) pin configuration.
 */
typedef struct {
    taa3040_gpo_mode_t mode;    ///< Functionality mode for the GPO pin
    taa3040_gpo_drive_t drive;  ///< Electrical drive type for the GPO pin
} taa3040_gpo_config_t;

/**
 * @brief GPIO and GPI system configuration.
 */
typedef struct {
    taa3040_gpo_config_t gpo_configs[TAA3040_NUM_GPO];  ///< GPO pin configurations
    taa3040_gpi_mode_t gpi_modes[TAA3040_NUM_GPI];      ///< GPI pin mode selections
} taa3040_gpio_config_t;

/**
 * @brief Main audio serial output configuration.
 */
typedef struct {
    
    taa3040_asi_mode_t mode;                ///< ASI output mode (TDM/I2S/LJ)
    taa3040_asi_word_length_t word_length;  ///< ASI word length (16, 20, 24, 32 bits)

    bool slave_mode;                ///< True if device is ASI slave
    bool auto_clock_enabled;        ///< Auto-detect clock rate
    bool fsync_polarity;            ///< Frame Sync polarity (normal/inverted)
    bool bclk_polarity;             ///< Bit Clock polarity (normal/inverted)
    bool transmit_edge;             ///< Data transmit edge (rising/falling)
    bool fill_zeros;                ///< Fill empty slots with zeros

    struct 
    {
        taa3040_sampling_rate_t sample_rate;    ///< What the ideal sample rate of the ASI bus is 
        taa3040_mclk_ratio_t mclk_fsync_ratio;  ///< What the ratio of FSYNC and MCLK should be

        bool automatic_clock_config;            ///< If the clock frequency should be automatically generated
        bool pll_disabled_autoclock;            ///< If the PLL is shutoff when auto clock generation is enabled
        bool gate_clocks;                       ///< If the clocks should be gated (BLCK and FSYNC)
        bool sample_rate_48khz;                 ///< If the clock is a submultiple of 48KHz
    } master_mode;

    taa3040_asi_channel_config_t channel_configs[TAA3040_NUM_CHANNELS]; ///< Per-channel slot mapping
    struct 
    {
        bool transmit_lsb_hiz;                  ///< Enable high impedance after transmitting LSB
        taa3040_keeper_mode_t keeper_mode;      ///< Keeper mode configuration
        uint8_t transmission_offset_cycles;     ///< Number of offset BCLK cycles
        bool daisy_chain_connection;            ///< Enable daisy-chaining multiple devices
        bool error_detection;                   ///< Enable ASI error detection logic
        bool error_recovery;                    ///< Enable ASI error auto-recovery
    } advanced;

} taa3040_asi_config_t;

/**
 * @brief Advanced device-level settings.
 */
typedef struct 
{
    bool adc_enabled;       ///< If the ADC is enabled (using analog signals)
    bool mic_bias_enabled;  ///< If the Microphone Bias voltage is enabled (using microphones)
    bool pll_enabled;       ///< If the PLL is enabled (clock generating)
    bool dynamic_power_mode;///< If channel power can be dynamically turned on and off when in an out of use

    taa3040_shutdown_dreg_mode_t shutdown_mode; ///< How the digital regulator should behave on shutdown
    struct 
    {
        taa3040_vref_qc_t vref_qc_time;     ///< Quick charge time for internal VREF
        taa3040_input_qc_t input_qc_time;   ///< Quick charge time for input capacitors
        bool fixed_i2c_address;             ///< True = fixed address, False = programmable address

        taa3040_pdm_clock_t pdm_clock;                      ///< What the PDM clock frequency is 
        bool pdm_latching_edge[TAA3040_NUM_CHANNELS / 2];   ///< What the PDM latching edge is

        taa3040_dynamic_mode_channels_t dynamic_mode_channels;  ///< Which channels have dynamic power mode enabled (if dynamic mode is enabled)

        taa3040_dreg_shutdown_time_t dreg_shutdown_time; ///< if the digital regulator is set to turn off with a timer, this sets the time
    
    } advanced;
} taa3040_system_config_t;

/**
 * @brief Controls the signal intake and processing
 * 
 */
typedef struct 
{
    bool volume_ganged;                                             ///< If all channels should use the volume set in the channel 1 volume control register
    uint8_t biquads_per_channel: 2;                                 ///< How many filters per channel (0, 1, 2, or 3): 12 filters total non-shared
    bool automatic_gain_control;                                    ///< If Automatic Gain Control is enabled globally
    taa3040_high_pass_filter_t high_pass_filter;                    ///< How aggressive the DC component removal is
    taa3040_decimation_filter_t decimation_filter;                  ///< What kind of filter is used to decimate the input signals
    taa3040_channel_summing_mode_t channel_summing;                 ///< If channel averaging is set up to maximize SNR
    taa3040_biquad_filter_t biquad_filters[TAA3040_NUM_BIQUADS];    ///< The main output filters
    struct 
    {
        bool soft_stepping;                             ///< If using dynamic volume control, if transitions between (changed) levels are slow or fast
        uint8_t automatic_gain_control_level: 4;        ///< Target input signal level (0-15 -> -6dB to -36dB)
        uint8_t automatic_gain_control_max_gain: 4;     ///< Maximum Gain allowed (0-13 -> 3dB to 42dB)
        taa3040_iir_filter_t custom_high_pass_filter;   ///< If using the custom high pass filter (see highpass filter) this defines that filter
    } advanced;
} taa3040_dsp_config_t;

/* === Mixer Matrix Configuration === */

/**
 * @brief Single mixer row for a channel (input weights for one output channel).
 */
typedef struct {
    int8_t coefficients[TAA3040_NUM_MIXERS]; ///< 8 signed 8-bit mixer coefficients
} taa3040_mixer_channel_config_t;

/**
 * @brief Full mixer configuration across all channels.
 *
 * Output channel N is mixed from input channels 0–7 using programmable weights.
 */
typedef struct {
    taa3040_mixer_channel_config_t channels[TAA3040_NUM_CHANNELS]; ///< Mixer config per output channel
} taa3040_mixer_config_t;

/**
 * @brief Per-channel analog/digital input configuration.
 */
typedef struct {
    bool enabled;       ///< Enable this input channel
    bool is_microphone; ///< True if input requires mic bias
    bool dc_coupled;    ///< True = DC coupled input, False = AC coupled

    taa3040_channel_mode_t mode;                    ///< Input mode (analog/digital/PDM)
    taa3040_channel_impedance_t input_impedance;    ///< Input impedance selection
    uint8_t gain_db;                                ///< Analog gain (0–63 = 0dB to +30dB typically)

    bool automatic_gain_control;    ///< Enable internal AGC (automatically adjusted gain)
    uint8_t digital_volume_setting; ///< Output digital volume (0–255, mapped to -100dB to +27dB)
    struct 
    {
        uint8_t gain_calibration;       ///< Fine gain calibration
        uint8_t phase_calibration;      ///< Fine phase calibration
    } advanced;
} taa3040_channel_config_t;

/**
 * @brief Global device interrupt configuration.
 */
typedef struct {
    taa3040_interrupt_polarity_t polarity;  ///< Interrupt active high/low
    taa3040_interrupt_event_t event;        ///< Event type (level, rising, falling, both)
    bool latch_enable;                      ///< True to enable latched interrupt

    bool mask_pll_interrupt;                ///< PLL Events trigger interrupt
    bool latch_pll_interrupt;               ///< PLL Interrupts stored in register

    bool mask_asi_interrupt;                ///< ASI Events trigger interrupts
    bool latch_asi_interrupt;               ///< ASI Interrupts stored in register

} taa3040_interrupt_config_t;

/**
 * @brief Full device configuration snapshot.
 */
typedef struct {
    taa3040_system_config_t system_config;                          ///< Precise system controls
    taa3040_asi_config_t asi_config;                                ///< Data output configuration
    taa3040_channel_config_t channel_configs[TAA3040_NUM_CHANNELS]; ///< Per-channel configs
    taa3040_gpio_config_t gpio_config;                              ///< Pin configuraton
    taa3040_dsp_config_t dsp_config;                                ///< Channel Filtering 
    taa3040_mixer_config_t mixer_config;                            ///< Mixer matrix configuration
} taa3040_config_t;

/**
 * @brief Registers are specific per page
 * 
 */
typedef struct 
{
    uint8_t page: 2;
    uint8_t reg;
} taa3040_reg_t;

/* === HAL Function Pointer Types === */

/**
 * @brief I2C write function type.
 * 
 * @param[in] address 7-bit I2C device address.
 * @param[in] reg Register address to write.
 * @param[in] data Byte to write.
 * @return true on success, false on failure.
 */
typedef bool (*taa3040_i2c_write_fn)(const uint8_t address, const uint8_t reg, const uint8_t data);

/**
 * @brief I2C read function type.
 * 
 * @param[in] address 7-bit I2C device address.
 * @param[in] reg Register address to read.
 * @param[out] data Pointer to store the read byte.
 * @return true on success, false on failure.
 */
typedef bool (*taa3040_i2c_read_fn)(const uint8_t address, const uint8_t reg, uint8_t *const data);

/**
 * @brief GPIO control function type.
 * 
 * @param[in] state True = set high, false = set low.
 */
typedef void (*taa3040_gpio_set_fn)(const bool state);

/* === HAL Context Structure === */

/**
 * @brief Hardware Abstraction Layer (HAL) connection.
 */
typedef struct {
    taa3040_i2c_read_fn i2c_read;       ///< I2C read function
    taa3040_i2c_write_fn i2c_write;     ///< I2C write function
#ifndef TAA3040_REDUCED_HAL
    taa3040_gpio_set_fn enable_write;   ///< Enable GPIO control (optional)
#endif
} taa3040_hal_t;

/**
 * @brief Device instance object.
 */
typedef struct taa3040 {
    taa3040_hal_t hal;          ///< HAL (I2C, GPIO control)
    uint8_t address;            ///< 7-bit I2C address
#ifndef TAA3040_MINIMAL_RAM
    taa3040_config_t config;    ///< Cached device configuration
#endif
} taa3040_t;

/* Default ASI Channel Configuration */
static const taa3040_asi_channel_config_t default_asi_channel_config = 
{
    .enabled = false,
    .gpio_output = false,
    .slot = 0  // Default slot assignment for TDM/I2S/LJ
};

/* Default ASI Configuration */
static const taa3040_asi_config_t default_asi_config = 
{
    .mode = TAA3040_ASI_MODE_TDM,
    .word_length = TAA3040_ASI_WORD_LENGTH_24BITS,
    .slave_mode = false,  // Device set as master by default
    .auto_clock_enabled = true,
    .fsync_polarity = false,
    .bclk_polarity = false,
    .transmit_edge = false,
    .fill_zeros = false,
    .master_mode = {
        .sample_rate = TAA3040_SAMPLING_RATE_48KHZ,
        .mclk_fsync_ratio = TAA3040_MCLK_RATIO_256,
        .automatic_clock_config = true,
        .pll_disabled_autoclock = false,
        .gate_clocks = false,
        .sample_rate_48khz = true
    },
    .channel_configs = 
    {
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 0  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 1  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 2  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 3  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 4  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 5  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 6  // Default slot assignment for TDM/I2S/LJ
        },
        {
            .enabled = false,
            .gpio_output = false,
            .slot = 7  // Default slot assignment for TDM/I2S/LJ
        },

    },
    .advanced = {
        .transmit_lsb_hiz = false,
        .keeper_mode = TAA3040_KEEPER_MODE_DISABLED,
        .transmission_offset_cycles = 0,
        .daisy_chain_connection = false,
        .error_detection = true,
        .error_recovery = true
    }
};

/* Default Mixer Configuration */
static const taa3040_mixer_config_t default_mixer_config = {
    .channels = {
        { { 1, 0, 0, 0, 0, 0, 0, 0 } }, // Mixer configuration for channel 1
        { { 0, 1, 0, 0, 0, 0, 0, 0 } }, // Mixer configuration for channel 2
        { { 0, 0, 1, 0, 0, 0, 0, 0 } }, // Mixer configuration for channel 3
        { { 0, 0, 0, 1, 0, 0, 0, 0 } }, // Mixer configuration for channel 4
        { { 0, 0, 0, 0, 1, 0, 0, 0 } }, // Mixer configuration for channel 5
        { { 0, 0, 0, 0, 0, 1, 0, 0 } }, // Mixer configuration for channel 6
        { { 0, 0, 0, 0, 0, 0, 1, 0 } }, // Mixer configuration for channel 7
        { { 0, 0, 0, 0, 0, 0, 0, 1 } }  // Mixer configuration for channel 8
    }
};

static const taa3040_channel_config_t taa3040_default_channel_config = 
{
    .enabled = false,
    .is_microphone = true,
    .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
    .dc_coupled = false,
    .gain_db = 0,
    .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
    .digital_volume_setting = 0xC9,
    .automatic_gain_control = false,
    .advanced = 
    {
        .gain_calibration = 8,
        .phase_calibration = 0
    }
};

/* Default DSP Configuration */
static const taa3040_dsp_config_t default_dsp_config = {
    .volume_ganged = false,
    .biquads_per_channel = 0,
    .automatic_gain_control = true,
    .high_pass_filter = TAA3040_HIGH_PASS_FILTER_FS_500,
    .decimation_filter = TAA3040_DECIMATION_FILTER_LIN_PHASE,
    .channel_summing = TAA3040_CHANNEL_SUMMING_MODE_NONE,
    .biquad_filters = {0}, /* Initialize all to zero */
    .advanced = {
        .soft_stepping = true,
        .automatic_gain_control_level = 10,
        .automatic_gain_control_max_gain = 13,
        .custom_high_pass_filter = {0, 0, 0}
    }
};

/* Default System Configuration */
static const taa3040_system_config_t default_system_config = 
{
    .adc_enabled = true,
    .mic_bias_enabled = true,
    .pll_enabled = true,
    .dynamic_power_mode = true,
    .shutdown_mode = TAA3040_SHUTDOWN_DREG_MODE_WAIT,
    .advanced = 
    {
        .vref_qc_time = TAA3040_VREF_QC_3500US,
        .input_qc_time = TAA3040_INPUT_QC_2500US,
        .fixed_i2c_address = false,
        .pdm_clock = TAA3040_PDM_CLOCK_3072KHZ,
        .dynamic_mode_channels = TAA3040_DYNAMIC_MODE_CHANNELS_1_2,
        .dreg_shutdown_time = TAA3040_DREG_SHUTDOWN_TIME_30MS
    }
};


/* Default GPO Configuration */
const taa3040_gpo_config_t default_gpo_config = 
{
    .mode = TAA3040_GPO_MODE_OUTPUT,
    .drive = TAA3040_GPO_DRIVE_PUSH_PULL
};

/* Default GPIO Configuration */
const taa3040_gpio_config_t default_gpio_config = {
    .gpo_configs = 
    {
        {
            .mode = TAA3040_GPO_MODE_OUTPUT,
            .drive = TAA3040_GPO_DRIVE_PUSH_PULL
        },
        {
            .mode = TAA3040_GPO_MODE_OUTPUT,
            .drive = TAA3040_GPO_DRIVE_PUSH_PULL
        },
        {
            .mode = TAA3040_GPO_MODE_OUTPUT,
            .drive = TAA3040_GPO_DRIVE_PUSH_PULL
        },
        {
            .mode = TAA3040_GPO_MODE_OUTPUT,
            .drive = TAA3040_GPO_DRIVE_PUSH_PULL
        },
    },
    .gpi_modes = {
        TAA3040_GPI_MODE_INPUT, TAA3040_GPI_MODE_INPUT, TAA3040_GPI_MODE_INPUT, TAA3040_GPI_MODE_INPUT
    }
};



const taa3040_config_t taa3040_default_config =
{
    .asi_config = 
    {
        .mode = TAA3040_ASI_MODE_TDM,
        .word_length = TAA3040_ASI_WORD_LENGTH_24BITS,
        .slave_mode = false,  // Device set as master by default
        .auto_clock_enabled = true,
        .fsync_polarity = false,
        .bclk_polarity = false,
        .transmit_edge = false,
        .fill_zeros = false,
        .master_mode = {
            .sample_rate = TAA3040_SAMPLING_RATE_48KHZ,
            .mclk_fsync_ratio = TAA3040_MCLK_RATIO_256,
            .automatic_clock_config = true,
            .pll_disabled_autoclock = false,
            .gate_clocks = false,
            .sample_rate_48khz = true
        },
        .channel_configs = 
        {
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 0  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 1  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 2  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 3  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 4  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 5  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 6  // Default slot assignment for TDM/I2S/LJ
            },
            {
                .enabled = false,
                .gpio_output = false,
                .slot = 7  // Default slot assignment for TDM/I2S/LJ
            },
    
        },
        .advanced = {
            .transmit_lsb_hiz = false,
            .keeper_mode = TAA3040_KEEPER_MODE_DISABLED,
            .transmission_offset_cycles = 0,
            .daisy_chain_connection = false,
            .error_detection = true,
            .error_recovery = true
        }
    },
    .channel_configs = 
    {
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        },
        {
            .enabled = false,
            .is_microphone = true,
            .mode = TAA3040_CHANNEL_MODE_ANALOG_DIFF,
            .dc_coupled = false,
            .gain_db = 0,
            .input_impedance = TAA3040_CHANNEL_IMPEDANCE_2K5,
            .digital_volume_setting = 0xC9,
            .automatic_gain_control = false,
            .advanced = 
            {
                .gain_calibration = 8,
                .phase_calibration = 0
            }
        }
    },
    .dsp_config = 
    {
        .volume_ganged = false,
        .biquads_per_channel = 0,
        .automatic_gain_control = true,
        .high_pass_filter = TAA3040_HIGH_PASS_FILTER_FS_500,
        .decimation_filter = TAA3040_DECIMATION_FILTER_LIN_PHASE,
        .channel_summing = TAA3040_CHANNEL_SUMMING_MODE_NONE,
        .biquad_filters = {0}, /* Initialize all to zero */
        .advanced = {
            .soft_stepping = true,
            .automatic_gain_control_level = 10,
            .automatic_gain_control_max_gain = 13,
            .custom_high_pass_filter = {0, 0, 0}
        }
    },
    .gpio_config = 
    {
        .gpo_configs = 
        {
            {
                .mode = TAA3040_GPO_MODE_OUTPUT,
                .drive = TAA3040_GPO_DRIVE_PUSH_PULL
            },
            {
                .mode = TAA3040_GPO_MODE_OUTPUT,
                .drive = TAA3040_GPO_DRIVE_PUSH_PULL
            },
            {
                .mode = TAA3040_GPO_MODE_OUTPUT,
                .drive = TAA3040_GPO_DRIVE_PUSH_PULL
            },
            {
                .mode = TAA3040_GPO_MODE_OUTPUT,
                .drive = TAA3040_GPO_DRIVE_PUSH_PULL
            },
        },
        .gpi_modes = {
            TAA3040_GPI_MODE_INPUT, TAA3040_GPI_MODE_INPUT, TAA3040_GPI_MODE_INPUT, TAA3040_GPI_MODE_INPUT
        }
    },
    .mixer_config = 
    {
        .channels = {
            { { 1, 0, 0, 0, 0, 0, 0, 0 } }, // Mixer configuration for channel 1
            { { 0, 1, 0, 0, 0, 0, 0, 0 } }, // Mixer configuration for channel 2
            { { 0, 0, 1, 0, 0, 0, 0, 0 } }, // Mixer configuration for channel 3
            { { 0, 0, 0, 1, 0, 0, 0, 0 } }, // Mixer configuration for channel 4
            { { 0, 0, 0, 0, 1, 0, 0, 0 } }, // Mixer configuration for channel 5
            { { 0, 0, 0, 0, 0, 1, 0, 0 } }, // Mixer configuration for channel 6
            { { 0, 0, 0, 0, 0, 0, 1, 0 } }, // Mixer configuration for channel 7
            { { 0, 0, 0, 0, 0, 0, 0, 1 } }  // Mixer configuration for channel 8
        }
    },
    .system_config = 
    {
        .adc_enabled = true,
        .mic_bias_enabled = true,
        .pll_enabled = true,
        .dynamic_power_mode = true,
        .shutdown_mode = TAA3040_SHUTDOWN_DREG_MODE_WAIT,
        .advanced = 
        {
            .vref_qc_time = TAA3040_VREF_QC_3500US,
            .input_qc_time = TAA3040_INPUT_QC_2500US,
            .fixed_i2c_address = false,
            .pdm_clock = TAA3040_PDM_CLOCK_3072KHZ,
            .dynamic_mode_channels = TAA3040_DYNAMIC_MODE_CHANNELS_1_2,
            .dreg_shutdown_time = TAA3040_DREG_SHUTDOWN_TIME_30MS
        }
    }
};