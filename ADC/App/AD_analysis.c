/*!
 * @file       AD_analysis.c
 * @brief      Ecust_Flying �����ֵ����
 * @author     
 * @version    v1.0
 * @date       2015-04-22
 */
 
#include "common.h"
#include "include.h"
#define   NM    8                                  //NM    8


int16  max_v[7],min_v[7];                           //�������Сֵ(���ڹ�һ)
int32  AD_valu[7],AD_V[7][NM];                      //��һ��ǰADֵ
int32  AD_sum[7];                                   //�����˲���ֵ
int16  AD_coe[NM]={5,5,10,10,10,10,20,30};          //��Ȩ {10,10,10,10,10,10,15,25}{1,2,3,5,8,10,20,51}; //ѧ��7��{5,5,10,10,10,10,20,30};
int16  ADTX[7],AD_sum3_TX;                          //��һ����ADֵתint16(0~100)


float  AD[7];                                       //��һ����ADֵ (0.1~100)
float  AD_sum3,AD_sum3_max,sum_max_v[3];            //��ͬ���ֵ(�����ֵ)
float  sensor_to_one[7];                            //��һ��ֵ(0.001~1)

int16  AD_MAX_NUM,AD_MAX34;                           //����б��
int16  max=0,max_last=0,max_crosstalk=0;              //����к� 
int16  position = 3,position_last = 3;                //С������λ��(3Ϊ���м�)


int32  d_value,d_value_last,d_value_err;             //�����ֵ  




void d_value_analysis()
{
           
    Read_ADC();                       //��ȡAD_value(�˲���)  
    AD_normalized();                  //��һ������ ��ȡAD[i] 
    AD_sum3 = AD[0]+AD[1]+AD[2];      //���ֵ�ܺ�
    
    
     ADTX[0]=(int16)AD[0],ADTX[1]=(int16)AD[1],ADTX[2]=(int16)AD[2],ADTX[3]=(int16)AD[3]
    ,ADTX[4]=(int16)AD[4];                    
    AD_sum3_TX=(int16)AD_sum3;        //����ֵ(תint16)
    
    
     if(AD[3]<65&&AD[0]<50&&AD[4]<65)    //AD[1]<60&&AD[4]<60)  AD[3]<50&&AD[1]<50&&AD[4]<50
       max = max_last;    

     if((AD[0]>70))
       max=0;  
     else if (AD[3]>AD[4])
       max=1;
     else max=2;
     max_last=max;
     AD_MAX_NUM = max;                //����б��


    ///////////////////������ж�С������λ��//////////////  
/*              *            *            *
      |       AD[2]        AD[0]       AD[1]         |
    P0|   P1          P2           P3          P4    |P5      
*/     
     if((AD_MAX_NUM==2) && (AD[0] <= 60))                 //������2�����·�
     {
          if(AD[2] <= 50)                       
          {
            position=0;   
          }
          else  if(AD[2] > 50)
          {
            position=1;  
          }                            
     }
     else if(((AD_MAX_NUM==2 && (AD[0]>60))) || (AD_MAX_NUM==0 && ((AD[2]-AD[0])>1 )))    // 2-0�Ŵ�����֮��
     {
          position=2;
     }
     else if((AD_MAX_NUM==0 && (AD[1]-AD[2])>1 )||(AD_MAX_NUM==1 && (AD[0]>60 )))         // 0-1�Ŵ�����֮��
     {
          position=3;
     }

     else if(AD_MAX_NUM==1 && (AD[0]<=60))                //������1�����·�  
     {        
          if(AD[1] <= 50)
          {
            position=5;
          }
          else if(AD[1] > 50)
          {
            position=4;
          }
     }
     
     if(abs(position-position_last)>=2)         //���ʱ ��ʱλ�û����� ���ɵ��ֵ�ͻ᲻�ܴ���
     position = position_last;                  //������λ��
     position_last = position;                  //����λ��




     
////////////////////��������ƫ��/////////////////////                    d_value -360,+360
       //       4                 3
     //    2            0              1 
     
     
#if 0
     if((AD[1]+AD[2])>60)
       d_value = (int32)((60)/(AD[1] + AD[2]) * 100);
     else if((AD[1] - AD[2])<-60)
       d_value = (int32)((-60)/(AD[0] + AD[2]) * 100);
     else d_value = (int32)((AD[1] - AD[2])/(AD[1] + AD[2]) * 100); 
                        
#else
     if((AD[1]<20)&&(AD[0]<10)&&(AD[2]<20))           //���ߴ���   
        d_value=d_value_last;
     
     else if(AD_MAX_NUM==0)     //0�ŵ�����ʱ  
     {
       d_value = (int32)((AD[1]-AD[2]-10) * 7.0/1.44*1.15/2.5/1.8);  //* 1.0/1.44*1.15 //d_value = (int32)((AD[0] - AD[2]) * 0.8/1.44); 
     }
     else if(AD_MAX_NUM == 2)    //2�ŵ������� ��0�ŵ��ֵ��ƫ�� �����Ӧ�����ռ�ձ�Ӧ��С��d_valueӦС��0
     {
        d_value = -(int32)((1/(float)(AD[0]+50))*13000-67);   //��67��������б�ʼ�С  ��С13000�����߳�ֵ�½�б�ʲ���
        d_value *=1.78/1.44*1.15*7.0/2.5/1.8;   
     } 
     else if(AD_MAX_NUM == 1)    //1�ŵ�����ʱ ��0�ŵ��ֵ��ƫ�� �����Ӧ���Ҵ�ռ�ձ�Ӧ����d_valueӦ����0
     {
        d_value = (int32)((1/(float)(AD[0]+50))*13000-67);
        d_value *=1.78/1.44*1.15*7.0/2.5/1.8; 
     }
  

     
     /////////////////////ֱ���ж�///////////////////
  
      if((abs((int)(AD_valu[5]-AD_valu[6]))>14))     //&&(AD[1]<60)&&(AD[2]<60)     30
      {    
         if((AD[1]>95&&AD[3]>95&&AD[0]>50)||(AD[2]>95&&AD[4]>95&&AD[0]>50))
            Cross_turn_Flag=0; 
       /*  else if (AD[1]>AD[2]&&AD[3]>AD[4]&&AD[5]<AD[6])
            Cross_turn_Flag=0;
         else if (AD[1]<AD[2]&&AD[3]<AD[4]&&AD[5]>AD[6])
            Cross_turn_Flag=0;   */
         else                         //80
            Cross_turn_Flag=1;
      } 
      else Cross_turn_Flag=0;
     
        //ֱ��ƫ���㷨     
     if(Cross_turn_Flag)          //ֱ�Ǵ���  
     {
        if(AD[5]>AD[6])
        {d_value = (int32)((1/(float)(AD[0]+50))*13000-67);
        d_value *=1.78/1.44*1.15*7.0/2.5/1.8;}   
        else 
        {d_value = -(int32)((1/(float)(AD[0]+50))*13000-67);
        d_value *=1.78/1.44*1.15*7.0/2.5/1.8;}
     }
    

#endif
     d_value_err = d_value_last-d_value;
     d_value_last = d_value;
        
}




