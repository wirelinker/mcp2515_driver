#ifndef MCP2515_CONTROL_REG_BITFIELDS_H
#define MCP2515_CONTROL_REG_BITFIELDS_H

/* =========================================================================
 * 0x0C: BFPCTRL - RXnBF(Buffer Full) Pin Control and Status Register
 * ========================================================================= */
#define BFPCTRL_B1BFS       0b00100000  /* RX1BF Pin State */
#define BFPCTRL_B0BFS       0b00010000  /* RX0BF Pin State */
#define BFPCTRL_B1BFE       0b00001000  /* RX1BF Pin Enable */
#define BFPCTRL_B0BFE       0b00000100  /* RX0BF Pin Enable */
#define BFPCTRL_B1BFM       0b00000010  /* RX1BF Pin Mode (1=Digital Out, 0=Interrupt) */
#define BFPCTRL_B0BFM       0b00000001  /* RX0BF Pin Mode (1=Digital Out, 0=Interrupt) */

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
/* Bit 7-5: OPMOD[2:0] Operation Mode */
#define CANSTAT_OPMOD_MASK   0b11100000  
#define CANSTAT_OPMOD_NORM   0b00000000  /* Normal Operation Mode */
#define CANSTAT_OPMOD_SLEEP  0b00100000  /* Sleep Mode */
#define CANSTAT_OPMOD_LOOP   0b01000000  /* Loopback Mode */
#define CANSTAT_OPMOD_LISTEN 0b01100000  /* Listen-Only Mode */
#define CANSTAT_OPMOD_CFG    0b10000000  /* Configuration Mode */

/* Bit 3-1: ICOD[2:0] Interrupt Flag Code */
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
/* Bit 7-5: REQOP[2:0] Request Operation Mode */
#define CANCTRL_REQOP_MASK   0b11100000  
#define CANCTRL_REQOP_NORM   0b00000000  /* Request Normal Mode */
#define CANCTRL_REQOP_SLEEP  0b00100000  /* Request Sleep Mode */
#define CANCTRL_REQOP_LOOP   0b01000000  /* Request Loopback Mode */
#define CANCTRL_REQOP_LISTEN 0b01100000  /* Request Listen-Only Mode */
#define CANCTRL_REQOP_CFG    0b10000000  /* Request Configuration Mode */

#define CANCTRL_ABAT        0b00010000  /* Abort All Pending Transmissions */
#define CANCTRL_OSM         0b00001000  /* One-Shot Mode Enable */
#define CANCTRL_CLKEN       0b00000100  /* CLKOUT Pin Enable */

/* Bit 1-0: CLKPRE[1:0] CLKOUT Pin Prescaler */
#define CANCTRL_CLKPRE_MASK 0b00000011  
#define CANCTRL_CLKPRE_DIV1 0b00000000  /* System Clock / 1 */
#define CANCTRL_CLKPRE_DIV2 0b00000001  /* System Clock / 2 */
#define CANCTRL_CLKPRE_DIV4 0b00000010  /* System Clock / 4 */
#define CANCTRL_CLKPRE_DIV8 0b00000011  /* System Clock / 8 */

/* =========================================================================
 * 0x28: CNF3 - Configuration Register 3
 * ========================================================================= */
#define CNF3_SOF            0b10000000  /* CLKOUT pin SOF Signal Output Enable */
#define CNF3_WAKFIL         0b01000000  /* Wake-up Filter Enable */

/* Bit 2-0: PHSEG2[2:0] PS2 Length Bits */
/* PS2 = (PHSEG2[2:0] + 1) x TQ. Minimum valid setting for PS2 is 2 TQs.*/
#define CNF3_PHSEG2         0b00000111  /* PS2 Length Bits */

/* =========================================================================
 * 0x29: CNF2 - Configuration Register 2
 * ========================================================================= */
/* Bit 7: BTLMODE PS2 Bit Time Length Source Select */
/* 1 = PS2 is determined by the PHSEG2[2:0] bits of CNF3 */
/* 0 = PS2 is the greater of PS1 and IPT (2 TQs) */
#define CNF2_BTLMODE        0b10000000

#define CNF2_SAM            0b01000000  /* Sample Point Configuration (1=3 times, 0=1 time) */

/* Bit 5-3: PHSEG1[2:0] PS1 Length Bits */
/* PS1 = (PHSEG1[2:0] + 1) x TQ */
#define CNF2_PHSEG1         0b00111000

/* Bit 2-0: PRSEG[2:0] Propagation Segment Length Bits */
/* PRS = (PRSEG[2:0] + 1) x TQ */
#define CNF2_PRSEG          0b00000111

/* =========================================================================
 * 0x2A: CNF1 - Configuration Register 1
 * ========================================================================= */
/* Bit 7-6: SJW[1:0] Synchronization Jump Width Length bits */
#define CNF1_SJW_MASK       0b11000000  
#define CNF1_SJW_1TQ        0b00000000  /* 1 x Tq */
#define CNF1_SJW_2TQ        0b01000000  /* 2 x Tq */
#define CNF1_SJW_3TQ        0b10000000  /* 3 x Tq */
#define CNF1_SJW_4TQ        0b11000000  /* 4 x Tq */

/* Bit 5-0: BRP[5:0] Baud Rate Prescaler bits */
/* TQ = 2 x (BRP[5:0] + 1) / FOSC */
#define CNF1_BRP_MASK       0b00111111

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
/* must be cleared by MCU to reset the interrupt condition */
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

