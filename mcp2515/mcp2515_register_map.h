#ifndef MCP2515_REGISTER_MAP_H
#define MCP2515_REGISTER_MAP_H

/* =========================================================================
 * MCP2515 Register Map (Addresses 0x00 - 0x7F)
 * All values represented in Binary format.
 * ========================================================================= */

/* -------------------------------------------------------------------------
 * Address Range: 0x00 - 0x0F
 * ------------------------------------------------------------------------- */
#define MCP_RXF0SIDH        0b00000000  /* Filter 0 Standard Identifier High */
#define MCP_RXF0SIDL        0b00000001  /* Filter 0 Standard Identifier Low */
#define MCP_RXF0EID8        0b00000010  /* Filter 0 Extended Identifier High */
#define MCP_RXF0EID0        0b00000011  /* Filter 0 Extended Identifier Low */
#define MCP_RXF1SIDH        0b00000100  /* Filter 1 Standard Identifier High */
#define MCP_RXF1SIDL        0b00000101  /* Filter 1 Standard Identifier Low */
#define MCP_RXF1EID8        0b00000110  /* Filter 1 Extended Identifier High */
#define MCP_RXF1EID0        0b00000111  /* Filter 1 Extended Identifier Low */
#define MCP_RXF2SIDH        0b00001000  /* Filter 2 Standard Identifier High */
#define MCP_RXF2SIDL        0b00001001  /* Filter 2 Standard Identifier Low */
#define MCP_RXF2EID8        0b00001010  /* Filter 2 Extended Identifier High */
#define MCP_RXF2EID0        0b00001011  /* Filter 2 Extended Identifier Low */
#define MCP_BFPCTRL         0b00001100  /* RXnBF Pin Control and Status */

#define MCP_TXRTSCTRL       0b00001101  /* TXnRTS Pin Control and Status *//* ONLY modifiable under Configuration Mode. */

#define MCP_CANSTAT         0b00001110  /* CAN Status Register */
#define MCP_CANCTRL         0b00001111  /* CAN Control Register */

/* -------------------------------------------------------------------------
 * Address Range: 0x10 - 0x1F
 * ------------------------------------------------------------------------- */
#define MCP_RXF3SIDH        0b00010000  /* Filter 3 Standard Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF3SIDL        0b00010001  /* Filter 3 Standard Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF3EID8        0b00010010  /* Filter 3 Extended Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF3EID0        0b00010011  /* Filter 3 Extended Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF4SIDH        0b00010100  /* Filter 4 Standard Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF4SIDL        0b00010101  /* Filter 4 Standard Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF4EID8        0b00010110  /* Filter 4 Extended Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF4EID0        0b00010111  /* Filter 4 Extended Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF5SIDH        0b00011000  /* Filter 5 Standard Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF5SIDL        0b00011001  /* Filter 5 Standard Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF5EID8        0b00011010  /* Filter 5 Extended Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXF5EID0        0b00011011  /* Filter 5 Extended Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_TEC             0b00011100  /* Transmit Error Counter */
#define MCP_REC             0b00011101  /* Receive Error Counter */

/* -------------------------------------------------------------------------
 * Address Range: 0x20 - 0x2F
 * ------------------------------------------------------------------------- */
#define MCP_RXM0SIDH        0b00100000  /* Mask 0 Standard Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM0SIDL        0b00100001  /* Mask 0 Standard Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM0EID8        0b00100010  /* Mask 0 Extended Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM0EID0        0b00100011  /* Mask 0 Extended Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM1SIDH        0b00100100  /* Mask 1 Standard Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM1SIDL        0b00100101  /* Mask 1 Standard Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM1EID8        0b00100110  /* Mask 1 Extended Identifier High *//* ONLY modifiable under Configuration Mode. */
#define MCP_RXM1EID0        0b00100111  /* Mask 1 Extended Identifier Low *//* ONLY modifiable under Configuration Mode. */
#define MCP_CNF3            0b00101000  /* Configuration Register 3 *//* ONLY modifiable under Configuration Mode. */
#define MCP_CNF2            0b00101001  /* Configuration Register 2 *//* ONLY modifiable under Configuration Mode. */
#define MCP_CNF1            0b00101010  /* Configuration Register 1 *//* ONLY modifiable under Configuration Mode. */
#define MCP_CANINTE         0b00101011  /* CAN Interrupt Enable Register */
#define MCP_CANINTF         0b00101100  /* CAN Interrupt Flag Register */
#define MCP_EFLG            0b00101101  /* Error Flag Register */

