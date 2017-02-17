#include "common.h"
#include "include.h"

/*#define MOTOR_TPM   FTM0
#define MOTOR1_PWM  FTM_CH3      //PTA6
#define MOTOR_HZ    (10*1000)

  
#define tpm_pwm_duty ftm_pwm_duty*/





/****************�����������********************/
#define  TURN_MID	2700	//�����ֵ	// ����10000u    950  1090    1230  //  ����10,0000u     ��С  9400  9700 10900�м�   12100  12400  �Ҵ� 1150
#define  TURN_MAX	920    //920


/****************������ƶ���********************/
#define  Steer_init()	  ftm_pwm_init(FTM2,FTM_CH0,38000,10000);	   //ת����  50HZ 	PTA12  
#define  Steer_duty(x)	  ftm_pwm_duty(FTM2,FTM_CH0,x);
#define  Deadband_Steer   1




/****************�����������********************/
//����ģʽ: PWM ���� IN �ܽ� ,IO���� INH ��ʹ�� ��
// INH ����Ϊ �ߵ�ƽ ��ʹ�� BTN7971
// IN  ����Ϊ �ߵ�ƽ , ���� �� IN ����Ϊ �͵�ƽ��ɲ����ע�⣬��ɲ�������ǽ�����ô�򵥣�
//����ģʽ �� ��ͣ���٣�INΪ�ߣ���Ȼ����٣�INΪ�ͣ���

#define  MOTO_init()      ftm_pwm_init(FTM0,FTM_CH3,10000,0);\
		          ftm_pwm_init(FTM0,FTM_CH4,10000,0);\
                          gpio_init(PTD15,GPO,0);\
                          gpio_init(PTA19,GPO,0);

//ȫ�ֵ��PWM����
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




/**************************����������******************************/
#define  CODER	  300
#define  PERCM	  50

/*************************�������ɼ�����**************************/
#define Encoder_init()    ftm_quad_init(FTM1);
                         
                          
                                                    

                          
/**************************��������ʼ��*****************************/
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
                          
                          


/******************************FLASH���ݶ���**************************/
#define	SECTOR_NUM	254		        //��������	
#define	SECTOR_TAB	253			//����ģʽ����  ��¼ֱ������ 	 
#define	SECTOR_ADM	252			//AD���ֵ�궨	����
#define	SECTOR_TOP	251			//�����Ǳ궨    ����
#define SECTOR_TURN 	250 			//�����ֵ      ����
#define	SECTOR_ADSM	249			//4��AD�����ֵ�궨	 ����
#define	SECTOR_ADFM	248			//��ֱ������ֵ�궨	 ����




                          
/******************************���뿪������***************************/
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


