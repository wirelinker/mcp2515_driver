/*
 * Copyright (c) 2026 wirelinker
 * SPDX-License-Identifier: MIT License
 */

#ifndef MCP2515_H
#define MCP2515_H


/*
 * MCP2515 definition
 */
#include "mcp2515_register_map.h"
#include "mcp2515_control_reg_bitfields.h"
#include "mcp2515_spi_command.h"

/*
 * Bit-stuffing applys from SOF to CRC,
 * not includes CRC delimiter.
 *
 * ======= standard data frame ======
 * - start of frame (SOF) = 1 bit = 0
 * - arbitration field
 *   ID = 11 bits
 *   RTR = 1 bit = 0
 * - control field
 *   IDE = 1 bit = 0
 *   RB0 = 1 bit = 0
 *   DLC = 4 bits
 * - data field
 *   data = 0 ~ 8 bytes
 * - crc field
 *   CRC = 15 bits
 *   CRC delimiter = 1 bit = 1
 * - ACK slot bit   = 1 bit
 * - ACK delimiter  = 1 bit = 1
 * - end of frame (EOF) = 7 bits
 *
 * - IFS(Inter Frame Space) = 3 bits
 *
 * ====== extended data frame ======
 * - start of frame (SOF) = 1 bit = 0
 * - arbitration field
 *   ID = 11 bits
 *   SRR = 1 bit = 1
 *   IDE = 1 bit = 1
 *   EID = 18 bits
 *   RTR = 1 bit = 0
 * - control field
 *   RB1 = 1 bit = 0
 *   RB0 = 1 bit = 0
 *   DLC = 4 bits
 * - data field
 *   data = 0 ~ 8 bytes
 * - crc field
 *   CRC = 15 bits
 *   CRC delimiter = 1 bit = 1
 * - ACK slot bit  = 1 bit
 * - ACK delimiter = 1 bit = 1
 * - end of frame (EOF) = 7 bits
 *
 * - IFS (Inter Frame Space) = 3 bits
 *
 * ====== mcp2515 tx buf registers ======
 * frame
 * total 13 bytes
 * MCP_TXB0SIDH
 * MCP_TXB0SIDL
 * MCP_TXB0EID8
 * MCP_TXB0EID0
 * MCP_TXB0DLC 
 * MCP_TXB0D0  
 * MCP_TXB0D1  
 * MCP_TXB0D2  
 * MCP_TXB0D3  
 * MCP_TXB0D4  
 * MCP_TXB0D5  
 * MCP_TXB0D6  
 * MCP_TXB0D7  
 */

typedef struct can_frame
{
    unsigned short ID;
    unsigned char  EXIDE;
    unsigned int   EID;
    unsigned char  RTR;
    unsigned char  DLC;
    unsigned char  data[8];
} can_frame_t;

typedef struct mcp2515_can_frame
{
    can_frame_t frame_field;
    unsigned char packed_reg[13];
} mcp2515_can_frame_t;

/*
 * platform spi function
 */
void mcp2515_spi_init(void);
#ifndef CS_FUNCTION
#define CS_FUNCTION
#ifdef PICO_DEFAULT_SPI_CSN_PIN
static inline void cs_select() {
    /* CS pin is active low */
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);
}

static inline void cs_unselect() {
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
}
#endif
#endif /* CS_FUNCTION */

/*
 * MCP2515 spi command function
 */
void mcp2515_spi_cmd_reset(void);
unsigned char mcp2515_spi_cmd_reg_read(unsigned char reg_addr, unsigned char *buf,  unsigned char len);
unsigned char mcp2515_spi_cmd_reg_write(unsigned char reg_addr, unsigned char *buf,  unsigned char len);
void mcp2515_spi_cmd_bit_modify(unsigned char reg_addr, unsigned char bit_mask, unsigned char data);
unsigned char mcp2515_spi_cmd_rx_buf_read(unsigned char buf_num,
                                          unsigned char *frame,
                                          unsigned char len,
                                          unsigned char data_only,
                                          unsigned char data_len_by_dlc);
unsigned char mcp2515_spi_cmd_tx_buf_write(unsigned char buf_num,
                                           const unsigned char *frame,
                                           unsigned char len,
                                           unsigned char data_only);
