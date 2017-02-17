/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,野火科技
 *     All rights reserved.
 *     技术讨论：野火初学论坛 http://www.chuxue123.com
 *
 *     除注明出处外，以下所有内容版权均属野火科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留野火科技的版权声明。
 *
 * @file       Data_out.h
 * @brief      上位机协议头文件
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
/////////////////////虚拟示波器///////////////////////
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

#define REAL_SPEED      0x1d	//实际速度
#define WANT_SPEED      0x1e    //目标速度
#define SERVO           0x1f    //舵机值
///////////wave///////////
#define P1_WAVE1        0x20    //通道1 曲线1
#define P1_WAVE2        0x21
#define P1_WAVE3        0x22
#define P1_WAVE4        0x23
#define P1_WAVE5        0x24
#define P1_WAVE6        0x25
#define P1_WAVE7        0x26
#define P1_WAVE8        0x27
#define P2_WAVE1        0x28    //通道2 曲线1
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
#define SPEED_CT_E      0x0a    //速度控制使能
#define SPEED_CT        0x0b    //速度控制
#define START_CAR       0x0c    //开车
#define STOP_CAR        0x0d    //停车

#define ORDER_MAX       0x3f

extern void Freecale_Send(char index,double value);
extern void Freecale_Re(char index,double value);


#endif
