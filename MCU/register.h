#include <systemc.h>
#include "reg_if.h"
#include <math.h>

class register_choose: public sc_module, reg_if
{
public:
	register_choose(sc_module_name name_, unsigned int start_address, unsigned int end_address):sc_module(name_),reg_start_address(start_address),reg_end_address(end_address)
	{
		sc_assert(end_address >= start_address);
		registers = new char[end_address - start_address];
	}

	~register_choose()
	{
		if(registers)
		{
			delete registers;
			registers = 0;
		}
	}

	transfer_status read(unsigned address, unsigned char& data)
	{
		if(address < reg_start_address || address > reg_end_address)
		{
			data = 0;
			return TRANSFER_ERROR;
		}
		data = registers[address - reg_start_address];
		return TRANSFER_OK;
	}

	transfer_status write(unsigned address, unsigned char& data)
	{
		if(address < reg_start_address || address > reg_end_address)
		{
			return TRANSFER_ERROR;
		}
		registers[address - reg_start_address] = data;
		return TRANSFER_OK;
	}

	transfer_status setbit(unsigned address, unsigned position, bit data)
	{
		if(address < reg_start_address || address > reg_end_address)
		{
			return TRANSFER_ERROR;
		}
		char masks;
		masks = pow(2, position);
		switch (data)
		{
		case BIT_CLEAN:
			masks = ~masks;
			registers[address - reg_start_address] = registers[address - reg_start_address] & masks;
			break;
		case BIT_ONE:
			registers[address - reg_start_address] = registers[address - reg_start_address] | masks;
			break;
		default:
			break;
		}
		return TRANSFER_OK;
	}

	unsigned int start_address()
	{
		return reg_start_address;
	}

	unsigned int end_address()
	{
		return reg_end_address;
	}

private:
	char* registers;
	unsigned int reg_start_address,reg_end_address;
};

class reg_work_choose:public reg_read_if, reg_write_if,sc_module
{
public:
	reg_work_choose(sc_module_name name_):sc_module(name_)
	{
		work_register = 0;
	}

	transfer_status read(unsigned int address, unsigned char& data)
	{
		data = work_register;
		return TRANSFER_OK;
	}

	transfer_status write(unsigned int address, unsigned char& data)
	{
		work_register = data;
		return TRANSFER_OK;
	}

private:
	char work_register;
};