void mcp2515_spi_cmd_tx_rts_set(unsigned char buf_num); /* set tx RTS by SPI cmd directly */

/*
 * It's a collection of bitfields from different registers.
 * spi cmd status data format
 * 
 * bit7 = TX2IF (CANINTF[4])  TX2 interrupt flag
 * bit6 = TXREQ (TXB2CTRL[3]) TX2 request to send
 * bit5 = TX1IF (CANINTF[3])  TX1 interrupt flag
 * bit4 = TXREQ (TXB1CTRL[3]) TX1 request to send
 * bit3 = TX0IF (CANINTF[2])  TX0 interrupt flag
 * bit2 = TXREQ (TXB0CTRL[3]) TX0 request to send
 * bit1 = RX1IF (CANINTF[1])  RX1 interrupt flag
 * bit0 = RX0IF (CANINTF[0])  RX0 interrupt flag
 * */
#define QUICK_STATUS_TX2IF  0b10000000
#define QUICK_STATUS_TX2RTS 0b01000000
#define QUICK_STATUS_TX1IF  0b00100000
#define QUICK_STATUS_TX1RTS 0b00010000
#define QUICK_STATUS_TX0IF  0b00001000
#define QUICK_STATUS_TX0RTS 0b00000100
#define QUICK_STATUS_RX1IF  0b00000010
#define QUICK_STATUS_RX0IF  0b00000001
unsigned char mcp2515_spi_cmd_quick_status_read(void);

/* 
 * It's a collection of bitfields from different registers.
 * spi cmd rx status data format
 *
 * bit7 = RXB1 message in buffer
 * bit6 = RXB0 message in buffer
 *
 * bit[4:3]
 * 0b00 = standard data frame
 * 0b01 = standard remote frame
 * 0b10 = extended data frame
 * 0b11 = extended remote frame
 *
 * bit[2:0] : RX filter match
 * 0b000 = RXF0
 * 0b001 = RXF1
 * 0b010 = RXF2
 * 0b011 = RXF3
 * 0b100 = RXF4
 * 0b101 = RXF5
 * 0b110 = RXF0 (RXB0 is full, so buffer data rollover to RXB1)
 * 0b111 = RXF1 (RXB0 is full, so buffer data rollover to RXB1)
 *
 */

#define QUICK_RX_STATUS_RXB1_HAS_MESSAGE 0b10000000
#define QUICK_RX_STATUS_RXB0_HAS_MESSAGE 0b01000000
#define QUICK_RX_STATUS_STD_DATA_FRAME   0b00000000
#define QUICK_RX_STATUS_STD_REMOTE_FRAME 0b00001000
#define QUICK_RX_STATUS_EXT_DATA_FRAME   0b00010000
#define QUICK_RX_STATUS_EXT_REMOTE_FRAME 0b00011000
#define QUICK_RX_STATUS_RXF0_MATCH       0b00000000
#define QUICK_RX_STATUS_RXF1_MATCH       0b00000001
#define QUICK_RX_STATUS_RXF2_MATCH       0b00000010
#define QUICK_RX_STATUS_RXF3_MATCH       0b00000011
#define QUICK_RX_STATUS_RXF4_MATCH       0b00000100
#define QUICK_RX_STATUS_RXF5_MATCH       0b00000101
#define QUICK_RX_STATUS_RXF0_MATCH_ROLLOVER       0b00000110
#define QUICK_RX_STATUS_RXF1_MATCH_ROLLOVER       0b00000111
void mcp2515_spi_cmd_quick_rx_status_read(unsigned char* buf);



/* wrapper functions using mcp2515 spi command functions */
/* for
 * 1. specific SPI command, not register read/write
 * 2. general register read/write
 * 3. specific register read/write, without overhead of general read/write command
 * */

/* CAN bus send data steps
 * 1. setup tx buffer
 * 2. set tx RTS(Request to Send)
 */
unsigned char mcp2515_tx_buf_write(unsigned char buf_num, unsigned char data_only, mcp2515_can_frame_t* frame);
/*
 * three methods to set RTS (Request to Send)
 * 1. spi cmd (lowest overhead)
 * 2. RTS pin input(depends on hardware design)
 * 3. TXBnCTRL (need reg addr and bit-modify cmd, higher overhead)
 */
