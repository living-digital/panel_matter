# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/david/components/bootloader/subproject"
  "/home/david/esp/panel_matter/build/bootloader"
  "/home/david/esp/panel_matter/build/bootloader-prefix"
  "/home/david/esp/panel_matter/build/bootloader-prefix/tmp"
  "/home/david/esp/panel_matter/build/bootloader-prefix/src/bootloader-stamp"
  "/home/david/esp/panel_matter/build/bootloader-prefix/src"
  "/home/david/esp/panel_matter/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/david/esp/panel_matter/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/david/esp/panel_matter/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
