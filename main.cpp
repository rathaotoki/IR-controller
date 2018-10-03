#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "IRdata_Mitsubishi_Kirigamine.hpp"
#include "IRdata_ONKYO.hpp"
#include "IRdata_IrisOyama_CeilingLight.hpp"

int main(int argc, char **argv)
{
	using namespace std;
	
	vector<string> args;
	IRdata_base *ir;
	
	for(int i=1; i<argc; i++)
		args.push_back(string(argv[i]));
	
	if(args.size() == 0)
	{
		cout << "ircom device [opts]" << endl;
		cout << " device = aircon, amp, light" << endl;
		cout << " opts : independent on devices" << endl;
		return 0;
	}		
	if(args.at(0) == "light")
	{
		IRdata_Light *_ir = new IRdata_Light();
		if(args.at(1) == "off")
			_ir->PushButton(IRdata_Light::Button::OFF);
		else if(args.at(1) == "on")
			_ir->PushButton(IRdata_Light::Button::MEMORY);
		else if(args.at(1) == "memory")
			_ir->PushButton(IRdata_Light::Button::MEMORY);
		else if(args.at(1) == "full")
			_ir->PushButton(IRdata_Light::Button::FULL);
		else if(args.at(1) == "night")
			_ir->PushButton(IRdata_Light::Button::NIGHT_LIGHT);
		else if(args.at(1) == "dark")
			_ir->PushButton(IRdata_Light::Button::DARK);
		else if(args.at(1) == "bright")
			_ir->PushButton(IRdata_Light::Button::BRIGHT);
		else if(args.at(1) == "set")
			_ir->PushButton(IRdata_Light::Button::SET);
		else if(args.at(1) == "sunny")
			_ir->PushButton(IRdata_Light::Button::SUNNY);
		else if(args.at(1) == "bulb")
			_ir->PushButton(IRdata_Light::Button::BULB);
		else if(args.at(1) == "sleep10")
			_ir->PushButton(IRdata_Light::Button::SLEEP10);
		else if(args.at(1) == "sleep30")
			_ir->PushButton(IRdata_Light::Button::SLEEP30);
		else if(args.at(1) == "sleepreset")
			_ir->PushButton(IRdata_Light::Button::SLEEP_RESET);
		else if(args.at(1) == "eco")
			_ir->PushButton(IRdata_Light::Button::ECO);
		else
		{
			cerr << "no modes are specified." << endl;
			delete _ir;
			return 1;
		}
		
		ir = dynamic_cast<IRdata_base*>(_ir);
	}
	else if(args.at(0) == "amp")
	{
		IRdata_ONKYO *_ir = new IRdata_ONKYO();
		
		#define CASE(x,y) else if (args.at(1)==(x)) _ir->PushButton(IRdata_ONKYO::Button::y)
		if(args.at(1).size() == 0)
		{
			cerr << "command not specified." << endl;
			delete _ir;
			return 1;
		}
		CASE("on", ON);
		CASE("off", OFF);
		CASE("vol_up", VOL_UP);
		CASE("vol_down", VOL_DOWN);
		CASE("mute", MUTE);
		CASE("input_next", INPUT_UP);
		CASE("input_prev", INPUT_DOWN);
		else
		{
			cerr << "unknown command " << args.at(1) << endl;
			delete _ir;
			return 1;
		}
		#undef CASE
		
		ir = dynamic_cast<IRdata_base*>(_ir);
	}
	else if(args.at(0) == "aircon")
	{
		Kirigamine *_ir = new Kirigamine();
		
		int argptr=1;
		
		_ir->setDefault();
		
		for(; argptr<args.size(); argptr++)
		{
			if(args.at(argptr).size() == 0)
			{
				cerr << "command not specified." << endl;
				delete _ir;
				return 1;
			}
			
			if(args.at(argptr) == "-t")
			{
				_ir->setTemperature(atoi(args.at(argptr+1).c_str()));
				argptr++;
			}
			else if(args.at(argptr) == "-on")
				_ir->setPowerState(true);
			else if(args.at(argptr) == "-off")
				;//nothing to do
			else if(args.at(argptr) == "-flow")
				cerr << "not implemented" << endl;
			
		}
		
		ir = dynamic_cast<IRdata_base*>(_ir);
	//	return 0;
	}
	
	IRCommand data = ir->GetData();
	
	std::fwrite(&data, sizeof(data), 1, stdout);
	//std::fwrite(&rep, sizeof(rep), 1, stdout);
	delete ir;
	return 0;
}
