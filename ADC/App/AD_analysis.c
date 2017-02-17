/*!
 * @file       AD_analysis.c
 * @brief      Ecust_Flying 电感数值处理
 * @author     
 * @version    v1.0
 * @date       2015-04-22
 */
 
#include "common.h"
#include "include.h"
#define   NM    8                                  //NM    8


int16  max_v[7],min_v[7];                           //采最大最小值(用于归一)
int32  AD_valu[7],AD_V[7][NM];                      //归一化前AD值
int32  AD_sum[7];                                   //滑动滤波总值
int16  AD_coe[NM]={5,5,10,10,10,10,20,30};          //加权 {10,10,10,10,10,10,15,25}{1,2,3,5,8,10,20,51}; //学长7个{5,5,10,10,10,10,20,30};
int16  ADTX[7],AD_sum3_TX;                          //归一化后AD值转int16(0~100)


float  AD[7];                                       //归一化后AD值 (0.1~100)
float  AD_sum3,AD_sum3_max,sum_max_v[3];            //不同电感值(和最大值)
float  sensor_to_one[7];                            //归一化值(0.001~1)

int16  AD_MAX_NUM,AD_MAX34;                           //最大电感标号
int16  max=0,max_last=0,max_crosstalk=0;              //最大电感号 
int16  position = 3,position_last = 3;                //小车所在位置(3为正中间)


int32  d_value,d_value_last,d_value_err;             //舵机差值  




