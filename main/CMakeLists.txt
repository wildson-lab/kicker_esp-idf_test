idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES i2c_driver i2c_kicker
)
