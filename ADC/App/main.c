/*!
 * @file       Gcar_main.c
 * @brief      Ecust_Flying 主控程序 
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
    EnableInterrupts;		    //开总中断    

    
    while(1)
    {      
      //Steer_duty(1780);   //    950  2700中间  1230  左小   右大   1600  1580
      
      // PTB20_OUT=0;
         
      //Data_out();
      //DELAY_MS(5);
       Steer_duty(10000);
      
    }
    
}




/*******************系统初始化函数*******************/
void system_init(void)
{   
    DisableInterrupts;                            //关总中断  防止系统初始化被打断
  
    MOTO_disable();                               //关电机 
    led_init(LED_MAX);                            //核心板LED 初始化
    Sensor_init();                                //传感器AD口初始化
    Stir_init();                                  //拨码开关初始化
    Steer_init();                                 //舵机初始化 
    MOTO_init(); 
    Encoder_init();                                //编码器初始化 FTM1
    flash_init();	                          //初始化flash   
    
    pit_init_us(PIT0,5000);                       //PIT 5MS定时
    
    gpio_init(PTC1,GPI,0);     //干簧管1
    port_init(PTC1, ALT1  | IRQ_EITHER |PULLUP);
    gpio_init(PTC2,GPI,0);     //干簧管2
    port_init(PTC2, ALT1  | IRQ_EITHER |PULLUP);
    gpio_init(PTD5,GPI,0);      //超声波接收模块的DO接口使用PTC  
    port_init(PTD5, ALT1  | IRQ_EITHER |PULLUP);  //   GPIO模式，上下边沿触发，上拉
    pit_init_us(PIT1,36666);   //超声波中断
    
    
   
    DELAY_MS(50);
    Parameter_Adjust();                           //参数调整
    AD_max_collect();                             //采集电感最大值
    AD_forward_max_collect();
    MOTO_enable();      
    //uart_init(UART4,115200);
}  



