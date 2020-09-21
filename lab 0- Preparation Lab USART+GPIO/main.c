#include <stdint.h>
int send_one=1;
int send_zero=0;



	void configRegisters()
{
	//CONFIG FOR SENDING- (ALSO SOME RECEIVING SO NO DOUBLES)
		//ENABLE USART+PROGRAM WORD LENGTH
		uint32_t* usart_cr1;
		uint32_t* usart_brr;
		uint32_t* usart_cr3;		
		uint32_t* usart_cr2;
	
		usart_cr1=0x4001380c;
		*usart_cr1=*usart_cr1|0b11000000000000;
		//NUMBER OF STOP BITS

		usart_cr2=0x40013810;
		*usart_cr2=*usart_cr2|0b00100000000000;
		//ENABLE PERPH CLOCK+DMA ENABLE

		usart_cr3=0x40013814;
		//*usart_cr3=*usart_cr3|0b10010000000;
		//SET BAUD RATE

		usart_brr=0x40013808;
		*usart_brr=*usart_brr|0b1110101001100;
		//ENABLES TRANSMITTING
	//*usart_cr1=*usart_cr1|0b1000;
	//CONFIG FOR RECEIVING
		//ENABLE DMAR+PERPH CLOCK ENABLE
		//*usart_cr3=*usart_cr3|0b10001000000;
		//ENABLES RECEIVING
		//*usart_cr1=*usart_cr1|0b0100;
}
 

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
		*CR1=(*CR1)|0b1100;
		//*dr=(*dr)&0x00;
		*dr=(*dr)|i;
		/*tc=*sr&0b1000000;
		while(tc==0){
			tc=*sr&0b1000000;
		}*/
		*CR1=(*CR1)&0xFFFFFFF7;
		//*sr=*sr&0xFFFFFFBF;
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
		*CR1=(*CR1)|0b100;
		read=(*dr)&0x7F;
		*CR1=(*CR1)|0b100;
		*dr=(*dr)&0xFFFFFF00;
		*CR1=(*CR1)&0xFFFFFFF3;
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
		configRegisters();
		while(1){
			if(send_one==1){
				send(1);
			}else{
				send(0);
			}
			r=recieve();
			if(r!=0){
				*ad2=*ad2|0b0100000000000000000000;
			}else{
				*ad2=*ad2&0xFFCFFFFF;
			}
		}
	}
	
