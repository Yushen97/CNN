#ifndef __TFTDRIVER_H
#define __TFTDRIVER_H	

#include "stdint.h"
#include "stm32f407xx.h"

//Input
#define IWA_High() 		HAL_GPIO_WritePin(IWA_GPIO_Port, IWA_Pin, GPIO_PIN_SET)
#define IWA_Low() 		HAL_GPIO_WritePin(IWA_GPIO_Port, IWA_Pin, GPIO_PIN_RESET)
#define IWB_High() 		HAL_GPIO_WritePin(IWB_GPIO_Port, IWB_Pin, GPIO_PIN_SET)
#define IWB_Low() 		HAL_GPIO_WritePin(IWB_GPIO_Port, IWB_Pin, GPIO_PIN_RESET)
#define IWC_High() 		HAL_GPIO_WritePin(IWC_GPIO_Port, IWC_Pin, GPIO_PIN_SET)
#define IWC_Low() 		HAL_GPIO_WritePin(IWC_GPIO_Port, IWC_Pin, GPIO_PIN_RESET)
#define IWD_High() 		HAL_GPIO_WritePin(IWD_GPIO_Port, IWD_Pin, GPIO_PIN_SET)
#define IWD_Low() 		HAL_GPIO_WritePin(IWD_GPIO_Port, IWD_Pin, GPIO_PIN_RESET)

#define RDA_High() 		HAL_GPIO_WritePin(RDA_GPIO_Port, RDA_Pin, GPIO_PIN_SET)
#define RDA_Low() 		HAL_GPIO_WritePin(RDA_GPIO_Port, RDA_Pin, GPIO_PIN_RESET)
#define RDB_High() 		HAL_GPIO_WritePin(RDB_GPIO_Port, RDB_Pin, GPIO_PIN_SET)
#define RDB_Low() 		HAL_GPIO_WritePin(RDB_GPIO_Port, RDB_Pin, GPIO_PIN_RESET)
#define RDC_High() 		HAL_GPIO_WritePin(RDC_GPIO_Port, RDC_Pin, GPIO_PIN_SET)
#define RDC_Low() 		HAL_GPIO_WritePin(RDC_GPIO_Port, RDC_Pin, GPIO_PIN_RESET)
#define RDD_High() 		HAL_GPIO_WritePin(RDD_GPIO_Port, RDD_Pin, GPIO_PIN_SET)
#define RDD_Low() 		HAL_GPIO_WritePin(RDD_GPIO_Port, RDD_Pin, GPIO_PIN_RESET)

#define EIW0_High()		HAL_GPIO_WritePin(EIW0_GPIO_Port, EIW0_Pin, GPIO_PIN_SET)
#define EIW0_Low() 		HAL_GPIO_WritePin(EIW0_GPIO_Port, EIW0_Pin, GPIO_PIN_RESET)	
#define EIW1_High()		HAL_GPIO_WritePin(EIW1_GPIO_Port, EIW1_Pin, GPIO_PIN_SET)
#define EIW1_Low() 		HAL_GPIO_WritePin(EIW1_GPIO_Port, EIW1_Pin, GPIO_PIN_RESET)	

#define EPRD0_High()	HAL_GPIO_WritePin(EPRD0_GPIO_Port, EPRD0_Pin, GPIO_PIN_SET)
#define EPRD0_Low() 	HAL_GPIO_WritePin(EPRD0_GPIO_Port, EPRD0_Pin, GPIO_PIN_RESET)	
#define EPRD1_High()	HAL_GPIO_WritePin(EPRD1_GPIO_Port, EPRD1_Pin, GPIO_PIN_SET)
#define EPRD1_Low() 	HAL_GPIO_WritePin(EPRD1_GPIO_Port, EPRD1_Pin, GPIO_PIN_RESET)

#define ENRD0_High()	HAL_GPIO_WritePin(ENRD0_GPIO_Port, ENRD0_Pin, GPIO_PIN_SET)
#define ENRD0_Low() 	HAL_GPIO_WritePin(ENRD0_GPIO_Port, ENRD0_Pin, GPIO_PIN_RESET)	
#define ENRD1_High()	HAL_GPIO_WritePin(ENRD1_GPIO_Port, ENRD1_Pin, GPIO_PIN_SET)
#define ENRD1_Low() 	HAL_GPIO_WritePin(ENRD1_GPIO_Port, ENRD1_Pin, GPIO_PIN_RESET)

#define SP0_High()		HAL_GPIO_WritePin(SP0_GPIO_Port, SP0_Pin, GPIO_PIN_SET)
#define SP0_Low()			HAL_GPIO_WritePin(SP0_GPIO_Port, SP0_Pin, GPIO_PIN_RESET)
#define SP1_High()		HAL_GPIO_WritePin(SP1_GPIO_Port, SP1_Pin, GPIO_PIN_SET)
#define SP1_Low()			HAL_GPIO_WritePin(SP1_GPIO_Port, SP1_Pin, GPIO_PIN_RESET)
#define SP2_High()		HAL_GPIO_WritePin(SP2_GPIO_Port, SP2_Pin, GPIO_PIN_SET)
#define SP2_Low()			HAL_GPIO_WritePin(SP2_GPIO_Port, SP2_Pin, GPIO_PIN_RESET)
#define SP3_High()		HAL_GPIO_WritePin(SP3_GPIO_Port, SP3_Pin, GPIO_PIN_SET)
#define SP3_Low()			HAL_GPIO_WritePin(SP3_GPIO_Port, SP3_Pin, GPIO_PIN_RESET)

