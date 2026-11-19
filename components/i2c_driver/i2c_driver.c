#include "i2c_driver.h"
#include <stddef.h>

#define I2C_TIMEOUT_MS 50


esp_err_t i2c_driver_init(
    i2c_driver_t *i2c,
    int sda,
    int scl,
    uint8_t address,
    uint32_t frequency
)
{
    if (i2c == NULL ||
        address > 0x7F ||
        frequency == 0)
    {
        return ESP_ERR_INVALID_ARG;
    }

    if (i2c->bus != NULL || i2c->dev != NULL)
        return ESP_ERR_INVALID_STATE;

    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = sda,
        .scl_io_num = scl,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };

    esp_err_t err = i2c_new_master_bus(
        &bus_cfg,
        &i2c->bus
    );

    if (err != ESP_OK)
        return err;

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = address,
        .scl_speed_hz = frequency
    };

    err = i2c_master_bus_add_device(
        i2c->bus,
        &dev_cfg,
        &i2c->dev
    );

    if (err != ESP_OK) {
        i2c_del_master_bus(i2c->bus);
        i2c->bus = NULL;
        return err;
    }

    return ESP_OK;
}


esp_err_t i2c_driver_write(
    i2c_driver_t *i2c,
    uint8_t reg,
    uint8_t value
)
{
    if (i2c == NULL || i2c->dev == NULL)
        return ESP_ERR_INVALID_STATE;

    uint8_t buffer[2] = {
        reg,
        value
    };

    return i2c_master_transmit(
        i2c->dev,
        buffer,
        sizeof(buffer),
        I2C_TIMEOUT_MS
    );
}


esp_err_t i2c_driver_read(
    i2c_driver_t *i2c,
    uint8_t reg,
    uint8_t *value
)
{
    if (i2c == NULL || value == NULL)
        return ESP_ERR_INVALID_ARG;

    if (i2c->dev == NULL)
        return ESP_ERR_INVALID_STATE;

    uint8_t received = 0;

    esp_err_t err = i2c_master_transmit_receive(
        i2c->dev,
        &reg,
        1,
        &received,
        1,
        I2C_TIMEOUT_MS
    );

    if (err == ESP_OK)
        *value = received;

    return err;
}


esp_err_t i2c_driver_deinit(
    i2c_driver_t *i2c
)
{
    if (i2c == NULL)
        return ESP_ERR_INVALID_ARG;

    if (i2c->dev != NULL) {
        esp_err_t err = i2c_master_bus_rm_device(i2c->dev);

        if (err != ESP_OK)
            return err;

        i2c->dev = NULL;
    }

    if (i2c->bus != NULL) {
        esp_err_t err = i2c_del_master_bus(i2c->bus);

        if (err != ESP_OK)
            return err;

        i2c->bus = NULL;
    }

    return ESP_OK;
}