/*************************************************************************
*  ��������   Read_ADC        ��һ�¸���ж�Ӧ��ͨ����(adc.h?)
*  ����˵���� AD�ɼ�
*  ����˵����         
*  �������أ� ��
*  �޸�ʱ�䣺 2015-04-22
*  ��    ע��
*************************************************************************/
void Read_ADC(void)
{
     int16  i,j,k,temp;
     int16  ad_valu[7][5],ad_valu_one[7],ad_sum[7];        //ð������ �˲�����   //ad_valu[7][5],ad_valu_one[7],ad_sum[7]
     
     for(i=0;i<5;i++)
     {
        ad_valu[0][i]=adc_ave(ADC0_SE9,ADC_10bit,5);      // PTB1 ͨ�� 2      
        ad_valu[1][i]=adc_ave(ADC1_SE13,ADC_10bit,5);     // PTB7 ͨ�� 6        PTB8              
        ad_valu[2][i]=adc_ave(ADC1_SE12,ADC_10bit,5);     // PTB6 ͨ��                      
 
        ad_valu[3][i]=adc_ave(ADC1_SE8,ADC_10bit,5);      // PTB0 ͨ��  4   ADC1_SE12,      // PTB6    ADC1_SE13,      // PTB7
        ad_valu[4][i]=adc_ave(ADC0_SE13,ADC_10bit,5);     // PTB3 ͨ��  1

        ad_valu[5][i]=adc_ave(ADC0_SE12,ADC_10bit,5);     // PTB2 ͨ��                     
        ad_valu[6][i]=adc_ave(ADC1_SE10,ADC_10bit,5);     // PTB4  


     }
  //////////////////////ð������///////////////////////////////////
     for(i=0;i<7;i++)                                                                 //for(i=0;i<7;i++)
     {
        for(j=0;j<4;j++)
        {
           for(k=0;k<4-j;k++)
           {
              if(ad_valu[i][k] > ad_valu[i][k+1])         //ǰ��ıȺ���Ĵ�  ����н���
              {
                 temp = ad_valu[i][k+1];
                 ad_valu[i][k+1] = ad_valu[i][k];
                 ad_valu[i][k] = temp;
              }
           } 
        }
     }
     for(i=0;i<7;i++)                                      //���м�����ĺ�(��ֵ�˲�) //for(i=0;i<7;i++)
     {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];       
        ad_valu_one[i] = ad_sum[i] / 3;
     }
  ////////////////////////������Ȩ�˲�/////////////////////////////
     for(i = 0;i < NM-1;i ++)
     {
         AD_V[0][i] = AD_V[0][i + 1];
         AD_V[1][i] = AD_V[1][i + 1];
         AD_V[2][i] = AD_V[2][i + 1];
         AD_V[3][i] = AD_V[3][i + 1];
         AD_V[4][i] = AD_V[4][i + 1];
         AD_V[5][i] = AD_V[5][i + 1];
         AD_V[6][i] = AD_V[6][i + 1];
     }
     for(i=0;i<7;i++)                                   // for(i=0;i<7;i++)
     {
         AD_V[i][NM-1] =  ad_valu_one[i];
     }
    
     for(i = 0;i < NM;i ++)          //��Ȩ
     {
         AD_sum[0] += AD_V[0][i]*AD_coe[i];
         AD_sum[1] += AD_V[1][i]*AD_coe[i];
         AD_sum[2] += AD_V[2][i]*AD_coe[i];
         AD_sum[3] += AD_V[3][i]*AD_coe[i];
         AD_sum[4] += AD_V[4][i]*AD_coe[i];
         AD_sum[5] += AD_V[5][i]*AD_coe[i]; 
         AD_sum[6] += AD_V[6][i]*AD_coe[i];
     }
     for(i=0;i<7;i++)                //��ƽ��                                        //for(i=0;i<7;i++)
     {
         AD_valu[i] = AD_sum[i] / 100;
         AD_sum[i] = 0;   
     }  
}






