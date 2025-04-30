idf_component_register(
    INCLUDE_DIRS
        "include"
    REQUIRES
        bsp
        log
        )
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/liblcd_touch.a")