/* -------------------------------------------------------------------------
 * Address Range: 0x30 - 0x3F (Transmit Buffer 0)
 * ------------------------------------------------------------------------- */
#define MCP_TXB0CTRL        0b00110000  /* Transmit Buffer 0 Control */
#define MCP_TXB0SIDH        0b00110001  /* Transmit Buffer 0 Standard Identifier High */
#define MCP_TXB0SIDL        0b00110010  /* Transmit Buffer 0 Standard Identifier Low */
#define MCP_TXB0EID8        0b00110011  /* Transmit Buffer 0 Extended Identifier High */
#define MCP_TXB0EID0        0b00110100  /* Transmit Buffer 0 Extended Identifier Low */
#define MCP_TXB0DLC         0b00110101  /* Transmit Buffer 0 Data Length Code */
#define MCP_TXB0D0          0b00110110  /* Transmit Buffer 0 Data Byte 0 */
#define MCP_TXB0D1          0b00110111  /* Transmit Buffer 0 Data Byte 1 */
#define MCP_TXB0D2          0b00111000  /* Transmit Buffer 0 Data Byte 2 */
#define MCP_TXB0D3          0b00111001  /* Transmit Buffer 0 Data Byte 3 */
#define MCP_TXB0D4          0b00111010  /* Transmit Buffer 0 Data Byte 4 */
#define MCP_TXB0D5          0b00111011  /* Transmit Buffer 0 Data Byte 5 */
#define MCP_TXB0D6          0b00111100  /* Transmit Buffer 0 Data Byte 6 */
#define MCP_TXB0D7          0b00111101  /* Transmit Buffer 0 Data Byte 7 */

/* -------------------------------------------------------------------------
 * Address Range: 0x40 - 0x4F (Transmit Buffer 1)
 * ------------------------------------------------------------------------- */
#define MCP_TXB1CTRL        0b01000000  /* Transmit Buffer 1 Control */
#define MCP_TXB1SIDH        0b01000001  /* Transmit Buffer 1 Standard Identifier High */
#define MCP_TXB1SIDL        0b01000010  /* Transmit Buffer 1 Standard Identifier Low */
#define MCP_TXB1EID8        0b01000011  /* Transmit Buffer 1 Extended Identifier High */
#define MCP_TXB1EID0        0b01000100  /* Transmit Buffer 1 Extended Identifier Low */
#define MCP_TXB1DLC         0b01000101  /* Transmit Buffer 1 Data Length Code */
#define MCP_TXB1D0          0b01000110  /* Transmit Buffer 1 Data Byte 0 */
#define MCP_TXB1D1          0b01000111  /* Transmit Buffer 1 Data Byte 1 */
#define MCP_TXB1D2          0b01001000  /* Transmit Buffer 1 Data Byte 2 */
#define MCP_TXB1D3          0b01001001  /* Transmit Buffer 1 Data Byte 3 */
#define MCP_TXB1D4          0b01001010  /* Transmit Buffer 1 Data Byte 4 */
#define MCP_TXB1D5          0b01001011  /* Transmit Buffer 1 Data Byte 5 */
#define MCP_TXB1D6          0b01001100  /* Transmit Buffer 1 Data Byte 6 */
#define MCP_TXB1D7          0b01001101  /* Transmit Buffer 1 Data Byte 7 */

/* -------------------------------------------------------------------------
 * Address Range: 0x50 - 0x5F (Transmit Buffer 2)
 * ------------------------------------------------------------------------- */
