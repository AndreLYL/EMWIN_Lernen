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


//ALIENTEK 探索者STM32F407开发板 实验37
//内存管理实验-库函数版本 
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
 
 

int main(void)
{        
	
	delay_init(168);       	//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	//中断分组配置
	uart_init(115200);    	//串口波特率设置
	LED_Init(); 			//LED初始化
	TFTLCD_Init();  		//LCD初始化
	TP_Init();				//触摸屏初始化
	FSMC_SRAM_Init(); 		//SRAM初始化
	TIM3_Int_Init(999,83); 	//1KHZ 定时器3设置为1ms
	
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	my_mem_init(SRAMCCM);		//初始化CCM内存池
	
	TIM4_Int_Init(999,839);  //触摸屏扫描速度,100HZ.
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//开启CRC时钟,否则STEMWIN不能使用
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


