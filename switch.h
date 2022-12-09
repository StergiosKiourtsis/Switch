#include <systemc.h>
template<int N>
SC_MODULE( arbiter ){
	
	sc_in< bool > clk;
	sc_in< bool > rst;

	sc_in < sc_int<16> > inpData[N];
	sc_in < sc_uint<4> > inpAddr[N];
	sc_out< bool > inp_rd[N];
	sc_in< bool > inp_vld[N];

	sc_out < sc_int<16> > outpData[N];
	sc_in< bool > outpData_rd[N];
	sc_out< bool > outpData_vld[N];
	

	void arbiter_main(void){
		sc_int<16> data[N];
		sc_uint<4> addr[N];
		sc_uint<N> arbiterOut[N];
		bool datavld[N];
		char arbiterOutBinary[N];
		//RESET
		for(int i=0;i<N;i++){
			inp_rd[i].write( 0 );
			outpData[i].write( 0 );
			outpData_vld[i].write( 0 );
			datavld[i]=0;
			data[i]=0;
			addr[i]=0;
		}
		wait();

		//main loop
		while (true){
			readData(data,addr,datavld);
			for(int i=1;i<=N;i++){
				arbiterOut[i-1] = arbiterCheck(datavld,addr,i);
			}

			for(int i=0;i<N;i++){
				convertTOBinary(arbiterOut[i],arbiterOutBinary);
				outputControl(arbiterOutBinary,data,i);
			}			
		}
	}

	void readData(sc_int<16> data[N],sc_uint<4> address[N],bool datavld[N]){
		for(int i=0;i<N;i++){
			inp_rd[i].write( 1 );
			wait(10 , SC_NS);
			if(inp_vld[i].read()){
				data[i] = inpData[i].read();
				address[i] = inpAddr[i].read();
				datavld[i] = 1;
			}
			inp_rd[i].write( 0 );
		}
	}
	
	sc_uint<N> arbiterCheck(bool datavld[N],sc_uint<4> addr[N],sc_uint<N> outpaddr){
		sc_uint<N> temp=0;

		for(int i=0;i<N;i++){
			if(datavld[i]==1 && addr[i] == outpaddr){
				temp += (1<<i);
				datavld[i] = 0;
			}
		}
		std::cout <<"temp:  " <<temp << std::endl;
		return temp;
	}
	

	void convertTOBinary(sc_uint<N> arbiterOut,char control[N]){
		sc_uint<N> temp= arbiterOut;
		for(int i=0;i<N;i++){
			control[i]= temp%2;
			temp = temp/2;
		}
	}

	void outputControl(char check[N],sc_int<16> data[N],int numberOfPort){
		for(int i=0;i<N;i++){
			if(check[i]==1){
				outpData[numberOfPort].write(data[i]);
				outpData_vld[numberOfPort].write(1);
				do{
					wait();
				}while(!outpData_rd[numberOfPort].read());
				outpData_vld[numberOfPort].write(0);
			}
		}
	}

	SC_CTOR( arbiter ){
		SC_CTHREAD(arbiter_main,clk.pos());
		reset_signal_is(rst,true);
	}
};
