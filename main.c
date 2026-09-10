/*
 * Copyright (c) 2026 wirelinker
 * SPDX-License-Identifier: MIT License
 */

#include <stdio.h>
//#include <string.h>
#include "pico/stdlib.h"
//#include "pico/binary_info.h"

#include "mcp2515.h"

int main() {


    unsigned char read_buf = 0;
    unsigned char can_message[8] = {'H', 'e', 'l', 'l', 'o', '0', '\n'};
    unsigned char char_stdio = 0;
    unsigned char quick_status = 0;
    unsigned char frame_count = 0;
    mcp2515_can_frame_t sent_frame;
    mcp2515_can_frame_t received_frame;

    stdio_init_all();

    printf("MCP2515 driver start\n");

    mcp2515_init();
    mcp2515_can_status_reg_get(&read_buf);
    printf("MCP2515 status reg = 0b%08b\n", read_buf);

    /* set MCP2515 mode */
    mcp2515_can_ctrl_reg_set(CANCTRL_REQOP_MASK, CANCTRL_REQOP_NORM);

    mcp2515_can_status_reg_get(&read_buf);
    printf("MCP2515 status reg = 0b%08b\n", read_buf);

    /* init sent frame data */
    sent_frame.field.ID = 1;
    sent_frame.field.EXIDE = 0;
    sent_frame.field.EID = 0;
    sent_frame.field.RTR = 0;

    /* copy message into data buffer space */
    for(unsigned char i = 0; i < 8; i++)
    {
        if(can_message[i] != '\n')
        {
            sent_frame.field.data[i] = can_message[i];
        }
        else
        {
            sent_frame.field.DLC = i;
            break;
        }
    }



    /* init received frame data */
    received_frame.field.ID = 1;
    received_frame.field.EXIDE = 0;
    received_frame.field.EID = 0;
    received_frame.field.RTR = 0;
    for(unsigned char j = 0; j < 8; j++)
    {
        received_frame.field.data[j] = 0;
    }


    for(;;)
    {
        sleep_ms(1000);
        char_stdio = stdio_getchar_timeout_us(100000);

        if((unsigned char)char_stdio == 's')
        {
            printf("Send message\n");
            /* send "Hello" to CAN bus. */

            /* add frame_count number into message */
            sent_frame.field.data[5] = frame_count + '0';

            /* increase frame count */
            /* limit (0 <= frame_count <= 9) */
            /* bits match method */
            //if((frame_count & 0xF8) && (frame_count & 0x01))
            //{
            //    frame_count = 0;
            //}
            //else
            //{
            //    frame_count++;
            //}

            /* branchless method */
            unsigned char mask_idx[3] = {0x0F, 0x0F, 0x00};
            unsigned char mask = 0;
            mask = mask_idx[((frame_count & 0x1) | ((frame_count & 0x2) >> 1) | ((frame_count & 0x4) >> 2)) + ((frame_count & 0x8) >> 3)];
            frame_count = (frame_count + 1) & mask;

            mcp2515_tx_buf_write(0, 0, &sent_frame);
            mcp2515_tx_rts_set(0);
        }


        if((unsigned char)char_stdio == 'r')
        {

            printf("Read RX0 buffer\n");
            mcp2515_rx_buf_read(0, 0, 0, 1, &received_frame);

            /* print frame info */
            printf("ID=%d, EXIDE=%d, EID=%d, RTR=%d, DLC=%d\n",
            received_frame.field.ID,
            received_frame.field.EXIDE,
            received_frame.field.EID,
            received_frame.field.RTR,
            received_frame.field.DLC
            );

            /* print received message */
            printf("Data= ");
            for(unsigned char j = 0; j < received_frame.field.DLC; j++)
            {
                printf("%c", received_frame.field.data[j]);
            }
            printf("\n");

        }
        /* check CAN rx buffer, quick read status */
        quick_status = mcp2515_spi_cmd_quick_status_read();
        printf("quick_status=0b%08b\n", quick_status);
        if(quick_status & QUICK_STATUS_RX0IF)
        {
            printf("Got message\n");
            mcp2515_rx_buf_read(0, 0, 0, 1, &received_frame);

            /* print frame info */
            printf("ID=%d, EXIDE=%d, EID=%d, RTR=%d, DLC=%d\n",
            received_frame.field.ID,
            received_frame.field.EXIDE,
            received_frame.field.EID,
            received_frame.field.RTR,
            received_frame.field.DLC
            );

            /* print received message */
            printf("Data= ");
            for(unsigned char j = 0; j < received_frame.field.DLC; j++)
            {
                printf("%c", received_frame.field.data[j]);
            }
            printf("\n");

        }



    }

}