#define MCP_TXB2CTRL        0b01010000  /* Transmit Buffer 2 Control */
#define MCP_TXB2SIDH        0b01010001  /* Transmit Buffer 2 Standard Identifier High */
#define MCP_TXB2SIDL        0b01010010  /* Transmit Buffer 2 Standard Identifier Low */
#define MCP_TXB2EID8        0b01010011  /* Transmit Buffer 2 Extended Identifier High */
#define MCP_TXB2EID0        0b01010100  /* Transmit Buffer 2 Extended Identifier Low */
#define MCP_TXB2DLC         0b01010101  /* Transmit Buffer 2 Data Length Code */
#define MCP_TXB2D0          0b01010110  /* Transmit Buffer 2 Data Byte 0 */
#define MCP_TXB2D1          0b01010111  /* Transmit Buffer 2 Data Byte 1 */
#define MCP_TXB2D2          0b01011000  /* Transmit Buffer 2 Data Byte 2 */
#define MCP_TXB2D3          0b01011001  /* Transmit Buffer 2 Data Byte 3 */
#define MCP_TXB2D4          0b01011010  /* Transmit Buffer 2 Data Byte 4 */
#define MCP_TXB2D5          0b01011011  /* Transmit Buffer 2 Data Byte 5 */
#define MCP_TXB2D6          0b01011100  /* Transmit Buffer 2 Data Byte 6 */
#define MCP_TXB2D7          0b01011101  /* Transmit Buffer 2 Data Byte 7 */

/* -------------------------------------------------------------------------
 * Address Range: 0x60 - 0x6F (Receive Buffer 0)
 * ------------------------------------------------------------------------- */
#define MCP_RXB0CTRL        0b01100000  /* Receive Buffer 0 Control */
#define MCP_RXB0SIDH        0b01100001  /* Receive Buffer 0 Standard Identifier High */
#define MCP_RXB0SIDL        0b01100010  /* Receive Buffer 0 Standard Identifier Low */
#define MCP_RXB0EID8        0b01100011  /* Receive Buffer 0 Extended Identifier High */
#define MCP_RXB0EID0        0b01100100  /* Receive Buffer 0 Extended Identifier Low */
#define MCP_RXB0DLC         0b01100101  /* Receive Buffer 0 Data Length Code */
#define MCP_RXB0D0          0b01100110  /* Receive Buffer 0 Data Byte 0 */
#define MCP_RXB0D1          0b01100111  /* Receive Buffer 0 Data Byte 1 */
#define MCP_RXB0D2          0b01101000  /* Receive Buffer 0 Data Byte 2 */
#define MCP_RXB0D3          0b01101001  /* Receive Buffer 0 Data Byte 3 */
#define MCP_RXB0D4          0b01101010  /* Receive Buffer 0 Data Byte 4 */
#define MCP_RXB0D5          0b01101011  /* Receive Buffer 0 Data Byte 5 */
#define MCP_RXB0D6          0b01101100  /* Receive Buffer 0 Data Byte 6 */
#define MCP_RXB0D7          0b01101101  /* Receive Buffer 0 Data Byte 7 */

/* -------------------------------------------------------------------------
 * Address Range: 0x70 - 0x7F (Receive Buffer 1)
 * ------------------------------------------------------------------------- */
#define MCP_RXB1CTRL        0b01110000  /* Receive Buffer 1 Control */
#define MCP_RXB1SIDH        0b01110001  /* Receive Buffer 1 Standard Identifier High */
#define MCP_RXB1SIDL        0b01110010  /* Receive Buffer 1 Standard Identifier Low */
#define MCP_RXB1EID8        0b01110003  /* Receive Buffer 1 Extended Identifier High */
#define MCP_RXB1EID0        0b01110100  /* Receive Buffer 1 Extended Identifier Low */
#define MCP_RXB1DLC         0b01110101  /* Receive Buffer 1 Data Length Code */
#define MCP_RXB1D0          0b01110110  /* Receive Buffer 1 Data Byte 0 */
#define MCP_RXB1D1          0b01110111  /* Receive Buffer 1 Data Byte 1 */
#define MCP_RXB1D2          0b01111000  /* Receive Buffer 1 Data Byte 2 */
#define MCP_RXB1D3          0b01111001  /* Receive Buffer 1 Data Byte 3 */
#define MCP_RXB1D4          0b01111010  /* Receive Buffer 1 Data Byte 4 */
#define MCP_RXB1D5          0b01111011  /* Receive Buffer 1 Data Byte 5 */
#define MCP_RXB1D6          0b01111100  /* Receive Buffer 1 Data Byte 6 */
#define MCP_RXB1D7          0b01111101  /* Receive Buffer 1 Data Byte 7 */

#endif /* MCP2515_REGISTER_MAP_H */
