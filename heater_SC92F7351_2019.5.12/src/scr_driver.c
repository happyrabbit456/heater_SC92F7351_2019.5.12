//Zero Crossing detection
//SCR Driver

#include "Function_Init.H"

//INT24 P20

//HEAT TRA PWM1

void Zero_Crossing_EXTI_Test(void);
void Zero_Crossing_EX_Init(void);
void Zero_Crossing_EX2_Handle();

void Scr_Driver_PWM_Init(void);
void Scr_Driver_PWMInt_Handle();

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
    if(P20 == 1) //INT24 P20 过零检测到零点
    {
        //PWM计数值重置
        Scr_Driver_PWM_Init();
    }
    if(P21 == 1) //INT25 P21 水流检测计数
    {

    }
}


void Scr_Driver_PWM_Init(void)
{
    //50hz 20ms 半个周期10ms 10ms/10=1ms PWM时钟为Fsys/128 187*128/24=997.33 187-1=186
    PWMCON  = 0x16;		//PWM输出到IO，PWM时钟为Fsys/128 HEAT TRA PWM1
    PWMPRD  = 186;		//PWM周期=(186+1)*(1*128/24us)=997.33≈=1ms;
    PWMCFG  = 0x10;		//PWM1输出反向,输出至P01
    PWMDTY1 = 15;     //PWM1的Duty = 15/60 =1/4
    PWMDTYA = 0x00;		//PWM占空比微调寄存器，这里不微调
    PWMCON |= 0x80;     //开启PWM
    IE1 |= 0x02;        //开启PWM中断
    EA = 1;
}

void Scr_Driver_PWMInt_Handle()
{
    //根据出水/进水温度自动调节PWM1的Duty
}
