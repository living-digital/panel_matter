
idf_component_register(
                    INCLUDE_DIRS "." "include"
                    PRIV_REQUIRES esp_wifi esp_timer nvs_flash lwip esp_http_server driver
                    EMBED_FILES
                    "www/index_uvc.html.gz")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/libxfer_http.a")