static inline void mcp2515_tx_rts_set(unsigned char tx_buf_num)
{
    mcp2515_spi_cmd_tx_rts_set(tx_buf_num);
}

void mcp2515_tx_buf_ctrl_status_get(unsigned char buf_num, unsigned char *reg_status);
void mcp2515_tx_buf_ctrl_rts_set(unsigned char buf_num);/* set tx RTS by modify RTS bit in tx buffer control register */
void mcp2515_tx_buf_ctrl_rts_clear(unsigned char buf_num);
void mcp2515_tx_buf_ctrl_pri_set(unsigned char buf_num, unsigned char buf_pri_set);

/*
 * CAN bus receive data steps
 * 1. check rx buffer interrupt
 * 2. read rx buffer
 * 3. clear rx buffer interrupt (spi command specific for reading rx buffer will clear the interrupt flag automatically)
 */
unsigned char mcp2515_rx_buf_read(unsigned char buf_num, unsigned char data_only, unsigned char data_len, unsigned char data_len_by_received_DLC, mcp2515_can_frame_t *frame);

void mcp2515_rx_filter_set(unsigned char filter_num, unsigned char *filter_value_array);
void mcp2515_rx_filter_get(unsigned char filter_num, unsigned char *filter_value_array);
void mcp2515_rx_mask_set(unsigned char mask_num, unsigned char *mask_value_array);
void mcp2515_rx_mask_get(unsigned char mask_num, unsigned char *mask_value_array);

void mcp2515_interrupt_flag_modify(unsigned char reg_mask, unsigned char reg_data);
void mcp2515_can_status_reg_get(unsigned char *reg_status);/* read register by general register read command */
void mcp2515_can_ctrl_reg_set(unsigned char reg_mask, unsigned char reg_data);

/* consider RTOS multi thread usage
 * One specific task handles all the CAN bus tx/rx.
 * It needs to take the lock of spi first, then performs the CAN bus operation.
 * The other tasks using CAN bus need to join a list of request for
 * using CAN bus. They also need to prepare their own space for their data to be
 * transmitted or received.
 * */
//typedef struct mcp2515_frame_t{
//
//    /* frame register array */
//    unsigned char frame[13];
//
//} mcp2515_frame_t;

/* MCP2515 instance struct */
typedef struct mcp2515_inst {


    /*
    typedef struct mcp2515_frame_t{ unsigned char frame[13]; } mcp2515_frame_t;
    typedef unsigned char frame[13] mcp2515_frame_t;
     * */
    /*
    unsigned char can_state;
    unsigned char can_control;
    */
    /*
    unsigned char bit_time_config_1;
    unsigned char bit_time_config_2;
    unsigned char bit_time_config_3;
    */

    /*
    unsigned char can_int_enable;
    unsigned char can_int_flag;
    */
    /*
    unsigned char tx_err_counter;
    unsigned char rx_err_counter;
    unsigned char can_err_flag;
    */
    /*
    unsigned char tx_rts_pin;
    unsigned char rx_buf_full_pin;
    */

    /*
    unsigned char tx_buf0_ctrl;
    unsigned char tx_buf1_ctrl;
    unsigned char tx_buf2_ctrl;
    unsigned char rx_buf0_ctrl;
    unsigned char rx_buf1_ctrl;
    */
    /*
    unsigned char rx_filter0[4];
    unsigned char rx_filter1[4];
    unsigned char rx_filter2[4];
    unsigned char rx_filter3[4];
    unsigned char rx_filter4[4];
    unsigned char rx_filter5[4];

    unsigned char rx_mask0[4];
    unsigned char rx_mask1[4];
    */


    /* tx/rx buffer registers */
    unsigned char *frame_tx0;
    unsigned char *frame_tx1;
    unsigned char *frame_tx2;
    unsigned char *frame_rx0;
    unsigned char *frame_rx1;

    /* method */
    /* rx buffer filter and mask*/

} mcp2515_t;

#endif /* MCP2515_H */
