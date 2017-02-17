/*!
 * @file       car_control.c
 * @brief      Ecust_Flying 主控程序
 * @author     JCL
 * @version    v1.0
 * @date       2015-04-23
 */
#include "Flying_def.h"

#include "common.h"
#include "include.h"
   

int16  Speed_table[5][4]=
{
  //低档   
  //直 高 低 坡 
   {72,64,56,73}, //较低速度  
   {70,62,55,73}, //中档速度  
   {58,57,52,73},//中档速度速度  
   {45,45,40,73}, //冲刺速度
   {28,28,25,73} //保底速度     //30  25  20  

};

int16  Speed_Max,Speed_Min,Speed_Ramp,Speed_Block,Stright_Speed,Curve_Speed_Add;

int16  Stright_Flag = 1,Stright_short_Flag = 1,Stright_long_Flag = 1,Stright_Flag_sharpturn = 1,       //直到,急弯,弯道,直角弯标志位
       Curve_Flag=0,Cross_turn_Flag=0,SmallS_Flag=0,Sharpturn_Flag= 0,Cheat_Flag= 0;

int16  Stright_Count,Curve_Count,Hill_Count,Stright_short_Count,
       Block_Count,Block_possible_Count[2];

int16  UPhill_Flag = 0,Dowmhill_Flag=0,Hill_possible_Flag=0,Dowmhill_time;       //坡道标志


/*************************************************************************
*  函数名称   Parameter_Adjust
*  功能说明： 参数调节
*  参数说明：          
*  函数返回： 
*  修改时间：
*  备    注： 
*************************************************************************/
void Parameter_Adjust(void)
{
        if (K3==0)
                   {   Stright_Speed = Speed_table[0][0];
                       Speed_Max     = Speed_table[0][1];
                       Speed_Min     = Speed_table[0][2];
                       Speed_Ramp    = Speed_table[0][3];
                   }

        else if (K4==0)        
                   {   Stright_Speed = Speed_table[1][0];
                       Speed_Max     = Speed_table[1][1];
                       Speed_Min     = Speed_table[1][2];
                       Speed_Ramp    = Speed_table[1][3];
                   }   

        else if (K5==0)
                   {   Stright_Speed = Speed_table[2][0];
                       Speed_Max     = Speed_table[2][1];
                       Speed_Min     = Speed_table[2][2];
                       Speed_Ramp    = Speed_table[2][3];
                   }

        else if (K6==0) 
                   {   Stright_Speed = Speed_table[3][0];
                       Speed_Max     = Speed_table[3][1];
                       Speed_Min     = Speed_table[3][2];
                       Speed_Ramp    = Speed_table[3][3]; 
                   }
        else
                    {  Stright_Speed = Speed_table[4][0];
                       Speed_Max     = Speed_table[4][1];
                       Speed_Min     = Speed_table[4][2];
                       Speed_Ramp    = Speed_table[4][3]; 
                   }
         
  }

/*************************************************************************
*  函数名称   Specialroad_analyse
*  功能说明： 特殊路段分析
*  参数说明：                     
*  函数返回： 无
*  修改时间：
*  备    注：
*************************************************************************/
void Specialroad_analyse(void)
{ 
  
  ;
}



/*************************************************************************
*  函数名称   Path_analyse
*  功能说明： 道路分析
*  参数说明：    
*                  
*  函数返回： 无
*  修改时间：
*  备    注：
*************************************************************************/
void Road_analyse(void)
{
    if(AD_MAX_NUM== 0&&(AD[5]<15&&AD[6]<15))//(position==2||position==3)//()           //偏差小于一定范围 记录编码器脉冲
    {
       Stright_Count += Now_speed;
       if(Stright_short_Flag==0 && Stright_Count>PERCM*18)    //大于15CM判定为短直道
       {
           Stright_short_Flag = 1;   
       }
       
       if(Stright_Flag==0&&Stright_Count>PERCM*35)            //大于35CM判定为直道
       {
           //Stright_Count = 0;
           //Stright_Count = PERCM*40;
           Curve_Flag = 0;
           Stright_Flag = 1;   
       }
       if(Stright_long_Flag==0 && Stright_Count>PERCM*55)     //大于55CM判定为长直道
       {
           Stright_long_Flag = 1;   
       }
       if(Stright_Flag==1) 
       {
         //Stright_Count = PERCM*40;
         Curve_Count = 0;
       }
       if(Stright_long_Flag==1) 
       {
         Stright_Count = PERCM*55;
         Curve_Count = 0;
       }
    }
    else                 
    {   
        Stright_Flag = 0 ;
        Stright_Count= 0 ;
        Stright_short_Flag = 0;
        Stright_long_Flag  = 0;
        Curve_Count += Now_speed;        //记录弯道编码器脉冲数
        if(Curve_Count>PERCM*20)         //20    
        {
          Curve_Flag = 1;
        }
        if(Curve_Flag&&Curve_Count > PERCM*2)        //3cm  1cm/50脉冲
        {
           //Curve_Flag = 1;
           Curve_Count = 0;
           Curve_Speed_Add++;
        }       
   
    } 
    if(Stright_Flag==1||d_value<23)      Curve_Speed_Add=0;                //跟随置0
    if(Stright_long_Flag==1) Stright_Flag_sharpturn = 1;                   //跟随至1 
    if(Curve_Flag  ==1)      Sharpturn_Flag=0,Stright_Flag_sharpturn=0;    //跟随置0
} 
  





