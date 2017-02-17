#ifndef __AD_ANALYSIS_H__
#define __AD_ANALYSIS_H__


#include "common.h"

extern int16  max_v[7];                                    //采最大最小值(用于归一)
extern int32  AD_valu[7];                                  //归一化前AD值
extern int32  d_value,d_value_last,d_value_err;            //舵机差值
extern float  AD[7];                                       //归一化后AD值 (0.1~100)
extern float  AD_sum3,AD_sum3_max,sum_max_v[3];            //不同电感值(和最大值))
extern int16  ADTX[7],AD_sum3_TX;                          //归一化后AD值转int16(0~100)



extern int16  AD_MAX_NUM,AD_MAX34;                                  //最大电感标号
extern int16  position,position_last;                //小车所在位置(3为正中间)



extern uint16  Encoder_get_left,Encoder_get_right;                                 //编码器采集脉冲数        左  右
extern uint16  Now_speed,Now_speed_last,Now_speed_left,Now_speed_right;            //脉冲数转换速度     全局 左  右 
extern uint32  Ultrasonic_count[6];



extern void AD_max_collect(void);
extern void AD_forward_max_collect(void);
extern void Read_ADC(void);
extern void AD_normalized(void);
extern void d_value_analysis(void);









#endif