void d_value_analysis()
{
           
    Read_ADC();                       //获取AD_value(滤波后)  
    AD_normalized();                  //归一化处理 获取AD[i] 
    AD_sum3 = AD[0]+AD[1]+AD[2];      //电感值总和
    
    
     ADTX[0]=(int16)AD[0],ADTX[1]=(int16)AD[1],ADTX[2]=(int16)AD[2],ADTX[3]=(int16)AD[3]
    ,ADTX[4]=(int16)AD[4];                    
    AD_sum3_TX=(int16)AD_sum3;        //传输值(转int16)
    
    
     if(AD[3]<65&&AD[0]<50&&AD[4]<65)    //AD[1]<60&&AD[4]<60)  AD[3]<50&&AD[1]<50&&AD[4]<50
       max = max_last;    

     if((AD[0]>70))
       max=0;  
     else if (AD[3]>AD[4])
       max=1;
     else max=2;
     max_last=max;
     AD_MAX_NUM = max;                //最大电感标号


    ///////////////////三电感判断小车所在位置//////////////  
/*              *            *            *
      |       AD[2]        AD[0]       AD[1]         |
    P0|   P1          P2           P3          P4    |P5      
*/     
     if((AD_MAX_NUM==2) && (AD[0] <= 60))                 //中线在2号正下方
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
     else if(((AD_MAX_NUM==2 && (AD[0]>60))) || (AD_MAX_NUM==0 && ((AD[2]-AD[0])>1 )))    // 2-0号传感器之间
     {
          position=2;
     }
     else if((AD_MAX_NUM==0 && (AD[1]-AD[2])>1 )||(AD_MAX_NUM==1 && (AD[0]>60 )))         // 0-1号传感器之间
     {
          position=3;
     }

     else if(AD_MAX_NUM==1 && (AD[0]<=60))                //中线在1号正下方  
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
     
     if(abs(position-position_last)>=2)         //弯道时 有时位置会跳变 过渡点的值就会不能储存
     position = position_last;                  //防丢线位置
     position_last = position;                  //储存位置




     
////////////////////得与中心偏差/////////////////////                    d_value -360,+360
       //       4                 3
     //    2            0              1 
     
     
#if 0
     if((AD[1]+AD[2])>60)
       d_value = (int32)((60)/(AD[1] + AD[2]) * 100);
     else if((AD[1] - AD[2])<-60)
       d_value = (int32)((-60)/(AD[0] + AD[2]) * 100);
     else d_value = (int32)((AD[1] - AD[2])/(AD[1] + AD[2]) * 100); 
                        
#else
     if((AD[1]<20)&&(AD[0]<10)&&(AD[2]<20))           //丢线处理   
        d_value=d_value_last;
     
     else if(AD_MAX_NUM==0)     //0号电感最大时  
     {
       d_value = (int32)((AD[1]-AD[2]-10) * 7.0/1.44*1.15/2.5/1.8);  //* 1.0/1.44*1.15 //d_value = (int32)((AD[0] - AD[2]) * 0.8/1.44); 
     }
     else if(AD_MAX_NUM == 2)    //2号电感最大是 用0号电感值算偏差 即舵机应向左打，占空比应减小，d_value应小于0
     {
        d_value = -(int32)((1/(float)(AD[0]+50))*13000-67);   //把67增大，曲线斜率减小  减小13000则曲线初值下降斜率不变
        d_value *=1.78/1.44*1.15*7.0/2.5/1.8;   
     } 
     else if(AD_MAX_NUM == 1)    //1号电感最大时 用0号电感值算偏差 即舵机应向右打，占空比应增大，d_value应大于0
     {
        d_value = (int32)((1/(float)(AD[0]+50))*13000-67);
        d_value *=1.78/1.44*1.15*7.0/2.5/1.8; 
     }
  

     
     /////////////////////直角判断///////////////////
  
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
     
        //直角偏差算法     
     if(Cross_turn_Flag)          //直角处理  
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
*  函数名称   Read_ADC        改一下各电感对应的通道口(adc.h?)
*  功能说明： AD采集
*  参数说明：         
*  函数返回： 无
*  修改时间： 2015-04-22
*  备    注：
*************************************************************************/
void Read_ADC(void)
{
     int16  i,j,k,temp;
     int16  ad_valu[7][5],ad_valu_one[7],ad_sum[7];        //冒泡排序 滤波变量   //ad_valu[7][5],ad_valu_one[7],ad_sum[7]
     
     for(i=0;i<5;i++)
     {
        ad_valu[0][i]=adc_ave(ADC0_SE9,ADC_10bit,5);      // PTB1 通道 2      
        ad_valu[1][i]=adc_ave(ADC1_SE13,ADC_10bit,5);     // PTB7 通道 6        PTB8              
        ad_valu[2][i]=adc_ave(ADC1_SE12,ADC_10bit,5);     // PTB6 通道                      
 
        ad_valu[3][i]=adc_ave(ADC1_SE8,ADC_10bit,5);      // PTB0 通道  4   ADC1_SE12,      // PTB6    ADC1_SE13,      // PTB7
        ad_valu[4][i]=adc_ave(ADC0_SE13,ADC_10bit,5);     // PTB3 通道  1

        ad_valu[5][i]=adc_ave(ADC0_SE12,ADC_10bit,5);     // PTB2 通道                     
        ad_valu[6][i]=adc_ave(ADC1_SE10,ADC_10bit,5);     // PTB4  


     }
  //////////////////////冒泡排序///////////////////////////////////
     for(i=0;i<7;i++)                                                                 //for(i=0;i<7;i++)
     {
        for(j=0;j<4;j++)
        {
           for(k=0;k<4-j;k++)
           {
              if(ad_valu[i][k] > ad_valu[i][k+1])         //前面的比后面的大  则进行交换
              {
                 temp = ad_valu[i][k+1];
                 ad_valu[i][k+1] = ad_valu[i][k];
                 ad_valu[i][k] = temp;
              }
           } 
        }
     }
     for(i=0;i<7;i++)                                      //求中间三项的和(中值滤波) //for(i=0;i<7;i++)
     {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];       
        ad_valu_one[i] = ad_sum[i] / 3;
     }
  ////////////////////////滑动加权滤波/////////////////////////////
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
    
     for(i = 0;i < NM;i ++)          //加权
     {
         AD_sum[0] += AD_V[0][i]*AD_coe[i];
         AD_sum[1] += AD_V[1][i]*AD_coe[i];
         AD_sum[2] += AD_V[2][i]*AD_coe[i];
         AD_sum[3] += AD_V[3][i]*AD_coe[i];
         AD_sum[4] += AD_V[4][i]*AD_coe[i];
         AD_sum[5] += AD_V[5][i]*AD_coe[i]; 
         AD_sum[6] += AD_V[6][i]*AD_coe[i];
     }
     for(i=0;i<7;i++)                //求平均                                        //for(i=0;i<7;i++)
     {
         AD_valu[i] = AD_sum[i] / 100;
         AD_sum[i] = 0;   
     }  
}






/*************************************************************************
*  函数名称   AD_normalized
*  功能说明： 电感数据归一化
*  参数说明：         
*  函数返回： 无
*  修改时间： 2015-04-22
*  备    注：
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
       
       AD[i] = 100 * sensor_to_one[i];     //AD[i]为归一化后的值  范围为0-100
    }       
}








/***********************************************************
*  函数名称   AD_max_collect  
*  功能说明： 最大值采样,
*  参数说明：            
*  函数返回： 无
*  修改时间： 2015-04-23
*  备    注：
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
           DELAY_MS(2);                      //延时	
       }
       flash_erase_sector(SECTOR_ADM);       //擦除254扇区	
       for(i=0; i<5; i++)                 // for(i=0; i<5; i++)
       {
           flash_write(SECTOR_ADM,i*4,(uint32)max_v[i]);     //讲所有参数写入扇区
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
*  函数名称   AD_forward_max_collect
*  功能说明： 竖直最大值采样,
*  参数说明：         
*  函数返回： 无
*  修改时间： 2015-04-23
*  备    注：
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
           DELAY_MS(1);                      //延时	
       }
       flash_erase_sector(SECTOR_ADFM);       //擦除254扇区	
       for(i=0; i<2; i++)
       {
           flash_write(SECTOR_ADFM,i*4,(uint32)max_v[i+5]);     //讲所有参数写入扇区
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











