#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t dev;
} i2c_driver_t;

esp_err_t i2c_driver_init(
    i2c_driver_t *i2c,
    int sda,
    int scl,
    uint8_t address,
    uint32_t frequency
);

esp_err_t i2c_driver_write(
    i2c_driver_t *i2c,
    uint8_t reg,
    uint8_t value
);

esp_err_t i2c_driver_read(
    i2c_driver_t *i2c,
    uint8_t reg,
    uint8_t *value
);

esp_err_t i2c_driver_deinit(
    i2c_driver_t *i2c
);

#ifdef __cplusplus
}
#endif

#endif