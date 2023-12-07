#include <stdio.h>
#include "PCA9548A.h"

static const char *TAG = "PCA9548A";


/**
 * @brief initialize PCA9548A
 * 
 * @param pca struct with PCA9548A parameters
*/
void PCA9548A_init(PCA9548A_t pca)
{
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = (1 << pca.reset),
        .pull_up_en = 0,
        .pull_down_en = 0
    };
    gpio_config(&io_conf);
    gpio_set_level(pca.reset, 1);
}


/**
 * @brief select channel on PCA9548A
 * 
 * @param pca struct with PCA9548A parameters
 * @param channel channel to select (0 -7)
*/
void PCA9548A_select_channel(PCA9548A_t pca, uint8_t channel)
{
    if (channel > 7)
    {
        ESP_LOGE(TAG, "channel out of range!");
        return;
    }

    channel = 1 << channel;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (pca.i2c_address << 1) | I2C_MASTER_WRITE, ACK_EN);
    i2c_master_write_byte(cmd, channel, ACK_EN);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(pca.i2c_port, cmd, PCA9548A_TIMEOUT);
    i2c_cmd_link_delete(cmd);
}


/**
 * @brief reset PCA9548A
 * 
 * @param pca struct with PCA9548A parameters
*/
void PCA9548A_reset(PCA9548A_t pca)
{
    gpio_set_level(pca.reset, 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(pca.reset, 1);
}
