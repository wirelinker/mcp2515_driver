#ifndef MCP2515_RXB1CTRL_BITS_H
#define MCP2515_RXB1CTRL_BITS_H

/* =========================================================================
 * 0x70: RXB1CTRL - Receive Buffer 1 Control Register
 * ========================================================================= */

/* Bit 6-5: RXM[1:0] Receive Buffer Operating Mode */
#define RXB1CTRL_RXM_ALL_MSG    0b01100000  /* Turn masks/filters off; receive all messages */
#define RXB1CTRL_RXM_VALID_EXT  0b01000000  /* Receive only valid messages with Extended IDs that satisfy filters */
#define RXB1CTRL_RXM_VALID_STD  0b00100000  /* Receive only valid messages with Standard IDs that satisfy filters */
#define RXB1CTRL_RXM_VALID_ALL  0b00000000  /* Receive all valid messages that satisfy filters */

/* Bit 3: RXRTR Received Remote Transfer Request */
#define RXB1CTRL_RXRTR          0b00001000  /* 1 = Remote Frame Received, 0 = Data Frame Received */

/* Bit 2-0: FILHIT[2:0] Filter Hit (Indicates which filter enabled reception) */
#define RXB1CTRL_FILHIT_RXF5    0b00000101  /* Acceptance Filter 5 (RXF5) hit */
#define RXB1CTRL_FILHIT_RXF4    0b00000100  /* Acceptance Filter 4 (RXF4) hit */
#define RXB1CTRL_FILHIT_RXF3    0b00000011  /* Acceptance Filter 3 (RXF3) hit */
#define RXB1CTRL_FILHIT_RXF2    0b00000010  /* Acceptance Filter 2 (RXF2) hit */
#define RXB1CTRL_FILHIT_RXF1    0b00000001  /* Acceptance Filter 1 (RXF1) hit (via Rollover from RXB0) */
#define RXB1CTRL_FILHIT_RXF0    0b00000000  /* Acceptance Filter 0 (RXF0) hit (via Rollover from RXB0) */

#endif /* MCP2515_RXB1CTRL_BITS_H */