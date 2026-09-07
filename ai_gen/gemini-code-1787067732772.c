#ifndef MCP2515_BITFIELDS_BIN_H
#define MCP2515_BITFIELDS_BIN_H

/* =========================================================================
 * 0x0C: BFPCTRL - RXnBF Pin Control and Status Register
 * ========================================================================= */
#define BFPCTRL_B1BFS       0b00100000  /* RX1BF Pin State */
#define BFPCTRL_B0BFS       0b00010000  /* RX0BF Pin State */
#define BFPCTRL_B1BFM       0b00001000  /* RX1BF Pin Mode (1=Digital Out, 0=Interrupt) */
#define BFPCTRL_B0BFM       0b00000100  /* RX0BF Pin Mode (1=Digital Out, 0=Interrupt) */
#define BFPCTRL_B1BFE       0b00000010  /* RX1BF Pin Enable */
#define BFPCTRL_B0BFE       0b00000001  /* RX0BF Pin Enable */

/* =========================================================================
 * 0x0D: TXRTSCTRL - TXnRTS Pin Control and Status Register
 * ========================================================================= */
#define TXRTSCTRL_B2RTS     0b00100000  /* TX2RTS Pin State */
#define TXRTSCTRL_B1RTS     0b00010000  /* TX1RTS Pin State */
#define TXRTSCTRL_B0RTS     0b00001000  /* TX0RTS Pin State */
#define TXRTSCTRL_B2RTSM    0b00000100  /* TX2RTS Pin Mode (1=RTS Request, 0=Digital In) */
#define TXRTSCTRL_B1RTSM    0b00000010  /* TX1RTS Pin Mode (1=RTS Request, 0=Digital In) */
#define TXRTSCTRL_B0RTSM    0b00000001  /* TX0RTS Pin Mode (1=RTS Request, 0=Digital In) */

/* =========================================================================
 * 0x0E: CANSTAT - CAN Status Register
 * ========================================================================= */
// Bit 7-5: OPMOD[2:0] Mode Status Mask
#define CANSTAT_OPMOD_MASK  0b11100000  
#define CANSTAT_OPMOD_NORM  0b00000000  /* Normal Operation Mode */
#define CANSTAT_OPMOD_SLEEP 0b00100000  /* Sleep Mode */
#define CANSTAT_OPMOD_LOOP  0b01000000  /* Loopback Mode */
#define CANSTAT_OPMOD_LISTEN 0b01100000 /* Listen-Only Mode */
#define CANSTAT_OPMOD_CFG   0b10000000  /* Configuration Mode */

// Bit 3-1: ICOD[2:0] Interrupt Code Mask
#define CANSTAT_ICOD_MASK   0b00001110  
#define CANSTAT_ICOD_NONE   0b00000000  /* No Interrupt */
#define CANSTAT_ICOD_ERR    0b00000010  /* Error Interrupt */
#define CANSTAT_ICOD_WAK    0b00000100  /* Wake-up Interrupt */
#define CANSTAT_ICOD_TX0    0b00000110  /* TXB0 Interrupt */
#define CANSTAT_ICOD_TX1    0b00001000  /* TXB1 Interrupt */
#define CANSTAT_ICOD_TX2    0b00001010  /* TXB2 Interrupt */
#define CANSTAT_ICOD_RX0    0b00001100  /* RXB0 Interrupt */
#define CANSTAT_ICOD_RX1    0b00001110  /* RXB1 Interrupt */

/* =========================================================================
 * 0x0F: CANCTRL - CAN Control Register
 * ========================================================================= */
// Bit 7-5: REQOP[2:0] Request Operation Mode Mask
#define CANCTRL_REQOP_MASK  0b11100000  
#define CANCTRL_REQOP_NORM  0b00000000  /* Request Normal Mode */
#define CANCTRL_REQOP_SLEEP 0b00100000  /* Request Sleep Mode */
#define CANCTRL_REQOP_LOOP  0b01000000  /* Request Loopback Mode */
#define CANCTRL_REQOP_LISTEN 0b01100000 /* Request Listen-Only Mode */
#define CANCTRL_REQOP_CFG   0b10000000  /* Request Configuration Mode */

#define CANCTRL_ABAT        0b00010000  /* Abort All Pending Transmissions */
#define CANCTRL_OSM         0b00001000  /* One-Shot Mode Enable */
#define CANCTRL_CLKEN       0b00000100  /* CLKOUT Pin Enable */

// Bit 1-0: CLKPRE[1:0] Prescaler Mask
#define CANCTRL_CLKPRE_MASK 0b00000011  
#define CANCTRL_CLKPRE_DIV1 0b00000000  /* System Clock / 1 */
#define CANCTRL_CLKPRE_DIV2 0b00000001  /* System Clock / 2 */
#define CANCTRL_CLKPRE_DIV4 0b00000010  /* System Clock / 4 */
#define CANCTRL_CLKPRE_DIV8 0b00000011  /* System Clock / 8 */

