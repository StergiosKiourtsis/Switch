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
	void readData(Data_t message[N],bool datavld[N],int data[N],int addr[N], bool arbiterCheck[N]);
	void arbiterCheck(bool datavld[N],int addr[N],int outpaddr,bool req[N]);
	void outputControl(bool check[N],int data[N],int numberOfPort,bool req[N]);

	
	
  SC_HAS_PROCESS(switchBL);
  switchBL(sc_module_name name_) : sc_module(name_){
    SC_THREAD (switch_main);
    sensitive << clk.pos();
    async_reset_signal_is(rst,false);
  }
};


template<int N> void switchBL<N>::switch_main(void){
	Data_t message[N];
	int data[N];
	int addr[N];
	int arbiterOut[N];
	bool datavld[N];
	bool req[N][N];
	bool arbiterOutBinary[N];
	
	//RESET
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			req[i][j]=0;
		}
		inp[i].Reset();
		sum[i].Reset();
		datavld[i]=0;
		data[i]=0;
		addr[i]=0;
		arbiterOutBinary[i]=0;
	}
	wait();

	//main loop
	while (true){
		readData(message,datavld,data,addr,arbiterOutBinary);
		//for(int i=0;i<N;i++){
		//	std::cout << "data : "<<data[i]<<" ,  addr : " << addr[i] << " , ";
		//	std::cout << " " <<std::endl;
		//}
		for(int i=1;i<=N;i++){
			arbiterCheck(datavld,addr,i,req[i-1]);
		}

		//std::cout << "req:" <<std::endl;
		//for(int i=0;i<N;i++){
		//	for(int j=0;j<N;j++){
		//		std::cout << req[i][j] << " , ";
		//	}
		//	std::cout << " " <<std::endl;
		//}
		
		for(int i=0;i<N;i++){
			outputControl(arbiterOutBinary,data,i,req[i]);
		}

		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(req[j][i]){
					arbiterOutBinary[i]=1;
					break;
				}else{
					arbiterOutBinary[i]=0;
				}
			}
		}
		wait();			
	}
}

template<int N> void switchBL <N> ::readData(Data_t message[N],bool datavld[N],int data[N],int addr[N],bool arbiterCheck[N]){
	for(int i=0;i<N;i++){
		//wait(10 , SC_NS);
		if(arbiterCheck[i]==0){
			inp[i].PopNB(message[i]);
			data[i] = message[i].data;
			addr[i] = message[i].addr;
			datavld[i] = 1;
		}
	}
}

template<int N> void switchBL<N>::arbiterCheck(bool datavld[N],int addr[N],int outpaddr,bool req[N]){
	for(int i=0;i<N;i++){
		//std::cout <<"arditere check  " << i <<"  :  addr  " << addr[i]<<"  ,  "<< datavld[i]<< std::endl;
		if(datavld[i]==1 && addr[i] == outpaddr){
			datavld[i] = 0;
			req[i] = 1;
		}
	}
}
	
template<int N> void switchBL<N>::outputControl(bool check[N],int data[N],int numberOfPort,bool req[N]){
	for(int i=0;i<N;i++){
		if(req[i]==1){
			sum[numberOfPort].Push(data[i]);
			req[i]=0;
			break;
		}
	}
}
