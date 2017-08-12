#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ILI93x.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "GUI.h"

//ALIENTEK ̽����STM32F407������ ʵ��37
//�ڴ����ʵ��-�⺯���汾 
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
 
 

int main(void)
{        
	u8 key;		 
 	u8 i=0;	    
	u8 *p=0;
	u8 *tp=0;
	u8 paddr[18];				//���P Addr:+p��ַ��ASCIIֵ
	u8 sramx=0;					//Ĭ��Ϊ�ڲ�sram

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	TFTLCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ�� 
 	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM  
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//����CRCʱ��
	GUI_Init();
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_RED);
	GUI_Clear();
	GUI_SetFont(&GUI_Font24_ASCII);
//	GUI_DispStringAt("Hello World!!!",0,0);
	GUI_DispString("Hello World!!!");


}


