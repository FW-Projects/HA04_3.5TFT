#include "PC_comm_handle.h"
#include "iap.h"
#include "iap_usart.h"

#include "HA01_HANDLE.h"
#include "lcd_handle.h"
PC_DATA_t pc_data;

pc_event_e pc_event = PC_END_EVENT;

static void RecvDataFromPC(PC_DATA_t *pc);
static void WriteDataToPC(PC_DATA_t * pc,
                          uint16_t cmd_1,  uint16_t cmd_2,
                          uint16_t id,     uint16_t data_len,
                          uint16_t data_1, uint16_t data_2,
                          uint16_t data_3, uint16_t data_4,
                          uint16_t data_5);
void pc_event_handle(void);
void send_heartbeat_data(PC_DATA_t * pc, HA01_Handle *this);

extern bool show_direct_currtne_temp_flag;
extern bool show_direct_set_temp_flag;
extern bool show_direct_set_wind_flag;
extern float direct_handle_pid_out;

void pc_comm_handle(void)
{
    static uint16_t time_1 = 0;
    static uint16_t time_2 = 0;

    time_1++;
    time_2++;

    if (time_1 >= 5)
    {
        pc_event_handle();
        time_1 = 0;
    }

    if (time_2 >= 100)
    {
        send_heartbeat_data(&pc_data, &sFWHA01_t);
        time_2 = 0;
    }

    RecvDataFromPC(&pc_data);
	
}

static void RecvDataFromPC(PC_DATA_t *pc)
{
    uint32_t crc_value;
    pc->read_size = usart_receiveData(PC_USART, pc->rx_buff);

    if (pc->read_size == PC_MAX_RECV_SIZE)
    {
        if (PC_CHECK_HEAD(pc->rx_buff[PC_HEAD1], pc->rx_buff[PC_HEAD2]))
        {
            /* crc check */
            memset(pc->check_crc_buff, 0, PC_CRC_BUFF_SIZE);
            convert_data(pc->rx_buff, pc->check_crc_buff, PC_CMD1, PC_DATA5_LEN_L);
            crc_value = crc_block_calculate(pc->check_crc_buff, 4);
            crc_data_reset();

            if (pc->rx_buff[PC_CRC32_1] == ((crc_value >> 24) & 0xff)  &&
                    pc->rx_buff[PC_CRC32_2] == ((crc_value >> 16) & 0xff)  &&
                    pc->rx_buff[PC_CRC32_3] == ((crc_value >> 8)  & 0xff)   &&
                    pc->rx_buff[PC_CRC32_4] == (crc_value & 0xff))
            {
                /* connect PC */
                if (pc->rx_buff[PC_CMD1] == 0x01 && pc->rx_buff[PC_CMD2] == 0x01 && pc->rx_buff[PC_ID_L] == 0x00)
                {
                    pc_event = CONNECT_PC_EVENT;
                }
                /* jump to bootloader */
                else if (pc->rx_buff[PC_CMD1] == PC_FIRMWARE_UPDATE && pc->rx_buff[PC_CMD2] == PC_FIRMWARE_UPDATE_CONNECT
                         && pc->rx_buff[PC_ID_L] == 0x00)
                {
                    pc_event = IAP_EVENT;
                }
                /* other cmd */
                else
                {
                    __NOP();
                }
            }
        }

        pc->read_size = 0;
    }
}


static void WriteDataToPC(PC_DATA_t * pc,
                          uint16_t cmd_1,  uint16_t cmd_2,
                          uint16_t id,     uint16_t data_len,
                          uint16_t data_1, uint16_t data_2,
                          uint16_t data_3, uint16_t data_4,
                          uint16_t data_5)
{
    static uint32_t crc_value;
    pc->tx_buff[PC_HEAD1] = PC_HEAD_1;
    pc->tx_buff[PC_CMD1] = cmd_1;
    pc->tx_buff[PC_CMD2] = cmd_2;
    pc->tx_buff[PC_ID_H] = (uint8_t)((id >> 8) & 0xff);
    pc->tx_buff[PC_ID_L] = (uint8_t)((id & 0XFF));
    pc->tx_buff[PC_DATA_LEN_H] = (uint8_t)((data_len >> 8) & 0xff)	;
    pc->tx_buff[PC_DATA_LEN_L] = (uint8_t)((data_len & 0XFF));
    pc->tx_buff[PC_DATA1_LEN_H] = (uint8_t)((data_1 >> 8) & 0xff);
    pc->tx_buff[PC_DATA1_LEN_L] = (uint8_t)((data_1 & 0XFF));
    pc->tx_buff[PC_DATA2_LEN_H] = (uint8_t)((data_2 >> 8) & 0xff);
    pc->tx_buff[PC_DATA2_LEN_L] = (uint8_t)((data_2 & 0XFF));
    pc->tx_buff[PC_DATA3_LEN_H] = (uint8_t)((data_3 >> 8) & 0xff);
    pc->tx_buff[PC_DATA3_LEN_L] = (uint8_t)((data_3 & 0XFF));
    pc->tx_buff[PC_DATA4_LEN_H] = (uint8_t)((data_4 >> 8) & 0xff);
    pc->tx_buff[PC_DATA4_LEN_L] = (uint8_t)((data_4 & 0XFF));
    pc->tx_buff[PC_DATA5_LEN_H] = (uint8_t)((data_5 >> 8) & 0xff);
    pc->tx_buff[PC_DATA5_LEN_L] = (uint8_t)((data_5 & 0XFF));
    memset(pc->check_crc_buff, 0, PC_CRC_BUFF_SIZE);
    convert_data(pc->tx_buff, pc->check_crc_buff, PC_CMD1, PC_DATA5_LEN_L);
    crc_value = crc_block_calculate(pc->check_crc_buff, 4);
    crc_data_reset();
    pc->tx_buff[PC_CRC32_1] = ((crc_value >> 24) & 0xff);
    pc->tx_buff[PC_CRC32_2] = ((crc_value >> 16) & 0xff);
    pc->tx_buff[PC_CRC32_3] = ((crc_value >> 8) & 0xff);
    pc->tx_buff[PC_CRC32_4] = (crc_value & 0xff);
    pc->tx_buff[PC_HEAD2] = PC_HEAD_2;
    /* send data */
    usart_sendData(PC_USART, pc->tx_buff, PC_MAX_SEND_SIZE);
}

