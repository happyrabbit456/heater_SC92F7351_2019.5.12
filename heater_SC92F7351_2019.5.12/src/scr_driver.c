//Zero Crossing detection
//SCR Driver

#include "Function_Init.H"

//INT24 P20

void Zero_Crossing_EXTI_Test(void);
void Zero_Crossing_EX_Init(void);
void Zero_Crossing_EX2_Handle();

uchar Zero_Crossing_INT1_flag = 0x00;
/*****************************************************
*函数名称：void EXTI_Test(void)
*函数功能：外部中断测试
*入口参数：void
*出口参数：void
*****************************************************/
void Zero_Crossing_EXTI_Test(void)
{
	Zero_Crossing_EX_Init();
	while(1)
	{					
	}
}
/*****************************************************
*函数名称：void EX_Init(void)
*函数功能：外部中断初始化
*入口参数：void
*出口参数：void
*****************************************************/
void Zero_Crossing_EX_Init(void)
{	
	//配置中断口INT24
	P2CON &= 0XFE;     //中断IO口设置为高阻输入
	P2PH  |= 0x01;     //中断IO口设置为高阻带上拉
 
	//INT24上升中断
    //下降沿设置
    INT2F = 0X00 ;    //0000 xxxx  0关闭 1使能
    //上升沿设置
	INT2R = 0X10 ;    //0000 xxxx  0关闭 1使能	
	
	//外部中断优先级设�
	IE1 |= 0x08;	//0000 x000  INT2使能
	IP1 |= 0X00;
	EA = 1;
}

void Zero_Crossing_EX2_Handle()
{
	//如果中断2有两路输入，根据上升沿或者下降沿来确认，上升沿中断，所以端口电平是1
    if(P20 == 1)
    {
        
    }
    if(P21 == 1) //INT25 P21 水流检测计数
    {
        
    }
}
