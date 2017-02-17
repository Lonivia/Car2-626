/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       Data_out.c
 * @brief      ��λ������Э��
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
   //////////////////////��������///////////////////////
  
     int16 str[100];
   
     str[30]=ADTX[0];str[31]=ADTX[1];str[32]=ADTX[2];
    
     printf("AD=[%d][%d][%d]",str[30],str[31],str[32]);

 
     

    /*/////////////////////��˼������λ��//////////////////////

 
      Freecale_Send(NUM11,ADTX[0]);
      Freecale_Send(NUM12,ADTX[1]);
      Freecale_Send(NUM13,ADTX[2]);
      
  
   Freecale_Send(P1_WAVE1,(double)d_value);
  
    */
                
}













//////////////////////Э��///////////////////////


unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++)
		{      
        CRC_Temp ^= Buf[i];//��λ���  ȥȡ��
        for (j=0;j<8;j++) 
				{
            if (CRC_Temp & 0x01)//�����λΪ1
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
//     Buf[8] = CRC_Temp & 0x00ff;  //����9�����ݸ���CRC�ĵ��ֽ�
//     Buf[9] = CRC_Temp >>8;//��10��������CRC�ĸ��ֽ�
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
ע�����
  1.����Hλ��+1����λ��Ӧ�ö�����Hλ�Լ�1
  2.�������8λΪ1����ֵΪ����
  3.�������7λΪ1��������HλΪ�������֣�����LλΪС������
    PC������:
        ������  :  4
        ����ʽ  :  ��ͷ	������	������H	������L
                ��λ�����ͣ�fDebug(SEND1,1234)
                ��λ���յ���SEND_HEAD SEND1 12 34
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
