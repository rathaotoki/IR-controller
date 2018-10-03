#ifndef IRdata_ONKYO_AMP_H
#define IRdata_ONKYO_AMP_H

#include "IRdata_NEC.hpp"

class IRdata_ONKYO : public IRdata_NEC
{
	private:
	
	protected:
		
	public:
		enum struct Button : unsigned short
		{
			ON = 0x000 + 0x04,
			OFF = 0x100 + 0x47,
			VOL_UP = 0x000 + 0x02,
			VOL_DOWN = 0x000 + 0x03,
			MUTE = 0x000 + 0x05,
			INPUT_UP = 0x100 + 0x1E,
			INPUT_DOWN = 0x100 + 0x1F
		};
	
		IRdata_ONKYO()
		{
			//setCustomerCode(0x00D2); //Little endian
			
			data.repeats = 1;
		}
		
		void PushButton(Button b)
		{
			char data = 0xFF & static_cast<unsigned char>(b);
			int c_code = (static_cast<short>(b)&0x100) ?4:3;
			setCustomerCode((c_code<<8) + 0xD2);
			setSendData(static_cast<unsigned char>(b));
		}
	
};

/*
01234567
//off
01001011 0xD2
00100000 0x04
11100010 0x47
00011101 

//vol up
01001011 0xD2
11000000 0x03
01000000 0x02
10111111

//vol down
01001011 0xD2
11000000 0x03
11000000 0x03
00111111

//mute
01001011 0xD2
11000000 0x03
10100000 0x05
01011111

//input up
01001011 0xD2
00100000 0x04
01111000 0x1E
10000111

//input down
01001011 0xD2
00100000 0x04
11111000 0x1F
00000111

//on
01001011 0xD2
11000000 0x03
00100000 0x04
11011111
*/


#endif //IRdata_ONKYO_AMP_H
