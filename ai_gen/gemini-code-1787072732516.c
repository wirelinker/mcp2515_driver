#ifndef MCP2515_RXB0CTRL_BITS_H
#define MCP2515_RXB0CTRL_BITS_H

/* =========================================================================
 * 0x60: RXB0CTRL - Receive Buffer 0 Control Register
 * ========================================================================= */

/* Bit 6-5: RXM[1:0] Receive Buffer Operating Mode */
#define RXB0CTRL_RXM_ALL_MSG    0b01100000  /* Turn masks/filters off; receive all messages */
#define RXB0CTRL_RXM_VALID_EXT  0b01000000  /* Receive only valid messages with Extended IDs that satisfy filters */
#define RXB0CTRL_RXM_VALID_STD  0b00100000  /* Receive only valid messages with Standard IDs that satisfy filters */
#define RXB0CTRL_RXM_VALID_ALL  0b00000000  /* Receive all valid messages that satisfy filters */

/* Bit 3: RXRTR Received Remote Transfer Request */
#define RXB0CTRL_RXRTR          0b00001000  /* 1 = Remote Frame Received, 0 = Data Frame Received */

/* Bit 2: BUKT Rollover Enable */
#define RXB0CTRL_BUKT           0b00000100  /* 1 = RXB0 message will roll over to RXB1 if RXB0 is full, 0 = Rollover disabled */

/* Bit 1: BUKT1 Read-Only Copy of BUKT Bit */
#define RXB0CTRL_BUKT1          0b00000010  /* Copy of BUKT bit state */

/* Bit 0: FILHIT0 Filter Hit (Indicates which acceptance filter enabled the message reception) */
#define RXB0CTRL_FILHIT_RXF1    0b00000001  /* Acceptance Filter 1 (RXF1) hit */
#define RXB0CTRL_FILHIT_RXF0    0b00000000  /* Acceptance Filter 0 (RXF0) hit */

#endif /* MCP2515_RXB0CTRL_BITS_H */