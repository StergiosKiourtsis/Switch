#include <systemc.h>
#include "switch.h"
#include "tb.h"



SC_MODULE ( SYSTEM ){
	tb *tb0;
	arbiter *arbiter0;
	
	sc_signal< bool > rst_sig;
	sc_signal< sc_int<16> > inp0Data_sig;
	sc_signal< bool > inp0Data_rd_sig;
	sc_signal< bool > inp0Data_vld_sig;
	sc_signal< sc_int<5> > inp0Addr_sig;
	sc_signal< bool > inp0Addr_rd_sig;
	sc_signal< bool > inp0Addr_vld_sig;
	sc_signal< sc_int<16> > inp1Data_sig;
	sc_signal< bool > inp1Data_rd_sig;
	sc_signal< bool > inp1Data_vld_sig;
	sc_signal< sc_int<5> > inp1Addr_sig;
	sc_signal< bool > inp1Addr_rd_sig;
	sc_signal< bool > inp1Addr_vld_sig;
	sc_signal< sc_int<16> > inp2Data_sig;
	sc_signal< bool > inp2Data_rd_sig;
	sc_signal< bool > inp2Data_vld_sig;
	sc_signal< sc_int<5> > inp2Addr_sig;
	sc_signal< bool > inp2Addr_rd_sig;
	sc_signal< bool > inp2Addr_vld_sig;
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
		tb0->inp0Data_rd( inp0Data_rd_sig);
		tb0->inp0Data_vld( inp0Data_vld_sig);
		tb0->inp0Addr( inp0Addr_sig);
		tb0->inp0Addr_rd( inp0Addr_rd_sig);
		tb0->inp0Addr_vld( inp0Addr_vld_sig);
		tb0->inp1Data( inp1Data_sig);
		tb0->inp1Data_rd( inp1Data_rd_sig);
		tb0->inp1Data_vld( inp1Data_vld_sig);
		tb0->inp1Addr( inp1Addr_sig);
		tb0->inp1Addr_rd( inp1Addr_rd_sig);
		tb0->inp1Addr_vld( inp1Addr_vld_sig);		
		tb0->inp2Data( inp2Data_sig);
		tb0->inp2Data_rd( inp2Data_rd_sig);
		tb0->inp2Data_vld( inp2Data_vld_sig);
		tb0->inp2Addr( inp2Addr_sig);
		tb0->inp2Addr_rd( inp2Addr_rd_sig);
		tb0->inp2Addr_vld( inp2Addr_vld_sig);
		tb0->outp0Data( outp0Data_sig);
		tb0->outp0Data_rd( outp0Data_rd_sig);
		tb0->outp0Data_vld( outp0Data_vld_sig);
		tb0->outp1Data( outp1Data_sig);
		tb0->outp1Data_rd( outp1Data_rd_sig);
		tb0->outp1Data_vld( outp1Data_vld_sig);
		tb0->outp2Data( outp2Data_sig);
		tb0->outp2Data_rd( outp2Data_rd_sig);
		tb0->outp2Data_vld( outp2Data_vld_sig);

		arbiter0 = new arbiter("arbiter0");
		arbiter0->clk( clk_sig);
		arbiter0->rst( rst_sig);
		arbiter0->inp0Data( inp0Data_sig);
		arbiter0->inp0Data_rd( inp0Data_rd_sig);
		arbiter0->inp0Data_vld( inp0Data_vld_sig);
		arbiter0->inp0Addr( inp0Addr_sig);
		arbiter0->inp0Addr_rd( inp0Addr_rd_sig);
		arbiter0->inp0Addr_vld( inp0Addr_vld_sig);
		arbiter0->inp1Data( inp1Data_sig);
		arbiter0->inp1Data_rd( inp1Data_rd_sig);
		arbiter0->inp1Data_vld( inp1Data_vld_sig);
		arbiter0->inp1Addr( inp1Addr_sig);
		arbiter0->inp1Addr_rd( inp1Addr_rd_sig);
		arbiter0->inp1Addr_vld( inp1Addr_vld_sig);		
		arbiter0->inp2Data( inp2Data_sig);
		arbiter0->inp2Data_rd( inp2Data_rd_sig);
		arbiter0->inp2Data_vld( inp2Data_vld_sig);
		arbiter0->inp2Addr( inp2Addr_sig);
		arbiter0->inp2Addr_rd( inp2Addr_rd_sig);
		arbiter0->inp2Addr_vld( inp2Addr_vld_sig);
		arbiter0->outp0Data( outp0Data_sig);
		arbiter0->outp0Data_rd( outp0Data_rd_sig);
		arbiter0->outp0Data_vld( outp0Data_vld_sig);
		arbiter0->outp1Data( outp1Data_sig);
		arbiter0->outp1Data_rd( outp1Data_rd_sig);
		arbiter0->outp1Data_vld( outp1Data_vld_sig);
		arbiter0->outp2Data( outp2Data_sig);
		arbiter0->outp2Data_rd( outp2Data_rd_sig);
		arbiter0->outp2Data_vld( outp2Data_vld_sig);
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