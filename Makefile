.PHONY: all build cmake clean

BUILD_DIR := build
BUILD_TYPE ?= Debug
MAKEFILE_DIR := $(shell pwd)
BOARD=default_board
TOOLCHAIN_INCLUDE_PATH=${HOME}/.local/arm-none-eabi/include

all: build

${BUILD_DIR}/Makefile:
	cmake \
		-B${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=${MAKEFILE_DIR}/toolchain/gcc-arm-none-eabi.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DDUMP_ASM=OFF \
		-DBOARD=${BOARD} \
		-DTOOLCHAIN_INCLUDE_PATH=${TOOLCHAIN_INCLUDE_PATH}

cmake: ${BUILD_DIR}/Makefile

build: cmake
	$(MAKE) -C ${BUILD_DIR} --no-print-directory

clean:
	rm -rf $(BUILD_DIR)

st_flash: checksum
	st-flash write ${BUILD_DIR}/bsp/${BOARD}/${BOARD}.bin 0x8000000

jflash: $(BUILD_DIR)/jflash checksum 
	JLinkExe -commanderscript ${MAKEFILE_DIR}/bsp/${BOARD}/jflash

checksum: 
	md5sum ${BUILD_DIR}/bsp/${BOARD}/${BOARD}.bin
