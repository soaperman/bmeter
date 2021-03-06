/**
  ******************************************************************************
  * @file    stm8s_it.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service 
  *          routine.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s_it.h"
#include "yxt.h"
    
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy Interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt, 25)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*_COSMIC_*/

extern volatile unsigned int    sys_tick;
extern unsigned char uart1_buf[16];
extern unsigned char uart1_index;


INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
{
	TIM2_ClearITPendingBit(TIM2_IT_UPDATE);

	sys_tick++;
	// if ( (sys_tick % 1000) == 0 ){
		// //if ( ++bike.Second == 60 )
        // {
			// bike.Second = 0;
			// if ( ++bike.Minute == 60 ){
				// bike.Minute = 0;
				// if ( ++bike.Hour == 12 )
					// bike.Hour = 0;
			// }
		// }
	// }
}

 
/**
  * @brief  Timer1 Capture/Compare Interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
  unsigned int low,period;
  unsigned int duty;
  char PlusCode;
  char checksum;
  char i;
  
  TIM1_ClearITPendingBit(TIM1_IT_CC2);
  
  period 	= TIM1_GetCapture1();
  low  		= TIM1_GetCapture2();
  duty 		= ((unsigned long)low * 100) / period;
  
  YXT_Tim_Receive(duty);
}

/**
  * @brief  UART1 RX Interrupt routine
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
  uint8_t rx;

  /* Read one byte from the receive data register and send it back */
  rx = (UART1_ReceiveData8() & 0x7F);
  uart1_buf[uart1_index++] = rx;
	if ( uart1_index >= sizeof(uart1_buf) )
		uart1_index = 0;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/