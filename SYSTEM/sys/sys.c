#include "sys.h"
/*==================================
* �� �� ��: NVIC_Configuration(void)
* ��    ��: ϵͳ�жϷ������û�
* ��ڲ���:
* ���ڲ���:
* ˵    ��: ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
* ���÷���: 
====================================*/  
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
}
/*===============End================*/
