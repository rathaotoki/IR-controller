
#include "IRdata_Mitsubishi_Kirigamine.hpp"

Kirigamine::Kirigamine()
{
	data.data_size = 18;
	data.repeats = 2;
	
	//customer codes
	data.data[0] = 0x23;
	data.data[1] = 0xCB;
	data.data[2] = 0x02<<4;	//only higher 4 bits
	
	//app data (constants)
	data.data[3] = 0x01;
	data.data[8] = 0x30;
	//data.data[4] = 0x30;
}

void Kirigamine::AppCalcParity()
{
	for(int i=0; i<(data.data_size-1); i++)
		data.data[data.data_size-1] += data.data[i];
}

void Kirigamine::setDefault()
{
	setMode(Mode::COOL);
	setTemperature(28);
	setAirFlow(AirFlow::AUTO);
	setAirDirection(AirDirection::MOVE);
	setInternalCleaning(true);
	setCurrentWeak(true);
}

void Kirigamine::setMode(Mode mode)
{
	switch(mode)
	{
		case Mode::COOL:
			copyBits(&data.data[6], 3<<3, 3, 4);
			copyBits(&data.data[8], 3<<1, 1, 2);
			break;
		
		case Mode::DRY_WEAK:
			copyBits(&data.data[6], 2<<3, 3, 4);
			copyBits(&data.data[8], 2<<1, 1, 2);
			break;
		
		case Mode::DRY_NORMAL:
			copyBits(&data.data[6], 2<<3, 3, 4);
			copyBits(&data.data[8], 1<<1, 1, 2);
			break;
		
		case Mode::DRY_STRONG:
			copyBits(&data.data[6], 2<<3, 3, 4);
			copyBits(&data.data[8], 0<<1, 1, 2);
			break;
		
		case Mode::WARM:
			copyBits(&data.data[6], 1<<3, 3, 4);
			copyBits(&data.data[8], 0<<1, 1, 2);
			break;
	}
}

void Kirigamine::setPowerState(bool on)
{
	copyBits(&data.data[5], (on?1:0)<<5, 5, 5);
}

void Kirigamine::setTemperature(int temp)
{
	if(temp > 31)
		temp=31;
	else if(temp < 16)
		temp=16;
	
	data.data[7] = temp-16;
}

void Kirigamine::setAirFlow(AirFlow mode)
{
	copyBits(&data.data[9], static_cast<int>(mode), 0, 2);
}

void Kirigamine::setAirDirection(AirDirection mode)
{
	copyBits(&data.data[9], static_cast<int>(mode)<<3, 3, 7);
}

void Kirigamine::setTimer(bool off_timer, int minute)
{
	if(minute <= 0)
	{
		//off
		data.data[11] = 0;
		data.data[12] = 0;
		data.data[13] = 0;
		return;
	}
	
	if(off_timer)
	{
		//turn off timer is enabled
		data.data[11] = minute/10;
		data.data[12] = 0;
		data.data[13] = 3;
	}
	else
	{
		//turn on timer is enabled
		data.data[11] = 0;
		data.data[12] = minute/10;
		data.data[13] = 5;
	}
}

void Kirigamine::setInternalCleaning(bool flg)
{
	copyBits(&data.data[14], (flg?1:0)<<2, 2, 2);
}

void Kirigamine::setPowerfullMode(bool flg)
{
	copyBits(&data.data[15], (flg?1:0)<<4, 4, 4);
}

void Kirigamine::setCurrentWeak(bool flg)
{
	copyBits(&data.data[6], (flg?1:0)<<2, 2, 2);
}
