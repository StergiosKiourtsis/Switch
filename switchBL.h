#include <systemc.h>
#include <connections/connections.h>
#include "types.h"

template<int N>
SC_MODULE(switchBL){
	public:
	sc_in_clk     clk;
	sc_in< bool > rst;
	
	Connections::In<Data_t> inp[N];
	
	Connections::Out<int> sum[N];
	
	void switch_main(void);
	void readData(Data_t message[N],bool datavld[N]);
	int arbiterCheck(bool datavld[N],int addr[N],int outpaddr);
	void convertTOBinary(int arbiterOut,char control[N]);
	void outputControl(char check[N],int data[N],int numberOfPort);

	
	
  SC_HAS_PROCESS(switchBL);
  switchBL(sc_module_name name_) : sc_module(name_){
    SC_THREAD (run);
    sensitive << clk.pos();
    async_reset_signal_is(rst,false);
  }
  void run(void){
  		switch_main();
  }
};


template<int N> void switchBL<N>::switch_main(void){
	Data_t message[N];
	int data[N];
	int addr[N];
	int arbiterOut[N];
	bool datavld[N];
	char arbiterOutBinary[N];
	
	//RESET
	for(int i=0;i<N;i++){
		inp[i].Reset();
		sum[i].Reset();
		datavld[i]=0;
		data[i]=0;
		addr[i]=0;
	}
	wait();

	//main loop
	while (true){
		readData(message,datavld);
		for(int i=0;i<N;i++){
			data[i] = message[i].data;
			addr[i] = message[i].addr;
			//std::cout <<"arditere check  " << i <<"  :  addr  " << addr[i-1]<<std::endl;
		}
		for(int i=1;i<=N;i++){
			arbiterOut[i-1] = arbiterCheck(datavld,addr,i);
			//std::cout <<"arbiterOut:  " << arbiterOut[i-1] << std::endl;
		}
		for(int i=0;i<N;i++){
			convertTOBinary(arbiterOut[i],arbiterOutBinary);
			outputControl(arbiterOutBinary,data,i);
		}			
	}
}

template<int N> void switchBL <N> ::readData(Data_t message[N],bool datavld[N]){
	for(int i=0;i<N;i++){
		wait(10 , SC_NS);
		//if(!inp[i].Empty()){
		message[i] =  inp[i].Pop();
		//std::cout <<"read  " << i <<"  :  " << message[i].data <<"  , addr: "<< message[i].addr << std::endl;
		datavld[i] = 1;
		
		//}
	}
}

template<int N> int switchBL<N>::arbiterCheck(bool datavld[N],int addr[N],int outpaddr){
	int temp=0;
	for(int i=0;i<N;i++){
		//std::cout <<"arditere check  " << i <<"  :  addr  " << addr[i]<<"  ,  "<< datavld[i]<< std::endl;
		if(datavld[i]==1 && addr[i] == outpaddr){
			temp = temp + (1<<i);
			datavld[i] = 0;
		}
	}
	std::cout <<"temp:  " <<temp << std::endl;
	return temp;
}
	
template<int N> void switchBL<N>::outputControl(char check[N],int data[N],int numberOfPort){
	for(int i=0;i<N;i++){
		if(check[i]==1){
			sum[numberOfPort].Push(data[i]);
		}
	}
}
template<int N> void switchBL<N>:: convertTOBinary(int arbiterOut,char control[N]){
	int temp= arbiterOut;
	for(int i=0;i<N;i++){
		control[i]= temp%2;
		temp = temp/2;
	}
}
