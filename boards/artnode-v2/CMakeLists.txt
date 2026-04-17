
add_executable(artnode_v2)

target_link_libraries(artnode_v2 PRIVATE
    logger
    stm32g474
)

target_sources(artnode_v2 PRIVATE
    src/main.cpp
)