#include <systemc.h>
#include "switch.h"
#include "tb.h"



SC_MODULE ( SYSTEM ){
	tb *tb0;
	arbiter<3> *arbiter0;
	
	sc_signal< bool > rst_sig;
	sc_signal< sc_int<16> > inp0Data_sig;
	sc_signal< sc_uint<4> > inp0Addr_sig;
	sc_signal< bool > inp0_rd_sig;
	sc_signal< bool > inp0_vld_sig;
	sc_signal< sc_int<16> > inp1Data_sig;
	sc_signal< sc_uint<4> > inp1Addr_sig;
	sc_signal< bool > inp1_rd_sig;
	sc_signal< bool > inp1_vld_sig;
	sc_signal< sc_int<16> > inp2Data_sig;
	sc_signal< sc_uint<4> > inp2Addr_sig;
	sc_signal< bool > inp2_rd_sig;
	sc_signal< bool > inp2_vld_sig;
	sc_signal< sc_int<16> > outp0Data_sig;
	sc_signal< bool > outp0Data_rd_sig;
	sc_signal< bool > outp0Data_vld_sig;
	sc_signal< sc_int<16> > outp1Data_sig;
	sc_signal< bool > outp1Data_rd_sig;
	sc_signal< bool > outp1Data_vld_sig;
	sc_signal< sc_int<16> > outp2Data_sig;
	sc_signal< bool > outp2Data_rd_sig;
	sc_signal< bool > outp2Data_vld_sig;



	sc_clock clk_sig;
	
	SC_CTOR( SYSTEM )
		: clk_sig("clk_sig" , 10 , SC_NS)
	{
		tb0 = new tb("tb0");
		tb0->clk( clk_sig);
		tb0->rst( rst_sig);
		tb0->inp0Data( inp0Data_sig);
		tb0->inp0_rd( inp0_rd_sig);
		tb0->inp0_vld( inp0_vld_sig);
		tb0->inp0Addr( inp0Addr_sig);
		tb0->inp1Data( inp1Data_sig);
		tb0->inp1_rd( inp1_rd_sig);
		tb0->inp1_vld( inp1_vld_sig);
		tb0->inp1Addr( inp1Addr_sig);
		tb0->inp2Data( inp2Data_sig);
		tb0->inp2_rd( inp2_rd_sig);
		tb0->inp2_vld( inp2_vld_sig);
		tb0->inp2Addr( inp2Addr_sig);
		tb0->outp0Data( outp0Data_sig);
		tb0->outp0Data_rd( outp0Data_rd_sig);
		tb0->outp0Data_vld( outp0Data_vld_sig);
		tb0->outp1Data( outp1Data_sig);
		tb0->outp1Data_rd( outp1Data_rd_sig);
		tb0->outp1Data_vld( outp1Data_vld_sig);
		tb0->outp2Data( outp2Data_sig);
		tb0->outp2Data_rd( outp2Data_rd_sig);
		tb0->outp2Data_vld( outp2Data_vld_sig);

		arbiter0 = new arbiter<3>("arbiter0");
		arbiter0->clk( clk_sig);
		arbiter0->rst( rst_sig);
		arbiter0->inpData[0]( inp0Data_sig);
		arbiter0->inpAddr[0]( inp0Addr_sig);
		arbiter0->inp_rd[0]( inp0_rd_sig);
		arbiter0->inp_vld[0]( inp0_vld_sig);
		arbiter0->inpData[1]( inp1Data_sig);
		arbiter0->inpAddr[1]( inp1Addr_sig);
		arbiter0->inp_rd[1]( inp1_rd_sig);
		arbiter0->inp_vld[1]( inp1_vld_sig);
		arbiter0->inpData[2]( inp2Data_sig);
		arbiter0->inpAddr[2]( inp2Addr_sig);
		arbiter0->inp_rd[2]( inp2_rd_sig);
		arbiter0->inp_vld[2]( inp2_vld_sig);
		arbiter0->outpData[0]( outp0Data_sig);
		arbiter0->outpData_rd[0]( outp0Data_rd_sig);
		arbiter0->outpData_vld[0]( outp0Data_vld_sig);
		arbiter0->outpData[1]( outp1Data_sig);
		arbiter0->outpData_rd[1]( outp1Data_rd_sig);
		arbiter0->outpData_vld[1]( outp1Data_vld_sig);
		arbiter0->outpData[2]( outp2Data_sig);
		arbiter0->outpData_rd[2]( outp2Data_rd_sig);
		arbiter0->outpData_vld[2]( outp2Data_vld_sig);
	}

	~SYSTEM(){
		delete tb0;
		delete arbiter0;
	}
	
};


SYSTEM *top = NULL;

int sc_main( int argc , char* argv[]){
	
	top = new SYSTEM ("top");
	sc_start();
	
	return 0;	
}