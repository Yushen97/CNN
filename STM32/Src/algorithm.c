#include "tim.h"
#include "data.h"
#include "main.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "tftdriver.h"
#include "algorithm.h"

//*************tftdrive****************//
extern uint8_t ADC_output_size;
extern uint16_t ADCP_output[32];
extern uint16_t ADCN_output[32];
extern int16_t ADC_output[32];

//*************tftdriver****************//
extern uint8_t SI0;
extern uint8_t SI1;
extern uint8_t SI2;
extern uint8_t SI3;
extern uint8_t SP0;
extern uint8_t SN0;
extern uint8_t SP1;
extern uint8_t SN1;
extern uint8_t SP2;
extern uint8_t SN2;
extern uint8_t SP3;
extern uint8_t SN3;

//*************data****************//
extern uint8_t 		Test_all[][32];								//Test_all
extern int16_t 		Test_Kernal[][3][3];					//Test_Kernal		
extern int16_t 		Test_Conv_result[32][32]; 		//Conv_result   2Dsl=0

extern const uint8_t 		HKUST_32x32[][32][32]; 	//HKUST_32x32
extern const uint8_t 		HKUST_58x58[][58][58];	//HKUST_58x58
extern const uint8_t 		Mnist[][28][28];				//Mnist data 		3Dsl=4 --- Mnist
extern const uint8_t 		Mnist_label[];					//Mnist label		1Dsl=1

extern int16_t 		Kernal_3x5x5[3][5][5];						//3Dsl=0
extern int16_t 		Delta_Kernal_3x5x5[3][5][5];			//3Dsl=5
extern int16_t 		Kernal_6x3x3x3[6][3][3][3];				//4Dsl=0
extern int16_t 		Delta_Kernal_6x3x3x3[6][3][3][3];	//4Dsl=1

extern uint16_t 	Conv1_result[3][24][24];					//3Dsl=1
extern uint16_t 	Conv2_result[6][6][6];						//3Dsl=2
extern uint8_t 		Conv2_result_s[18][12];							//2Dsl=1
extern uint16_t 	Pool1_result[3][8][8];						//3Dsl=3
extern uint8_t 		Pool1_result_s[8][24];							//2Dsl=2	
extern uint16_t 	Pool2_result[9][6];									//2Dsl=3	
extern uint8_t 		Flatten[2][28];											//2Dsl=4
extern int16_t 		Weight_20x28[20][28];								//2Dsl=5
extern int32_t 		Delta_Weight_20x28[20][28];					//2Dsl=6
extern uint16_t 	Final_result[10];										//1Dsl=0

//*************algorithm****************//
uint8_t 	HKUST_Row=30; 				//Row size
uint8_t 	HKUST_Col=30;					//Col size
uint8_t 	HKUST_kernal_size=3;	//Kernal size
uint8_t 	HKUST_image_num=  4;	//Image size
uint8_t 	HKUST_kernal_num= 5;	//Kernal size

uint8_t 	MNIST_Row=28; 				//Row size
uint8_t 	MNIST_Col=28;					//Col size
uint16_t 	MNIST_total_num=500;	//Total image size
uint16_t 	MNIST_train_num=101;	//Training image size
uint16_t 	MNIST_pre_num	 =0;		//Predict image size

uint8_t 	MNIST_conv1_size=5;		//MNIST_conv1_size
uint8_t 	MNIST_conv1_num= 3;		//MNIST_conv1_num
uint8_t 	MNIST_conv2_size=3;		//MNIST_conv2_size
uint8_t 	MNIST_conv2_num= 6;		//MNIST_conv2_num
uint8_t 	MNIST_pool1_size=3;		//MNIST_pool1_size
uint8_t 	MNIST_pool2_size=2;		//MNIST_pool2_size

uint32_t 	INSC=0xFFFFFFFF;
int32_t 	LR=180000; 						//100000 建议更大一点
uint32_t 	Cost=0;
float 		Count=0;
int32_t 	Delta=0;

