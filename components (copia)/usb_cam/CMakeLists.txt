idf_component_register(
                    INCLUDE_DIRS "include"
                    REQUIRES 
                    driver
                    usb_stream
                    bsp
                    main
                    esp_jpeg
                    )
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/libusb_cam.a")