/* =========================================================================
 * 0x28: CNF3 - Configuration Register 3
 * ========================================================================= */
#define CNF3_SOF            0b10000000  /* SOF Signal Output Enable */
#define CNF3_WAKFIL         0b01000000  /* Wake-up Filter Enable */

// Bit 2-0: PHSEG2[2:0] Mask
#define CNF3_PHSEG2_MASK    0b00000111  /* PS2 Length Bits */

/* =========================================================================
 * 0x29: CNF2 - Configuration Register 2
 * ========================================================================= */
#define CNF2_BTLMODE        0b10000000  /* PS2 Bit Time Length Source Select */
#define CNF2_SAM            0b01000000  /* Sample Point Configuration (1=3 times, 0=1 time) */

// Bit 5-3: PHSEG1[2:0] Mask
#define CNF2_PHSEG1_MASK    0b00111000  /* PS1 Length Bits */

// Bit 2-0: PRSEG[2:0] Mask
#define CNF2_PRSEG_MASK     0b00000111  /* Propagation Segment Length Bits */

/* =========================================================================
 * 0x2A: CNF1 - Configuration Register 1
 * ========================================================================= */
// Bit 7-6: SJW[1:0] Mask
#define CNF1_SJW_MASK       0b11000000  
#define CNF1_SJW_1TQ        0b00000000  /* 1 x Tq */
#define CNF1_SJW_2TQ        0b01000000  /* 2 x Tq */
#define CNF1_SJW_3TQ        0b10000000  /* 3 x Tq */
#define CNF1_SJW_4TQ        0b11000000  /* 4 x Tq */

// Bit 5-0: BRP[5:0] Mask
#define CNF1_BRP_MASK       0b00111111  /* Baud Rate Prescaler Bits */

/* =========================================================================
 * 0x2B: CANINTE - CAN Interrupt Enable Register
 * ========================================================================= */
#define CANINTE_MERRE       0b10000000  /* Message Error Interrupt Enable */
#define CANINTE_WAKIE       0b01000000  /* Wake-up Interrupt Enable */
#define CANINTE_ERRIE       0b00100000  /* Error Interrupt Enable */
#define CANINTE_TX2IE       0b00010000  /* Transmit Buffer 2 Empty Interrupt Enable */
#define CANINTE_TX1IE       0b00001000  /* Transmit Buffer 1 Empty Interrupt Enable */
#define CANINTE_TX0IE       0b00000100  /* Transmit Buffer 0 Empty Interrupt Enable */
#define CANINTE_RX1IE       0b00000010  /* Receive Buffer 1 Full Interrupt Enable */
#define CANINTE_RX0IE       0b00000001  /* Receive Buffer 0 Full Interrupt Enable */

/* =========================================================================
 * 0x2C: CANINTF - CAN Interrupt Flag Register
 * ========================================================================= */
#define CANINTF_MERRF       0b10000000  /* Message Error Interrupt Flag */
#define CANINTF_WAKIF       0b01000000  /* Wake-up Interrupt Flag */
#define CANINTF_ERRIF       0b00100000  /* Error Interrupt Flag */
#define CANINTF_TX2IF       0b00010000  /* Transmit Buffer 2 Empty Interrupt Flag */
#define CANINTF_TX1IF       0b00001000  /* Transmit Buffer 1 Empty Interrupt Flag */
#define CANINTF_TX0IF       0b00000100  /* Transmit Buffer 0 Empty Interrupt Flag */
#define CANINTF_RX1IF       0b00000010  /* Receive Buffer 1 Full Interrupt Flag */
#define CANINTF_RX0IF       0b00000001  /* Receive Buffer 0 Full Interrupt Flag */

/* =========================================================================
 * 0x2D: EFLG - Error Flag Register
 * ========================================================================= */
#define EFLG_RX1OVR         0b10000000  /* Receive Buffer 1 Overflow Flag */
#define EFLG_RX0OVR         0b01000000  /* Receive Buffer 0 Overflow Flag */
#define EFLG_TXBO           0b00100000  /* Bus-Off Error Flag */
#define EFLG_TXEP           0b00010000  /* Transmit Error-Passive Flag */
#define EFLG_RXEP           0b00001000  /* Receive Error-Passive Flag */
#define EFLG_TXWAR          0b00000100  /* Transmit Error Warning Flag */
#define EFLG_RXWAR          0b00000010  /* Receive Error Warning Flag */
#define EFLG_EWARN          0b00000001  /* Error Warning Flag */

#endif /* MCP2515_BITFIELDS_BIN_H */