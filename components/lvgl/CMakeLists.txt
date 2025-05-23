# CMakeLists.txt
#
# Copyright 2021 Espressif Systems (Shanghai) Co. Ltd.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#              http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

# Search for src files
file(GLOB_RECURSE LVGL_SOURCES
    lvgl/src/*.c
    lvgl/examples/*.c
    lvgl/demos/*.c)

# Resister components
idf_component_register(
    SRCS
        ${LVGL_SOURCES}
        ${LV_PORT_SOURCES}
    INCLUDE_DIRS
        "."
        "include"
        "lvgl/src"
        "lvgl/demos"
        "../lv_port"
    REQUIRES
        bsp
        main)

# Some of warinings from LVGL. Block them.
target_compile_options(${COMPONENT_LIB} PRIVATE -w)

# We're using Kconfig, will will add `CONFIG_` prifix to MACRO.
# This macro will use a wrapper macro like `#define LV_USE_XXX CONFIG_LV_USE_XXX`
# But since `lv_conf_internal.h` will add `_LV_KCONFIG_PRESENT` if 
#   `CONFIG_LV_COLOR_DEPTH` is defined. So this might not required.
# target_compile_definitions(${COMPONENT_LIB} PUBLIC "-D_LV_KCONFIG_PRESENT")

# Use simple include
target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_CONF_INCLUDE_SIMPLE")
target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_DEMO_CONF_INCLUDE_SIMPLE")

# Workaround for file system support
target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DCONFIG_LV_USE_FS_STDIO='S'")

if (CONFIG_LV_MEM_CUSTOM)
    if (CONFIG_LV_MEM_CUSTOM_ALLOC)
        target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_MEM_CUSTOM_ALLOC=${CONFIG_LV_MEM_CUSTOM_ALLOC}")
    endif()

    if (CONFIG_LV_MEM_CUSTOM_FREE)
        target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_MEM_CUSTOM_FREE=${CONFIG_LV_MEM_CUSTOM_FREE}")
    endif()
endif()

if (CONFIG_LV_TICK_CUSTOM)
    if (CONFIG_LV_TICK_CUSTOM_SYS_TIME_EXPR)
        target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_TICK_CUSTOM_SYS_TIME_EXPR=${CONFIG_LV_TICK_CUSTOM_SYS_TIME_EXPR}")
    endif()
endif()

# This will make LVGL faster but use more RAM if enabled
if (CONFIG_LV_ATTRIBUTE_FAST_MEM_USE_IRAM)
    target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_ATTRIBUTE_FAST_MEM=IRAM_ATTR")
endif()
