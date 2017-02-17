/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,野火科技
 *     All rights reserved.
 *     技术讨论：野火初学论坛 http://www.chuxue123.com
 *
 *     除注明出处外，以下所有内容版权均属野火科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留野火科技的版权声明。
 *
 * @file       Data_out.c
 * @brief      上位机发送协议
 * @author     D.Fly
 * @version    v1.0
 * @date       2015-05-26
 */

#include "include.h"

float  OutData[4] = { 0 };
uint32 count[10];
int16  K[8];
 
void Data_out(void)
{
   //////////////////////串口助手///////////////////////
  
     int16 str[100];
   
     str[30]=ADTX[0];str[31]=ADTX[1];str[32]=ADTX[2];
    
     printf("AD=[%d][%d][%d]",str[30],str[31],str[32]);

 
     

    /*/////////////////////飞思卡尔上位机//////////////////////

 
      Freecale_Send(NUM11,ADTX[0]);
      Freecale_Send(NUM12,ADTX[1]);
      Freecale_Send(NUM13,ADTX[2]);
      
  
   Freecale_Send(P1_WAVE1,(double)d_value);
  
    */
                
}













//////////////////////协议///////////////////////


unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++)
		{      
        CRC_Temp ^= Buf[i];//逐位异或  去取反
        for (j=0;j<8;j++) 
				{
            if (CRC_Temp & 0x01)//如果地位为1
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
//     Buf[8] = CRC_Temp & 0x00ff;  //将第9个数据赋上CRC的低字节
//     Buf[9] = CRC_Temp >>8;//第10数据上是CRC的高字节
    return(CRC_Temp);
}

void OutPut_Data(void)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
  {
    
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
  }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
  uart_putchar(UART3,databuf[i]);
}




/*
注意事项：
  1.数据H位会+1，下位机应该对数据H位自减1
  2.包种类第8位为1代表值为负数
  3.包种类第7位为1代表报数据H位为整数部分，数据L位为小数部分
    PC机接收:
        包长度  :  4
        包格式  :  包头	包种类	包数据H	包数据L
                下位机发送：fDebug(SEND1,1234)
                上位机收到：SEND_HEAD SEND1 12 34
*/


unsigned char RTBuf[4];
char order[4];

void Freecale_Send(char index,double value)
{
    if(value < 0)
      index |= 0x80;
    if((int32)value*100%100 != 0)
      index |= 0x40;

    RTBuf[0] = SEND_HEAD;
    RTBuf[1] = index;
    RTBuf[2] = ((int)value/100 + 1);
    RTBuf[3] = ((int)value%100);
    uart_putstr(UART4,RTBuf);
}

void Freecale_Re(char index,double value)
{
  
}
