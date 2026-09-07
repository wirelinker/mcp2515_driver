/*
 * Copyright (c) 2026 wirelinker
 * SPDX-License-Identifier: MIT License
 */

#ifndef MCP2515_SPI_COMMAND_H
#define MCP2515_SPI_COMMAND_H

/*
 * MCP2515 spi instruction set
 */
#define MCP_SPI_CMD_RESET 0b11000000
#define MCP_SPI_CMD_READ  0b00000011 /* read register */
#define MCP_SPI_CMD_WRITE 0b00000010 /* write register */
#define MCP_SPI_CMD_BIT_MODIFY 0b00000101
#define MCP_SPI_CMD_READ_RX_BUF_0_SIDH  0b10010000
#define MCP_SPI_CMD_READ_RX_BUF_0_D0    0b10010010
#define MCP_SPI_CMD_READ_RX_BUF_1_SIDH  0b10010100
#define MCP_SPI_CMD_READ_RX_BUF_1_D0    0b10010110
#define MCP_SPI_CMD_LOAD_TX_BUF_0_SIDH 0b01000000
#define MCP_SPI_CMD_LOAD_TX_BUF_0_D0   0b01000001
#define MCP_SPI_CMD_LOAD_TX_BUF_1_SIDH 0b01000010
#define MCP_SPI_CMD_LOAD_TX_BUF_1_D0   0b01000011
#define MCP_SPI_CMD_LOAD_TX_BUF_2_SIDH 0b01000100
#define MCP_SPI_CMD_LOAD_TX_BUF_2_D0   0b01000101
#define MCP_SPI_CMD_RTS_TX_BUF   0b10000000
#define MCP_SPI_CMD_RTS_TX_BUF_0 0b10000001
#define MCP_SPI_CMD_RTS_TX_BUF_1 0b10000010
#define MCP_SPI_CMD_RTS_TX_BUF_2 0b10000100
#define MCP_SPI_CMD_READ_STATUS 0b10100000 /* Read out a collection of bitfields from different registers. */
#define MCP_SPI_CMD_RX_STATUS 0b10110000 /* Read out a collection of bitfields from different registers. */

#endif /* MCP2515_REGISTER_MAP_H */
