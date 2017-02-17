#ifndef __CAR_CONTROL_H__
#define __CAR_CONTROL_H__



extern int32  incpid;                               //���PWM���


extern int16  Stright_Count,Curve_Count,Hill_Count,Stright_short_Count,
        Block_Count,Block_possible_Count[2];



extern int16  Goal_speed_last;
extern int16  Goal_speed;           //Ŀ���ٶ�        ȫ�� 
extern int32  Goal_MOTO_pwm;  //Ŀ����ռ�ձ�  ȫ�� (����)
extern int32  Now_MOTO_pwm;     //Ŀǰ���ռ�ձ�  ȫ�� 
extern int32  MOTO_pwm;          //���ռ�ձ�       ȫ�� �� ��
extern int16  Speed_P,Speed_I,Speed_D;


extern int16  period;
extern int16  Mid_D_value,D_turn;                     //����ֵ֮��
extern int16  Lose_value;                               //���߱���ֵ
extern uint32 steer_pwmdty,Turn_Mid;                      //���ռ�ձ� 100000u                     
extern uint32 steer_pwmdty_last;                 //��һ��ռ�ձ�

extern uint16 Encoder_gets;                                 //�������ɼ�������    
extern uint16 Now_speed;
extern uint16 Now_speed_last;                     //������ת���ٶ�    

extern void Steer_conter(int32 D_value);
extern void Speed_conter(void);
extern void  Speed_analyse(void); 
extern void PID_conter(void);


extern void BangBangGO(void);
extern void BangBangBack(void);


/****************���������********************/
extern void Encoder_get(void);



#endif