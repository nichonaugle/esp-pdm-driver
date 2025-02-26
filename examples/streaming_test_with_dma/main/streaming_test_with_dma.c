#include <stdio.h>
#include "esp_pdm_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s_pdm.h"
#include "driver/gpio.h"
#include "esp_heap_caps.h"
#include "esp_err.h"
#include "esp_log.h"

#define SAMPLE_RATE         16000           // Sample rate for a MEMS microphone
#define DMA_BUF_LEN         2048            // Buffer length in 16-bit words. Seconds of audio = DMA_BUF_LEN / SAMPLE_RATE
#define PDM_DATA_GPIO       GPIO_NUM_20     // Need the actual PDM data input GPIO pin
#define PDM_CLOCK_GPIO      GPIO_NUM_19     // Need the actual PDM data input GPIO pin

const char *TAG = "PDM_I2S_DMA_STREAMING";

DMA_ATTR static int16_t audio_buffer[DMA_BUF_LEN];
static const size_t audio_buffer_size = DMA_BUF_LEN * sizeof(int16_t);

void app_main(void) {
    ESP_LOGI(TAG, "Initializing I2S in PDM mode...");

    /* Initialize PDM I2S Microphone */
    i2s_chan_handle_t rx_pdm_chan = pdm_i2s_init(PDM_DATA_GPIO, PDM_CLOCK_GPIO, SAMPLE_RATE);
    size_t rx_bytes = 0;

    /* Read Microphone in increments. NOT REAL TIME, JUST TESTS FUCNTIONALITY */
    while (1) {
        if (i2s_channel_read(rx_pdm_chan, audio_buffer, audio_buffer_size, &rx_bytes, 1000) == ESP_OK) {
            ESP_LOGI(TAG, "Read Task: i2s read %d bytes\n-----------------------------------\n", rx_bytes);
            printf("[");
            for (int i = 0; i < (rx_bytes / sizeof(int16_t) - 1); i++) {
                printf("%d, ", audio_buffer[i]);
            }
            printf("%d]\n", audio_buffer[rx_bytes / sizeof(int16_t) - 1]);
        } else {
            ESP_LOGI(TAG, "Read Task: i2s read failed\n");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    /* Clean up buffer */
    free(audio_buffer);
}
