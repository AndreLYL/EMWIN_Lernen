#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ILI93x.h"
#include "led.h"
#include "sram.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "timer.h"
#include "GUIDemo.h"


//ALIENTEK ̽����STM32F407������ ʵ��37
//�ڴ����ʵ��-�⺯���汾 
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
 
 

int main(void)
{        
	
	delay_init(168);       	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	//�жϷ�������
	uart_init(115200);    	//���ڲ���������
	LED_Init(); 			//LED��ʼ��
	TFTLCD_Init();  		//LCD��ʼ��
	TP_Init();				//��������ʼ��
	FSMC_SRAM_Init(); 		//SRAM��ʼ��
	TIM3_Int_Init(999,83); 	//1KHZ ��ʱ��3����Ϊ1ms
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
	
	TIM4_Int_Init(999,839);  //������ɨ���ٶ�,100HZ.
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//����CRCʱ��,����STEMWIN����ʹ��
//	GUI_Init();
//	GUI_SetBkColor(GUI_BLUE);
//	GUI_SetColor(GUI_RED);
//	GUI_Clear();
//	GUI_SetFont(&GUI_Font24_ASCII);
//	GUI_DispStringAt("Hello World!!!",0,0);
//	GUI_DispString("Hello World!!!");

	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
	GUIDEMO_Main();

	while(1);
}


