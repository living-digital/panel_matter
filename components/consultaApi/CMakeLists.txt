idf_component_register(
    SRCS
        "consultaApi.c"
    INCLUDE_DIRS 
        "."
    PRIV_REQUIRES
	esp_http_client
)
