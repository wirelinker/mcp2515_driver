/*
 * Copyright (c) 2026 wirelinker
 * SPDX-License-Identifier: MIT License
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "mcp2515.h"

/*
 * platform spi function
 */

void mcp2515_spi_init(void)
{
    unsigned int actual_spi_baud = 0;

    printf("MCP2515 driver start\n");

    /* use 10 MHz spi clock */
    actual_spi_baud = spi_init(spi_default, 10 * 1000 * 1000);
    printf("MCP2515 spi baud = %d\n", actual_spi_baud);

    /* set spi pin function*/
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);

    /* set spi format */
    /* mode 0,0 or mode 1,1, 8-bits, MSb first */
    spi_set_format(spi_default, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

}


/*
 * MCP2515 spi command wrapper function
 */
void mcp2515_spi_cmd_reset(void)
{
    
    unsigned char cmd[1] = {0};

    cmd[0] = MCP_SPI_CMD_RESET;

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    cs_unselect();
}

/*
 * register address
 * data buffer pointer
 * data length
 */
unsigned char mcp2515_spi_cmd_reg_read(unsigned char reg_addr, unsigned char *buf,  unsigned char len)
{

    unsigned char cmd[2] = {0};

    if(buf == NULL)
    {
        return 0;
    }
    cmd[0] = MCP_SPI_CMD_READ;
    cmd[1] = reg_addr;

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    spi_read_blocking(spi_default, 0x00, buf, len);
    cs_unselect();

    return len;
}

/*
 * register address
 * data buffer pointer
 * data length
 */
unsigned char mcp2515_spi_cmd_reg_write(unsigned char reg_addr, unsigned char *buf,  unsigned char len)
{

    unsigned char cmd[2] = {0};

    if(buf == NULL)
    {
        return 0;
    }
    cmd[0] = MCP_SPI_CMD_WRITE;
    cmd[1] = reg_addr;

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    spi_write_blocking(spi_default, (const unsigned char*) buf, len);
    cs_unselect();

    return len;
}

/*
 * register address
 * bit mask
 * data
 */
void mcp2515_spi_cmd_bit_modify(unsigned char reg_addr, unsigned char bit_mask, unsigned char data)
{
    
    unsigned char cmd[4] = {0};

    cmd[0] = MCP_SPI_CMD_BIT_MODIFY;
    cmd[1] = reg_addr;
    cmd[2] = bit_mask;
    cmd[3] = data;

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    cs_unselect();
}

/*
 * rx buffer number <= 1
 * frame_info
 * standard ID = 2 bytes
 * extended ID = 2 bytes
 * DLC = 1 byte
 * data length <= 8 bytes
 */
unsigned char mcp2515_spi_cmd_rx_buf_read(unsigned char buf_num,
                                  unsigned char *frame,
                                  unsigned char len,
                                  unsigned char data_only,
                                  unsigned char data_len_by_dlc)
{
    unsigned char cmd[1] = {0};
    unsigned char DLC = 0, data_len = 0;
    unsigned char *frame_info_ptr = frame;
    unsigned char *frame_data_ptr = frame + 5;

    if( buf_num > 1 )
    {
        return 0;
    }
    if( frame == NULL )
    {
        return 0;
    }
    if( (data_only) && (!len))
    {
        return 0;
    }
    if( (data_only) && (len > 8) )
    {
        return 0;
    }
    if( len > 13 )
    {
        return 0;
    }
    if( (data_only) && (data_len_by_dlc) )
    {
        /* Must read frame info for DLC,
         * so must not data_only. 
         */
        return 0;
    }

    cmd[0] = MCP_SPI_CMD_READ_RX_BUF_0_SIDH | (buf_num << 2);
    if(data_only)
    {
        cmd[0] = cmd[0] | 0b00000010;
    }

    if(data_only)
    {
        data_len = len;
    }
    else
    {
        if(!data_len_by_dlc)
        {
            /* data_len = (total packed register data length) - 5 */
            data_len = len - 5;
        }
    }


    printf("start spi rx buf read\n");
    printf("data len=%d\n", data_len);
    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    if(!data_only)
    {
        printf("read frame info\n");
        spi_read_blocking(spi_default, 0x00, frame_info_ptr, 5);
    }

    if(data_len_by_dlc)
    {
        /* extract data length from the DLC field of register*/
        DLC = ( *(frame_info_ptr + 4) ) & 0x0F;

        /* must avoid data buffer overflow */
        /* The DLC field received by CAN controller may not be 
         * whthin the standard range (0 <= DLC <= 8).
         */
        if(DLC > 8)
        {
            data_len = 8;
        }
        else
        {
            data_len = DLC;
        }
    }

    if(data_len)
    {
        printf("read frame data, len= %d\n", data_len);
        spi_read_blocking(spi_default, 0x00, frame_data_ptr, data_len);
    }
    cs_unselect();
    printf("finish read rx buf\n");

    if(data_only)
    {
        return data_len;
    }
    /* return the actual read out total register length */
    return (data_len + 5);
}

