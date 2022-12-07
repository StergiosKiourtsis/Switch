#include <systemc.h>

SC_MODULE( arbiter ){
	
	sc_in< bool > clk;
	sc_in< bool > rst;

	sc_in < sc_int<16> > inp0Data;
	sc_out< bool > inp0Data_rd;
	sc_in< bool > inp0Data_vld;

	sc_in < sc_int<5> > inp0Addr;
	sc_out< bool > inp0Addr_rd;
	sc_in< bool > inp0Addr_vld;

	sc_in< sc_int<16> > inp1Data;
	sc_out< bool > inp1Data_rd;
	sc_in< bool > inp1Data_vld;
	
	sc_in< sc_int<5> > inp1Addr;
	sc_out< bool > inp1Addr_rd;
	sc_in< bool > inp1Addr_vld;

	sc_in < sc_int<16> > inp2Data;
	sc_out< bool > inp2Data_rd;
	sc_in< bool > inp2Data_vld;

	sc_in < sc_int<5> > inp2Addr;
	sc_out< bool > inp2Addr_rd;
	sc_in< bool > inp2Addr_vld;

	sc_out < sc_int<16> > outp0Data;
	sc_in< bool > outp0Data_rd;
	sc_out< bool > outp0Data_vld;

	sc_out < sc_int<16> > outp1Data;
	sc_in< bool > outp1Data_rd;
	sc_out< bool > outp1Data_vld;

	sc_out < sc_int<16> > outp2Data;
	sc_in< bool > outp2Data_rd;
	sc_out< bool > outp2Data_vld;	

	void arbiter_main(void);
	void readData(sc_int<16> &data0,sc_int<5> &data0adress,bool &data0vld,sc_int<16> &data1,sc_int<5> &data1adress,bool &data1vld,sc_int<16> &data2,sc_int<5> &data2adress,bool &data2vld);
	sc_int<5> arbiterCheck0(bool &data0vld,bool &data1vld,bool &data2vld,sc_int<5> addr0,sc_int<5> addr1,sc_int<5> addr2);
	sc_int<5> arbiterCheck1(bool &data0vld,bool &data1vld,bool &data2vld,sc_int<5> addr0,sc_int<5> addr1,sc_int<5> addr2);
	sc_int<5> arbiterCheck2(bool &data0vld,bool &data1vld,bool &data2vld,sc_int<5> addr0,sc_int<5> addr1,sc_int<5> addr2);
	void output0Control(sc_int<5> arbiterOut,sc_int<16> &data0,sc_int<16> &data1,sc_int<16> &data2);
	void output1Control(sc_int<5> arbiterOut,sc_int<16> &data0,sc_int<16> &data1,sc_int<16> &data2);
	void output2Control(sc_int<5> arbiterOut,sc_int<16> &data0,sc_int<16> &data1,sc_int<16> &data2);

	SC_CTOR( arbiter ){
		SC_CTHREAD(arbiter_main,clk.pos());
		reset_signal_is(rst,true);
	}
};
