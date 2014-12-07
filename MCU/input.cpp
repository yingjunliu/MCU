#include <systemc.h>
#include <iostream>
#include <math.h>
#include "handle_register.h"

using namespace std;

int sc_main(int, char **)
{
	Master master("Master");
	sc_start();

	system("pause");

	return 0;
}

unsigned int Master::BitToNumber(char * bits, unsigned int totalNumber)
{
	unsigned int position = 0;

	for(int i = totalNumber - 1, k = 0; i >= 0; i--, k++)
	{
		position += pow(2,k) * ( bits[i] - '0' );
	}

	return position;
}

char* Master::numberToBit(unsigned char number)
{
	char bits[9];

	for(int i = 7; i >= 0; i--)
	{
		bits[i] = (number % 2) + '0';
		number = number / 2;
	}
	bits[8] = '\0';

	return bits;
}

void Master::main_action()
{
	while(true)
	{
		cin>>inputs;
		inputs[14] = '\0';
		//data = (char)inputs;
		if(strcmp(inputs,"00000000000000") == 0)
			break;
		else if(inputs[0] == '0' && inputs[1] == '1')
		{
			if(inputs[2] == '0' && inputs[3] == '0')
			{
				BCF(BitToNumber(&inputs[7],7),BitToNumber(&inputs[4],3));
			}
			else if(inputs[2] == '0' && inputs[3] == '1')
			{
				BSF(BitToNumber(&inputs[7],7),BitToNumber(&inputs[4],3));
			}
		}
		else
		{
			char instruction[7];
			strncpy(instruction,inputs,6);
			instruction[6] =  '\0';
			if(strcmp(instruction,"110000") == 0)
			{
				MOVELW(&inputs[6]);
			}
			else if(strcmp(instruction,"111110") == 0)
			{
				ADDLW(&inputs[6]);
			}
			else if(strcmp(instruction,"000000") == 0)
			{
				MOVEWF(BitToNumber(&inputs[7],7));
			}
			else if(strcmp(instruction,"111001") == 0)
			{
				unsigned char data = (unsigned char)BitToNumber(&inputs[6],8);
				ANDLW(data);
			}
		}
	}
}