/*
 * tx_buffer number <= 2
 * standard ID = 2 bytes
 * extended ID = 2 bytes
 * DLC = 1 byte
 * data buffer pointer
 * data length <= 8 bytes
 */
unsigned char mcp2515_spi_cmd_tx_buf_write(unsigned char buf_num,
                                  const unsigned char *frame,
                                  unsigned char len,
                                  unsigned char data_only)
{

    unsigned char cmd[1] = {0};

    if( buf_num > 2 )
    {
        return 0;
    }
    if( frame == NULL )
    {
        return 0;
    }
    if( data_only && (!len) )
    {
        return 0;
    }
    if( data_only && (len > 8) )
    {
        return 0;
    }
    if( len > 13 )
    {
        return 0;
    }

    cmd[0] = MCP_SPI_CMD_LOAD_TX_BUF_0_SIDH | (buf_num << 0x1);
    if(data_only)
    {
        cmd[0] = cmd[0] | 0x1; 
    }

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    if(data_only)
    {
        spi_write_blocking(spi_default, (const unsigned char*) (frame + 5), len);
    }
    else
    {
        spi_write_blocking(spi_default, (const unsigned char*) frame, len);
    }
    cs_unselect();

    return len;
}

/*
 * tx buffer number
 */
void mcp2515_spi_cmd_tx_rts_set(unsigned char buf_num)
{

    unsigned char cmd[1] = {0};

    if( buf_num > 2)
    {
        return;
    }

    cmd[0] = MCP_SPI_CMD_RTS_TX_BUF | (0x1 << buf_num);

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    cs_unselect();
}

/*
 * status data buffer pointer
 * status data is only 8-bit.
 *
 * read tx/rx interrupt and rts status
 */
unsigned char mcp2515_spi_cmd_quick_status_read(void)
{

    unsigned char cmd[1] = {0};
    unsigned char buf = 0;

    cmd[0] = MCP_SPI_CMD_READ_STATUS;

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    spi_read_blocking(spi_default, 0x00, &buf, 1);
    cs_unselect();

    return buf;
}

/*
 * rx status data buffer pointer
 * rx status data is only 8-bit.
 */
void mcp2515_spi_cmd_quick_rx_status_read(unsigned char* buf)
{

    unsigned char cmd[1] = {0};

    if(buf == NULL)
    {
        return;
    }
    cmd[0] = MCP_SPI_CMD_RX_STATUS;

    cs_select();
    spi_write_blocking(spi_default, (const unsigned char*) cmd, sizeof(cmd));
    spi_read_blocking(spi_default, 0x00, buf, 1);
    cs_unselect();

}



/*
 * wrapper functions using mcp2515 spi command functions
 * configuration
 *  can controller mode
 *  interrupt
 * tx
 *  id
 *  eid
 *  dlc
 *  data
 *  crc
 *  ack/nack
 *  rts
 *  remote frame
 * rx
 *  id
 *  eid
 *  dlc
 *  data
 *  crc
 *  ack/nack
 * error status monitor
 *  active error
 *  passive error
 */

/*
 * For Tx Buffer
 */
unsigned char mcp2515_tx_buf_write(unsigned char buf_num, unsigned char data_only, mcp2515_can_frame_t* frame)
{
    unsigned char packed_data_len = 0;

    if(buf_num > 2)
    {
        return 0;
    }
    if(frame->frame_field.DLC > 8)
    {
        return 0;
    }
    if((frame->frame_field.DLC == 0) && data_only)
    {
        return 0;
    }

    if(!data_only)
    {
        packed_data_len = 5;

        frame->packed_reg[0] = (unsigned char) (frame->frame_field.ID >> 3);
        frame->packed_reg[1] = (unsigned char) ((frame->frame_field.ID & 0x7) << 5);
        if(frame->frame_field.EXIDE)
        {
            frame->packed_reg[1] = frame->packed_reg[1] | 0b00001000;
            frame->packed_reg[1] = frame->packed_reg[1] | (unsigned char)(frame->frame_field.EID >> 16);

            frame->packed_reg[2] = (unsigned char)(frame->frame_field.EID >> 8);
            frame->packed_reg[3] = (unsigned char)(frame->frame_field.EID);
        }

        if(frame->frame_field.RTR)
        {
            frame->packed_reg[4] = 0b01000000;
        }
        else
        {
            frame->packed_reg[4] = frame->frame_field.DLC;
        }
    }

    if(frame->frame_field.DLC)
    {
        packed_data_len = packed_data_len + frame->frame_field.DLC;
        for(unsigned char i = 0; i < frame->frame_field.DLC; i++)
        {
            frame->packed_reg[5 + i] = frame->frame_field.data[i];
        }
    }

    if(data_only)
    {
        return mcp2515_spi_cmd_tx_buf_write(buf_num, &(frame->packed_reg[5]), packed_data_len, data_only);
    }
    return mcp2515_spi_cmd_tx_buf_write(buf_num, &(frame->packed_reg[0]), packed_data_len, data_only);
}


