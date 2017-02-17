#include "common.h"
#include "include.h"

#include "Flying_def.h"


void ADCinit(){

    //adc_init(ADC1_SE16);              //ADC��ʼ��
    adc_init(ADC0_SE8);      // PTB0
    adc_init(ADC0_SE9);      // PTB1
    adc_init(ADC0_SE12);     // PTB2
    adc_init(ADC0_SE13);     // PTB3
    //1234 for BDAC

}

void FTMinit(){
    ftm_pwm_init(FTM0, FTM_CH3,10*1000,20);  //���ռ�ձ�
    ftm_pwm_init(FTM2, FTM_CH0,300,30);     //�����ֵ 30
    
    //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,10);
    //tpm_pwm_duty(FTM2, FTM_CH0,30);
}

void GLN_LEDinit(){
    gpio_init(PTB20,GPO,1);                         //��ʼ��LED0  ����
    gpio_init(PTB21,GPO,1);                         //��ʼ��LED1   ����
}