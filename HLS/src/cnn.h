#include"layers.h"
#include "ap_axi_sdata.h"

double sigmoid(double x);
void Input_To_C1(unsigned int input[28*28],struct C1 &c1);
void C1_To_S2(struct C1 &c1,struct S2 &s2);
void S2_To_C3(struct S2 &s2,struct C3 &c3);
void C3_To_S4(struct C3 &c3,struct S4 &s4);
void S4_To_Output(struct S4 &s4,struct Output &output);
//void Get_Result(struct Output &output,ap_axis<32,2,5,6> *recognition);
unsigned int Get_Result(struct Output &output,unsigned int number);
