#include <systemc.h>
#include <connections/connections.h>
#include "types.h"

SC_MODULE( Sink ){
	sc_in< bool > clk;
	sc_in< bool > rst;
	
	Connections::In<int> sum;
	const int cycles_val;

	void run(void);
	
	SC_HAS_PROCESS( Sink );
  	Sink(sc_module_name name_,const int &cycles_val_) :
    sc_module(name_),
    cycles_val(cycles_val_),
    sum("sum"),
    clk("clk"),
    rst("rst"){
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst,false);
  }
};

////////////
//Definition
////////////


void Sink::run(void){
		sum.Reset();
		int indata = 0;
		int i = 0;
		
		wait(20.0, SC_NS);
		
		wait();
			
		
    //while(true){
    for(int j=0;j<cycles_val;j++){
			indata = sum.Pop();
			std::cout<<name()<< "  " << i <<" : "<< indata << std::endl;
			i++;
		}
	}
