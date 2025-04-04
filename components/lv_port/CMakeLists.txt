idf_component_register(
    INCLUDE_DIRS
    "include"
    PRIV_REQUIRES
        bsp
        main
        lvgl
        )
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/liblv_port.a")
