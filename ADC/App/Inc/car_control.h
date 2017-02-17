#ifndef __CAR_CONTROL_H__
#define __CAR_CONTROL_H__



extern int32  incpid;                               //电机PWM误差


extern int16  Stright_Count,Curve_Count,Hill_Count,Stright_short_Count,
        Block_Count,Block_possible_Count[2];



extern int16  Goal_speed_last;
extern int16  Goal_speed;           //目标速度        全局 
extern int32  Goal_MOTO_pwm;  //目标电机占空比  全局 (开环)
extern int32  Now_MOTO_pwm;     //目前电机占空比  全局 
extern int32  MOTO_pwm;          //电机占空比       全局 左 右
extern int16  Speed_P,Speed_I,Speed_D;


extern int16  period;
extern int16  Mid_D_value,D_turn;                     //与中值之差
extern int16  Lose_value;                               //丢线保护值
extern uint32 steer_pwmdty,Turn_Mid;                      //舵机占空比 100000u                     
extern uint32 steer_pwmdty_last;                 //上一次占空比

extern uint16 Encoder_gets;                                 //编码器采集脉冲数    
extern uint16 Now_speed;
extern uint16 Now_speed_last;                     //脉冲数转换速度    

extern void Steer_conter(int32 D_value);
extern void Speed_conter(void);
extern void  Speed_analyse(void); 
extern void PID_conter(void);


extern void BangBangGO(void);
extern void BangBangBack(void);


/****************编码器相关********************/
extern void Encoder_get(void);



#endif