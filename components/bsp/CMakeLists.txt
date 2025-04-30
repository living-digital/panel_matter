idf_component_register(
    INCLUDE_DIRS
        "include"
    REQUIRES 
    driver
    esp_common 
    log
    i2c_bsp
    lcd_touch
    esp_lcd
    lcd_bsp
    fatfs
    )
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/libbsp.a")

