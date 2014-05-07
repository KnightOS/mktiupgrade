cmake_minimum_required(VERSION 2.8.5)
project(mktiupgrade)
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
add_definitions("-Wall")

set(LIBS ${LIBS})

include_directories(
    upgrade/
    crypto/
    crypto/libtom/
)

FILE(GLOB TomSources crypto/libtom/*.c)

add_executable(mktiupgrade
    main.c
    upgrade/devices.c
    upgrade/upgrade.c
    upgrade/intelhex.c
    crypto/ticrypto.c
    crypto/md5.c
    ${TomSources}
)

target_link_libraries(mktiupgrade ${LIBS})

install(PROGRAMS bin/mktiupgrade
    DESTINATION bin)

set(CMAKE_BUILD_TYPE Release)

ADD_CUSTOM_TARGET(man ALL)

ADD_CUSTOM_COMMAND(
  TARGET man
  SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/mktiupgrade.1.txt
  COMMAND a2x --doctype manpage --format manpage ${CMAKE_CURRENT_SOURCE_DIR}/mktiupgrade.1.txt 
  OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/mktiupgrade.1
)

ADD_CUSTOM_COMMAND(
  TARGET man
  SOURCE man
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mktiupgrade.1
)

INSTALL(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/mktiupgrade.1
    DESTINATION ${CMAKE_INSTALL_PREFIX}/man/man1
)
