
set(TARGET_NAME mcp2515_driver)
add_library(${TARGET_NAME}
    mcp2515.c
    )
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/
    )
target_link_libraries(${TARGET_NAME} PRIVATE
    pico_stdlib
    hardware_spi
    )

