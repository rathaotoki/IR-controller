#ifndef IRdata_IrisOyama_CeilingLight_H
#define IRdata_IrisOyama_CeilingLight_H

#include "IRdata_IrisOyama.hpp"

class IRdata_Light : public IRdata_IrisOyama
{
	private:
		
	public:
		enum struct Button : short
		{
			FULL = 3,
			OFF,
			NIGHT_LIGHT,
			MEMORY,
			DARK,
			
			BULB = 0x100,
			SET,
			SUNNY,
			BRIGHT,
			SLEEP10,
			SLEEP30,
			SLEEP_RESET,
			ECO
		};
	
		IRdata_Light() : IRdata_IrisOyama(0b10101101, 5) // 0xAD
		{
			setChannel(1);
			data.repeats = 3;
		}
		
		virtual void setChannel(int ch)
		{
			if(ch==1)
				data.data[0] = (1<<7);
			else
				data.data[3] = (1<<7);
		}
		
		virtual void PushButton(Button b)
		{
			if(0x100 & static_cast<int>(b))
				data.data[2] = 1<<(0xFF&static_cast<int>(b));
			else
				data.data[1] = 1<<(0xFF&static_cast<int>(b));
		}
	
};

#endif //IRdata_IrisOyama_CeilingLight_H
/*
01234567

00000000
00000000
00001000
00000001
10111100

00000000
00000000
00000100
00000001
10110000

00000001
00000000
00000100
00000000
10110000



00000000
00000000
00000010
00000001
10110110

00000001
00000000
00000010
00000000
10110110

*/
