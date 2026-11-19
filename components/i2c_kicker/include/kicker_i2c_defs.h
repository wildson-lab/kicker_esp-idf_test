/*
 * Mapa de Registradores do Kicker
 * Registradores de escrita e/ou leitura
 * */
#define KICKER_REG_VERSION         0x00
#define KICKER_REG_BOARD_STATUS    0x01
#define KICKER_REG_FB_DUTY         0X02
#define KICKER_REG_VSEC            0x03
#define KICKER_REG_VSEC_SET        0x04
#define KICKER_REG_KICK_DURATION   0x05
#define KICKER_REG_KICK_DUTY       0x06
#define KICKER_REG_VPRI_1          0x07
#define KICKER_REG_VPRI_2          0x08

/*
 * Registradores de comando
 * */
#define KICKER_REG_BOARD_RESET     0xA0
#define KICKER_REG_CHARGE_ENABLE   0xA1
#define KICKER_REG_KICK_START      0xA2
#define KICKER_REG_BLEEDER_ENABLE  0xA3

/*
 * Mascaras de status da placa
 * */
#define KICKER_BOARD_STATUS_CHARGE               (1U << 0)
#define KICKER_BOARD_STATUS_KICK                 (1U << 1)
#define KICKER_BOARD_STATUS_BLEEDER              (1U << 2)
#define KICKER_BOARD_STATUS_FAULT                (1U << 3)
#define KICKER_BOARD_STATUS_DONE                 (1U << 4)
#define KICKER_BOARD_STATUS_OV_TRIP              (1U << 5)
#define KICKER_BOARD_STATUS_I2C_LAST_REG_ERROR   (1U << 6)
#define KICKER_BOARD_STATUS_I2C_LAST_VALUE_ERROR (1U << 7)

/*
 * Comandos de start e stop
 * */
#define KICKER_COMMAND_STOP  0x00
#define KICKER_COMMAND_START 0x01



#define KICKER_VSEC_MAX 200U
#define KICKER_DUTY_MAX 100U
#define KICKER_DURATION_MAX 255U

