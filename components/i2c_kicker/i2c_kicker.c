#include "i2c_kicker.h"
#include <stddef.h>

static i2c_driver_t *i2c_kicker_driver = NULL;

bool kicker_init(i2c_driver_t *i2c)
{
    if (i2c == NULL || i2c->dev == NULL)
        return false;

    i2c_kicker_driver = i2c;

    return true;
}

bool kicker_is_initialized()
{
    return i2c_kicker_driver != NULL;
}

esp_err_t kicker_get_version(uint8_t *version)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_VERSION,
        version
    );
}


esp_err_t kicker_get_status(uint8_t *status)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_BOARD_STATUS,
        status
    );
}

esp_err_t kicker_get_voltage(uint8_t *voltage)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_VSEC,
        voltage
    );
}

esp_err_t kicker_get_setpoint_voltage(uint8_t *setpoint_voltage)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_VSEC_SET,
        setpoint_voltage
    );
}

esp_err_t kicker_get_kick_duty(uint8_t *kick_duty)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_KICK_DUTY,
        kick_duty
    );
}

esp_err_t kicker_get_kick_duration(uint8_t *kick_duration)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_KICK_DURATION,
        kick_duration
    );
}


esp_err_t kicker_get_primary_voltage(uint8_t *primary_voltage)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_VPRI_1,
        primary_voltage
    );
}

esp_err_t kicker_get_secondary_voltage(uint8_t *secondary_voltage)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_read(
        i2c_kicker_driver,
        KICKER_REG_VPRI_2,
        secondary_voltage
    );
}


esp_err_t kicker_set_setpoint_voltage(uint8_t setpoint_voltage)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    if (setpoint_voltage > KICKER_VSEC_MAX)
        return ESP_ERR_INVALID_ARG;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_VSEC_SET,
        setpoint_voltage
    );
}


esp_err_t kicker_set_kick_duty(uint8_t kick_duty)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    if (kick_duty > KICKER_DUTY_MAX)
        return ESP_ERR_INVALID_ARG;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_KICK_DUTY,
        kick_duty
    );
}

esp_err_t kicker_set_kick_duration(uint8_t kick_duration)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_KICK_DURATION,
        kick_duration
    );
}



esp_err_t kicker_reset_board(void)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_BOARD_RESET,
        KICKER_COMMAND_START
    );
}

esp_err_t kicker_enable_charge(bool enable)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    uint8_t command = enable ? KICKER_COMMAND_START : KICKER_COMMAND_STOP;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_CHARGE_ENABLE,
        command
    );
}

esp_err_t kicker_start_kick()
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_KICK_START,
        KICKER_COMMAND_START
    );
}

esp_err_t kicker_enable_bleeder(bool enable)
{
    if (kicker_is_initialized() == false)
        return ESP_ERR_INVALID_STATE;

    uint8_t command = enable ? KICKER_COMMAND_START : KICKER_COMMAND_STOP;

    return i2c_driver_write(
        i2c_kicker_driver,
        KICKER_REG_BLEEDER_ENABLE,
        command
    );
}