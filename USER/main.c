#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"
#include "usmart.h"
//ALIENTEKս��STM32������ʵ��34
//FLASHģ��EEPROM ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)	 			  	//���鳤��
#define FLASH_SAVE_ADDR  0X08070000 				//����FLASH �����ַ(����Ϊż��)

 int main(void)
 {	 
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];

	u16 clearFlag = 0x0000;//app run state
	NVIC_SetVectorTable(0X8000000, 0X3000);//�����ж�������
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &clearFlag, 1);//���IAP������־
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	         //��ʼ��LCD
	KEY_Init();	 		 //��ʼ��KEY
		
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART
	 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"FLASH EEPROM TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2012/9/13");  
	LCD_ShowString(60,130,200,16,16,"WK_UP:Write KEY1:Read");
	POINT_COLOR=BLUE;
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	//FLASH_SetLatency(FLASH_ACR_LATENCY_2);	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY_UP)//WK_UP����,д��STM32 FLASH
		{
			LCD_Fill(0,150,239,319,WHITE);//�������    
 			LCD_ShowString(60,150,200,16,16,"Start Write FLASH....");
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
			LCD_ShowString(60,150,200,16,16,"FLASH Write Finished!");//��ʾ�������
		}
		if(key==KEY_DOWN)//KEY1����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(60,150,200,16,16,"Start Read FLASH.... ");
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			LCD_ShowString(60,150,200,16,16,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(60,170,200,16,16,datatemp);//��ʾ�������ַ���
		}
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}   	   
}


