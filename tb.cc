#include <systemc.h>
#include <connections/connections.h>

#include"switchBL.h"
#include"source.h"
#include"sink.h"

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

//main  


int sc_main(int argc, char *argv[])
{
  tb my_testbench("my_testbench");
  sc_start();
  cout << "CMODEL PASS" << endl;
  return 0;
};


