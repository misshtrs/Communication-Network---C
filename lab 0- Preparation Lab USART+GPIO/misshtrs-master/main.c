#include <stdint.h>
int send_one=1;
int send_zero=0;

	int send(uint32_t i){
		uint32_t* sr;
		int tc;
		int rxne;
		uint32_t* dr;
		uint32_t* CR1;
		sr=0x40013800;
		dr=0x40013804;
		CR1=0x4001380C;
		rxne=*sr&100000;
		/*while(rxne!=0){
			rxne=*sr&0b100000;
		}*/
		*CR1=*CR1|0b1100;
		*dr=*dr&0xFFFFFF00;
		*dr=*dr|0b1;
		/*tc=*sr&0b1000000;
		while(tc==0){
			tc=*sr&0b1000000;
		}*/
		*CR1=*CR1&0xFFFFFFF7;
		*sr=*sr&0xFFFFFFBF;
	}
	
	int recieve(){
		uint32_t* sr;
		int tc;
		int rxne;
		int read;
		uint32_t* dr;
		uint32_t* CR1;
		sr=0x40013800;
		dr=0x40013804;
		CR1=0x4001380C;
		tc=*sr|0b1000000;
	/*	while(tc==0){
			tc=*sr&0b1000000;
		}*/
		rxne=*sr&100000;
		/*while(rxne!=0){
			rxne=*sr&0b100000;
		}*/
		*CR1=*CR1|0b100;
		read=*dr&0xFF;
		*CR1=*CR1&0xFFFFFFFB;
		return read;
	}

	int main(void)
	{
		uint32_t* ad1;
		uint32_t* ad2;
		int r=0;
		ad1=0x40021018;
		ad2=0x40011004;
		*ad1=*ad2|0b10000;
		while(1){
			if(send_one==1){
				send(1);
			}else{
				send(0);
			}
			r=recieve();
			if(r){
				*ad2=*ad2|0b1100000000000000000000;
			}else{
				*ad2=*ad2&0xFFCFFFFF;
			}
		}
	}
	
