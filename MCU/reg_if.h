#include <systemc.h>

enum transfer_status{TRANSFER_OK = 0, TRANSFER_ERROR};
enum bit{BIT_CLEAN = 0, BIT_ONE};

class reg_read_if: public sc_interface
{
public:
	virtual transfer_status read(unsigned int address, char& data) = 0;
};
class reg_write_if: public sc_interface
{
public:
	virtual transfer_status write(unsigned int address, char& data) = 0;
};

class reg_set_if: public sc_interface
{
public:
	virtual transfer_status setbit(unsigned int address, unsigned int position, bit data) = 0;
};

class reg_if: public reg_read_if,public reg_write_if,public reg_set_if
{
public:
	virtual unsigned int start_address() = 0;
	virtual unsigned int end_address() = 0;
};