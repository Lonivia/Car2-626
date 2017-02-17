#include "common.h"
#include "include.h"

/*#define MOTOR_TPM   FTM0
#define MOTOR1_PWM  FTM_CH3      //PTA6
#define MOTOR_HZ    (10*1000)

  
#define tpm_pwm_duty ftm_pwm_duty*/





/****************舵机参数配置********************/
#define  TURN_MID	2700	//舵机中值	// 精度10000u    950  1090    1230  //  精度10,0000u     左小  9400  9700 10900中间   12100  12400  右大 1150
#define  TURN_MAX	920    //920


/****************舵机控制定义********************/
#define  Steer_init()	  ftm_pwm_init(FTM2,FTM_CH0,38000,10000);	   //转向舵机  50HZ 	PTA12  
#define  Steer_duty(x)	  ftm_pwm_duty(FTM2,FTM_CH0,x);
#define  Deadband_Steer   1




/****************电机控制配置********************/
//常规模式: PWM 接入 IN 管脚 ,IO控制 INH 来使能 。
// INH 输入为 高电平 ，使能 BTN7971
// IN  输入为 高电平 , 加速 ； IN 输入为 低电平，刹车（注意，是刹车，不是降速那么简单）
//常规模式 是 不停加速（IN为高），然后减速（IN为低），

#define  MOTO_init()      ftm_pwm_init(FTM0,FTM_CH3,10000,0);\
		          ftm_pwm_init(FTM0,FTM_CH4,10000,0);\
                          gpio_init(PTD15,GPO,0);\
                          gpio_init(PTA19,GPO,0);

//全局电机PWM定义
#define MOTO_GO_dty(x)         ftm_pwm_duty(FTM0,FTM_CH3, x);
                               
#define MOTO_BAC_dty(x)        ftm_pwm_duty(FTM0,FTM_CH4, x);
                              
//MOTOR1_IO   PTD15      LEFT_MOTO_GO_dty     FTM0_CH3  PTA6
//MOTOR2_IO   PTA19      LEFT_MOTO_BAC_dty    FTM0_CH3  PTA7    
//MOTOR3_IO   PTA5       RIGHT_MOTO_GO_dty    FTM0_CH3  PTD5 
//MOTOR4_IO   PTA24      RIGHT_MOTO_BAC_dty   FTM0_CH3  PTD6

#define MOTO_enable()	  gpio_init(PTD15,GPO,1);\
                          gpio_init(PTA19,GPO,1);
                         
#define MOTO_disable()	  gpio_init(PTD15,GPO,0);\
                          gpio_init(PTA19,GPO,0);
                         
#define Deadband_moto   2




/**************************编码器线数******************************/
#define  CODER	  300
#define  PERCM	  50

/*************************编码器采集定义**************************/
#define Encoder_init()    ftm_quad_init(FTM1);
                         
                          
                                                    

                          
/**************************传感器初始化*****************************/
//  ADC0_SE8(PTB0)      ADC0_SE9(PTB1)      ADC0_SE12(PTB2)
//          ADC0_SE13(PTB3)         ADC1_SE10(PTB4) 
//          ADC1_SE11(PTB5)         ADC1_SE12(PTB6)

#define Sensor_init()     adc_init(ADC0_SE8); \
                          adc_init(ADC0_SE9); \
                          adc_init(ADC0_SE12); \
                          adc_init(ADC0_SE13); \
                          adc_init(ADC1_SE10); \
                          adc_init(ADC1_SE11); \
                          adc_init(ADC1_SE12);                            
                          
                          


/******************************FLASH数据定义**************************/
#define	SECTOR_NUM	254		        //参数扇区	
#define	SECTOR_TAB	253			//特殊模式起跑  记录直道扇区 	 
#define	SECTOR_ADM	252			//AD最大值标定	扇区
#define	SECTOR_TOP	251			//陀螺仪标定    扇区
#define SECTOR_TURN 	250 			//舵机中值      扇区
#define	SECTOR_ADSM	249			//4个AD和最大值标定	 扇区
#define	SECTOR_ADFM	248			//竖直电感最大值标定	 扇区




                          
/******************************拨码开关配置***************************/
#define  Stir_init()	  gpio_init(PTC8,GPI,1),port_init_NoALT(PTC8,PULLUP );   \
			  gpio_init(PTC9,GPI,1),port_init_NoALT(PTC9,PULLUP );   \
			  gpio_init(PTC10,GPI,1),port_init_NoALT(PTC10,PULLUP );  \
			  gpio_init(PTC11,GPI,1),port_init_NoALT(PTC11,PULLUP );  \
			  gpio_init(PTC12,GPI,1),port_init_NoALT(PTC12,PULLUP );  \
			  gpio_init(PTC13,GPI,1),port_init_NoALT(PTC13,PULLUP );  \
                          gpio_init(PTC14,GPI,1),port_init_NoALT(PTC14,PULLUP );  \
                          gpio_init(PTC15,GPI,1),port_init_NoALT(PTC15,PULLUP );  

#define  K1 		  gpio_get(PTC8)
#define  K2 		  gpio_get(PTC9)
#define  K3 		  gpio_get(PTC10)
#define  K4 		  gpio_get(PTC11)
#define  K5 		  gpio_get(PTC12)
#define  K6 		  gpio_get(PTC13)
#define  K7 		  gpio_get(PTC14)
#define  K8 		  gpio_get(PTC15)


