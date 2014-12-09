#include <systemc.h>
#include "register.h"

SC_MODULE(Master)
{
	register_choose *Register;
	reg_work_choose *work_register;

	void main_action();
	unsigned int BitToNumber(char* bits, unsigned int totalNumber);
	char * numberToBit(unsigned char number);
	void BCF(unsigned int address, unsigned int position);
	void BSF(unsigned int address, unsigned int position);
	void MOVELW(char* data);
	void ADDLW(char* data);
	void MOVEWF(unsigned int address);
	void ANDLW(unsigned char data);

	unsigned char data;
	char inputs[15];
	unsigned int address;

	SC_CTOR(Master)
	{
		SC_METHOD(main_action);
		Register = new register_choose("register",0,128);
		work_register = new reg_work_choose("work_register");
	}
};

void Master::BCF(unsigned int address, unsigned int position)
{
	if(Register->setbit(address,position,BIT_CLEAN))
	{
		if(Register->read(address,data))
		{
			char work_result[9];
			strcpy(work_result, numberToBit(data));
			cout<<"��f("<<address<<")��"<<position<<"λΪ0��f���Ϊ"<<work_result<<endl;
		}
	}
}

void Master::BSF(unsigned int address, unsigned int position)
{
	if(Register->setbit(address,position,BIT_ONE))
	{
		if(Register->read(address,data))
		{
			char work_result[9];
			strcpy(work_result, numberToBit(data));
			cout<<"��f("<<address<<")��"<<position<<"λΪ1��f���Ϊ"<<work_result<<endl;
		}
	}
}

void Master::MOVELW(char* data)
{
	unsigned char number = (unsigned char)BitToNumber(data,8);
	if(work_register->write(0,number))
	{
		cout<<"�������͵�W��W��ֵΪ"<<data<<endl;
	}
}

void Master::ADDLW(char* data)
{
	unsigned char number = (unsigned char)BitToNumber(data,8);
	unsigned char work_number;
	if(work_register->read(0,work_number))
	{
		work_number += number;
		work_register->write(0,work_number);
		char work_result[9];
		strcpy(work_result, numberToBit(work_number));
		cout<<"��������W��W��ֵΪ"<<work_result<<endl;
	}
}

void Master::MOVEWF(unsigned int address)
{
	unsigned char work_number;
	if(work_register->read(0,work_number))
	{
		if(Register->write(address,work_number))
		{
			char work_result[9];
			strcpy(work_result, numberToBit(work_number));
			cout<<"W��ֵ�͵�f("<<address<<")�У�fֵΪ"<<work_result<<endl;
		}
	}
}

void Master::ANDLW(unsigned char data)
{
	unsigned char work_number;
	if(work_register->read(0,work_number))
	{
		work_number += data;
		work_register->write(0,work_number);
		char work_result[9];
		strcpy(work_result, numberToBit(work_number));
		cout<<"��������W��W�Ľ��Ϊ"<<work_result<<endl;
	}
}