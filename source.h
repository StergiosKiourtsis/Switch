#include <systemc.h>
#include <connections/connections.h>
#include "types.h"

SC_MODULE( Source ){
	sc_in< bool > clk;
	sc_in< bool > rst;
	const int start_val;
	const int addr_val;
	Connections::Out<Data_t> inp;
	
  SC_HAS_PROCESS(Source);

  Source(sc_module_name name_, const int &start_val_,const int &addr_val_) :
    sc_module(name_),
    inp("inp"),
    clk("clk"),
    rst("rst"),
    start_val(start_val_),
    addr_val(addr_val_){
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst,false);
  }
  	
	void run(void);	
	
};


////////////
//Definition
////////////

	void Source::run(void){
   
    inp.Reset();
    int i =0;
    int x = 0;
	  Data_t msg;

    wait();
    
    //while(true){
    for(int j=0;j<16;j++){
    
      x = i;
    	msg.data = x+ start_val;
    	msg.addr = ((x+addr_val)%3)+1;
		  inp.Push(msg);
		  std::cout<< name() <<"   " << x <<" : a ="<< x+ start_val << "   b ="<< ((x+addr_val)%3)+1 <<std::endl;
		  i++;
      wait();
	 }
	 	msg.data = 10 * start_val;
    msg.addr = 3;
		inp.Push(msg);
	}	