//***D4_array_print
void D4_array_print(uint8_t sl, uint8_t x, uint8_t y, uint8_t z, uint8_t c){
	switch(sl){
		case 0:{printf("Kernal_6x3x3x3 \n");			}break; 
		case 1:{printf("Delta_Kernal_6x3x3x3 \n");}break;
		default: break;
	}
	for(uint8_t i=0;i<x;i++){
		printf("ID%d = [",i);		
		for(uint8_t j=0;j<y;j++){
			printf("[\n");
			for(uint8_t k=0;k<z;k++){
				printf("[");
				for(uint8_t l=0;l<c;l++){
					switch(sl){
						case 0:{printf("%4d ",Kernal_6x3x3x3[i][j][k][l]);			}break;
						case 1:{printf("%4d ",Delta_Kernal_6x3x3x3[i][j][k][l]);}break;
						default: break;
					}
				}
				printf("] \n");
			}
			printf("]");
		}
		printf("] \n");
	}
}
//***D3_array_print
void D3_array_print(uint8_t sl, uint8_t x, uint8_t y, uint8_t z){
	switch(sl){
		case 0:{printf("Kernal_3x5x5 \n");}break;
		case 1:{printf("Conv1_result \n");}break;
		case 2:{printf("Conv2_result \n");}break;
		case 3:{printf("Pool1_result \n");}break;
		case 4:{printf("Mnist \n");				}break;
		case 5:{printf("Delta_Kernal_3x5x5 \n");}break;
		default: break;
	}
	for(uint8_t i=0;i<x;i++){
		printf("ID%d = [\n",i);		
		for(uint8_t j=0;j<y;j++){
			printf("[");
			for(uint8_t k=0;k<z;k++){
				switch(sl){
					case 0:{printf("%4d ",Kernal_3x5x5[i][j][k]);}break;
					case 1:{printf("%4d ",Conv1_result[i][j][k]);}break;
					case 2:{printf("%4d ",Conv2_result[i][j][k]);}break;
					case 3:{printf("%4d ",Pool1_result[i][j][k]);}break;
					case 4:{printf("%4d ",       Mnist[i][j][k]);}break;
					case 5:{printf("%4d ",Delta_Kernal_3x5x5[i][j][k]);}break;
					default: break;
				}
			}
			printf("],\n");
		}
		printf("]\n");
	}
}
//***D2_array_print
void D2_array_print(uint8_t sl, uint8_t x, uint8_t y){
	switch(sl){
		case 0:{printf("Test_Conv_result \n");	}break; 
		case 1:{printf("Conv2_result_s \n"	);	}break;
		case 2:{printf("Pool1_result_s \n"	);	}break;
		case 3:{printf("Pool2_result \n"		);	}break;
		case 4:{printf("Flatten \n"					);	}break;
		case 5:{printf("Weight_20x28 \n"		);	}break;
		case 6:{printf("Delta_Weight_20x28 \n");}break;
		default: break;
	}
	for(uint8_t i=0;i<x;i++){
		printf("[ ");		
		for(uint8_t j=0;j<y;j++){
				switch(sl){
					case 0:{printf("%4d ",Test_Conv_result[i][j]);	}break; 
					case 1:{printf("%4d ",Conv2_result_s[i][j]);		}break;
					case 2:{printf("%4d ",Pool1_result_s[i][j]);		}break;
					case 3:{printf("%4d ",Pool2_result[i][j]);			}break;
					case 4:{printf("%4d ",Flatten[i][j]);						}break;
					case 5:{printf("%4d ",Weight_20x28[i][j]);			}break;
					case 6:{printf("%4d ",Delta_Weight_20x28[i][j]/LR);}break;
					default: break;
			}
		}
		printf("]\n");
	}
}
//***D1_array_print
void D1_array_print(uint8_t sl, uint8_t x){
	switch(sl){
		case 0:{printf("Final_result \n");}break; 
		case 1:{printf("Mnist_label \n" );}break;
		default: break;
	}
	for(uint8_t i=0;i<x;i++){
		switch(sl){
			case 0:{printf("%4d ",Final_result[i]);}break; 
			case 1:{printf("%4d ",Mnist_label[i]);}break;
			default: break;
		}
	}
	printf("]\n");
}
//***Full_result_print
void Full_result_print(uint16_t image_id, uint8_t kernal_id){
	for(uint8_t row=0;row<32;row++){
		for(uint8_t col=0; col<32;col++){
			printf("%4d ",Test_Conv_result[row][col]);
		}printf("\n");
	}
}
//***Full_result_STM32_print
void Full_result_STM32_print(uint16_t image_id, uint8_t kernal_id){
	printf("ID%dKL%d = [\n",image_id,kernal_id);
	for(uint8_t row=0;row<28;row++){
		printf("[");
		for(uint8_t col=0; col<28;col++){
			printf("%4d, ",Test_Conv_result[row][col]);
		}printf("],\n");
	}
	printf("]\n");
}

//***single_image_conv
void HKUST_Conv(uint8_t Ch, uint16_t image_id, uint8_t kernal_id){
	uint8_t kernal_P[3]={0,0,0};//分离正负权重
	uint8_t kernal_N[3]={0,0,0};//分离正负权重
	//***写入图片数据
	for(uint8_t row=0;row<HKUST_Row;row++){
		Data_input8((uint8_t *)HKUST_32x32[image_id][row],HKUST_Col);		//Gray_image
		HV66PG_Write(SI0,Write_Data_Convert(row));
	}
	//***卷积计算
	//列扫描
	for(uint8_t col=0;col<(HKUST_Col-HKUST_kernal_size+1);col++){				//Left-->Right size: Col-Kernal_Size+1=30
		//!!!清空数据线，1是防止与图片数据共享影响，2是消除前列卷积核
		Data_input8(Test_all[2],HKUST_Col);			
		//行扫描滑动三次
		for(uint8_t slide=0;slide<HKUST_kernal_size;slide++){	//Top-->Bottom size: 3
			//权重写入
			for(uint8_t row=0;row<HKUST_kernal_size;row++){	
				//分离正负权重
				for(uint8_t x=0;x<HKUST_kernal_size;x++){
					if(Test_Kernal[kernal_id][row][x]>=0){
						kernal_P[x]=Test_Kernal[kernal_id][row][x];
						kernal_N[x]=0;
					}else{
						kernal_P[x]=0;
						kernal_N[x]=-Test_Kernal[kernal_id][row][x];
					}
				}
				//写入正权重
				Kernel_input(col,HKUST_kernal_size,kernal_P);  
				HV66PG_Write(SP0,Conv_Data_Convert(slide+row));
				//写入负权重
				Kernel_input(col,HKUST_kernal_size,kernal_N);
				HV66PG_Write(SN0,Conv_Data_Convert(slide+row));	
			}
			//读取数据
			CompCh_select(0);
		  //转移分配数据
			for(uint8_t row=slide;row<(HKUST_Col-HKUST_kernal_size+1);row=row+3){			
				Test_Conv_result[row][col]=(ADC_output[row]+ADC_output[row+1]+ADC_output[row+2])/3;
			}
		}
	}	
	//打印数据
	//Full_result_print(image_id,kernal_id);
	Full_result_STM32_print(image_id,kernal_id);	
}

