#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#define I2C_MASTER_SDA_IO       GPIO_NUM_21
#define I2C_MASTER_SCL_IO       GPIO_NUM_22

#define I2C_MASTER_NUM          I2C_NUM_0
#define I2C_MASTER_FREQ_HZ      100000

#define I2C_SLAVE_ADDR          0x27

#define I2C_MASTER_TIMEOUT_MS   50

#endif