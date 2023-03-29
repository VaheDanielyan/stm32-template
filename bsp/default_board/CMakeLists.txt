set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F407xx)
set(MCU_MODEL_FULL STM32F407VE)
set(MCU_ADDRESS_OFFSET 0x8000000)
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f407xx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F407VETx_FLASH.ld)

option(DUMP_ASM "Create full assembly of final executable" OFF)

set(EXECUTABLE ${BOARD})
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME}-${BOARD}-${CMAKE_BUILD_TYPE})

set(STM32CUBEMX_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include)

set(STM32CUBEMX_SOURCES
    ./Src/main.c
    ./Src/stm32f4xx_hal_msp.c
    ./Src/stm32f4xx_it.c
    ./Src/system_stm32f4xx.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c)

add_executable(${EXECUTABLE} ${STARTUP_SCRIPT} ${STM32CUBEMX_SOURCES})

target_include_directories(${EXECUTABLE} PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp) 

target_compile_options(${EXECUTABLE} PRIVATE
        ${CPU_PARAMETERS}
        -Wall
        -Wformat=2 
        -Wformat-truncation
        -Wundef
        -fno-common
        -Wno-unused-parameter
        $<$<COMPILE_LANGUAGE:CXX>:
            -Wno-conversion # STM libraries!
            -Wno-volatile
            -Wsuggest-override>
        $<$<CONFIG:Debug>:-O0 -g3 -ggdb>
        $<$<CONFIG:Release>:-Os -g0>)

target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL}
    ${MCU_FAMILY}
    USE_HAL_DRIVER)

target_link_libraries(${EXECUTABLE} PUBLIC 
    ${CMAKE_PROJECT_NAME})
target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -u_printf_float
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

set_target_properties(${EXECUTABLE} PROPERTIES OUTPUT_NAME ${EXECUTABLE_NAME})
message(${EXECUTABLE_NAME})

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE_NAME}.bin)

# Jlink upload script generation
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/jflash
    COMMAND echo device ${MCU_MODEL_FULL} > jflash
    COMMAND echo si 1 >> jflash
    COMMAND echo speed 4000 >> jflash
    COMMAND echo loadbin ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_NAME}.bin >> jflash
    COMMAND echo h >> jflash
    COMMAND echo r >> jflash
    COMMAND echo g >> jflash
    COMMAND echo sleep 1000 >> jflash
    COMMAND echo qc >> jflash)

# STlink upload script generation
set(STLINK_CMD st-flash write ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_NAME}.bin ${MCU_ADDRESS_OFFSET})
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/stlink.sh
    COMMAND echo echo ${STLINK_CMD} >> stlink.sh
    COMMAND echo  ${STLINK_CMD} >> stlink.sh)

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)

endif()
