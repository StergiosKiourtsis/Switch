#include "tb.h"


void tb::source0(void){
    
    sc_int<16> data0 = 0;
    sc_int<5> addr0 = 0;

    inp0Data.write( data0 );
    inp0Data_vld.write( 0 );

    inp0Addr.write( addr0 );
    inp0Addr_vld.write( 0 );


    //reset
    rst.write( 1 );
    wait();
    rst.write( 0 );

    wait();
    
    for(int i=1; i <10;i++){
        data0 = 200+i;
        addr0 = (i%3)+1;
        
        inp0Data.write(data0);
        inp0Data_vld.write( 1 );
        do{
            wait();
        }while(!inp0Data_rd.read());
        inp0Data_vld.write( 0 );
        
        inp0Addr.write(addr0);
        inp0Addr_vld.write( 1 );
        do{
            wait();
        }while(!inp0Addr_rd.read());
        inp0Addr_vld.write( 0 );

    }
    
    data0 = 2222;
    addr0 = 3;
    
    inp0Data.write(data0);
    inp0Data_vld.write( 1 );
    do{
        wait();
    }while(!inp0Data_rd.read());
    inp0Data_vld.write( 0 );
    
    inp0Addr.write(addr0);
    inp0Addr_vld.write( 1 );
    do{
        wait();
    }while(!inp0Addr_rd.read());
    inp0Addr_vld.write( 0 );
}

void tb::sink0(void){
    sc_int<16> indata;
    for(int i = 0;i<9;i++){
        
        outp0Data_rd.write( 1 );
        do{
            wait();
        }while (!outp0Data_vld.read());
	    indata = outp0Data.read();
	    
        outp0Data_rd.write( 0 );

        std::cout << "Sink 1 " << " :" << indata << std::endl;
    }

}


void tb::source1(void){
    

    sc_int<16> data1 = 0;
    sc_int<5> addr1 = 0;

    inp1Data.write( data1 );
    inp1Data_vld.write( 0 );

    inp1Addr.write( addr1 );
    inp1Addr_vld.write( 0 );


    //wait();

    for(int i=0; i <9;i++){
        data1 = 300+i;
        addr1 = (i%3)+1;
        
        inp1Data.write(data1);
        inp1Data_vld.write( 1 );
        do{
            wait();
        }while(!inp1Data_rd.read());

        inp1Data_vld.write( 0 );
        
        inp1Addr.write(addr1);
        inp1Addr_vld.write( 1 );
        do{
            wait();
        }while(!inp1Addr_rd.read());
        inp1Addr_vld.write( 0 );
    }

    data1 = 3333;
    addr1 = 3;
    
    inp1Data.write(data1);
    inp1Data_vld.write( 1 );
    do{
        wait();
    }while(!inp1Data_rd.read());
    inp1Data_vld.write( 0 );
    
    inp1Addr.write(addr1);
    inp1Addr_vld.write( 1 );
    do{
        wait();
    }while(!inp1Addr_rd.read());
    inp1Addr_vld.write( 0 );
}

void tb::sink1(void){
    sc_int<16> indata;
    for(int i = 0;i<9;i++){
        
        outp1Data_rd.write( 1 );
        do{
            wait();
        }while (!outp1Data_vld.read());
	    indata = outp1Data.read();
	    
        outp1Data_rd.write( 0 );

        std::cout << "Sink 2 " << " :" << indata << std::endl;
    }

}

void tb::source2(void){
    

    sc_int<16> data2 = 0;
    sc_int<5> addr2 = 0;

    inp2Data.write( data2 );
    inp2Data_vld.write( 0 );

    inp2Addr.write( addr2 );
    inp2Addr_vld.write( 0 );



    //wait();

    for(int i=0; i <9;i++){
        data2 = 400+i;
        addr2 = (i%3)+1;
        
        inp2Data.write(data2);
        inp2Data_vld.write( 1 );
        do{
            wait();
        }while(!inp2Data_rd.read());
        inp2Data_vld.write( 0 );
        
        inp2Addr.write(addr2);
        inp2Addr_vld.write( 1 );
        do{
            wait();
        }while(!inp2Addr_rd.read());
        inp2Addr_vld.write( 0 );
    }

    data2 = 4444;
    addr2 = 3;
    
    inp2Data.write(data2);
    inp2Data_vld.write( 1 );
    do{
        wait();
    }while(!inp2Data_rd.read());
    inp2Data_vld.write( 0 );
    
    inp2Addr.write(addr2);
    inp2Addr_vld.write( 1 );
    do{
        wait();
    }while(!inp2Addr_rd.read());
    inp2Addr_vld.write( 0 );
    
}

void tb::sink2(void){
    sc_int<16> indata;
    for(int i = 0;i<12;i++){
        
        outp2Data_rd.write( 1 );
        do{
            wait();
        }while (!outp2Data_vld.read());
	    indata = outp2Data.read();
	    
        outp2Data_rd.write( 0 );

        std::cout << "Sink 3 " << " :" << indata << std::endl;
    }
    sc_stop();
}