#ifndef I2C_KICKER_H
#define I2C_KICKER_H

#include <stdint.h>
#include "esp_err.h"
#include "driver/i2c_master.h"

#include "kicker_i2c_defs.h"
#include "i2c_driver.h"

#ifdef __cplusplus
extern "C" {
#endif


#define KICKER_I2C_ADDRESS 0x27

bool kicker_init(i2c_driver_t *i2c);


esp_err_t kicker_get_version(uint8_t *version);
esp_err_t kicker_get_status(uint8_t *status);
esp_err_t kicker_get_voltage(uint8_t *voltage);
esp_err_t kicker_get_setpoint_voltage(uint8_t *setpoint_voltage);
esp_err_t kicker_get_kick_duty(uint8_t *kick_duty);
esp_err_t kicker_get_kick_duration(uint8_t *kick_duration); 
esp_err_t kicker_get_primary_voltage(uint8_t *primary_voltage);
esp_err_t kicker_get_secondary_voltage(uint8_t *secondary_voltage);

esp_err_t kicker_set_setpoint_voltage(uint8_t setpoint_voltage);
esp_err_t kicker_set_kick_duty(uint8_t kick_duty);
esp_err_t kicker_set_kick_duration(uint8_t kick_duration);

esp_err_t kicker_reset_board(void);
esp_err_t kicker_enable_charge(bool enable);
esp_err_t kicker_start_kick(void);
esp_err_t kicker_enable_bleeder(bool enable);
esp_err_t kicker_reset_board(void);
esp_err_t kicker_set_setpoint_voltage(uint8_t setpoint_voltage);


#ifdef __cplusplus
}
#endif

#endif