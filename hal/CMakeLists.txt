add_library(hal 
    ./gpio.cpp)

get_target_property(bsp_include ${BOARD} INCLUDE_DIRECTORIES)
get_target_property(bsp_compile_options ${BOARD} COMPILE_OPTIONS)
get_target_property(bsp_definitions ${BOARD} COMPILE_DEFINITIONS)

target_compile_definitions(hal PUBLIC ${bsp_definitions})
target_compile_options(hal PUBLIC ${bsp_compile_options})
target_include_directories(hal PUBLIC
    ${bsp_include}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/bsp)
