#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"
#include "usmart.h"

int main(void)
{	 
	u16 i=0;
	u16 clearFlag = 0x0000;  //��־Ϊ����״̬
	NVIC_SetVectorTable(0X8000000, 0X3000);//�����ж�������
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &clearFlag, 1);//���IAP������־
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	 //���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	             //��ʼ��LCD
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART
	   
    printf("\r\n ����:help��ѯָ��\r\n");	
	while(1)
	{
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}   	   
}