/* =========================================================================
 * TXBnCTRL - Transmit Buffer n Control Register (TXB0CTRL, TXB1CTRL, TXB2CTRL)
 * Address: 0x30 (TXB0CTRL), 0x40 (TXB1CTRL), 0x50 (TXB2CTRL)
 * ========================================================================= */

#define TXBNCTRL_ABTF       0b01000000  /* Bit 6: Message Aborted Flag (1 = Transmission aborted, 0 = Completed) */
#define TXBNCTRL_MLOA       0b00100000  /* Bit 5: Message Lost Arbitration (1 = Lost arbitration, 0 = No loss) */
#define TXBNCTRL_TXERR      0b00010000  /* Bit 4: Transmission Error Detected (1 = Bus error occurred, 0 = No error) */

/* MCU sets this bit to request message be transmitted – bit is automatically cleared when the
message is sent. */
#define TXBNCTRL_TXREQ      0b00001000  /* Bit 3: Message Transmit Request (1 = Buffer pending tx, 0 = Clear/Done) */

/* Bit 1-0: TXP[1:0] Transmit Buffer Priority */
#define TXBNCTRL_TXP_LOWEST  0b00000000 /* Priority 0 (Lowest priority) */
#define TXBNCTRL_TXP_LOW     0b00000001 /* Priority 1 (Low-intermediate priority) */
#define TXBNCTRL_TXP_HIGH    0b00000010 /* Priority 2 (High-intermediate priority) */
#define TXBNCTRL_TXP_HIGHEST 0b00000011 /* Priority 3 (Highest priority) */

/* =========================================================================
 * 0x60: RXB0CTRL - Receive Buffer 0 Control Register
 * ========================================================================= */

/* Bit 6-5: RXM[1:0] Receive Buffer Operating Mode */
#define RXB0CTRL_RXM_ALL_MSG    0b01100000  /* Turn masks/filters off; receive all messages */
#define RXB0CTRL_RXM_RESERVED_2 0b01000000  /* Reserved */
#define RXB0CTRL_RXM_RESERVED_1 0b00100000  /* Reserved */
#define RXB0CTRL_RXM_VALID_ALL  0b00000000  /* Receive all valid messages that satisfy filters */
/* Extended ID Filter registers, RXFnEID8:RXFnEID0, are applied to the first two bytes of data in
the messages with standard IDs */

/* Bit 3: RXRTR Received Remote Transfer Request */
#define RXB0CTRL_RXRTR          0b00001000  /* 1 = Remote Frame Received, 0 = No Remote Frame Received */

/* Bit 2: BUKT Rollover Enable */
#define RXB0CTRL_BUKT           0b00000100  /* 1 = RXB0 message will roll over to RXB1 if RXB0 is full, 0 = Rollover disabled */

/* Bit 1: BUKT1 Read-Only Copy of BUKT Bit */
#define RXB0CTRL_BUKT1          0b00000010  /* Copy of BUKT bit state */

/* Bit 0: FILHIT0 Filter Hit (Indicates which acceptance filter enabled the message reception) */
#define RXB0CTRL_FILHIT_RXF1    0b00000001  /* Acceptance Filter 1 (RXF1) hit */
#define RXB0CTRL_FILHIT_RXF0    0b00000000  /* Acceptance Filter 0 (RXF0) hit */
/* If a rollover from RXB0 to RXB1 occurs, the FILHIT0 bit will reflect the filter that accepted the message
that rolled over. */

/* =========================================================================
 * 0x70: RXB1CTRL - Receive Buffer 1 Control Register
 * ========================================================================= */

/* Bit 6-5: RXM[1:0] Receive Buffer Operating Mode */
#define RXB1CTRL_RXM_ALL_MSG    0b01100000  /* Turn masks/filters off; receive all messages */
#define RXB1CTRL_RXM_RESERVED_2 0b01000000  /* Reserved */
#define RXB1CTRL_RXM_RESERVED_1 0b00100000  /* Reserved */
#define RXB1CTRL_RXM_VALID_ALL  0b00000000  /* Receive all valid messages that satisfy filters */
/* Extended ID Filter registers, RXFnEID8:RXFnEID0, are applied to the first two bytes of data in
the messages with standard IDs */

/* Bit 3: RXRTR Received Remote Transfer Request */
#define RXB1CTRL_RXRTR          0b00001000  /* 1 = Remote Frame Received, 0 = No Remote Frame Received */

/* Bit 2-0: FILHIT[2:0] Filter Hit (Indicates which filter enabled reception) */
#define RXB1CTRL_FILHIT_RXF5    0b00000101  /* Acceptance Filter 5 (RXF5) hit */
#define RXB1CTRL_FILHIT_RXF4    0b00000100  /* Acceptance Filter 4 (RXF4) hit */
#define RXB1CTRL_FILHIT_RXF3    0b00000011  /* Acceptance Filter 3 (RXF3) hit */
#define RXB1CTRL_FILHIT_RXF2    0b00000010  /* Acceptance Filter 2 (RXF2) hit */
#define RXB1CTRL_FILHIT_RXF1    0b00000001  /* Acceptance Filter 1 (RXF1) hit (via Rollover from RXB0) */
#define RXB1CTRL_FILHIT_RXF0    0b00000000  /* Acceptance Filter 0 (RXF0) hit (via Rollover from RXB0) */

#endif /* MCP2515_CONTROL_REG_BITFIELDS_H */
