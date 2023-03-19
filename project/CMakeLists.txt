add_library(${CMAKE_PROJECT_NAME}
    ./project.cpp)

get_target_property(bsp_include ${BOARD} INCLUDE_DIRECTORIES)
get_target_property(bsp_compile_options ${BOARD} COMPILE_OPTIONS)
get_target_property(bsp_definitions ${BOARD} COMPILE_DEFINITIONS)
get_target_property(drivers_include drivers INCLUDE_DIRECTORIES)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    hal
    drivers
    utils)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ${bsp_definitions})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${bsp_compile_options})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${bsp_include}
    ${drivers_include}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/launcher
    ${CMAKE_SOURCE_DIR}/bsp)