//***full_image_conv
void HKUST_full_conv(void){
	
	for(uint16_t i=0;i<HKUST_image_num;i++){
		for(uint8_t j=0;j<HKUST_kernal_num;j++){
			//printf("Image ID:%d   Kernel ID:%d\n",i,j);
			HKUST_Conv(0, i, j);
		}	
	}
}
//***MNIST_Conv1						Mnist[][28][28]		--->	Conv1_result[3][24][24]
void MNIST_Conv1(uint16_t image_id){
	uint8_t kernal_P[5]={0,0,0,0,0};//分离正负权重
	uint8_t kernal_N[5]={0,0,0,0,0};//分离正负权重
	
	//***写入图片数据
	for(uint8_t row=0;row<MNIST_Row;row++){
		Data_input8((uint8_t *)Mnist[image_id][row],MNIST_Col);
		HV66PG_Write(SI0,Write_Data_Convert(row));
	}
	
	//每张图3个卷积核
	for(uint8_t i=0;i<MNIST_conv1_num;i++){	
		
		//***卷积计算
		//列扫描
		for(uint8_t col=0;col<(MNIST_Col-MNIST_conv1_size+1);col++){				//Left-->Right size: Col-Kernal_Size+1
			
			//!!!清空数据线，1是防止与图片数据共享影响，2是消除前列卷积核
			Data_input8(Test_all[2],30);			
			
			//行扫描滑动三次
			for(uint8_t slide=0;slide<MNIST_conv1_size;slide++){	//Top-->Bottom size: 5
				
				//权重写入
				for(uint8_t row=0;row<MNIST_conv1_size;row++){	
					
					//分离正负权重
					for(uint8_t x=0;x<MNIST_conv1_size;x++){
						if(Kernal_3x5x5[i][row][x]>=0){
							kernal_P[x]=Kernal_3x5x5[i][row][x];
							kernal_N[x]=0;
						}else{
							kernal_P[x]=0;
							kernal_N[x]=-Kernal_3x5x5[i][row][x];
						}
					}
					
					//写入正权重
					Kernel_input(col,MNIST_conv1_size,kernal_P);  
					HV66PG_Write(SP0,Conv_Data_Convert(slide+row));
					//写入负权重
					Kernel_input(col,MNIST_conv1_size,kernal_N);
					HV66PG_Write(SN0,Conv_Data_Convert(slide+row));	
				}
				//读取数据
				CompCh_select(0);
				//转移分配数据
				for(uint8_t row=slide;row<(HKUST_Col-MNIST_conv1_size+1);row=row+MNIST_conv1_size){			
					Conv1_result[i][row][col]=(ADC_output[row]+ADC_output[row+1]+ADC_output[row+2]+ADC_output[row+3]+ADC_output[row+4])/5;
				}
				//调试打印
				//printf("col:%d, slide:%d\n",col,slide);
				//ADC_Output_print();
				//Full_result_print();	
			}
		}	
	}
	//打印数据
	//Any_array_print(2,3,24,24);
}
//***MNIST_Conv2			Pool1_result_s[8][24]		---> 	Conv2_result[6][6][6]
void MNIST_Conv2(void){
	uint8_t kernal_P[3][3]={{0,0,0},{0,0,0},{0,0,0}};//分离正负权重
	uint8_t kernal_N[3][3]={{0,0,0},{0,0,0},{0,0,0}};//分离正负权重
	//写入图片数据8*8到1*3阵列中
	for(uint8_t row=0;row<8;row++){
		Data_input8(Pool1_result_s[row],24);
		HV66PG_Write(SI0,Write_Data_Convert(row));
	}
	//6个卷积核
	for(uint8_t kernal_id=0;kernal_id<6;kernal_id++){
		//列扫描
		for(uint8_t col=0;col<6;col++){
			//!!!清空数据线，1是防止与图片数据共享影响，2是消除前列卷积核
			Data_input8(Test_all[2],30);
			//行扫描滑动三次
			for(uint8_t slide=0;slide<3;slide++){
				//权重写入
				for(uint8_t row=0;row<3;row++){
					//3个卷积核在3列同时进行卷积			
					for(uint8_t p=0;p<3;p++){
						//分离正负权重
						for(uint8_t x=0;x<3;x++){
							if(Kernal_6x3x3x3[kernal_id][p][row][x]>=0){
								kernal_P[p][x]=Kernal_6x3x3x3[kernal_id][p][row][x];
								kernal_N[p][x]=0;
							}else{
								kernal_P[p][x]=0;
								kernal_N[p][x]=-Kernal_6x3x3x3[kernal_id][p][row][x];
							}
						}
					}
					//写入正权重
					Kernel_input(col,3,kernal_P[0]);
					Kernel_input(col+8,3,kernal_P[1]); 
					Kernel_input(col+16,3,kernal_P[2]); 
					HV66PG_Write(SP0,Conv_Data_Convert(slide+row));
					//写入负权重
					Kernel_input(col,3,kernal_N[0]);
					Kernel_input(col+8,3,kernal_N[1]);
					Kernel_input(col+16,3,kernal_N[2]);
					HV66PG_Write(SN0,Conv_Data_Convert(slide+row));	
				}
				//读取数据
				CompCh_select(0);
				//转移分配数据
				for(uint8_t row=slide;row<6;row=row+3){			
					Conv2_result[kernal_id][row][col]=(ADC_output[row]+ADC_output[row+1]+ADC_output[row+2])/3;
				}				
			}
		}
	}
}

