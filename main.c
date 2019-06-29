#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include <system_stm32f10x.h>



void delay()
{
  for(unsigned int loopIndex = 0; loopIndex < 65000u; loopIndex++)
  {
    for(unsigned int loopIndex2 = 0; loopIndex2 < 10u; loopIndex2++)
    {
    //Do Nothing
    }
  }
}

int main()
{
  //Enable GPIOA Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  //Set up configuration for LED pin which is at PA4
  GPIO_InitTypeDef LD2PinGpioTypeDef;
  LD2PinGpioTypeDef.GPIO_Pin = (1u<<5);
  LD2PinGpioTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
  LD2PinGpioTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
  
  // Initialize PA4
  GPIO_Init(GPIOA, &LD2PinGpioTypeDef);
  
  
  //Initialize PA2 and PA3 for UART function
  LD2PinGpioTypeDef.GPIO_Pin = (GPIO_Pin_2|GPIO_Pin_3);
  LD2PinGpioTypeDef.GPIO_Speed = GPIO_Speed_10MHz;
  LD2PinGpioTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &LD2PinGpioTypeDef);
  
  
  
  //Enable the clock to USART 2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  //Set up USART configurations.
  {
  USART_InitTypeDef usartConfig;
  usartConfig.USART_BaudRate = 115200u;
  usartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usartConfig.USART_Mode = (USART_Mode_Tx | USART_Mode_Rx);
  usartConfig.USART_Parity = USART_Parity_No;
  usartConfig.USART_StopBits = USART_StopBits_1;
  usartConfig.USART_WordLength = USART_WordLength_8b;
  
  USART_Init(USART2, &usartConfig);
  USART_Cmd(USART2, ENABLE);
  }
  
  
  unsigned int counter = 0;
  while(1)
  {
    GPIO_WriteBit(GPIOA, (1u<<5), Bit_SET);
    delay();
    GPIO_WriteBit(GPIOA, (1u<<5), Bit_RESET);
    delay();
    USART_SendData(USART2, counter++);
  }
  
}
