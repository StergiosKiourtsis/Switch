#include "switch.h"


void arbiter::arbiter_main(void){


sc_int<16> data0,data1,data2,dataToSend;
sc_int<5> addr0,addr1,addr2,addrToSend;
	sc_int<3> check = 0;
	bool data0vld,data1vld,data2vld;
	sc_int<5> arbiterOut0 = 0;
	sc_int<5> arbiterOut1 = 0;
	sc_int<5> arbiterOut2 = 0;

	data0= 0;
    addr0= 0;
	data1= 0;
    addr1= 0;
	data2= 0;
    addr2= 0;
	dataToSend = 0;
    addrToSend = 0;
	//RESET
	inp0Data_rd.write( 0 );
	inp1Data_rd.write( 0 );
	inp2Data_rd.write( 0 );
	////////////////////////
	outp0Data.write( 0 );
	outp0Data_vld.write( 0 );
	outp1Data.write( 0 );
	outp1Data_vld.write( 0 );
	outp2Data.write( 0 );
	outp2Data_vld.write( 0 );
	wait();
	
	//main loop
	while (true){

		readData(data0,addr0,data0vld,data1,addr1,data1vld,data2,addr2,data2vld);
		//std::cout << "data0 :"<< data0<< "   ,data0vld :"<< data0vld << std::endl;
		//std::cout << "data1 :"<< data1<< "   ,data1vld :"<< data1vld << std::endl;	
		arbiterOut0 = arbiterCheck0(data0vld,data1vld,data2vld,addr0,addr1,addr2);
		arbiterOut1 = arbiterCheck1(data0vld,data1vld,data2vld,addr0,addr1,addr2);
		arbiterOut2 = arbiterCheck2(data0vld,data1vld,data2vld,addr0,addr1,addr2);
		std::cout << "arbiterOut1: " << arbiterOut0 << std::endl;
		std::cout << "arbiterOut2: " << arbiterOut1 << std::endl;
		std::cout << "arbiterOut3: " << arbiterOut2 << std::endl;
		output0Control(arbiterOut0,data0,data1,data2);
		output1Control(arbiterOut1,data0,data1,data2);
		output2Control(arbiterOut2,data0,data1,data2);
		
		
	}
	
}

void arbiter::readData(sc_int<16> &data0,sc_int<5> &data0adress,bool &data0vld,sc_int<16> &data1,sc_int<5> &data1adress,bool &data1vld,sc_int<16> &data2,sc_int<5> &data2adress,bool &data2vld){
	inp0Data_rd.write( 1 );
	wait(10 , SC_NS);
	if(inp0Data_vld.read()){
		data0 = inp0Data.read();
		data0vld = 1;

		inp0Addr_rd.write( 1 );
		do{
			wait();
		} while (!inp0Addr_vld.read());
		data0adress = inp0Addr.read();
		inp0Addr_rd.write( 0 );

	}
	inp0Data_rd.write( 0 );
	std::cout << "Read data 1 " << " :" << data0<<" , "<< data0adress << std::endl;

	inp1Data_rd.write( 1 );
	wait(10 , SC_NS);
	if(inp1Data_vld.read()){
		data1 = inp1Data.read();
		data1vld = 1;

		inp1Addr_rd.write( 1 );
		do{
			wait();
		} while (!inp1Addr_vld.read());
		data1adress = inp1Addr.read();
		inp1Addr_rd.write( 0 );

	}
	inp1Data_rd.write( 0 );

	std::cout << "Read data 2 " << " :" << data1<<" , "<< data1adress << std::endl;


	inp2Data_rd.write( 1 );
	wait(10 , SC_NS);
	if(inp2Data_vld.read()){
		data2 = inp2Data.read();
		data2vld = 1;

		inp2Addr_rd.write( 1 );
		do		{
			wait();
		} while (!inp2Addr_vld.read());
		data2adress = inp2Addr.read();
		inp2Addr_rd.write( 0 );

	}
	inp2Data_rd.write( 0 );

	std::cout << "Read data 3 " << " :" << data2<<" , "<< data2adress << std::endl;

}

sc_int<5> arbiter::arbiterCheck0(bool &data0vld,bool &data1vld,bool &data2vld,sc_int<5> addr0,sc_int<5> addr1,sc_int<5> addr2){
	sc_int<5> temp=0;
	if(data0vld==1 && addr0 == 1){
		temp += 1; //001;
		data0vld = 0;
	}	
	if(data1vld==1 && addr1 == 1){
		temp += 2; //010
		data1vld = 0;
	}
	if(data2vld==1 && addr2 == 1){
		temp += 4; //010
		data2vld = 0;
	}
	//std::cout << temp << std::endl;
	return temp;
}

