set(
     PRIVREQ 
     esp_timer
     )
idf_component_register(
                       INCLUDE_DIRS . jpeg-9a
                       REQUIRES driver ${REQ}
                       PRIV_REQUIRES ${PRIVREQ}
                       )
                       target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/libavi.a")