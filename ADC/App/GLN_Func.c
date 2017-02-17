
#include "common.h"
#include "include.h"

#include "Flying_def.h"

int i,j,max1,max2,max3,max4,min1,min2,min3,min4;
int avg1=0,avg2=0,avg3=0,avg4=0;
    
uint16 var[4];
uint16 caiji1_var[10]={0,0,0,0,0,0,0,0,0,0};
uint16 caiji2_var[10]={0,0,0,0,0,0,0,0,0,0};
uint16 caiji3_var[10]={0,0,0,0,0,0,0,0,0,0};
uint16 caiji4_var[10]={0,0,0,0,0,0,0,0,0,0};

void GLN_ADCfunc(){
        int sum1=0,sum2=0,sum3=0,sum4=0;
    	for(i=0;i<10;i++)
        {
        var[0] = (uint16_t)adc_once(ADC0_SE8,  ADC_16bit);  //var[0]+=1;       
        var[1] = (uint16_t)adc_once(ADC0_SE9,  ADC_16bit);   //var[1]+=1; 
        var[2] = (uint16_t)adc_once(ADC0_SE12, ADC_16bit);   //var[2]+=15;   
        var[3] = (uint16_t)adc_once(ADC0_SE13, ADC_16bit);   //var[3]+=0; 
               
        caiji1_var[i] =var[0];  //取10组存入数组
	caiji2_var[i] =var[1];
	caiji3_var[i] =var[2];
	caiji4_var[i] =var[3];
        
        

        DELAY_MS(50);

    	}
	

        max1=caiji1_var[0];
        min1=caiji1_var[0];
        max2=caiji2_var[0];
        min2=caiji2_var[0];
        max3=caiji3_var[0];
        min3=caiji3_var[0];
        max4=caiji4_var[0];
        min4=caiji4_var[0];
        
        
        for(j=0;j<9;j++)
        {	
            if(caiji1_var[j+1]>max1)
                max1=caiji1_var[j+1];	
            if(caiji1_var[j+1]<min1)
                min1=caiji1_var[j+1];	
				
            if(caiji2_var[j+1]>max2)
                max2=caiji2_var[j+1];	
            if(caiji2_var[j+1]<min2)
                min2=caiji2_var[j+1];	
				
            if(caiji3_var[j+1]>max3)
                max3=caiji3_var[j+1];	
            if(caiji3_var[j+1]<min3)
                min3=caiji3_var[j+1];
				
            if(caiji4_var[j+1]>max4)
                max4=caiji4_var[j+1];	
            if(caiji4_var[j+1]<min4)
                min4=caiji4_var[j+1];	 

            sum1=sum1+caiji1_var[j];
            sum2=sum2+caiji2_var[j];
            sum3=sum3+caiji3_var[j];
            sum4=sum4+caiji4_var[j]; //取出最值，求和
        }
        
        avg1=(sum1-max1-min1)/8;
        avg2=(sum2-max2-min2)/8;
        avg3=(sum3-max3-min3)/8;
        avg4=(sum4-max4-min4)/8;
        
        
}

void GLN_SD5func(){
  /*
        if(avg4>=67&&avg4<=68&&avg1<=65&&avg1>63)        //直线修正              //先左转的情况
        {
           tpm_pwm_duty(SD5_TPM, SD5_CH,24);   //DELAY_MS(10); //24,36 dead
           //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,9);
        }
        if(avg4>=68&&avg1<=63)        //直线修正              //先左转的情况
        {
           tpm_pwm_duty(SD5_TPM, SD5_CH,20);   //DELAY_MS(10); //24,36 dead
           //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,9);
        } 
        if(avg1>63)        //直线修正              //先左转的情况
      
        {
           tpm_pwm_duty(SD5_TPM, SD5_CH,30);   //DELAY_MS(10); //24,36 dead
           //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,9);
        }
  */
  
       if(avg4>1&&avg3>4)   //Turn right
       {
           tpm_pwm_duty(SD5_TPM, SD5_CH,30);   //DELAY_MS(10); //20,39 dead
           //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,9);
       } 
       if(avg4<=1&&avg3<=5)   //Turn right
        {
           tpm_pwm_duty(SD5_TPM, SD5_CH,36);   //DELAY_MS(10); //20,39 dead
           //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,9);
        } 
       if(avg4<=1&&avg3<=1)   //Turn right
        {
           tpm_pwm_duty(SD5_TPM, SD5_CH,42);   //DELAY_MS(10); //20,39 dead
           //tpm_pwm_duty(MOTOR_TPM, MOTOR1_PWM,9);
        } 
       
  
}