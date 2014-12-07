#include <systemc.h>
#include "register.h"

SC_MODULE(Master)
{
	sc_in_clk clk;
	register_choose *Register;
	void main_action();
	char data;
	unsigned int address;
	SC_CTOR(Master)
	{
		SC_CTHREAD(main_action,clk.pos());
		Register = new register_choose("register",0,128);
	}
};

void Master::main_action()
{
	wait();
	data = 32;
	address = Register->start_address();
	if(Register->write(address,data))
	{
		cout<<"ok"<<endl;
	}
}