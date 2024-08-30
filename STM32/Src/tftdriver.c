#include "dac.h"
#include "adc.h"
#include "tim.h"
#include "main.h"
#include "stdio.h"
#include "tftdriver.h"

//*************algorithm****************//
extern uint8_t Row; 							//Row size
extern uint8_t Col;								//Col size
extern uint8_t Kernal_Size;				//Kernal size
extern uint8_t Image_num;					//Image size
extern uint8_t Kernal_num;		  	//Kernal size

//****************data*******************//
extern uint8_t Mnist[][28][28];
extern uint8_t Kernal_P[][3][3];
extern uint8_t Kernal_N[][3][3];

//*************tftdriver****************//
//Scan chip selection
uint8_t SI0=0;
uint8_t SI1=1;
uint8_t SI2=2;
uint8_t SI3=3;
uint8_t SP0=4;
uint8_t SN0=5;
uint8_t SP1=6;
uint8_t SN1=7;
uint8_t SP2=8;
uint8_t SN2=9;
uint8_t SP3=10;
uint8_t SN3=11;


uint8_t	 ErrPin[][2]={
	{12,18}, //0-Ch0
	{50,50}, //1-Ch1
	{50,50}, //2-Ch2
	{50,50}, //3-Ch3
	{50,50}, //4-None
};

uint8_t  ADC_output_size=32;
uint16_t ADCP_output[32];
uint16_t ADCN_output[32];
int16_t  ADC_output[32];


//Basic chips or modules driver
//ADC read P/N, 0~4096 --> 0~3.3V
void ADC_Read(uint8_t P1N0){	   	//Reading range:0~3.3V
	EPRD0_High();
	EPRD1_High();
	ENRD0_High();
	ENRD1_High();
	
	uint16_t ADC_Value;
	for(uint8_t i=0; i<32; i++){ 
		RD_MUX(i);
		if(P1N0==1){
			if(i<16){EPRD0_Low();}
			else		{EPRD1_Low();}
		}else{
			if(i<16){ENRD0_Low();}
			else		{ENRD1_Low();}
		}
		HAL_ADC_Start(&hadc1);
		HAL_ADC_Start(&hadc1);
		ADC_Value=HAL_ADC_GetValue(&hadc1);
			if(P1N0==1){ADCP_output[i]=ADC_Value;}
			else			 {ADCN_output[i]=ADC_Value;}
		
	EPRD0_High();
	EPRD1_High();
	ENRD0_High();
	ENRD1_High();
	}
	
}

//DAC_Write
void DAC_Write(uint8_t voltage){ 	//12bits 16*voltage
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 1545+10*voltage);  // 0~255 >>> 1545(*100)~4095
	HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
}

//DAC_Write16
void DAC_Write16(uint16_t voltage){ 	//12bits 16*voltage
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 1545+10*voltage);  // 0~255 >>> 1545(*100)~4095
	HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
}

//IW_MUX
void IW_MUX(uint8_t num){ 				//delay_sec=1 for Data or weight input, delay_sec=2 for Kernal input
		if(num>=ErrPin[0][0]){
			num=num+1;
		}
		if(num>=(ErrPin[0][1])){
			num=num+1;
		}
		//printf("%d\n",num);
		GPIO_Write(IWA_GPIO_Port, IWA_Pin, num%2);
		GPIO_Write(IWB_GPIO_Port, IWB_Pin, num/2%2);
		GPIO_Write(IWC_GPIO_Port, IWC_Pin, num/4%2);
		GPIO_Write(IWD_GPIO_Port, IWD_Pin, num/8%2);
		if(num<16){
		EIW0_Low();
		delay_us(1);  //1us is needed for writing 0-->5V
		EIW0_High();
		}else{
		EIW1_Low();
		delay_us(1);
		EIW1_High();
		}
}	

//RD_MUX
void RD_MUX(uint8_t num){
		GPIO_Write(RDA_GPIO_Port, RDA_Pin, num%2);
		GPIO_Write(RDB_GPIO_Port, RDB_Pin, num/2%2);
		GPIO_Write(RDC_GPIO_Port, RDC_Pin, num/4%2);
		GPIO_Write(RDD_GPIO_Port, RDD_Pin, num/8%2);
}

