/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_it.c
 * @brief      ɽ��K60 ƽ̨�жϷ�����
 * @author     ɽ��Ƽ�
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
     PIT_Flag_Clear(PIT0);     //���жϱ�־λ
    
    // Encoder_get();            //�õ�Now_speed
     
     
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
    uint8  n = 0;    //���ź�
    uint32 flag = PORTD_ISFR;
    PORTD_ISFR  = ~0;                                   //���жϱ�־λ
    n = 5;	
    if(flag & (1<<n))
    {
      if(gpio_get(PTD5) == 1)  //������
      {
          PIT_TCTRL(PIT1) &= ~PIT_TCTRL_TEN_MASK;
          PIT_LDVAL(PIT1) = 0xFFFFFFFF;
          PIT_TCTRL(PIT1) |=  PIT_TCTRL_TEN_MASK;
      }
      else                     //�½���
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
*  ��������   �����жϺ������ж�������ʹ��
*  ����˵���� 
*  ����˵����         
*  �������أ� ��
*  �޸�ʱ�䣺 2015-05-23
*  ��    ע��
*************************************************************************/
void All_set_vector_handler(void)
{
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϸ�λ����Ϊ PIT0_IRQHandler
    
    //set_vector_handler(UART3_RX_TX_VECTORn ,uart3_handler);  //    ����uart3ģ��
   
    //set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    //���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn  //    NRF24L0 ����ģ��   
    
    set_vector_handler(PORTD_VECTORn ,PORTD_IRQHandler);    //���� PORTD ���жϸ�λ����Ϊ PORTD_VECTORn  //    ������ģ��
    
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    //���� PORTD ���жϸ�λ����Ϊ PORTD_VECTORn   //    �ɻɹ�
    
    /*///////////////�����ж����ȼ�///////////////// 
   
    NVIC_SetPriorityGrouping(4);
    NVIC_SetPriority(UART3_RX_TX_IRQn,1);
    NVIC_SetPriority(PORTE_IRQn,1);
    NVIC_SetPriority(PORTD_IRQn,0);
    NVIC_SetPriority(PORTC_IRQn,0);
    NVIC_SetPriority(PIT0_IRQn,2);*/
}

void ALL_NVIC_EnableIRQ (void)
{
    NVIC_EnableIRQ (PIT0_IRQn);                              //ʹ��PIT0���жϸ�λ����
    
    //uart_rx_irq_en(UART3);                                   //ʹ�ܽ����뷢�� //    ����uart3ģ��   
    //uart_tx_irq_en(UART3);
    
   //NVIC_EnableIRQ (PORTE_IRQn);                             //ʹ��PORTE ���жϸ�λ���� //    NRF24L0 ����ģ��
    
   NVIC_EnableIRQ (PORTD_IRQn);                             //ʹ��PORTD ���жϸ�λ����//    ������ģ��
   
   NVIC_EnableIRQ (PORTC_IRQn);                             //ʹ��PORTC ���жϸ�λ����  //    �ɻɹ�
}
