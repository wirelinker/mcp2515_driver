#ifndef MCP2515_TXBNCTRL_BITS_H
#define MCP2515_TXBNCTRL_BITS_H

/* =========================================================================
 * TXBnCTRL - Transmit Buffer n Control Register (TXB0CTRL, TXB1CTRL, TXB2CTRL)
 * Address: 0x30 (TXB0CTRL), 0x40 (TXB1CTRL), 0x50 (TXB2CTRL)
 * ========================================================================= */

#define TXBNCTRL_ABTF       0b01000000  /* Bit 6: Message Aborted Flag (1 = Transmission aborted, 0 = Completed) */
#define TXBNCTRL_MLOA       0b00100000  /* Bit 5: Message Lost Arbitration (1 = Lost arbitration, 0 = No loss) */
#define TXBNCTRL_TXERR      0b00010000  /* Bit 4: Transmission Error Detected (1 = Bus error occurred, 0 = No error) */
#define TXBNCTRL_TXREQ      0b00001000  /* Bit 3: Message Transmit Request (1 = Buffer pending tx, 0 = Clear/Done) */

/* Bit 1-0: TXP[1:0] Transmit Buffer Priority Values */
#define TXBNCTRL_TXP_LOWEST  0b00000000 /* Priority 0 (Lowest priority) */
#define TXBNCTRL_TXP_LOW     0b00000001 /* Priority 1 (Low-intermediate priority) */
#define TXBNCTRL_TXP_HIGH    0b00000010 /* Priority 2 (High-intermediate priority) */
#define TXBNCTRL_TXP_HIGHEST 0b00000011 /* Priority 3 (Highest priority) */

#endif /* MCP2515_TXBNCTRL_BITS_H */