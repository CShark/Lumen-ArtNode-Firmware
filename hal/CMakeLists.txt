# ETL
include(FetchContent)
FetchContent_Declare(
    etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl
    GIT_TAG        20.45.0
)
FetchContent_MakeAvailable(etl)

# CMSIS
add_library(cmsis INTERFACE)
target_include_directories(cmsis INTERFACE
    cmsis
)

# RTT
add_library(rtt INTERFACE)
target_include_directories(rtt INTERFACE
    rtt/inc
)
target_sources(rtt INTERFACE
    rtt/src/segger_rtt.c
)

# Logger
add_library(logger INTERFACE)
target_link_libraries(logger INTERFACE
    rtt
    hal
)
target_include_directories(logger INTERFACE
    logger/inc
)
target_sources(logger INTERFACE
    logger/src/logger.cpp    
)
IF(DEFINED ENV{LOG_LEVEL})
    target_compile_definitions(logger INTERFACE
        LEVEL_$ENV{LOG_LEVEL}
    )
ENDIF()

# HAL
add_library(hal INTERFACE)
target_include_directories(hal INTERFACE
    hal-core/inc
)

# Supported chip families
add_subdirectory(stm32g4)