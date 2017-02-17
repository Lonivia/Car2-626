#ifndef __ROAD_ANALYSIS_H__
#define __ROAD_ANALYSIS_H__

extern int16  Stright_Flag,Stright_Flag_sharpturn,Stright_short_Flag,Stright_long_Flag,Curve_Flag,Cross_turn_Flag,  //直到,急弯,弯道,直角弯标志位
              SmallS_Flag,Sharpturn_Flag,Cheat_Flag;

extern int16  Speed_Max,Speed_Min,Speed_Ramp,Speed_Block,Stright_Speed,Curve_Speed_Add;



extern void Specialroad_analyse(void);
extern void Road_analyse(void);
extern void Parameter_Adjust(void);


#endif