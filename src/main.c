#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

int main()
{

  //Enable GPIO A clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  //Set PA1 as General purpose output
  GPIO_InitTypeDef GPIOA_StructInit = { GPIO_Pin_1, GPIO_Speed_2MHz, GPIO_Mode_Out_OD };
  GPIO_Init(GPIOA, &GPIOA_StructInit);

  volatile unsigned long i = 0;
  while(1)
  {
    //Turn LED ON
    GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
    //Delay
    for( i=0; i<1000000 ;++i );
    //Turn LED OFF
    GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
    //Delay
    for( i=0; i<1000000 ;++i );
  }

  return 0;
}
