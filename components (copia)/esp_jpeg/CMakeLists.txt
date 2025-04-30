idf_component_register(
    SRCS "src/audio_malloc.c"
    INCLUDE_DIRS "include"
    REQUIRES
	esp_timer
    PRIV_REQUIRES
	esp_event
        driver
        usb_stream
        usb_cam
        espressif__button
        lvgl_wifi_connect
        esp_jpeg
        bsp
        main
	nvs_flash
	spi_flash
)
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/libs/${CONFIG_IDF_TARGET}/libesp_codec.a")
target_link_libraries(${COMPONENT_LIB} INTERFACE "-u audio_free -u audio_calloc_inner -u audio_calloc")
