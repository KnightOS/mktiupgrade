cmake_minimum_required(VERSION 2.8.5)
project(mktiupgrade)
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
add_definitions("-Wall")
find_package(GMP REQUIRED)
find_package(OpenSSL REQUIRED)

set(LIBS ${LIBS} ${OpenSSL_LIBRARIES} ${GMP_LIBRARIES})

include_directories(
    ${OpenSSL_INCLUDE_DIRS}
    ${GMP_INCLUDE_DIRS}
    upgrade/
    crypto/
)

add_executable(mktiupgrade
    main.c
    upgrade/devices.c
    upgrade/upgrade.c
    crypto/ticrypto.c
)

target_link_libraries(mktiupgrade ${LIBS} ssl crypto)

install(PROGRAMS bin/mktiupgrade
    DESTINATION bin)

set(CMAKE_BUILD_TYPE Release)
