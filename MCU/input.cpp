#include <systemc.h>
#include <iostream>
//#include "register.h"
#include "handle_register.h"
//#define _REG_IF_H
//#include "reg_if.h"

using namespace std;

int sc_main(int, char **)
{
	sc_clock clk("Clk",20,SC_NS);
	//register Register("register",0,128);
	//register_choose Register("registers",0,128);
	Master master("Master");
	master.clk(clk);
	sc_start(2000,SC_NS);

	system("pause");

	return 0;
}