/*
 * Copyright (c) 2026 wirelinker
 * SPDX-License-Identifier: MIT License
 */

#ifndef MCP2515_RP2040_STUB_H
#define MCP2515_RP2040_STUB_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define MCP2515_SPI_INSTANCE (spi_default)

#ifdef PICO_DEFAULT_SPI_CSN_PIN
#define MCP2515_SPI_CS_PIN (PICO_DEFAULT_SPI_CSN_PIN)
#elif
#define MCP2515_SPI_CS_PIN
#endif
#define SPI_CS_SELECT()   (gpio_put(MCP2515_SPI_CS_PIN, 0))
#define SPI_CS_UNSELECT() (gpio_put(MCP2515_SPI_CS_PIN, 1))

#define MCP2515_SPI_SCK_PIN  (PICO_DEFAULT_SPI_SCK_PIN)
#define MCP2515_SPI_MOSI_PIN (PICO_DEFAULT_SPI_TX_PIN)
#define MCP2515_SPI_MISO_PIN (PICO_DEFAULT_SPI_RX_PIN)


#define SPI_INIT() ( mcp2515_spi_init() )
void mcp2515_spi_init(void)
{
    unsigned int actual_spi_baud = 0;

    printf("MCP2515 driver start\n");

    /* use 10 MHz spi clock */
    actual_spi_baud = spi_init(MCP2515_SPI_INSTANCE, 10 * 1000 * 1000);
    printf("MCP2515 spi baud = %d\n", actual_spi_baud);

    /* set spi pin function*/
    gpio_set_function(MCP2515_SPI_SCK_PIN,  GPIO_FUNC_SPI);
    gpio_set_function(MCP2515_SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(MCP2515_SPI_MISO_PIN, GPIO_FUNC_SPI);
    gpio_init(MCP2515_SPI_CS_PIN);
    gpio_set_dir(MCP2515_SPI_CS_PIN, GPIO_OUT);
    gpio_put(MCP2515_SPI_CS_PIN, 1);

    /* set spi format */
    /* mode 0,0 or mode 1,1, 8-bits, MSb first */
    spi_set_format(MCP2515_SPI_INSTANCE, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
}

#define SPI_WRITE(ptr, len) ( spi_write_blocking(MCP2515_SPI_INSTANCE, (ptr), (len)) )
#define SPI_READ(ptr, len) ( spi_read_blocking(MCP2515_SPI_INSTANCE, 0x00, (ptr), (len)) )

#endif /* MCP2515_RP2040_STUB_H */
