#include <systemc.h>

SC_MODULE( tb ){
	
	sc_in< bool > clk;
	sc_out< bool > rst;

	sc_out< sc_int<16> > inp0Data;
	sc_in< bool > inp0Data_rd;
	sc_out< bool > inp0Data_vld;

	sc_out< sc_int<5> > inp0Addr;
	sc_in< bool > inp0Addr_rd;
	sc_out< bool > inp0Addr_vld;

	sc_out< sc_int<16> > inp1Data;
	sc_in< bool > inp1Data_rd;
	sc_out< bool > inp1Data_vld;

	sc_out< sc_int<5> > inp1Addr;
	sc_in< bool > inp1Addr_rd;
	sc_out< bool > inp1Addr_vld;

	sc_out< sc_int<16> > inp2Data;
	sc_in< bool > inp2Data_rd;
	sc_out< bool > inp2Data_vld;

	sc_out< sc_int<5> > inp2Addr;
	sc_in< bool > inp2Addr_rd;
	sc_out< bool > inp2Addr_vld;

	sc_in< sc_int<16> > outp0Data;
	sc_out< bool > outp0Data_rd;
	sc_in< bool > outp0Data_vld;

	sc_in< sc_int<16> > outp1Data;
	sc_out< bool > outp1Data_rd;
	sc_in< bool > outp1Data_vld;

	sc_in< sc_int<16> > outp2Data;
	sc_out< bool > outp2Data_rd;
	sc_in< bool > outp2Data_vld;	
	
	void source0(void);
	void source1(void);
	void source2(void);
	void sink0(void);
	void sink1(void);
	void sink2(void);

	SC_CTOR( tb ){
		SC_CTHREAD( source0, clk.pos() );
		SC_CTHREAD( sink0, clk.pos() );

		SC_CTHREAD( source1, clk.pos() );
		SC_CTHREAD( sink1, clk.pos() );

		SC_CTHREAD( source2, clk.pos() );
		SC_CTHREAD( sink2, clk.pos() );
	}
};