#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_err.h"

#include "i2c_configs.h"
#include "i2c_driver.h"
#include "i2c_kicker.h"

static const char *TAG = "MAIN";

static i2c_driver_t i2c_driver = {0};

void app_main(void)
{
    TAG = "KICKER_MAIN";

    esp_err_t err = i2c_driver_init(
        &i2c_driver,
        I2C_MASTER_SDA_IO,
        I2C_MASTER_SCL_IO,
        KICKER_I2C_ADDRESS,
        I2C_MASTER_FREQ_HZ
    );

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Erro inicializando I2C: %s",
                 esp_err_to_name(err));
        return;
    }

    ESP_LOGI(TAG, "I2C inicializado!");

    if (!kicker_init(&i2c_driver)) {
        ESP_LOGE(TAG, "Falha na inicializacao do kicker");
        return;
    }

    uint8_t status = 0;
    uint8_t voltage = 0;
    uint8_t setpoint_voltage = 0;

    while (1)
    {
        int command = getchar();

        if (command != EOF) {
            ESP_LOGI(TAG, "Comando recebido: %c", command);
        }

        switch (command) {
            case 'r':
                ESP_LOGI(TAG, "Comando de reset...");
                err = kicker_reset_board();
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de reset: %s",
                             esp_err_to_name(err));
                }
                break;
            case 's':
                err = kicker_get_status(&status);

                if (err == ESP_OK) {
                    ESP_LOGI(TAG, "Status: 0x%02X", status);
                } else {
                    ESP_LOGE(TAG, "Erro lendo status: %s",
                            esp_err_to_name(err));
                }    
                break;
            case 'v':
                    err = kicker_get_voltage(&voltage);
                    if (err == ESP_OK) {
                        ESP_LOGI(TAG, "Tensao: %u V", voltage);
                    } else {
                        ESP_LOGE(TAG, "Erro lendo tensao: %s",
                                esp_err_to_name(err));
                    }
                break;
            case 'V':
                    err = kicker_get_setpoint_voltage(&setpoint_voltage);
                    if (err == ESP_OK) {
                        ESP_LOGI(TAG, "Tensao de setpoint: %u V", setpoint_voltage);
                    } else {
                        ESP_LOGE(TAG, "Erro lendo tensao de setpoint: %s",
                                esp_err_to_name(err));
                    }
                break;
            case 'C':
                ESP_LOGI(TAG, "Comando de charge enable...");
                err = kicker_enable_charge(true);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de charge enable: %s",
                             esp_err_to_name(err));
                }
                break;
            case 'c':
                ESP_LOGI(TAG, "Comando de charge disable...");
                err = kicker_enable_charge(false);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de charge disable: %s",
                             esp_err_to_name(err));
                }
                break;
            case 'k':
                ESP_LOGI(TAG, "Comando de kick start...");
                err = kicker_start_kick();
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de kick start: %s",
                             esp_err_to_name(err));
                }
                break; 
                
            case 'B':
                ESP_LOGI(TAG, "Comando de bleeder enable...");
                err = kicker_enable_bleeder(true);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de bleeder enable: %s",
                             esp_err_to_name(err));
                }
                break;

            case 'b':
                ESP_LOGI(TAG, "Comando de bleeder disable...");
                err = kicker_enable_bleeder(false);
                if (err != ESP_OK) {    
                    ESP_LOGE(TAG, "Erro enviando comando de bleeder disable: %s",
                             esp_err_to_name(err));
                }
                break;

            case '1':
                ESP_LOGI(TAG, "Comando de setpoint voltage 50V...");
                err = kicker_set_setpoint_voltage(50);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de setpoint voltage: %s",
                             esp_err_to_name(err));
                }
                break;
            case '2':
                ESP_LOGI(TAG, "Comando de setpoint voltage 100V...");
                err = kicker_set_setpoint_voltage(100);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de setpoint voltage: %s",
                             esp_err_to_name(err));
                }
                break;

            case '3':
                ESP_LOGI(TAG, "Comando de setpoint voltage 150V...");
                err = kicker_set_setpoint_voltage(150);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de setpoint voltage: %s",
                             esp_err_to_name(err));
                }
                break;
            case '4':
                ESP_LOGI(TAG, "Comando de setpoint voltage 200V...");
                err = kicker_set_setpoint_voltage(200);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "Erro enviando comando de setpoint voltage: %s",
                             esp_err_to_name(err));
                }
                break;

            default:
                // ESP_LOGW(TAG, "Comando desconhecido: %c", command);
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(100));

    }
}