void pc_event_handle(void)
{
	static uint32_t crc_value;
    switch (pc_event)
    {
    case CONNECT_PC_EVENT:
        pc_data.tx_buff[PC_HEAD1] = PC_HEAD_1;
	
        pc_data.tx_buff[PC_CMD1] = 0x01;
        pc_data.tx_buff[PC_CMD2] = 0x01;
	
        pc_data.tx_buff[PC_ID_H] = LOCAL_DEVECE_ID_2;
        pc_data.tx_buff[PC_ID_L] = LOCAL_DEVECE_ID_1;
	
        pc_data.tx_buff[PC_DATA_LEN_H] =  0x00;
        pc_data.tx_buff[PC_DATA_LEN_L] =  0x0A;
	
        pc_data.tx_buff[PC_DATA1_LEN_H] = 0x01;
        pc_data.tx_buff[PC_DATA1_LEN_L] = 0x00;
        pc_data.tx_buff[PC_DATA2_LEN_H] = 0x04;
	
        pc_data.tx_buff[PC_DATA2_LEN_L] = 0x01;
        pc_data.tx_buff[PC_DATA3_LEN_H] = 0x00;
        pc_data.tx_buff[PC_DATA3_LEN_L] = 0x01;
	
        pc_data.tx_buff[PC_DATA4_LEN_H] = 0x00;
        pc_data.tx_buff[PC_DATA4_LEN_L] = 0x00;
		
        pc_data.tx_buff[PC_DATA5_LEN_H] = 0x00;
        pc_data.tx_buff[PC_DATA5_LEN_L] = 0x00;
		
        memset(pc_data.check_crc_buff, 0, PC_CRC_BUFF_SIZE);
        convert_data(pc_data.tx_buff, pc_data.check_crc_buff, PC_CMD1, PC_DATA5_LEN_L);
        crc_value = crc_block_calculate(pc_data.check_crc_buff, 4);
        crc_data_reset();
		
        pc_data.tx_buff[PC_CRC32_1] = ((crc_value >> 24) & 0xff);
        pc_data.tx_buff[PC_CRC32_2] = ((crc_value >> 16) & 0xff);
        pc_data.tx_buff[PC_CRC32_3] = ((crc_value >> 8) & 0xff);
        pc_data.tx_buff[PC_CRC32_4] = (crc_value & 0xff);
        pc_data.tx_buff[PC_HEAD2] = PC_HEAD_2;
		/* send data */
        usart_sendData(PC_USART, pc_data.tx_buff, PC_MAX_SEND_SIZE);
 
        pc_event = PC_END_EVENT;
 
        break;

    case IAP_EVENT:
        pc_event = PC_END_EVENT;
        iap_flag = IAP_REV_FLAG_DONE;
        break;

    case PC_END_EVENT:
        break;
    }
}

void send_heartbeat_data(PC_DATA_t * pc, HA01_Handle *this)
{
    static uint32_t crc_value;
    static uint32_t convert_result;
	
    pc->tx_buff[0]        = PC_HEAD_1;
    pc->tx_buff[1]        = 0x01;
    pc->tx_buff[2]        = 0x02;
    pc->tx_buff[3]        = LOCAL_DEVECE_ID_2;
    pc->tx_buff[4]        = LOCAL_DEVECE_ID_1;
    pc->tx_buff[5]        = 0x00;
    pc->tx_buff[6]        = 0x06;
    pc->tx_buff[7]        = (uint8_t)((((uint32_t)temp_to_display) >> 8) & 0xff);
    pc->tx_buff[8]        = (uint8_t)((((uint32_t)temp_to_display) & 0XFF));
    pc->tx_buff[9]        = (uint8_t)wind_to_display;
    pc->tx_buff[10]       = (uint8_t)this->temp_unit;
    pc->tx_buff[11]       = 0x00;
    pc->tx_buff[12]       = 0x00;
    memset(pc->check_crc_buff, 0, PC_CRC_BUFF_SIZE);
    convert_data(pc->tx_buff, pc->check_crc_buff, 1, 12);
    crc_value = crc_block_calculate(pc->check_crc_buff,3);
    crc_data_reset();
    pc->tx_buff[13] = ((crc_value >> 24) & 0xff);
    pc->tx_buff[14] = ((crc_value >> 16) & 0xff);
    pc->tx_buff[15] = ((crc_value >> 8) & 0xff);
    pc->tx_buff[16] = (crc_value & 0xff);
    pc->tx_buff[17] = PC_HEAD_2;
	 /* send data */
    usart_sendData(PC_USART, pc->tx_buff, 18);
}
    




















