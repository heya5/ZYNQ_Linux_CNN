#include<math.h>
#include"cnn.h"
#include <ap_int.h>
double sigmoid(double x){
	return 1.0/(1+exp(-x));
}


void Input_To_C1(unsigned int input[28*28],struct C1 &c1){
	int i,j,k,l,m;
	double input_double[28*28];

	for(i=0;i<28*28;i++){
		input_double[i] = double(input[i])/255;
	}

	double tmp;
	for(i=0;i<28;i++){
		for(j=0;j<i;j++){
			tmp = input_double[i*28+j];
			input_double[i*28+j] = input_double[j*28+i];
			input_double[j*28+i] = tmp;
		}
	}

	for(i=0;i<6;i++){
		for(j=0;j<24;j++){
			for(k=0;k<24;k++){
				for(l=0;l<5;l++){
					Input_To_C1_label4:for(m=0;m<5;m++){
						c1.map[i][j*24+k]+=c1.kernel[i][l*5+m]*input_double[j*28+k+l*28+m];
					}
				}
			}
		}
	}

	for(i=0;i<6;i++){
		for(j=0;j<24*24;j++){
			c1.map[i][j] = sigmoid(c1.map[i][j]+c1.bias[i]);
		}
	}
}


void C1_To_S2(struct C1 &c1,struct S2 &s2){
	int i,j,k,l,m;

	for(i=0;i<6;i++){
		for(j=0;j<12;j++){
			for(k=0;k<12;k++){
				C1_To_S2_label8:for(l=0;l<2;l++){
					C1_To_S2_label5:for(m=0;m<2;m++){
						s2.map[i][j*12+k]+=c1.map[i][j*2*24+k*2+l*24+m]/4.0;
					}
				}
			}
		}
	}
}


void S2_To_C3(struct S2 &s2,struct C3 &c3){
	int i,j,k,l,m,n;

	for(i=0;i<12;i++){
		for(j=0;j<6;j++){
			for(k=0;k<8;k++){
				for(l=0;l<8;l++){
					for(m=0;m<5;m++){
						S2_To_C3_label6:for(n=0;n<5;n++){
							c3.map[i][k*8+l]+=c3.kernel[i*6+j][m*5+n]*s2.map[j][k*12+l+m*12+n];
						}
					}
				}
			}
		}
	}

	for(i=0;i<12;i++){
		S2_To_C3_label13:for(j=0;j<8*8;j++){
			c3.map[i][j] = sigmoid(c3.map[i][j]+c3.bias[i]);
		}
	}
}


void C3_To_S4(struct C3 &c3,struct S4 &s4){
	int i,j,k,l,m;

	for(i=0;i<12;i++){
		for(j=0;j<4;j++){
			for(k=0;k<4;k++){
				C3_To_S4_label1:for(l=0;l<2;l++){
					C3_To_S4_label0:for(m=0;m<2;m++){
						s4.map[i][j*4+k]+=c3.map[i][j*2*8+k*2+l*8+m]/4.0;
					}
				}
			}
		}
	}
}


void S4_To_Output(struct S4 &s4,struct Output &output){
	int i,j,k,l;

	for(i=0;i<10;i++){
		for(j=0;j<12;j++){
			for(k=0;k<4;k++){
				S4_To_Output_label2:for(l=0;l<4;l++){
					output.map[i]+=output.w[i][j*16+k*4+l]*s4.map[j][k+l*4];
				}
				
			}
		}
	}

	for(i=0;i<10;i++){
		output.map[i] = sigmoid(output.map[i]+output.bias[i]);
	}
}


unsigned int Get_Result(struct Output &output,unsigned int number){
	double tmp = output.map[0];
	unsigned int i;
	number =0;
	for(i=1;i<10;i++){
		if(output.map[i]>tmp){
			tmp = output.map[i];
			number =i;
		}
	}

	return number;
}
