idf_component_register(
    SRCS
        "lv_port_disp.c"
        "lv_port_indev.c"
    INCLUDE_DIRS
	"include"
    PRIV_REQUIRES
        bsp
        main
        lvgl
        )
#target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/liblv_port.a")
