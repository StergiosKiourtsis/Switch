#ifndef TYPES_H
#define TYPES_H
#include <iostream>
#include <connections/marshaller.h>

class Data_t {
public:	
  int data;
  int addr;
  static const int width = 64;

  inline friend std::ostream& operator << (std::ostream& os, const Data_t& d_t) {
    os << d_t.data << " " << d_t.addr << "\n";
    return os;
  }

  inline friend void sc_trace(sc_trace_file* tf, const Data_t& d_t, const std::string& name) {
	  sc_trace(tf, d_t.data, name + ".data");
          sc_trace(tf, d_t.addr, name + ".addr");
  }
  template<unsigned int Size>
  void Marshall(Marshaller<Size>& m) {
    m& data; m& addr;	   
  }	  
};
#endif
