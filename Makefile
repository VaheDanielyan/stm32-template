.PHONY: all build cmake clean

PROJECT_NAME=project
BUILD_DIR := build
MAKEFILE_DIR := $(shell pwd)
BOARD=default_board

CMAKE_GEN_MF_DIR_DEBUG=${BUILD_DIR}/${BOARD}_Debug
CMAKE_GEN_MF_DIR_RELEASE=${BUILD_DIR}/${BOARD}_Release

# stlink or jlink
FLASH_METHOD=jlink
STLINK_FLASH_ADDRESS_OFFSET=0x8000000

define CMAKE_FLAGS
-DCMAKE_TOOLCHAIN_FILE=${MAKEFILE_DIR}/toolchain/gcc-arm-none-eabi.cmake \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
-DDUMP_ASM=OFF \
-DBOARD=${BOARD}
endef

all: build

${CMAKE_GEN_MF_DIR_DEBUG}:
	cmake \
		-B${CMAKE_GEN_MF_DIR_DEBUG} \
		-DCMAKE_BUILD_TYPE=Debug \
		${CMAKE_FLAGS}

cmake_debug: ${CMAKE_GEN_MF_DIR_DEBUG}

${CMAKE_GEN_MF_DIR_RELEASE}:
	cmake \
		-B${CMAKE_GEN_MF_DIR_RELEASE} \
		-DCMAKE_BUILD_TYPE=Release \
		${CMAKE_FLAGS}

cmake_release: ${CMAKE_GEN_MF_DIR_RELEASE}

debug: cmake_debug
	$(MAKE) -C ${CMAKE_GEN_MF_DIR_DEBUG} --no-print-directory

release: cmake_release
	$(MAKE) -C ${CMAKE_GEN_MF_DIR_RELEASE} --no-print-directory

build: debug release cmake_debug cmake_release

clean:
	rm -rf $(BUILD_DIR)

# Flash scrips are generated by the bsp CmakeLists file
st_flash_debug:
	bash ${CMAKE_GEN_MF_DIR_DEBUG}/bsp/${BOARD}/stlink.sh

st_flash_release:
	bash ${CMAKE_GEN_MF_DIR_RELEASE}/bsp/${BOARD}/stlink.sh

jflash_debug:
	JLinkExe -commanderscript ${CMAKE_GEN_MF_DIR_DEBUG}/bsp/${BOARD}/jflash

jflash_release:
	JLinkExe -commanderscript ${CMAKE_GEN_MF_DIR_RELEASE}/bsp/${BOARD}/jflash

compile_commands:
	ln -sf ./build/Debug/compile_commands.json ${MAKEFILE_DIR}
