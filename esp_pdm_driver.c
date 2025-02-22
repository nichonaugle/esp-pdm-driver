#include <stdio.h>
#include "esp_pdm_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/i2s_pdm.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "PDM_I2S_EXAMPLE";

esp_err_t pdm_i2s_init(void) {
    // I2S configuration structure
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM,  // Master, receive, and PDM mode
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,            // Most MEMS microphones provide mono output
        .communication_format = I2S_COMM_FORMAT_STAND_MSB,
        .dma_buf_count = DMA_BUF_COUNT,
        .dma_buf_len = DMA_BUF_LEN,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                // Adjust interrupt level as needed
    };

    esp_err_t err = i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed installing I2S driver: %d", err);
        return;
    }

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_PIN_NO_CHANGE,       // Not used in PDM configurations
        .ws_io_num = I2S_PIN_NO_CHANGE,        // Not used or may be used as a clock if required
        .data_out_num = I2S_PIN_NO_CHANGE,     // Not used in RX mode
        .data_in_num = PDM_DATA_GPIO           // PDM data input pin – update as needed
   };

    err = i2s_set_pin(I2S_NUM, &pin_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed setting I2S pins: %d", err);
    }

    return err;
}

esp_err_t pdm_i2s_read_audio(void *buffer, size_t size) {
    size_t bytes_read = 0;
    esp_err_t err = i2s_read(I2S_NUM, buffer, size, &bytes_read, portMAX_DELAY);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error reading I2S data: %d", err);
    } else {
        ESP_LOGI(TAG, "Read %d bytes from I2S", bytes_read);
    }
    return err;
}

esp_err_t pdm_i2s_set_sample_rate(int sample_rate)
{
    esp_err_t err = i2s_set_clk(I2S_NUM, sample_rate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_FMT_ONLY_LEFT);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed setting I2S clock: %d", err);
    }
    returne err;
}

esp_err_t pdm_i2s_deinit(void)
{
    esp_err_t err = i2s_driver_uninstall(I2S_NUM);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed uninstalling I2S driver: %d", err);
    }
    return err;
}
