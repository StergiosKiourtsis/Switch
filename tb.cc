#include <systemc.h>
#include <connections/connections.h>

#include"switchBL.h"

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
  	
	void run(void){
   
    inp.Reset();
    int i =0;
    int x = 0;
	 Data_t msg;

    wait(5.0, SC_NS);
    wait();
    
    //while(true){
    for(int j=0;j<16;j++){
    
      x = i;
    	msg.data = x+ start_val;
    	msg.addr = ((x+addr_val)%3)+1;
		inp.Push(msg);
		std::cout<< name() <<"   " << x <<" : a ="<< x+ start_val << "   b ="<< ((x+addr_val)%3)+1 <<std::endl;
		i++;
	 }
	 	msg.data = 10 * start_val;
    	msg.addr = 3;
		inp.Push(msg);
	}	
	
	
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SC_MODULE( Sink ){
	sc_in< bool > clk;
	sc_in< bool > rst;
	
	Connections::In<int> sum;
	const int cycles_val;

	void run(void){
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SC_MODULE( tb ){

  //CCS_DESIGN(Con) con;
  switchBL<3> block0;
  Source src1,src2,src3;
  Sink sink1,sink2,sink3;
  Connections::Combinational<Data_t> inp0,inp1,inp2;
  Connections::Combinational<int> sum0,sum1,sum2;

  sc_clock clk;
  sc_signal<bool> rst;
  
  SC_CTOR(tb) :
    block0("block0"),
    src1("src1", 100,0),
    src2("src2", 200,0),
    src3("src3", 300,1),
    sink1("sink1",17),  //using a member inside constrction sequence could lead to a runtime bug
    sink2("sink2",16),
    sink3("sink3",18),
    inp0("inp0"),
    inp1("inp1"),
    inp2("inp2"),
    sum0("sum0"),
    sum1("sum1"),
    sum2("sum2"),
    clk("clk", 1, SC_NS, 0.5,0,SC_NS,true),
    rst("rst") {
    
    block0.clk(clk);
    block0.rst(rst);

    src1.clk(clk);
    src1.rst(rst);
    src2.clk(clk);
    src2.rst(rst);
    src3.clk(clk);
    src3.rst(rst);
    
    sink1.clk(clk);
    sink1.rst(rst);
    sink2.clk(clk);
    sink2.rst(rst);
    sink3.clk(clk);
    sink3.rst(rst);
    
    src1.inp(inp0);
	 src2.inp(inp1);
	 src3.inp(inp2);
	 
    block0.inp[0](inp0);
    block0.inp[1](inp1);
    block0.inp[2](inp2);
    block0.sum[0](sum0);
    block0.sum[1](sum1);
    block0.sum[2](sum2);
   
    sink1.sum(sum0);
 	 sink2.sum(sum1);
 	 sink3.sum(sum2);
    
    SC_THREAD(run);
  }
    void run() {
    //reset
    rst = 1;
    wait(10.5, SC_NS);
    rst = 0;
    cout << "@" << sc_time_stamp() << " Asserting Reset " << endl ;
    wait(1, SC_NS);
    cout << "@" << sc_time_stamp() << " Deasserting Reset " << endl ;
    rst = 1;
    wait(10000,SC_NS);
    cout << "@" << sc_time_stamp() << " Stop " << endl ;
    sc_stop();
  }
  
};


int sc_main(int argc, char *argv[])
{
  tb my_testbench("my_testbench");
  sc_start();
  cout << "CMODEL PASS" << endl;
  return 0;
};


