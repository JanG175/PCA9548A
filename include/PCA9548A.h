#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"

#define PCA9548A_ADDRESS0 0x70
#define PCA9548A_ADDRESS1 0x71
#define PCA9548A_ADDRESS2 0x72
#define PCA9548A_ADDRESS3 0x73
#define PCA9548A_ADDRESS4 0x74
#define PCA9548A_ADDRESS5 0x75
#define PCA9548A_ADDRESS6 0x76
#define PCA9548A_ADDRESS7 0x77

#define ACK_EN            true
#define PCA9548A_TIMEOUT  (100 / portTICK_PERIOD_MS)

typedef struct PCA9548A_t
{
    i2c_port_t i2c_port;
    uint8_t i2c_address;
    gpio_num_t reset;
} PCA9548A_t;


void PCA9548A_init(PCA9548A_t pca);

void PCA9548A_select_channel(PCA9548A_t pca, uint8_t channel);

void PCA9548A_reset(PCA9548A_t pca);