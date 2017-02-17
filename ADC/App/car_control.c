/*!
 * @file       car_control.c
 * @brief      Ecust_Flying ���س���
 * @author     JCL
 * @version    v1.0
 * @date       2015-04-23
 */

#include "common.h"
#include "include.h"
   
#include "Flying_def.h"



int16  Mid_D_value = 0,D_turn=0;                     //����ֵ֮��
int16  Lose_value = 0;                               //���߱���ֵ
uint32 steer_pwmdty = TURN_MID,Turn_Mid= TURN_MID;   //���ռ�ձ� 100000u                     
uint32 steer_pwmdty_last = TURN_MID;                 //��һ��ռ�ձ�




int16  Goal_speed;           //Ŀ���ٶ�        ȫ�� 
int16  Goal_speed_last;
int32  Goal_MOTO_pwm;  //Ŀ����ռ�ձ�  ȫ�� (����)
int32  Now_MOTO_pwm;     //Ŀǰ���ռ�ձ�  ȫ�� 
int32  MOTO_pwm;          //���ռ�ձ�       ȫ�� �� ��
int16  Speed_P=180,Speed_I=15,Speed_D=10;
float  speed_p,speed_i,speed_d;
int32  incpid;                               //���PWM���

int16  Err_speed,Err_speed_last,Err_speed_pre;    //�ٶ�PID�洢����  ��


float  angle_p,Angle_P=1;              //���P  D 
float  angle_d,Angle_D=0; 
float  kp=1;
float  kc=0;

uint16  Encoder_gets;                                 //�������ɼ�������    
uint16  Now_speed,Now_speed_last;                     //������ת���ٶ�     ȫ�� ��  �� 
uint32  Ultrasonic_count[6];
uint32  All_Count;



/*************************************************************************
*  ��������   Steer_conter
*  ����˵���� �������
*  ����˵���� steer_pwmdty //������PWM_Dutyֵ
               
*  �������أ� ��
*  �޸�ʱ�䣺 2015-05-17
*  ��    ע��
*************************************************************************/
void  Steer_conter(int32 D_value)
{        
  
            if(D_value<0)
            {led(LED3,LED_OFF);led(LED2,LED_ON);}
            else
            {led(LED2,LED_OFF);led(LED3,LED_ON);}

       
                      
 ////////////////////���P D ȡֵ����////////////////////////
       
       kp=25.0 /(920.0*920.0);                                                   //30 25
                                                                         //1.8       
  if (Stright_Speed>=55)
    
    { if (abs(d_value)>=65)         { kc=2.2;angle_d =20;}                    //2.5
      
      else if(abs(d_value)>=45)    { kc=2.1;angle_d = 20;}
      
      else if(abs(d_value)>=35)    { kc=2.1;angle_d = 20;}
      
      else                         { kc=1.8;angle_d = 20;}
    }
  
  else  if (Stright_Speed>=40)
    
    { if (abs(d_value)>=65)         { kc=2.2;angle_d =20;}                    //2.5
      
      else if(abs(d_value)>=45)    { kc=2.2;angle_d = 20;}
      
      else if(abs(d_value)>=35)    { kc=2.1;angle_d = 20;}
      
      else                         { kc=1.8;angle_d = 20;}
    }
  else if  (Stright_Speed<45)
    {
      if (abs(d_value)>=65)         { kc=2.1;angle_d =20;}                    //2.5
      
      else if(abs(d_value)>=45)    { kc=2.1;angle_d = 20;}
      
      else if(abs(d_value)>=35)    { kc=2.1;angle_d = 20;}
      
      else if(abs(d_value)>=15)    { kc=2.1;angle_d = 20;}
      
      else                        { kc=1.8;angle_d = 15;}
    }

      angle_p=kp*D_value*D_value+kc;
    
      //////////////////////���С���޷�/////////////////////////
       D_turn=(int16)((D_value*angle_p)+(D_value-d_value_last)*angle_d);
       
       //D_turn=D_value;                                                        //(int16)(D_value*angle_p)+((D_value-D_value_last)*angle_d);
       if(D_turn>-Deadband_Steer&&D_turn<Deadband_Steer)                        //����
               D_turn=0;
       else if(D_turn>=Deadband_Steer) D_turn-=Deadband_Steer;
       else    D_turn+=Deadband_Steer;         
      
       
       steer_pwmdty =(uint32)(Turn_Mid+D_turn);
       d_value_last = D_value;      
       if(steer_pwmdty > Turn_Mid + TURN_MAX)        
         steer_pwmdty = Turn_Mid + TURN_MAX;                                    //�������ֵ
       else if(steer_pwmdty < Turn_Mid - TURN_MAX)   
         steer_pwmdty = Turn_Mid - TURN_MAX;                                    //С����Сֵ
       
       Lose_value = steer_pwmdty_last-steer_pwmdty;
       Lose_value = abs(Lose_value);     
       if(Lose_value>(TURN_MAX+450))  steer_pwmdty=steer_pwmdty_last;           //������߱���
       
       Steer_duty(steer_pwmdty);      
       steer_pwmdty_last = steer_pwmdty;
}



