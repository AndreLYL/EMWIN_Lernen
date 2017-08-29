#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sram.h"
#include "malloc.h"
#include "ILI93x.h"
#include "led.h"
#include "timer.h"
#include "touch.h"
#include "GUI.h"
#include "GUIDemo.h"
#include "includes.h"
/************************************************
 ALIENTEK ̽����STM32F407������ 
 STemWin STemWin+UCOSII��ֲʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 �������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//START����
//������������ȼ�
#define START_TASK_PRIO				0
//�����ջ��С 
#define START_STK_SIZE			  128
//�����ջ
OS_STK	START_TASK_STK[START_STK_SIZE];
//start_task����
void start_task(void *pdata);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				2
//�����ջ��С
#define TOUCH_STK_SIZE				128
//�����ջ
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *pdata);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				3
//�����ջ��С
#define LED0_STK_SIZE				64
//�����ջ
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *pdata);


//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO			4
//�����ջ��С
#define EMWINDEMO_STK_SIZE			2048
//�����ջ
OS_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwindemo_task(void *pdata);

int main(void)
{
	delay_init(168);       	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//�жϷ�������
	uart_init(115200);    	//���ڲ���������
	TFTLCD_Init();			//��ʼ��LCD
	TP_Init();				//��ʼ��������
	LED_Init();   			//LED��ʼ��
	FSMC_SRAM_Init(); 		//SRAM��ʼ��	
	
	
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
	
	OSInit();  				//��ʼ��UCOS
	OSTaskCreate(start_task,  								//start_task����
				(void*)0,    								//����
				(OS_STK*)&START_TASK_STK[START_STK_SIZE-1], //�����ջջ��
				START_TASK_PRIO);  							//�������ȼ�
	OSStart();  //����UCOS
}

//START����
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//����CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();  			//STemWin��ʼ��
	
	OSStatInit(); 			//��ʼ��ͳ������
	OS_ENTER_CRITICAL();  	//�����ٽ���,�ر��ж�
	
	OSTaskCreate(emwindemo_task,(void*)0,(OS_STK*)&EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE-1],EMWINDEMO_TASK_PRIO);  	//STemWin Demo����				
	OSTaskCreate(touch_task,(void*)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO); 					//����������
	OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO); 						//LED0����
	
	OSTaskSuspend(OS_PRIO_SELF); 	//����start����
	OS_EXIT_CRITICAL();  			//�˳��ٽ���,���ж�					
}

//EMWINDEMO����
void emwindemo_task(void *pdata)
{
	while(1)
	{
		GUIDEMO_Main(); 
	}
}

//TOUCH����
void touch_task(void *pdata)
{
	while(1)
	{
		GUI_TOUCH_Exec();	   
		OSTimeDlyHMSM(0,0,0,5);//��ʱ5ms
	}
}

//LED0����
void led0_task(void *pdata)
{
	while(1)
	{
		LED0 = !LED0;
		OSTimeDlyHMSM(0,0,0,500);//��ʱ500ms
	}
}
