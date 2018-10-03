#include "IRdata_template.hpp"

static void ZeroMemory(void *dest, int size)
{
	for(int i=0; i<size; i++)
		((char*)dest)[i]=0;
}

IRtemplate::IRtemplate()
{
	IRCommand com;
	ZeroMemory(&com, sizeof(com));
	
	//NEC format
	com.transmit = 562;
	com.leader[0] = 16;
	com.leader[1] = 8;
	com.one[0] = 1;
	com.one[1] = 3;
	com.zero[0] = 1;
	com.zero[1] = 1;
	com.tail = 192;		//108 ms
	
	config.push_back(com);
	
	ZeroMemory(&com, sizeof(com));
	
	//家電協フォーマット (AEHA)
	com.transmit = 425;
	com.leader[0] = 8;
	com.leader[1] = 4;
	com.one[0] = 1;
	com.one[1] = 3;
	com.zero[0] = 1;
	com.zero[1] = 1;
	com.tail = 31;
	
	config.push_back(com);
	
	ZeroMemory(&com, sizeof(com));
	
	//SONY format
	com.transmit = 600;
	com.leader[0] = 4;
	com.one[0] = 1;
	com.one[1] = 2;
	com.zero[0] = 1;
	com.zero[1] = 1;
	com.tail = 30;
	
	config.push_back(com);
	
	ZeroMemory(&com, sizeof(com));
	
	//IrisOyama format
	com.transmit = 500;
	com.leader[0] = 4;
	com.leader[1] = 2;
	com.leader[2] = 11;
	com.leader[3] = 2;
	com.leader[4] = 3;
	com.one[0] = 1;
	com.one[1] = 3;
	com.zero[0] = 1;
	com.zero[1] = 1;
	com.tail = 19;
	
	config.push_back(com);
}



