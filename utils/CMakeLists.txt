add_library(utils
    crc.c
    swo.cpp)

get_target_property(bsp_include ${BOARD} INCLUDE_DIRECTORIES)
get_target_property(bsp_compile_options ${BOARD} COMPILE_OPTIONS)
get_target_property(bsp_definitions ${BOARD} COMPILE_DEFINITIONS)

target_compile_definitions(utils PUBLIC ${bsp_definitions})
target_compile_options(utils PUBLIC ${bsp_compile_options})
target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}
    ${bsp_include}
    ${CMAKE_SOURCE_DIR}/bsp)
