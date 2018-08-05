#include"CNN_HLS.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include "ap_axi_sdata.h"

int main(){
		//FILE *fp_lable = fopen("C:\\Users\\wangchunjie\\Desktop\\MINIST\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte","rb");
		FILE *fp_lable = fopen("D:\\lyy\\01_Zynq\\vivado_HLS\\CNN_IP\\MNIST\\t10k-labels.idx1-ubyte","rb");
		if(!fp_lable){
			printf("open lable file failed!\n");
			return -1;
		}

		int a,num;
		fread(&a,sizeof(int),1,fp_lable);
		fread(&num,sizeof(int),1,fp_lable);
		printf("a = %x\nnum = %x\n",a,num);

		FILE *fp_image = fopen("D:\\lyy\\01_Zynq\\vivado_HLS\\CNN_IP\\MNIST\\t10k-images.idx3-ubyte","rb");
		if(!fp_image){
			printf("open image file failed!\n");
			return -1;
		}

		//read picture
		int size1,size2;
		fread(&a,sizeof(int),1,fp_image);	//magic
		fread(&num,sizeof(int),1,fp_image);	//numbers
		fread(&size1,sizeof(int),1,fp_image);	//length
		fread(&size2,sizeof(int),1,fp_image);	//width
		printf("a = %x\nnum = %x\nsize1 = %x\nsize2 = %x\n",a,num,size1,size2);


		unsigned char input1[28*28];
		ap_axis<32,4,5,5> input2[28*28];
		ap_axis<32,4,5,5> recognition;

		unsigned char label;

		int err_cnt=0;
		for(int i=0;i<1;i++){
				fread(input1,sizeof(unsigned char),28*28,fp_image);
				fread(&label,sizeof(unsigned char),1,fp_lable);
				for(int j=0;j<28*28;j++){
					input2[j].data =  (int)input1[j];
					input2[j].keep = 1;
					input2[j].strb = 1;
					input2[j].user = 1;
					input2[j].last = 0;
					input2[j].id = 0;
					input2[j].dest = 1;
				}


				CNN_HLS1(input2,&recognition);
				while(recognition.data.to_uint()!=7);
				if(recognition.data!=label){
					err_cnt++;
					for(int i=0;i<28;i++){
						for(int j=0;j<28;j++){
							if(input2[i*28+j].data>128){
								printf(" 1");
							}else{
								printf("  ");
							}
						}
						printf("\n");
					}
					printf("\nlabel = %d , recognization = %d\n",label,(unsigned int)recognition.data);
				}
			}
		printf("\nlabel = %d , recognization = %d\n",label,(unsigned int)recognition.data);
			printf("err_cnt = %d\n",err_cnt);
			fclose(fp_lable);
			fclose(fp_image);
			return 0;
}

