/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_it.c
 * @brief      山外K60 平台中断服务函数
 * @author     山外科技
 * @version    v5.0
 * @date       2013-06-26
 */


#include "include.h"

int MOTO_FLAG=1; 
int Gcount=0;
int Curvecount=0;
int FinalCount=0;

void PIT0_IRQHandler(void)
{   
     PIT_Flag_Clear(PIT0);     //清中断标志位
    
    // Encoder_get();            //得到Now_speed
     
     
     //d_value_analysis();
    // Road_analyse();
     //Steer_conter(d_value);
     
     /*
      if(MOTO_FLAG)
      {

        Speed_analyse();
        
        
        MOTO_GO_dty(MOTO_pwm);
          
       }
      
      if(MOTO_FLAG==0){
        FinalCount++;
        
       if(FinalCount>0 && FinalCount<170){
        MOTO_BAC_dty(3000);
      }
      
      if(FinalCount>170){
      
        MOTO_GO_dty(0);
        MOTO_BAC_dty(0);
        
      }
        
      
      }
     */
   
  //  Speed_analyse();
  //  Speed_conter();
  //  MOTO_GO_dty(MOTO_pwm);
    Gcount++;

}

uint32  chaoshengboTime;
uint32  ABDistance;
void PORTD_IRQHandler(){
    uint8  n = 0;    //引脚号
    uint32 flag = PORTD_ISFR;
    PORTD_ISFR  = ~0;                                   //清中断标志位
    n = 5;	
    if(flag & (1<<n))
    {
      if(gpio_get(PTD5) == 1)  //上升沿
      {
          PIT_TCTRL(PIT1) &= ~PIT_TCTRL_TEN_MASK;
          PIT_LDVAL(PIT1) = 0xFFFFFFFF;
          PIT_TCTRL(PIT1) |=  PIT_TCTRL_TEN_MASK;
      }
      else                     //下降沿
      {
          chaoshengboTime = (uint32)((0xFFFFFFFF - PIT_CVAL(PIT1))/36.66666666);
          ABDistance =  chaoshengboTime * 340 / 1000;  //mm
          PIT_TCTRL(PIT1) &= ~PIT_TCTRL_TEN_MASK;
      }
      
    }
}

void PORTC_IRQHandler(){
  
    if(  (gpio_get(PTC1) == 0 || gpio_get(PTC2) == 0)  &&  Gcount>=3000){
      MOTO_FLAG=0;
      MOTO_GO_dty(0);
      

      //MOTO_disable();
    }
  

}


/*************************************************************************
*  函数名称   设置中断函数到中断向量表及使能
*  功能说明： 
*  参数说明：         
*  函数返回： 无
*  修改时间： 2015-05-23
*  备    注：
*************************************************************************/
void All_set_vector_handler(void)
{
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断复位函数为 PIT0_IRQHandler
    
    //set_vector_handler(UART3_RX_TX_VECTORn ,uart3_handler);  //    蓝牙uart3模块
   
    //set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    //设置 PORTE 的中断复位函数为 PORTE_VECTORn  //    NRF24L0 无线模块   
    
    set_vector_handler(PORTD_VECTORn ,PORTD_IRQHandler);    //设置 PORTD 的中断复位函数为 PORTD_VECTORn  //    超声波模块
    
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    //设置 PORTD 的中断复位函数为 PORTD_VECTORn   //    干簧管
    
    /*///////////////设置中断优先级///////////////// 
   
    NVIC_SetPriorityGrouping(4);
    NVIC_SetPriority(UART3_RX_TX_IRQn,1);
    NVIC_SetPriority(PORTE_IRQn,1);
    NVIC_SetPriority(PORTD_IRQn,0);
    NVIC_SetPriority(PORTC_IRQn,0);
    NVIC_SetPriority(PIT0_IRQn,2);*/
}

void ALL_NVIC_EnableIRQ (void)
{
    NVIC_EnableIRQ (PIT0_IRQn);                              //使能PIT0的中断复位函数
    
    //uart_rx_irq_en(UART3);                                   //使能接受与发送 //    蓝牙uart3模块   
    //uart_tx_irq_en(UART3);
    
   //NVIC_EnableIRQ (PORTE_IRQn);                             //使能PORTE 的中断复位函数 //    NRF24L0 无线模块
    
   NVIC_EnableIRQ (PORTD_IRQn);                             //使能PORTD 的中断复位函数//    超声波模块
   
   NVIC_EnableIRQ (PORTC_IRQn);                             //使能PORTC 的中断复位函数  //    干簧管
}
