# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ../../components)

# Forzar uso de LWIP en Matter (¡debe estar antes de 'project()'!)
add_compile_definitions(CHIP_SYSTEM_CONFIG_USE_LWIP=1)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lvgl_demo)
