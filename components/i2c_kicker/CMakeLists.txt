idf_component_register(
    SRCS "i2c_kicker.c"
    INCLUDE_DIRS "include"
    REQUIRES i2c_driver
)