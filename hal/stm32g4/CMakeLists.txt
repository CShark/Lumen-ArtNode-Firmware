# Base lib
add_library(stm32g4 INTERFACE)
target_link_libraries(stm32g4 INTERFACE
    cmsis
    logger
)
target_include_directories(stm32g4 INTERFACE
    inc
)
target_sources(stm32g4 INTERFACE
    src/syscalls.c
    src/system_stm32g4xx.c
    src/hal/systick.cpp
)

# STM32G474
add_library(stm32g474 INTERFACE)
target_link_libraries(stm32g474 INTERFACE
    stm32g4
)
target_include_directories(stm32g474 INTERFACE
    stm32g474/inc
)
target_sources(stm32g474 INTERFACE
    stm32g474/src/startup_stm32g474xx.s
)
target_compile_definitions(stm32g474 INTERFACE
    STM32G474xx
)
target_link_options(stm32g474 INTERFACE
    -T "${CMAKE_CURRENT_SOURCE_DIR}/stm32g474/STM32G474XX_FLASH.ld"
)