/*************************************************************************
*  ��������   Speed_analyse
*  ����˵���� Ŀ���ٶȷ���
*  ����˵����    
*                  
*  �������أ� ��
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/

void  Speed_analyse(void) 
{  
  
  if (Cross_turn_Flag||d_value>42)                { Goal_speed = Speed_Max-(int16)((float)(abs(d_value)*(Speed_Max-Speed_Min)) / 300.0);
                                               if(Goal_speed >= Speed_Max)   Goal_speed = Speed_Max;
                                               if(Goal_speed < Speed_Min)    Goal_speed = Speed_Min; 
                                       }
       
  else if(AD[0]>90&&abs(d_value)<40)   Goal_speed = Stright_Speed;
 
  else                                 Goal_speed= Speed_Max ;
    
  MOTO_pwm=2000 + Goal_speed*15 ;
  
  Goal_speed_last=Goal_speed;
     
}
 

/*************************************************************************
*  ��������   PID_conter
*  ����˵���� ���PID����
*  ����˵���� MOTO_PWM    �����PWM    
*        
*  �������أ� ��
*  �޸�ʱ�䣺 
*  ��    ע��
*************************************************************************/
void PID_conter(void)
{  
      // int16  incpid;                               //���PWM���

       if(Now_speed > 60)                      // �ٶȸ���60 ʱ  
       speed_p = Speed_P+abs(Err_speed)/5;
       else speed_p = Speed_P;
       speed_i = Speed_I/10.0;
       speed_d = Speed_D;
       incpid = (int32)(speed_p * (Err_speed - Err_speed_last) + speed_i * Err_speed + 
                speed_d * (Err_speed + Err_speed_pre - 2 * Err_speed_last));    
      
       Err_speed_pre = Err_speed_last;						  
       Err_speed_last = Err_speed;        //�������
       
       MOTO_pwm += incpid;                     //����ʽ       
       
       
                
       if(MOTO_pwm >5000 )   MOTO_pwm =5000 ;     //  if(MOTO_pwm_left > (Speed_Max*70+2000))   MOTO_pwm_left = (Speed_Max*70+2000);       //PWM ����
       else if(MOTO_pwm <= -3500)  MOTO_pwm = -3500; 
       
       if(MOTO_pwm>=0)                          //����
          {MOTO_GO_dty(MOTO_pwm);     MOTO_BAC_dty(0);}
       else
          {MOTO_BAC_dty(abs(MOTO_pwm));MOTO_GO_dty(0);}
       
       
       
      
     /* if(MOTO_pwm>4000)  MOTO_pwm=4000;
       else if (MOTO_pwm<=-2000) MOTO_pwm=2000;
       
       if(MOTO_pwm>=0)      
       {MOTO_GO_dty(MOTO_pwm);}
       else 
       {MOTO_GO_dty(abs(MOTO_pwm));}  
     */  
                 
}



/*************************************************************************
*  ��������   BangBang
*  ����˵���� ��������
*  ����˵����         
*  �������أ� 
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
void BangBangGO(void)     //��������
{     
     MOTO_GO_dty((Speed_Max*70+2000)); 
     MOTO_BAC_dty(0); 
}
void BangBangBack(void)   //��������
{   
     MOTO_GO_dty(0);      //ռ�ձȸ�ֵСһЩ  ʹPID�л�ƽ�� Ѹ�ټ�����
     MOTO_BAC_dty(3500);
}


/************************************************************************
*  ��������   Speed_conter     1800  40     2000   46   2300  55    2500  60     2700  66  3000  72
*  ����˵���� �ٶ�ȫ�ֿ���(Ŀ���ٶ�&ʵ���ٶ�PID���ƣ���������)
*  ����˵����         
*  �������أ� 
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/

void Speed_conter(void)
{ 
    if (Goal_speed<=Goal_speed_last)
    { MOTO_BAC_dty(1000);}
    else 
    {   MOTO_GO_dty(MOTO_pwm); }                                                                  
}






/*************************************************************************
*  ��������   Encoder_get()
*  ����˵���� �������ɼ�
*  ����˵����         
*  �������أ� ��
*  �޸�ʱ�䣺 2015-04-28
*  ��    ע��
*************************************************************************/

void Encoder_get(void)
{
  Encoder_gets  = abs(ftm_quad_get(FTM1));     //��ȡ������  
  ftm_quad_clean(FTM1);                            //��  ������ 
  

 //////////////������ ת�� ����///////////////////
  Now_speed =  (Encoder_gets +Now_speed_last )/2;          
  Now_speed = (Now_speed_last+Now_speed)/2;       //ƽ���ȶ�
  Now_speed_last      = Now_speed;
  if(All_Count>0xefffffff)
    All_Count=0xefffffff;
  else All_Count+=Now_speed;

}
