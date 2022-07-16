cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "toolchain/arm-none-eabi.cmake")

project(sneak100-rtos)

enable_language(C ASM)

set(TARGET ${CMAKE_PROJECT_NAME}.elf)

add_executable(${TARGET}
	"third-party/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c"
	"third-party/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f405xx.s"

	"third-party/FreeRTOS-Kernel/tasks.c"
	"third-party/FreeRTOS-Kernel/queue.c"
	"third-party/FreeRTOS-Kernel/list.c"
	"third-party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c"
	"third-party/FreeRTOS-Kernel/portable/MemMang/heap_4.c"
	"third-party/FreeRTOS-Plus-CLI/FreeRTOS_CLI.c"

	"app/core/src/main.c"
	"app/core/src/adc.c"
	"app/core/src/motors.c"
	"app/core/src/sensors.c"
	"app/cli/src/uart2.c"
	"app/cli/src/uart3.c"
	"app/cli/src/cli_apps.c"
	"app/cli/src/cli.c"
)

target_compile_definitions(${TARGET} PRIVATE
	STM32F405xx
	ARM_MATH_CM4
)

target_include_directories(${TARGET} PRIVATE
	"third-party/CMSIS/Include"
	"third-party/CMSIS/Device/ST/STM32F4xx/Include"
	"third-party/CMSIS/DSP/Include"

	"third-party/FreeRTOS-Kernel/include"
	"third-party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F"
	"third-party/FreeRTOS-Plus-CLI"
	
	"app/core/inc"
	"app/cli/inc"
)

target_compile_options(${TARGET} PRIVATE
	-O0 -g
	
	-Wall
	-Wextra
	-Wpedantic
	-Wdouble-promotion
	
	-mcpu=cortex-m4
	-mfloat-abi=hard
	-mfpu=fpv4-sp-d16

	-specs=nosys.specs
)

target_link_options(${TARGET} PRIVATE
	-T ${CMAKE_SOURCE_DIR}/linker/STM32F405RGTX_FLASH.ld

	-mthumb
	-mcpu=cortex-m4
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard

	-specs=nosys.specs
)

target_link_libraries(${TARGET} 
	m
	${CMAKE_SOURCE_DIR}/third-party/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a
)

add_custom_command(
	TARGET ${TARGET} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${CMAKE_PROJECT_NAME}.bin
	COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${CMAKE_PROJECT_NAME}.hex
	COMMAND ${CMAKE_SIZE} ${TARGET}
)