sc_int<5> arbiter::arbiterCheck1(bool &data0vld,bool &data1vld,bool &data2vld,sc_int<5> addr0,sc_int<5> addr1,sc_int<5> addr2){
	sc_int<5> temp=0;
	if(data0vld==1 && addr0 == 2){
		temp += 1; //001;
		data0vld = 0;
	}	
	if(data1vld==1 && addr1 == 2){
		temp += 2; //010
		data1vld = 0;
	}
	if(data2vld==1 && addr2 == 2){
		temp += 4; //010
		data2vld = 0;
	}
	//std::cout << temp << std::endl;
	return temp;
}

sc_int<5> arbiter::arbiterCheck2(bool &data0vld,bool &data1vld,bool &data2vld,sc_int<5> addr0,sc_int<5> addr1,sc_int<5> addr2){
	sc_int<5> temp=0;
	if(data0vld==1 && addr0 == 3){
		temp += 1; //001;
		data0vld = 0;
	}	
	if(data1vld==1 && addr1 == 3){
		temp += 2; //010
		data1vld = 0;
	}
	if(data2vld==1 && addr2 == 3){
		temp += 4; //010
		data2vld = 0;
	}
	//std::cout << temp << std::endl;
	return temp;
}

void arbiter::output0Control(sc_int<5> arbiterOut,sc_int<16> &data0,sc_int<16> &data1,sc_int<16> &data2){
	switch (arbiterOut){
		//none
		case 0:
			outp0Data_vld.write( 0 );
			break;
		//only inp0
		case 1:
			outp0Data.write(data0);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;	
		//only inp1
		case 2:
			outp0Data.write(data1);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;
		//inp0 ,inp1
		case 3:
			outp0Data.write(data0);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			outp0Data.write(data1);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;
		//only inp2
		case 4:
			outp0Data.write(data2);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;
		//inp0 inp2
		case 5:
			outp0Data.write(data0);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			outp0Data.write(data2);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;
		//inp1,inp2
		case 6:
			outp0Data.write(data1);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			outp0Data.write(data2);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;
		//all inp0 , inp1 , inp2
		case 7:
			outp0Data.write(data0);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			outp0Data.write(data1);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			outp0Data.write(data2);
			outp0Data_vld.write( 1 );
			do{
				wait();
			}while(!outp0Data_rd.read());
			outp0Data_vld.write( 0 );
			break;		
		//only inp2
		//none
		default:
			outp0Data_vld.write( 0 );
			break;
		}


}

void arbiter::output1Control(sc_int<5> arbiterOut,sc_int<16> &data0,sc_int<16> &data1,sc_int<16> &data2){
	switch (arbiterOut){
		//none
		case 0:
			outp1Data_vld.write( 0 );
			break;
		//only inp0
		case 1:
			outp1Data.write(data0);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;	
		//only inp1
		case 2:
			outp1Data.write(data1);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;
		//inp0 ,inp1
		case 3:
			outp1Data.write(data0);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );

			outp1Data.write(data1);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;
		//only inp2
		case 4:
			outp1Data.write(data2);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;
		//inp0 inp2
		case 5:
			outp1Data.write(data0);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			outp1Data.write(data2);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;
		//inp1,inp2
		case 6:
			outp1Data.write(data1);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			outp1Data.write(data2);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;
		//all inp0 , inp1 , inp2
		case 7:
			outp1Data.write(data0);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			outp1Data.write(data1);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			outp1Data.write(data2);
			outp1Data_vld.write( 1 );
			do{
				wait();
			}while(!outp1Data_rd.read());
			outp1Data_vld.write( 0 );
			break;		
		//only inp2
		//none
		default:
			outp1Data_vld.write( 0 );
			break;
		}


}

void arbiter::output2Control(sc_int<5> arbiterOut,sc_int<16> &data0,sc_int<16> &data1,sc_int<16> &data2){
	switch (arbiterOut){
		//none
		case 0:
			outp2Data_vld.write( 0 );
			break;
		//only inp0
		case 1:
			outp2Data.write(data0);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;	
		//only inp1
		case 2:
			outp2Data.write(data1);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;
		//inp0 ,inp1
		case 3:
			outp2Data.write(data0);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			outp2Data.write(data1);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;
		//only inp2
		case 4:
			outp2Data.write(data2);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;
		//inp0 inp2
		case 5:
			outp2Data.write(data0);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			outp2Data.write(data2);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;
		//inp1,inp2
		case 6:
			outp2Data.write(data1);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			outp2Data.write(data2);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;
		//all inp0 , inp1 , inp2
		case 7:
			outp2Data.write(data0);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			outp2Data.write(data1);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			outp2Data.write(data2);
			outp2Data_vld.write( 1 );
			do{
				wait();
			}while(!outp2Data_rd.read());
			outp2Data_vld.write( 0 );
			break;		
		//only inp2
		//none
		default:
			outp2Data_vld.write( 0 );
			break;
		}


}