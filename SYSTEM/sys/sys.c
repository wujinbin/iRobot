#include "sys.h"
/*==================================
* 函 数 名: NVIC_Configuration(void)
* 功    能: 系统中断分组设置化
* 入口参数:
* 出口参数:
* 说    明: 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
* 调用方法: 
====================================*/  
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
}
/*===============End================*/
