uint8_t switchMode = 0; // 0 = OFF, 1 = ON
uint32_t pMillis;
uint32_t Value1 = 0;
uint32_t Value2 = 0;
uint16_t Distance = 0;
uint8_t segmentNumber[11] = { // Segment numbers stored in the array as binary
 0x3f, // 0
 0x06, // 1
 0x5b, // 2
 0x4f, // 3
 0x66, // 4
 0x6d, // 5
 0x7d, // 6
 0x07, // 7
 0x7f, // 8
 0x67, // 9
0x40 // -
};
void SevenSegmentConf(uint8_t number)
{
HAL_GPIO_WritePin(m_DisplayA_GPIO_Port, m_DisplayA_Pin, ((number>>0)&0x01));
HAL_GPIO_WritePin(m_DisplayB_GPIO_Port, m_DisplayB_Pin, ((number>>1)&0x01));
HAL_GPIO_WritePin(m_DisplayC_GPIO_Port, m_DisplayC_Pin, ((number>>2)&0x01));
HAL_GPIO_WritePin(m_DisplayD_GPIO_Port, m_DisplayD_Pin, ((number>>3)&0x01));
HAL_GPIO_WritePin(m_DisplayE_GPIO_Port, m_DisplayE_Pin, ((number>>4)&0x01));
HAL_GPIO_WritePin(m_DisplayF_GPIO_Port, m_DisplayF_Pin, ((number>>5)&0x01));
HAL_GPIO_WritePin(m_DisplayG_GPIO_Port, m_DisplayG_Pin, ((number>>6)&0x01));
}
while (1)
 {
 /* USER CODE END WHILE */
 /* USER CODE BEGIN 3 */
 if(HAL_GPIO_ReadPin(m_Button_GPIO_Port, m_Button_Pin) == GPIO_PIN_RESET)
 {
 HAL_Delay(50);
 switchMode = (switchMode == 0) ? 1 : 0;
 HAL_GPIO_WritePin(m_GreenLed_GPIO_Port, m_GreenLed_Pin, switchMode);
 if(switchMode == 0){
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_RESET);
 SevenSegmentConf(segmentNumber[10]);
 }
 HAL_Delay(400);
 }
 if(switchMode == 1)
 {
 HAL_GPIO_WritePin(m_SensorTrig_GPIO_Port, m_SensorTrig_Pin, GPIO_PIN_SET);
 __HAL_TIM_SET_COUNTER(&htim1, 0);
 while (__HAL_TIM_GET_COUNTER (&htim1) < 10);
 HAL_GPIO_WritePin(m_SensorTrig_GPIO_Port, m_SensorTrig_Pin, GPIO_PIN_RESET);
 pMillis = HAL_GetTick();
 while (!(HAL_GPIO_ReadPin (m_SensorEcho_GPIO_Port, m_SensorEcho_Pin)) && pMillis + 10 > 
HAL_GetTick());
 Value1 = __HAL_TIM_GET_COUNTER (&htim1);
 pMillis = HAL_GetTick();
 while ((HAL_GPIO_ReadPin (m_SensorEcho_GPIO_Port, m_SensorEcho_Pin)) && pMillis + 50 > 
HAL_GetTick());
 Value2 = __HAL_TIM_GET_COUNTER (&htim1);
 Distance = (Value2-Value1)* 0.034/2;
 HAL_Delay(50);
 if(Distance > 9){
 Distance = 10;
 }
 SevenSegmentConf(segmentNumber[Distance]);
 if(Distance > 9){
 //SevenSegmentConf(segmentNumber[10]);
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_RESET);
 }
 else if(Distance < 3){
 //SevenSegmentConf(segmentNumber[Distance]);
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_RESET);
 HAL_Delay(100);
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_SET);
 }
 else if(Distance >= 7 && Distance <= 9){
 //SevenSegmentConf(segmentNumber[Distance]);
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_RESET);
 }
 else if(Distance >= 5 && Distance <= 7){
 //SevenSegmentConf(segmentNumber[Distance]);
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_RESET);
 }
 else if(Distance >= 3 && Distance <= 5){
 //SevenSegmentConf(segmentNumber[Distance]);
 HAL_GPIO_WritePin(m_RedLed1_GPIO_Port, m_RedLed1_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed2_GPIO_Port, m_RedLed2_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(m_RedLed3_GPIO_Port, m_RedLed3_Pin, GPIO_PIN_SET);
 }
 if(Distance >= 3 && Distance <= 9){
 int delay = Distance * 75;
 HAL_GPIO_TogglePin(m_Buzzer_GPIO_Port, m_Buzzer_Pin);
 HAL_Delay(delay);
 }
 else if(Distance <= 3){
 HAL_GPIO_WritePin(m_Buzzer_GPIO_Port, m_Buzzer_Pin, GPIO_PIN_SET);
 }
 }
 }
