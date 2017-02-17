/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       Data_out.h
 * @brief      ��λ��Э��ͷ�ļ�
 * @author     D.Fly
 * @version    v1.0
 * @date       2015-05-26
 */

#ifndef __DATA_OUT_H
#define __DATA_OUT_H

#include "common.h"

extern float OutData[4];
extern uint32 count[10];
extern int16  K[8];

extern void Data_out(void);
extern void Data_received(void);
/////////////////////����ʾ����///////////////////////
extern void OutPut_Data(void);
extern unsigned short CRC_CHECK(uint8 *Buf, uint8 CRC_CNT);


/////////////////////freecale_2013/////////////////////
#define SEND_HEAD       0xfe
#define SEND_EMPTY      0x00
//////////car send//////////
#define NUM1            0x01
#define NUM2            0x02
#define NUM3            0x03
#define NUM4            0x04
#define NUM5            0x05
#define NUM6            0x06
#define NUM7            0x07
#define NUM8            0x08
#define NUM9            0x09
#define NUM10           0x0a
#define NUM11           0x0b
#define NUM12           0x0c
#define NUM13           0x0d
#define NUM14           0x0e
#define NUM15           0x0f

#define ROAD_LEFT       0x10
#define ROAD_RIGHT      0x11
#define ROAD_HEAD       0x12

#define REAL_SPEED      0x1d	//ʵ���ٶ�
#define WANT_SPEED      0x1e    //Ŀ���ٶ�
#define SERVO           0x1f    //���ֵ
///////////wave///////////
#define P1_WAVE1        0x20    //ͨ��1 ����1
#define P1_WAVE2        0x21
#define P1_WAVE3        0x22
#define P1_WAVE4        0x23
#define P1_WAVE5        0x24
#define P1_WAVE6        0x25
#define P1_WAVE7        0x26
#define P1_WAVE8        0x27
#define P2_WAVE1        0x28    //ͨ��2 ����1
#define P2_WAVE2        0x29
#define P2_WAVE3        0x2a
#define P2_WAVE4        0x2b
#define P2_WAVE5        0x2c
#define P2_WAVE6        0x2d
#define P2_WAVE7        0x2e
#define P2_WAVE8        0x2f

#define P1_CLEAN        0x30
#define P2_CLEAN        0x31
//////////host send//////////
#define SEND1           0x01
#define SEND2           0x02
#define SEND3           0x03
#define SEND4           0x04
#define SEND5           0x05
#define SEND6           0x06
#define SEND7           0x07
#define SEND8           0x08
#define SEND9           0x09
#define SPEED_CT_E      0x0a    //�ٶȿ���ʹ��
#define SPEED_CT        0x0b    //�ٶȿ���
#define START_CAR       0x0c    //����
#define STOP_CAR        0x0d    //ͣ��

#define ORDER_MAX       0x3f

extern void Freecale_Send(char index,double value);
extern void Freecale_Re(char index,double value);


#endif