//***MNIST_Pool1		Conv1_result[3][24][24]		---> 	Pool1_result[3][8][8]
void MNIST_Pool1(void){
	
	uint8_t Pool_IN1[3]={255,255,255};

	//3张图片池化需要进行三次
	for(uint8_t i=0;i<3;i++){
		
		//写入图片数据
		for(uint8_t row=0;row<24;row++){
			Data_input16(Conv1_result[i][row],24);
			HV66PG_Write(SI0,Write_Data_Convert(row));
		}
		
		//列扫描
		for(uint8_t col=0;col<22;col=col+3){ //池化列扫描，24-3+1
			//!!!清空数据线，1是防止与图片数据共享影响，2是消除前列卷积核
			Data_input8(Test_all[2],30);
			//写入对应列的权重
			Kernel_input(col,3,Pool_IN1);
			HV66PG_Write(SP0,INSC);
			//读取数据
			CompCh_select(0);
			//转移分配数据
			for(uint8_t row=0;row<22;row=row+3){
				Pool1_result[i][row/3][col/3]=(ADC_output[row]+ADC_output[row+1]+ADC_output[row+2])/3;
			}
		}
	}
}
//***MNIST_Pool2	 	 Conv2_result_s[18][12]		---> 	Pool2_result[9][6]
void MNIST_Pool2(void){
	
	uint8_t Pool_IN2[2]={255,255};
	
	//写入图片数据
	for(uint8_t row=0;row<18;row++){
		Data_input8(Conv2_result_s[row],12);
		HV66PG_Write(SI0,Write_Data_Convert(row));
	}
	
	//列扫描
	for(uint8_t col=0;col<11;col=col+2){ //池化列扫描，12-2+1
		//!!!清空数据线，1是防止与图片数据共享影响，2是消除前列卷积核
		Data_input8(Test_all[2],30);
		//写入对应列的权重
		Kernel_input(col,2,Pool_IN2);
		HV66PG_Write(SP0,INSC);
		//读取数据
		CompCh_select(0);
		//转移分配数据
		for(uint8_t row=0;row<17;row=row+2){ //池化列扫描，18-2+1
			Pool2_result[row/2][col/2]=(ADC_output[row]+ADC_output[row+1])/2;
		}
	}
	
	
	
}
//***FC_layer			         	 Flatten[2][28]		--->  Final_result[10]
void FC_layer(void){
	uint32_t IN1010=0xAAAAAAAA;
	uint32_t IN0101=0x55555555;
	uint8_t kernal_P[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//分离正负权重
	uint8_t kernal_N[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//分离正负权重
		
	//写入输入数据
	Data_input8(Flatten[0],28);
	HV66PG_Write(SI0,IN1010);
	Data_input8(Flatten[1],28);
	HV66PG_Write(SI0,IN0101);
		
	//输入权重数据
	for(uint8_t row=0;row<20;row++){
		
		//分离正负权重
		for(uint8_t x=0;x<28;x++){
			if(Weight_20x28[row][x]>=0){
				kernal_P[x]=Weight_20x28[row][x];
				kernal_N[x]=0;
			}else{
				kernal_P[x]=0;
				kernal_N[x]=-Weight_20x28[row][x];
			}
		}
				
		//写入正权重
		Kernel_input(0,28,kernal_P);  
		HV66PG_Write(SP0,Write_Data_Convert(row));
		//写入负权重
		Kernel_input(0,28,kernal_N);
		HV66PG_Write(SN0,Write_Data_Convert(row));
	}
	
	//读取数据
	CompCh_select(0);

	//分配数据
	for(uint8_t row=0;row<19;row=row+2){ //20-2+1
		Final_result[row/2]=(ADC_output[row]+ADC_output[row+1])/2;
	}
	
}
//***Cost
uint32_t Cost_cal(uint16_t image_id){
	int32_t pCost=0;
	for(uint8_t i=0;i<10;i++){
		if(i==Mnist_label[image_id]){
		pCost+=(4000-Final_result[i])*(4000-Final_result[i]);
		}else{
		pCost+=Final_result[i]*Final_result[i];
		}
	}
	pCost=pCost/2;
	return pCost;
}
//***ForwPropagation
void ForPropagation(uint16_t image_id){
	//Conv1
	MNIST_Conv1(image_id);
		//D3_array_print(1,3,24,24);
		uint32_t buff_Conv1_result=0;
		for(uint8_t i=0;i<3;i++){
			for(uint8_t j=0;j<24;j++){
				for(uint8_t k=0;k<24;k++){
					buff_Conv1_result+=Conv1_result[i][j][k];
				}
			}
		}
		printf(" %d",buff_Conv1_result);
	Array_nomr(0);
	//D3_array_print(1,3,24,24);
	
	//Pool1
	MNIST_Pool1();
		//D3_array_print(3,3,8,8);
		uint32_t buff_Pool1_result=0;
		for(uint8_t i=0;i<3;i++){
			for(uint8_t j=0;j<8;j++){
				for(uint8_t k=0;k<8;k++){
					buff_Pool1_result+=Pool1_result[i][j][k];
				}
			}
		}
		printf(" %d",buff_Pool1_result);
	Array_nomr(2);
	//D2_array_print(2,8,24);
	
	//Conv2
	MNIST_Conv2();
		//D3_array_print(2,6,6,6);
		uint32_t buff_Conv2_result=0;
		for(uint8_t i=0;i<6;i++){
			for(uint8_t j=0;j<6;j++){
				for(uint8_t k=0;k<6;k++){
					buff_Conv2_result+=Conv2_result[i][j][k];
				}
			}
		}
		printf(" %d",buff_Conv2_result);
	Array_nomr(1);
	//D2_array_print(1,18,12);
	
	//Pool2
	MNIST_Pool2();
		//D2_array_print(3,9,6); 	//Pool2_result
		uint32_t buff_Pool2_result=0;
		for(uint8_t i=0;i<9;i++){
			for(uint8_t j=0;j<6;j++){
					buff_Pool2_result+=Pool2_result[i][j];
			}
		}
		printf(" %d",buff_Pool2_result);
	Array_nomr(3);
	//D2_array_print(4,2,28);	//Flatten
	
	//FC_layer
	FC_layer();
		//D1_array_print(0,10);
		uint32_t buff_Final_result=0;
		for(uint8_t i=0;i<10;i++){
			buff_Final_result+=Final_result[i];
		}
		printf(" %d\n",buff_Final_result);	
}
//***Training
void Training(uint8_t epoch){

	printf("Start training...\n");
	//printf("Init inference:\n");
	//Inference(0,MNIST_train_num);
	//Inference(100,500);
	

	for(uint16_t e=0; e<epoch; e++){
		printf("\nEpoch: %d\n",e);
		

		Cost=0;
		Count=0;
		for(uint8_t i=0;i<20;i++){
			for(uint8_t j=0;j<28;j++){
				Delta_Weight_20x28[i][j]=0;
			}
		}
		
		//Forward propagation to calc cost
		printf("Forward progress: ");
		for(uint16_t id=0;id<MNIST_train_num;id++){

			if(id%(MNIST_train_num/10)==0){
				printf("-");
			}

			ForPropagation(id);

			Cost+=Cost_cal(id)/MNIST_train_num;

			Count+=Predict(id);
			

			for(uint8_t i=0;i<20;i++){
				for(uint8_t j=0;j<28;j++){
					if((i/2)==Mnist_label[id]){
						Delta_Weight_20x28[i][j]+=(Final_result[i/2]-4000)*Flatten[i%2][j];
					}else{
						Delta_Weight_20x28[i][j]+=(Final_result[i/2])*Flatten[i%2][j];
					}
				}
			}
		}printf(" Finish!\n");
	
		//printf("Cost = %d, Acc = %5.2f%%\n",Cost, Count/MNIST_train_num*100);
		
		D2_array_print(6,20,28); 
		
		//Backward propagation
		for(uint8_t i=0;i<20;i++){
			for(uint8_t j=0;j<28;j++){
				Delta=Delta_Weight_20x28[i][j]/LR;
				
				if(Delta>40){
					Weight_20x28[i][j]-=40;
				}else if(Delta<-40){
					Weight_20x28[i][j]-=-40;
				}else{
					Weight_20x28[i][j]-=Delta;
				}
				
				if(Weight_20x28[i][j]>255){
					Weight_20x28[i][j]=255;
				}else if(Weight_20x28[i][j]<-255){
					Weight_20x28[i][j]=-255;
				}

			}
		}
		
		D2_array_print(5,20,28);
		
		//Inference(301,500);
		Inference(0,  101);
		Inference(101,  202);
	}
}
//***Kernel Training
void Training_Kernel(uint8_t epoch, uint16_t Id_start, uint16_t Id_stop){
	//定义必要常量
	uint32_t Cost_delta=0;
	int32_t Change=0;
	int16_t Sweep=0;
	
	for(uint16_t e=0; e<epoch; e++){
		printf("Kernal epoch:%d\n",e);
		
		//选定组做一次Inference训练，记录Cost数值
		Inference(Id_start,Id_stop);
		
		//前向传播测试Kernal_3x5x5
		printf("\nKernal_3x5x5:\n");
		for(uint8_t i=0; i<3; i++){
			for(uint8_t j=0; j<5; j++){
				for(uint8_t k=0; k<5; k++){
					
					//printf("-");
					
					//正增加或负减小Delta_K
					//前50组做一次Inference训练,反馈Cost数值并记录在Delta_Kernel数组中
					Sweep=Kernal_3x5x5[i][j][k];
					if(Kernal_3x5x5[i][j][k]>=100){
						Kernal_3x5x5[i][j][k]-=80;
					}else{
						Kernal_3x5x5[i][j][k]+=80;
					}
					
					//选定组做一次Inference训练，记录Cost数值
					Cost_delta=0;
					for(uint16_t id=Id_start;id<Id_stop;id++){
						//前向传播
						ForPropagation(id);
						//更新Cost
						Cost_delta+=Cost_cal(id)/(Id_stop-Id_start);
					}
					//printf("Kernal_3x5x5[%d][%d][%d]: %d\n",i,j,k,Cost_delta);
					printf("-");
					
					//更新Delta_Kernal_3x5x5
					Change=Cost_delta-Cost;
					if(Sweep>=100){
						Delta_Kernal_3x5x5[i][j][k]=-Change/8000;	//5000
					}else{
						Delta_Kernal_3x5x5[i][j][k]=Change/8000;
					}
					
					//恢复Kernal_3x5x5[i][j][k]
					Kernal_3x5x5[i][j][k]=Sweep;
					
				}
			}
		}
		
		//前向传播测试Kernal_6x3x3x3
		printf("\nKernal_6x3x3x3:\n");
		for(uint8_t i=0; i<6; i++){
			for(uint8_t j=0; j<3; j++){
				for(uint8_t k=0; k<3; k++){
					for(uint8_t l=0; l<3; l++){
					//printf("-");
					//正增加或负减小Delta_K
					//前50组做一次Inference训练,反馈Cost数值并记录在Delta_Kernel数组中
					Sweep=Kernal_6x3x3x3[i][j][k][l];
					if(Kernal_6x3x3x3[i][j][k][l]>=100){
						Kernal_6x3x3x3[i][j][k][l]-=80;
					}else{
						Kernal_6x3x3x3[i][j][k][l]+=80;
					}
					
					//选定组做一次Inference训练，记录Cost数值
					Cost_delta=0;
					for(uint16_t id=Id_start;id<Id_stop;id++){
						//前向传播
						ForPropagation(id);
						//更新Cost
						Cost_delta+=Cost_cal(id)/(Id_stop-Id_start);
					}
					
					//printf("Kernal_6x3x3x3[%d][%d][%d][%d]: %d\n",i,j,k,l,Cost_delta);
					printf("-");
					
					//更新Delta_Kernal_3x5x5
					Change=Cost_delta-Cost;
					if(Sweep>=100){
						Delta_Kernal_6x3x3x3[i][j][k][l]=-Change/8000; //5000
					}else{
						Delta_Kernal_6x3x3x3[i][j][k][l]=Change/8000;
					}
					
					//恢复Kernal_3x5x5[i][j][k]
					Kernal_6x3x3x3[i][j][k][l]=Sweep;
										
					}
				}
			}
		}
		printf("\n");
		//打印Delta_Kernal_3x5x5, Delta_Kernal_6x3x3x3
		D3_array_print(5,3,5,5);
		D4_array_print(1,6,3,3,3);
		
		//根据卷积核参数正负，更新卷积核参数并注意上下限
		for(uint8_t i=0; i<3; i++){
			for(uint8_t j=0; j<5; j++){
				for(uint8_t k=0; k<5; k++){
					
					if(Delta_Kernal_3x5x5[i][j][k]>30){
						Delta_Kernal_3x5x5[i][j][k]=30;
					}else if(Delta_Kernal_3x5x5[i][j][k]<-30){
						Delta_Kernal_3x5x5[i][j][k]=-30;
					}else{}
					
					Kernal_3x5x5[i][j][k]-=Delta_Kernal_3x5x5[i][j][k];
					
					if(Kernal_3x5x5[i][j][k]>255){
						Kernal_3x5x5[i][j][k]=255;
					}else if(Kernal_3x5x5[i][j][k]<-255){
						Kernal_3x5x5[i][j][k]=-255;
					}else{}
					
				}
			}
		}
		for(uint8_t i=0; i<6; i++){
			for(uint8_t j=0; j<3; j++){
				for(uint8_t k=0; k<3; k++){
					for(uint8_t l=0; l<3; l++){
						
						if(Delta_Kernal_6x3x3x3[i][j][k][l]>30){
							Delta_Kernal_6x3x3x3[i][j][k][l]=30;
						}else if(Delta_Kernal_6x3x3x3[i][j][k][l]<-30){
							Delta_Kernal_6x3x3x3[i][j][k][l]=-30;
						}else{}
						
						Kernal_6x3x3x3[i][j][k][l]-=Delta_Kernal_6x3x3x3[i][j][k][l];
						
						if(Kernal_6x3x3x3[i][j][k][l]>255){
							Kernal_6x3x3x3[i][j][k][l]=255;
						}else if(Kernal_6x3x3x3[i][j][k][l]<-255){
							Kernal_6x3x3x3[i][j][k][l]=-255;
						}else{}
						
					}
				}
			}
		}

		//打印Kernal_3x5x5, Kernal_6x3x3x3
		D3_array_print(0,3,5,5);
		D4_array_print(0,6,3,3,3);
		
	}
}
//***Inference
void Inference(uint16_t start, uint16_t stop){
	Count=0;
	Cost=0;
	printf("Predict---\n");
	//printf("Predict: %d - %d\n",start,stop);
	for(uint16_t i=start;i<stop;i++){
		printf("ID:%d, label:%d ",i, Mnist_label[i]);
		ForPropagation(i);

			Count+=Predict(i);
		Cost+=Cost_cal(i)/(stop-start);
	}
	printf("Cost = %d, Acc = %5.2f%%\n",Cost, Count/(stop-start)*100);
}
//***Predict
uint16_t Predict(uint16_t image_id){
	uint16_t max_val=0;
	uint16_t max_id=0;
	for(int i = 0; i < 10; i++) {
		if(Final_result[i] > max_val) {
			max_val = Final_result[i];
			max_id = i;
    }
	} //printf("ID-%3d Label:%d, Pre:%d\n",image_id, Mnist_label[image_id], max_id);
	if(Mnist_label[image_id]==max_id){
		return 1;
	}else{
		return 0;
	}
}
//******Running******
void Running(void){

	//*****Memory Characteristic*****//
	//printf("Memory Characteristic...\n");
	//Module_test();
	
	//full_scan();
	
	//BiDirScan();
	
	//BiDirScan_Single_TenTimes();
	
	//LeakageTest();	
	

	
	//*****Conv Characteristic*****//
	//printf("Conv Running...\n");
	//HKUST_full_conv();
	


	//*****CNN Charac*****//	
	printf("\nRUN0_SA%d_LR100000_LM30_EP20_AC\n",MNIST_train_num);
	
	//Kernel training
	//for (uint8_t n=0;n<10;n++){
	//	printf("***************n=%d\n",n);
	//	Training_Kernel(2,0+n*50,50+n*50);
	//	Training(2);
	//}
	
	//Training
	Training(20);
	
}
//***full_scan
void full_scan(void){
	//初始化所有权重
	Data_input8(Test_all[2],32);
	HV66PG_Write(SI0,INSC);
	HV66PG_Write(SP0,INSC);
	HV66PG_Write(SN0,INSC);
	
	//数据写入
	Data_input8(Test_all[3],32);
	HV66PG_Write(SI0,INSC);
	//Scaning and reading data
	for(uint8_t col=0;col<32;col++){
		//扫描列准备
		for(uint8_t x=0;x<32;x++){
			if(x==col){
				Test_all[4][x]=255;
			}else{
				Test_all[4][x]=0;
			}
		}
		//开启扫描与计算
		Data_input8(Test_all[4],32);
		HV66PG_Write(SP0,INSC);
		CompCh_select(0);
		
		for(uint8_t row=0;row<32;row++){			
				Test_Conv_result[row][col]=ADC_output[row];
		}
	}
	Full_result_print(0,0);
	HAL_Delay(500);
}
//***BiDirScan
void BiDirScan(void){
	//初始化
	All_clear();
	
	for(uint16_t t=0;t<1000;t++){ //Runing times
		printf("Running times: %d\n", t);
		//Writing weight, fixed at 255	
		Test_all[4][0]=255;
		Data_input8(Test_all[4],30);
		HV66PG_Write(SI0,INSC);	
		
		for(uint16_t i=0; i<256; i++){
			//Writing data, increasing from 0 to 255
				Test_all[4][0]=i;
				Data_input8(Test_all[4],30);
				HV66PG_Write(SP0,INSC);
			
				//Computing
				CompCh_select(0);
				printf("Data: %d\n", i);
				ADC_Output_print();
			}
		for(uint16_t i=255; i>0; i--){
			//Writing data, increasing from 0 to 255
				Test_all[4][0]=i;
				Data_input8(Test_all[4],30);
				HV66PG_Write(SP0,INSC);
				
				//Computing	
				CompCh_select(0);
				printf("Data: %d\n", i);
				ADC_Output_print();
		}
	}
}
//***BiDirScan_Single_TenTimes
void BiDirScan_Single_TenTimes(void){
	//初始化
	All_clear();
	
	uint16_t ave=0;
	
	for(uint16_t t=0;t<1000;t++){ //Runing times
		printf("Running times: %d\n", t);
		
		//Writing P weight, fixed at 255	
		Test_all[2][0]=255;
		Data_input8(Test_all[2],30);
		HV66PG_Write(SP0,INSC);	
		//Writing N weight, fixed at 0			
		Test_all[2][0]=0;
		Data_input8(Test_all[2],30);
		HV66PG_Write(SI0,INSC);	
		
		for(uint16_t i=0; i<256; i++){
			//Writing data, increasing from 0 to 255
			Test_all[2][0]=i;
			Data_input8(Test_all[2],30);
			HV66PG_Write(SI0,INSC);
			//Computing
			ave=0;
			for(uint8_t average=0;average<10;average++){	
				CompCh_select(0);
				ave+=ADCP_output[0];			
				if(average==9){
					printf("%3d %4d\n",i, ave/10);
				}
			}
		}
		for(uint16_t i=255; i>1; i--){
			//Writing data, increasing from 0 to 255
			Test_all[2][0]=i;
			Data_input8(Test_all[2],30);
			HV66PG_Write(SI0,INSC);
			//Computing
			ave=0;
			for(uint8_t average=0;average<10;average++){	
				CompCh_select(0);
				ave+=ADCP_output[0];			
				if(average==9){
					printf("%3d %4d\n",i, ave/10);
				}
			}	
		}
	}
}
//***LeakageTest
void LeakageTest(void){
	printf("Leakage test\n");
	//初始化
	All_clear();
	
	uint16_t ave=0;
	//Short term test
//	for(uint8_t i=0;i<2;i++){ 
//		Data_input8(Test_all[4],30);
//		HV66PG_Write(SP0,INSC);
//		HV66PG_Write(SI0,INSC);
//		printf("Para=%d\n",i*10);
//		for(uint32_t t=0;t<5000;t++){ //Runing times
//			HAL_Delay(1); //Measuring every 10s
//			Test_all[2][0]=i*10;
//			Data_input8(Test_all[2],30);
//			ave=0;
//			for(uint8_t average=0;average<10;average++){	
//				CompCh_select(0);
//				//ADC_Output_print();
//				ave+=ADCP_output[0];			
//				if(average==9){
//					printf("%3d %4d\n",t, ave/10);
//				}
//			}
//		}
//	}
	//Long term test
	for(uint8_t i=0;i<6;i++){ 
		Data_input8(Test_all[4],30);
		HV66PG_Write(SP0,INSC);
		HV66PG_Write(SI0,INSC);
		printf("Para=%d\n",0+i*50);
		for(uint32_t t=0;t<500000;t++){ //Runing times
			//每次采样刷新权重
			Data_input8(Test_all[4],30);
			HV66PG_Write(SP0,INSC);
			
			//设定初始状态
			//Test_all[2][0]=255;
			//Data_input8(Test_all[2],30);
			
			HAL_Delay(1000); //Measuring every 1s
			
			ave=0;
			for(uint8_t average=0;average<10;average++){	
				CompCh_select(0);
				ave+=ADCP_output[0];			
				if(average==9){
					printf("%3d %4d\n",t, ave/10);
				}
			}
		}
	}
}
//***All_clear
void All_clear(void){
	Data_input8(Test_all[2],30);	
	HV66PG_Write(SI0,INSC);
	HV66PG_Write(SP0,INSC);
	HV66PG_Write(SN0,INSC);
}
//***Module_test
void Module_test(void){
	//**DAC_Write test
	//DAC_Write(0);
	//HAL_Delay(10);
	//DAC_Write(5);
	//HAL_Delay(10);
	
	//**ADC test
	//ADC_Read(1);
	//ADC_Read(0);
	//ADC_Output_print();
	//HAL_Delay(10);
	
	//**CompCh_select
	//CompCh_select(0);
	//ADC_Output_print();
	
	//**Data_input8 test
	//Data_input8(Test_all[0],32);
	//HAL_Delay(10);
	//Data_input8(Test_all[1],32);
	//HAL_Delay(10);
	
	//**Kernel_input test
	//Kernel_input(21,3,Kernal_P[0][0]);
	//HAL_Delay(10);
	//Kernel_input(21,3,Kernal_P[0][1]);
	//HAL_Delay(10);
	
	//**HV66PG_Write test
	//HV66PG_Write(SP3,INSC);
	//HAL_Delay(10);
}
//***Write_Data_Convert
uint32_t Write_Data_Convert(uint8_t num){
	uint32_t Scan_Row=0x80000000;
	for(uint8_t i=0;i<num;i++){
		Scan_Row=Scan_Row/2;
	}
	return Scan_Row;
}
//***Conv_Data_Convert
uint32_t Conv_Data_Convert(uint8_t num){
	if(num%3==0){
		return 0x92492492;
	}else if(num%3==1){
		return 0x49249249;
	}else if(num%3==2){
		return 0x24924924;
	}else{
		return 0x92492492;
	}
}
//***Conv1_result_Nomr
void Array_nomr(uint8_t C1_0_C2_1_P1_2_P2_3){
	if(C1_0_C2_1_P1_2_P2_3==0){ //Conv1_result[3][24][24] ---> Conv1_result[3][24][24]
		for(uint8_t i=0;i<3;i++){
			//寻找最大值
			uint16_t max=Conv1_result[i][0][0];
			for(uint8_t row=0;row<24;row++){
				for(uint8_t col=0;col<24;col++){
					if(Conv1_result[i][row][col]>max){
						max=Conv1_result[i][row][col];
					}
				}
			}
			//归一化
			if(max>200){																																		//255
				for(uint8_t row=0;row<24;row++){
					for(uint8_t col=0;col<24;col++){
						Conv1_result[i][row][col]=(float)(Conv1_result[i][row][col])/max*200;     //255
					}
				}
			}else{
				for(uint8_t row=0;row<24;row++){
					for(uint8_t col=0;col<24;col++){
						Conv1_result[i][row][col]=Conv1_result[i][row][col];
						//Conv1_result[i][row][col]=(200/(float)max)*(Conv1_result[i][row][col]);		//255
					}
				}				
			}
		}
	}else if(C1_0_C2_1_P1_2_P2_3==1){ //Conv2_result[6][6][6] ---> Conv2_result_s[18][12]
		for(uint8_t i=0;i<6;i++){
			//寻找最大值
			uint16_t max=Conv2_result[i][0][0];
			for(uint8_t row=0;row<6;row++){
				for(uint8_t col=0;col<6;col++){
					if(Conv2_result[i][row][col]>max){
						max=Conv2_result[i][row][col];
					}
				}
			}
			//归一化
			if(max>200){																																											//255
				for(uint8_t row=0;row<6;row++){
					for(uint8_t col=0;col<6;col++){
						Conv2_result_s[((i/2)*6)+row][((i%2)*6)+col]=(float)(Conv2_result[i][row][col])/max*200;		//255
					}
				}
			}else{
				for(uint8_t row=0;row<6;row++){
					for(uint8_t col=0;col<6;col++){
						Conv2_result_s[((i/2)*6)+row][((i%2)*6)+col]=Conv2_result[i][row][col];
						//Conv2_result_s[((i/2)*6)+row][((i%2)*6)+col]=(200/(float)max)*(Conv2_result[i][row][col]);	//255
					}
				}
			}
		}	
	}else if(C1_0_C2_1_P1_2_P2_3==2){ //Pool1_result[3][8][8] ---> Pool1_result_s[8][24]
		for(uint8_t i=0;i<3;i++){
			//寻找最大值
			uint16_t max=Pool1_result[i][0][0];
			for(uint8_t row=0;row<8;row++){
				for(uint8_t col=0;col<8;col++){
					if(Pool1_result[i][row][col]>max){
						max=Pool1_result[i][row][col];
					}
				}
			}
			//归一化
			if(max>200){																																				//255
				for(uint8_t row=0;row<8;row++){
					for(uint8_t col=0;col<8;col++){
						Pool1_result_s[row][i*8+col]=(float)(Pool1_result[i][row][col])/max*200;			//255
					}
				}
			}else{
				for(uint8_t row=0;row<8;row++){
					for(uint8_t col=0;col<8;col++){
						Pool1_result_s[row][i*8+col]=Pool1_result[i][row][col];
						//Pool1_result_s[row][i*8+col]=(200/(float)max)*(Pool1_result[i][row][col]);		//255
					}
				}
			}
		}		
	}else if(C1_0_C2_1_P1_2_P2_3==3){ //Pool2_result[9][6] ---> Flatten[2][28]; 
		for(uint8_t i=0;i<6;i++){				//原本6个图案，合并成一个，现在归一化仍然按照6个来
			//寻找最大值
			uint16_t max=Pool2_result[(i/2)*3][(i%2)*3];
			for(uint8_t row=0;row<3;row++){
				for(uint8_t col=0;col<3;col++){
					if(Pool2_result[(i/2)*3+row][(i%2)*3+col]>max){
						max=Pool2_result[(i/2)*3+row][(i%2)*3+col];
					}
				}
			}
			
			//归一化
			if(max>200){																																													//255
				for(uint8_t row=0;row<3;row++){
					for(uint8_t col=0;col<3;col++){
						Flatten[i>2?1:0][(i%3)*9+row*3+col]=(float)(Pool2_result[(i/2)*3+row][(i%2)*3+col])/max*200;		//255
					}
				}
			}else{
				for(uint8_t row=0;row<3;row++){
					for(uint8_t col=0;col<3;col++){
						Flatten[i>2?1:0][(i%3)*9+row*3+col]=Pool2_result[(i/2)*3+row][(i%2)*3+col];
						//Flatten[i>2?1:0][(i%3)*9+row*3+col]=(200/(float)max)*(Pool2_result[(i/2)*3+row][(i%2)*3+col]);	//255
					}
				}
			}
		}
	}else{}
}