#define SN0_High() 		HAL_GPIO_WritePin(SN0_GPIO_Port, SN0_Pin, GPIO_PIN_SET)	
#define SN0_Low() 		HAL_GPIO_WritePin(SN0_GPIO_Port, SN0_Pin, GPIO_PIN_RESET)	
#define SN1_High() 		HAL_GPIO_WritePin(SN1_GPIO_Port, SN1_Pin, GPIO_PIN_SET)	
#define SN1_Low() 		HAL_GPIO_WritePin(SN1_GPIO_Port, SN1_Pin, GPIO_PIN_RESET)	
#define SN2_High() 		HAL_GPIO_WritePin(SN2_GPIO_Port, SN2_Pin, GPIO_PIN_SET)
#define SN2_Low() 		HAL_GPIO_WritePin(SN2_GPIO_Port, SN2_Pin, GPIO_PIN_RESET)
#define SN3_High() 		HAL_GPIO_WritePin(SN3_GPIO_Port, SN3_Pin, GPIO_PIN_SET)
#define SN3_Low() 		HAL_GPIO_WritePin(SN3_GPIO_Port, SN3_Pin, GPIO_PIN_RESET)	

#define SI0_High()		HAL_GPIO_WritePin(SI0_GPIO_Port, SI0_Pin, GPIO_PIN_SET)
#define SI0_Low() 		HAL_GPIO_WritePin(SI0_GPIO_Port, SI0_Pin, GPIO_PIN_RESET)
#define SI1_High()		HAL_GPIO_WritePin(SI1_GPIO_Port, SI1_Pin, GPIO_PIN_SET)
#define SI1_Low() 		HAL_GPIO_WritePin(SI1_GPIO_Port, SI1_Pin, GPIO_PIN_RESET)	
#define SI2_High()		HAL_GPIO_WritePin(SI2_GPIO_Port, SI2_Pin, GPIO_PIN_SET)
#define SI2_Low() 		HAL_GPIO_WritePin(SI2_GPIO_Port, SI2_Pin, GPIO_PIN_RESET)	
#define SI3_High()		HAL_GPIO_WritePin(SI3_GPIO_Port, SI3_Pin, GPIO_PIN_SET)
#define SI3_Low() 		HAL_GPIO_WritePin(SI3_GPIO_Port, SI3_Pin, GPIO_PIN_RESET)

#define W_DIN_High()	HAL_GPIO_WritePin(W_DIN_GPIO_Port, W_DIN_Pin, GPIO_PIN_SET)
#define W_DIN_Low() 	HAL_GPIO_WritePin(W_DIN_GPIO_Port, W_DIN_Pin, GPIO_PIN_RESET)
#define I_DIN_High()	HAL_GPIO_WritePin(I_DIN_GPIO_Port, I_DIN_Pin, GPIO_PIN_SET)
#define I_DIN_Low() 	HAL_GPIO_WritePin(I_DIN_GPIO_Port, I_DIN_Pin, GPIO_PIN_RESET)
#define W_LE_High()		HAL_GPIO_WritePin(W_LE_GPIO_Port, W_LE_Pin, GPIO_PIN_SET)
#define W_LE_Low()		HAL_GPIO_WritePin(W_LE_GPIO_Port, W_LE_Pin, GPIO_PIN_RESET)
#define I_LE_High()		HAL_GPIO_WritePin(I_LE_GPIO_Port, I_LE_Pin, GPIO_PIN_SET)
#define I_LE_Low()		HAL_GPIO_WritePin(I_LE_GPIO_Port, I_LE_Pin, GPIO_PIN_RESET)

#define CLK_High()		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define CLK_Low()			HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)

#define VDDc0_High()	HAL_GPIO_WritePin(VDDc0_GPIO_Port, VDDc0_Pin, GPIO_PIN_SET)
#define VDDc0_Low()		HAL_GPIO_WritePin(VDDc0_GPIO_Port, VDDc0_Pin, GPIO_PIN_RESET)
#define VDDc1_High()	HAL_GPIO_WritePin(VDDc1_GPIO_Port, VDDc1_Pin, GPIO_PIN_SET)
#define VDDc1_Low()		HAL_GPIO_WritePin(VDDc1_GPIO_Port, VDDc1_Pin, GPIO_PIN_RESET)
#define VDDc2_High()	HAL_GPIO_WritePin(VDDc2_GPIO_Port, VDDc2_Pin, GPIO_PIN_SET)
#define VDDc2_Low()		HAL_GPIO_WritePin(VDDc2_GPIO_Port, VDDc2_Pin, GPIO_PIN_RESET)
#define VDDc3_High()	HAL_GPIO_WritePin(VDDc3_GPIO_Port, VDDc3_Pin, GPIO_PIN_SET)
#define VDDc3_Low()		HAL_GPIO_WritePin(VDDc3_GPIO_Port, VDDc3_Pin, GPIO_PIN_RESET)



//*****Basic chips or modules driver*****//
//ADC
void ADC_Read(uint8_t P1N0);									  //------OK
//DAC                                           
void DAC_Write(uint8_t voltage);							  //------OK
void DAC_Write16(uint16_t voltage);							//------OK
//IW_MUX                                        
void IW_MUX(uint8_t num);											  //------OK
//RD_MUX                                        
void RD_MUX(uint8_t num);											  //------OK
//HV66PG driver                                 
void HV66PG_Write(uint8_t Ch, uint32_t data);	  //------OK
//Computing element select                      
void CompCh_select(uint8_t Ch);								  //------OK	
																							  
//*****Futher functions*****//
//Data_input
void Data_input8(uint8_t *pArray, uint8_t size);		//------OK
void Data_input16(uint16_t *pArray, uint8_t size); 	//------OK

//Kernel_input
void Kernel_input(uint8_t start_pin, uint8_t size, uint8_t *pArray);	//------OK

//*****Basic function*****//
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t i);		//------OK
void Diff_ADC(void);																									//------OK
void ADC_Output_print(void);																					//------OK
#endif	
