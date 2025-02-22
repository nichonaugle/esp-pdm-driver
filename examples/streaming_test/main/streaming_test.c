#include <stdio.h>
#include "esp_pdm_driver.h"

// I2S configuration definitions
#define I2S_NUM             I2S_NUM_0
#define SAMPLE_RATE         16000           // Sample rate for a MEMS microphone
#define DMA_BUF_COUNT       8
#define DMA_BUF_LEN         64              // Adjust length as needed for the latency/throughput requirements
#define PDM_DATA_GPIO       GPIO_NUM_xx      // Need the actual PDM data input GPIO pin

const char *TAG = "PDM_I2S_STREAMING";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing I2S in PDM mode...");
    pdm_i2s_init();

    // Allocate a buffer for DMA transfers (in bytes)
    size_t buffer_size = DMA_BUF_LEN * sizeof(int16_t);
    int16_t *audio_buffer = (int16_t *)malloc(buffer_size);
    if (audio_buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate audio buffer");
        return;
    }

    // Main loop: continuously capture audio data from the PDM microphone
    while (1) {
        pdm_i2s_read_audio(audio_buffer, buffer_size);

        // Delay between reads (adjust as needed)
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // Clean up resources
    free(audio_buffer);
    pdm_i2s_deinit();
}