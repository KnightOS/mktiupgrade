cmake_minimum_required(VERSION 2.8.5)

project(mktiupgrade C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Werror")

if (NOT DEFINED CMAKE_BUILD_TYPE)                                                                              
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type (Debug or Release)" FORCE)                           
endif() 

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

install(TARGETS mktiupgrade DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_CUSTOM_TARGET(man ALL)

ADD_CUSTOM_COMMAND(
  TARGET man
  COMMAND a2x --no-xmllint --doctype manpage --format manpage ${CMAKE_CURRENT_SOURCE_DIR}/mktiupgrade.1.txt -D ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/mktiupgrade.1
)

INSTALL(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/mktiupgrade.1
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/man/man1
)
