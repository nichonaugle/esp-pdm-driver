#ifndef ESP_PDM_DRIVER_H
#define ESP_PDM_DRIVER_H

#include "esp_err.h"
#include "driver/i2s.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize an I2S channel in PDM RX mode
 *
 * @param pdm_data_gpio GPIO number for PDM data input
 * @param pdm_clock_gpio GPIO number for PDM clock input
 * @param sample_rate Sample rate for the PDM data
 *
 * @return i2s_chan_handle_t Handle to the I2S channel
 */
i2s_chan_handle_t pdm_i2s_init(gpio_num_t pdm_data_gpio, gpio_num_t pdm_clock_gpio, uint16_t sample_rate);

#ifdef __cplusplus
}
#endif

#endif // ESP_PDM_DRIVER_H