/*
 * For TXBnCTRL
 */

/*
 * buf number
 * status buf
 * rts
 * buf priority
 */
void mcp2515_tx_buf_ctrl_status_get(unsigned char buf_num, unsigned char *reg_status)
{

    unsigned char reg_addr = MCP_TXB0CTRL + (buf_num << 4);

    if(reg_status != NULL)
    {
        mcp2515_spi_cmd_reg_read(reg_addr, reg_status, 1);
    }
}

void mcp2515_tx_buf_ctrl_rts_set(unsigned char buf_num)
{
    unsigned char reg_addr = MCP_TXB0CTRL + (buf_num << 4);
    unsigned char reg_mask = TXBNCTRL_TXREQ;
    unsigned char reg_data = TXBNCTRL_TXREQ;

    mcp2515_spi_cmd_bit_modify(reg_addr, reg_mask, reg_data);
}

void mcp2515_tx_buf_ctrl_rts_clear(unsigned char buf_num)
{
    unsigned char reg_addr = MCP_TXB0CTRL + (buf_num << 4);
    unsigned char reg_mask = TXBNCTRL_TXREQ;
    unsigned char reg_data = 0x00;

    mcp2515_spi_cmd_bit_modify(reg_addr, reg_mask, reg_data);
}

void mcp2515_tx_buf_ctrl_pri_set(unsigned char buf_num, unsigned char buf_pri_set)
{

    unsigned char reg_addr = MCP_TXB0CTRL + (buf_num << 4);
    unsigned char reg_mask = TXBNCTRL_TXP_HIGHEST;

    mcp2515_spi_cmd_bit_modify(reg_addr, reg_mask, buf_pri_set);
}

/*
 * For TXRTSCTRL
 * ONLY modifiable under Configuration Mode.
 *
 * config the rts pin and read status
 * The RTS pin depends on hardware design.
 */
void mcp2515_tx_rts_pin_ctrl()
{
    /* todo with available hardware*/
}

/*
 * For Rx Buffer
 */
unsigned char mcp2515_rx_buf_read(unsigned char buf_num, unsigned char data_only, unsigned char data_len, unsigned char data_len_by_received_DLC, mcp2515_can_frame_t *frame)
{

    unsigned char read_reg_len = 0, read_data_len = 0;
    if(buf_num > 1)
    {
        return 0;
    }
    if(frame == NULL)
    {
        return 0;
    }
    if((data_len > 8) && (!data_len_by_received_DLC))
    {
        return 0;
    }
    if(data_only && data_len_by_received_DLC)
    {
        /* data length must got from DLC
         * if data_only, then we won't get DLC from frame field
         */
        return 0;
    }

    printf("spi cmd rx buf read\n");
    read_reg_len = mcp2515_spi_cmd_rx_buf_read(buf_num, frame->packed_reg, data_len, data_only, data_len_by_received_DLC);

    if(!data_only)
    {
        printf("not data only\n");
        /* parse the register */
        frame->frame_field.ID = ((unsigned short)frame->packed_reg[0]) << 3 | ((unsigned short) (frame->packed_reg[1] >> 5));

        if(frame->packed_reg[1] & 0b00001000)
        {
            frame->frame_field.EXIDE = 1;

            frame->frame_field.EID = ((((unsigned int)frame->packed_reg[1]) & 0x3) << 16) |
                                     (((unsigned int)frame->packed_reg) << 8) |
                                     ((unsigned int)frame->packed_reg);
        }
        if(frame->packed_reg[4] & 0b01000000)
        {
            printf("Frame type = Standard/Extended Remote Frame\n");
            frame->frame_field.RTR = 1;
        }
        else
        {
            printf("Frame type = Standard/Extended Data Frame\n");
            /* & with 0x0F to make sure the DLC is within 4 bits */
            frame->frame_field.DLC = frame->packed_reg[4] & 0x0F;
        }
    }


    if(data_only)
    {
        printf("data only, read_reg_len= %d", read_reg_len);
        if(read_reg_len < 9)
        {
            read_data_len = read_reg_len;
        }
        else
        {
            /* something strange happend */
            return read_reg_len;
        }
    }
    else
    {
        if( (read_reg_len > 5) && (read_reg_len < 14))
        {
            read_data_len = read_reg_len - 5;
        }
        else
        {
            /* something strange happend */
            return read_reg_len;
        }
    }


    /* copy data */
    if(read_data_len)
    {
        printf("data len = %d\n", read_data_len);
        for(unsigned char i = 0; i < read_data_len; i++)
        {
            frame->frame_field.data[i] = frame->packed_reg[5 + i];
        }
    }

    printf("return read rx buf\n");
    return read_reg_len;
}