//HV66PG driver //Low---Mid---High  1(0)010 ... 1010(31) 
void HV66PG_Write(uint8_t Ch, uint32_t data){
	//Transfering data to shift register
	for(uint8_t i=0; i<32; i++){
		if(Ch<4){GPIO_Write(I_DIN_GPIO_Port, I_DIN_Pin, data%2);}
		else{GPIO_Write(W_DIN_GPIO_Port, W_DIN_Pin, data%2);}
		
		CLK_High();
		data/=2;
		CLK_Low();
	}
	
	//Transfering data from shift register to latch
	if(Ch<4){I_LE_High(); delay_us(1); I_LE_Low();}
	else{W_LE_High(); delay_us(1); W_LE_Low();}
	
	//Output == Scaning for 5us must!
	switch(Ch){
		case 0:{SI0_High();delay_us(5);SI0_Low();}break;	//5us is OK.
		case 1:{SI1_High();delay_us(5);SI1_Low();}break;
		case 2:{SI2_High();delay_us(5);SI2_Low();}break;
		case 3:{SI3_High();delay_us(5);SI3_Low();}break;
		case 4:{SP0_High();delay_us(5);SP0_Low();}break;
		case 5:{SN0_High();delay_us(5);SN0_Low();}break;
		case 6:{SP1_High();delay_us(5);SP1_Low();}break;
		case 7:{SN1_High();delay_us(5);SN1_Low();}break;
		case 8:{SP2_High();delay_us(5);SP2_Low();}break;
		case 9:{SN2_High();delay_us(5);SN2_Low();}break;
		case 10:{SP3_High();delay_us(5);SP3_Low();}break;
		case 11:{SN3_High();delay_us(5);SN3_Low();}break;
		default: break;
	}
}
//Computing element select
void CompCh_select(uint8_t Ch){
	switch(Ch){
		case 0:{VDDc0_High();delay_us(10);}break; //20us is OK.
		case 1:{VDDc1_High();delay_us(10);}break;
		case 2:{VDDc2_High();delay_us(10);}break;
		case 3:{VDDc3_High();delay_us(10);}break;
		default: break;
	}
	
	//ADC read
	ADC_Read(1);
	ADC_Read(0);
	Diff_ADC();
	
	//close Ch
	switch(Ch){
		case 0:{VDDc0_Low();}break;
		case 1:{VDDc1_Low();}break;
		case 2:{VDDc2_Low();}break;
		case 3:{VDDc3_Low();}break;
		default: break;
	}
}

//*****Futher functions*****//
//Data_input
void Data_input8(uint8_t *pArray, uint8_t size){
	for(uint8_t i=0;i<size;i++){
		DAC_Write(pArray[i]);	
		IW_MUX(i);
	}
}

//Data_input
void Data_input16(uint16_t *pArray, uint8_t size){
	for(uint8_t i=0;i<size;i++){
		DAC_Write16(pArray[i]);	
		IW_MUX(i);
	}
}

//Kernel_input
void Kernel_input(uint8_t start_pin, uint8_t size, uint8_t *pArray){
	for(uint8_t i=0;i<size;i++){
		DAC_Write(pArray[i]);
		IW_MUX(i+start_pin);
	}
}
//*****Basic function*****//
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t i){
	(i==1) ? HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET)	:	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}
//Diff_ADC
void Diff_ADC(void){	//Setting the negative value to zero.
	int16_t buff=0;
	for(uint8_t i=0;i<ADC_output_size;i++){
		buff=ADCN_output[i]-ADCP_output[i];
		if(buff>0){ADC_output[i]=buff;}
		else{ADC_output[i]=0;}
		//ADC_output[i]=buff;
	}
}
//ADC_Output_print
void ADC_Output_print(void){
	printf("************\n");
	for(uint8_t i=0;i<ADC_output_size;i++){
		printf("Channel %2d : %4d - %4d - %4d\n",i,ADCP_output[i], ADCN_output[i], ADC_output[i]);
	}
	printf("************\n");
}