/*************************************************************************
*  ��������   AD_normalized
*  ����˵���� ������ݹ�һ��
*  ����˵����         
*  �������أ� ��
*  �޸�ʱ�䣺 2015-04-22
*  ��    ע��
*************************************************************************/
void AD_normalized(void)
{   
    int16 i;
      min_v[0]=34;min_v[1]=42;min_v[2]=31;min_v[3]=27;min_v[4]=34;min_v[5]=33;min_v[6]=40;//min_v[0]=46;min_v[1]=53;min_v[2]=45;min_v[3]=47;min_v[4]=49; 
     //max_v[0]=184;max_v[1]=188;max_v[2]=173;max_v[3]=179;max_v[4]=167;//max_v[0]=115;max_v[1]=129;max_v[2]=135;max_v[3]=191;max_v[4]=232;

    for(i=0;i<7;i++)                                                                  // for(i=0;i<7;i++) 
    {
       sensor_to_one[i] = (float)(AD_valu[i] - min_v[i])/(float)(max_v[i] - min_v[i]); 
       if(sensor_to_one[i]<=0.0)  sensor_to_one[i]=0.001;
       if(sensor_to_one[i]>1.0)   sensor_to_one[i]=1.0; 
       
       AD[i] = 100 * sensor_to_one[i];     //AD[i]Ϊ��һ�����ֵ  ��ΧΪ0-100
    }       
}








/***********************************************************
*  ��������   AD_max_collect  
*  ����˵���� ���ֵ����,
*  ����˵����            
*  �������أ� ��
*  �޸�ʱ�䣺 2015-04-23
*  ��    ע��
**************************************************************/
void AD_max_collect(void)
{
   uint16  i,j;
    
   led(LED0,LED_ON); 
                                              
   if(K1==0)
   {   //PTB21_OUT=0; 
       Steer_duty((TURN_MID-TURN_MAX));
       DELAY_MS(100);  
       max_v[0]=max_v[1]=max_v[2]=max_v[3]=max_v[4]=0;     
       for(i=0;i<2000;i++) 
       {
           Read_ADC();       
           for(j=0;j<5;j++)              //for(j=0;j<5;j++)
           { 
               if(AD_valu[j] > max_v[j])  
               max_v[j] = AD_valu[j];
               //DELAY_MS(1);
           } 
           DELAY_MS(2);                      //��ʱ	
       }
       flash_erase_sector(SECTOR_ADM);       //����254����	
       for(i=0; i<5; i++)                 // for(i=0; i<5; i++)
       {
           flash_write(SECTOR_ADM,i*4,(uint32)max_v[i]);     //�����в���д������
       } 
   }
   else 
   {
       for(i=0;i<3;i++)
       {  
          for(j=0;j<5;j++)
          {
             max_v[j] = flash_read(SECTOR_ADM,j*4,uint32);
          }
           DELAY_MS(10);           
       }
   }
}


/***********************************************************
*  ��������   AD_forward_max_collect
*  ����˵���� ��ֱ���ֵ����,
*  ����˵����         
*  �������أ� ��
*  �޸�ʱ�䣺 2015-04-23
*  ��    ע��
**************************************************************/
void AD_forward_max_collect(void)
{
   uint16  i,j;
    
   led(LED1,LED_ON);  
   if(K2==0)
   {   //PTB20_OUT=0; 
       Steer_duty(TURN_MID);
       DELAY_MS(100);  
       for(i=0;i<2000;i++) 
       {
           Read_ADC();       
           for(j=5;j<7;j++)                                                          //for(j=5;j<7;j++) 
           { 
               if(AD_valu[j] > max_v[j])  
               max_v[j] = AD_valu[j];
           } 
           DELAY_MS(1);                      //��ʱ	
       }
       flash_erase_sector(SECTOR_ADFM);       //����254����	
       for(i=0; i<2; i++)
       {
           flash_write(SECTOR_ADFM,i*4,(uint32)max_v[i+5]);     //�����в���д������
       } 
   }
   else 
   {
       for(i=0;i<3;i++)
       { 
          for(j=0;j<2;j++)
          {
             max_v[j+5] = flash_read(SECTOR_ADFM,j*4,uint32);
          }
           DELAY_MS(10);           
       }
   }
}