/*
 * ONLY modifiable under Configuration Mode.
 *
 * For Rx Receive ID Filter
 */
void mcp2515_rx_filter_set(unsigned char filter_num, unsigned char *filter_value_array)
{

    unsigned char reg_addr;

    if(filter_num > 5)
    {
        return;
    }

    if(filter_num < 3)
    {
        reg_addr = MCP_RXF0SIDH + (filter_num << 2);
    }
    else
    {
        reg_addr = MCP_RXF3SIDH + (filter_num << 2);
    }

    /* todo: compose packed filter register by arguments */
    if(filter_value_array != NULL)
    {
        mcp2515_spi_cmd_reg_write(reg_addr, filter_value_array, 4);
    }

}

void mcp2515_rx_filter_get(unsigned char filter_num, unsigned char *filter_value_array)
{

    unsigned char reg_addr;

    if(filter_num > 5)
    {
        return;
    }

    if(filter_num < 3)
    {
        reg_addr = MCP_RXF0SIDH + (filter_num << 2);
    }
    else
    {
        reg_addr = MCP_RXF3SIDH + (filter_num << 2);
    }

    /* todo: parse packed filter register to arguments */
    if(filter_value_array != NULL)
    {
        mcp2515_spi_cmd_reg_read(reg_addr, filter_value_array, 4);
    }

}

/*
 * ONLY modifiable under Configuration Mode.
 *
 * For Rx Receive ID Mask
 */
void mcp2515_rx_mask_set(unsigned char mask_num, unsigned char *mask_value_array)
{

    unsigned char reg_addr;

    if(mask_num > 1)
    {
        return;
    }

    reg_addr = MCP_RXM0SIDH + mask_num;

    /* todo: compose packed register by arguments */
    if(mask_value_array != NULL)
    {
        mcp2515_spi_cmd_reg_write(reg_addr, mask_value_array, 4);
    }

}

void mcp2515_rx_mask_get(unsigned char mask_num, unsigned char *mask_value_array)
{

    unsigned char reg_addr;

    if(mask_num > 1)
    {
        return;
    }

    reg_addr = MCP_RXM0SIDH + mask_num;

    /* todo: parse packed register to arguments */
    if(mask_value_array != NULL)
    {
        mcp2515_spi_cmd_reg_read(reg_addr, mask_value_array, 4);
    }

}

/*
 * RXB0CTRL, RXB1CTRL
 * Just use bit-field map and general register read/write.
 */

/*
 * CNF3, CNF2, CNF1 config register
 * ONLY modifiable under Configuration Mode.
 *
 * Just use bit-field map and general register read/write.
 */

/*
 * CANINTE interrupt register
 * Just use bit-field map and general register read/write.
 */

/*
 * CANINTF interrupt register
 * Just use bit-field map and bit-modify spi command.
 *
 *
 */
void mcp2515_interrupt_flag_modify(unsigned char reg_mask, unsigned char reg_data)
{
    unsigned char reg_addr = MCP_CANINTF;

    mcp2515_spi_cmd_bit_modify(reg_addr, reg_mask, reg_data);
}

/*
 * EFLG error flag register
 * Just use bit-field map and general register read/write.
 */

/*
 * BFPCTRL buffer full pin control
 * Just use bit-field map and general register read/write.
 */

/*
 * TEC, REC
 * Just read by general resigter read.
 */

/*
 * CANSTAT
 */
void mcp2515_can_status_reg_get(unsigned char *reg_status)
{

    unsigned char reg_addr = MCP_CANSTAT;

    if(reg_status != NULL)
    {
        mcp2515_spi_cmd_reg_read(reg_addr, reg_status, 1);
    }
}

/*
 * CANCTRL
 */

void mcp2515_can_ctrl_reg_set(unsigned char reg_mask, unsigned char reg_data)
{
    unsigned char reg_addr = MCP_CANCTRL;

    mcp2515_spi_cmd_bit_modify(reg_addr, reg_mask, reg_data);
}


