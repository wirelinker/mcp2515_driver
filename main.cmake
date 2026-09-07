
set(TARGET_NAME mcp2515_main)
add_executable(${TARGET_NAME}
    main.c
    )

add_subdirectory(mcp2515)

target_link_libraries(${TARGET_NAME} PRIVATE
    pico_stdlib
    mcp2515_driver
    )

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/mcp2515
    )

pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 1)
pico_add_extra_outputs(${TARGET_NAME})
