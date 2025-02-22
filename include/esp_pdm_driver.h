#ifndef ESP_PDM_DRIVER_H
#define ESP_PDM_DRIVER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function to initialize the PDM I2S driver
esp_err_t pdm_i2s_init(void);

// Function to read audio data from the PDM I2S driver
esp_err_t pdm_i2s_read_audio(void *buffer, size_t size);

// Function to set the sample rate for the PDM I2S driver
esp_err_t pdm_i2s_set_sample_rate(int sample_rate);

// Function to deinitialize the PDM I2S driver
esp_err_t pdm_i2s_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // ESP_PDM_DRIVER_H