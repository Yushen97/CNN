#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include "stdint.h"

//Print function
void D4_array_print(uint8_t sl, uint8_t x, uint8_t y, uint8_t z, uint8_t c);
void D3_array_print(uint8_t sl, uint8_t x, uint8_t y, uint8_t z);
void D2_array_print(uint8_t sl, uint8_t x, uint8_t y);
void D1_array_print(uint8_t sl, uint8_t x);

void Full_result_print(uint16_t image_id, uint8_t kernal_id);
void Full_result_STM32_print(uint16_t image_id, uint8_t kernal_id);

//HKUST Conv part
void HKUST_Conv(uint8_t Ch, uint16_t image_id, uint8_t kernal_id);
void HKUST_full_conv(void);

//ForwPropagation
void ForPropagation(uint16_t image_id);
void MNIST_Conv1(uint16_t image_id);
void MNIST_Conv2(void);
void MNIST_Pool1(void);
void MNIST_Pool2(void);
void FC_layer(void);
uint32_t Cost_cal(uint16_t image_id);
uint16_t Predict(uint16_t image_id);

//CNN
void Training(uint8_t epoch);
void Training_Kernel(uint8_t epoch, uint16_t Id_start, uint16_t Id_stop);
void Inference(uint16_t start, uint16_t stop);

//***Running
void Running(void);

//Test part
void full_scan(void);
void BiDirScan(void);
void All_clear(void);
void BiDirScan_Single_TenTimes(void);
void LeakageTest(void);
void Module_test(void);
uint32_t Write_Data_Convert(uint8_t num);
uint32_t Conv_Data_Convert(uint8_t num);
void Array_nomr(uint8_t C1_0_C2_1_P1_2_P2_3);

#endif

