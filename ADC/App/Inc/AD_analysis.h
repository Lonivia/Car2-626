#ifndef __AD_ANALYSIS_H__
#define __AD_ANALYSIS_H__


#include "common.h"

extern int16  max_v[7];                                    //�������Сֵ(���ڹ�һ)
extern int32  AD_valu[7];                                  //��һ��ǰADֵ
extern int32  d_value,d_value_last,d_value_err;            //�����ֵ
extern float  AD[7];                                       //��һ����ADֵ (0.1~100)
extern float  AD_sum3,AD_sum3_max,sum_max_v[3];            //��ͬ���ֵ(�����ֵ))
extern int16  ADTX[7],AD_sum3_TX;                          //��һ����ADֵתint16(0~100)



extern int16  AD_MAX_NUM,AD_MAX34;                                  //����б��
extern int16  position,position_last;                //С������λ��(3Ϊ���м�)



extern uint16  Encoder_get_left,Encoder_get_right;                                 //�������ɼ�������        ��  ��
extern uint16  Now_speed,Now_speed_last,Now_speed_left,Now_speed_right;            //������ת���ٶ�     ȫ�� ��  �� 
extern uint32  Ultrasonic_count[6];



extern void AD_max_collect(void);
extern void AD_forward_max_collect(void);
extern void Read_ADC(void);
extern void AD_normalized(void);
extern void d_value_analysis(void);









#endif