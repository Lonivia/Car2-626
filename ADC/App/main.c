/*!
 * @file       Gcar_main.c
 * @brief      Ecust_Flying ���س��� 
 * @author     GLN
 * @version    v1.0
 * @date       2015-04-03
 */

#include "common.h"
#include "include.h"
   
#include "Flying_def.h"
#include "main.h"

void system_init(void);




void main()
{
    system_init();
    
    All_set_vector_handler(); 
    ALL_NVIC_EnableIRQ();
    
    //PTB21_OUT=0;
    led(LED1,LED_OFF);
    led(LED0,LED_OFF);
    DELAY_MS(2000);
    EnableInterrupts;		    //�����ж�    

    
    while(1)
    {      
      //Steer_duty(1780);   //    950  2700�м�  1230  ��С   �Ҵ�   1600  1580
      
      // PTB20_OUT=0;
         
      //Data_out();
      //DELAY_MS(5);
       Steer_duty(10000);
      
    }
    
}




/*******************ϵͳ��ʼ������*******************/
void system_init(void)
{   
    DisableInterrupts;                            //�����ж�  ��ֹϵͳ��ʼ�������
  
    MOTO_disable();                               //�ص�� 
    led_init(LED_MAX);                            //���İ�LED ��ʼ��
    Sensor_init();                                //������AD�ڳ�ʼ��
    Stir_init();                                  //���뿪�س�ʼ��
    Steer_init();                                 //�����ʼ�� 
    MOTO_init(); 
    Encoder_init();                                //��������ʼ�� FTM1
    flash_init();	                          //��ʼ��flash   
    
    pit_init_us(PIT0,5000);                       //PIT 5MS��ʱ
    
    gpio_init(PTC1,GPI,0);     //�ɻɹ�1
    port_init(PTC1, ALT1  | IRQ_EITHER |PULLUP);
    gpio_init(PTC2,GPI,0);     //�ɻɹ�2
    port_init(PTC2, ALT1  | IRQ_EITHER |PULLUP);
    gpio_init(PTD5,GPI,0);      //����������ģ���DO�ӿ�ʹ��PTC  
    port_init(PTD5, ALT1  | IRQ_EITHER |PULLUP);  //   GPIOģʽ�����±��ش���������
    pit_init_us(PIT1,36666);   //�������ж�
    
    
   
    DELAY_MS(50);
    Parameter_Adjust();                           //��������
    AD_max_collect();                             //�ɼ�������ֵ
    AD_forward_max_collect();
    MOTO_enable();      
    //uart_init(UART4,115200);
}  



