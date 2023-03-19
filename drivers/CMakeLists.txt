add_library(drivers
    ./dummy_driver/dummy.cpp)

get_target_property(bsp_include ${BOARD} INCLUDE_DIRECTORIES)
get_target_property(bsp_compile_options ${BOARD} COMPILE_OPTIONS)
get_target_property(bsp_definitions ${BOARD} COMPILE_DEFINITIONS)

target_link_libraries(drivers PUBLIC utils)
target_compile_definitions(drivers PUBLIC ${bsp_definitions})
target_compile_options(drivers PUBLIC ${bsp_compile_options})
target_include_directories(drivers PUBLIC
    ${bsp_include}
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy_driver
    ${CMAKE_SOURCE_DIR}/bsp)
