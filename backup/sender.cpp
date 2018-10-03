#ifndef IR_BASE_H
#define IR_BASE_H



class IRsender
{
	protected:
		IRCommand data;
		IRtemplate::Format format;
	
	public:
		static IRtemplate irtemp;
	
	IRsender(IRtemplate::Format f) : format(f){}
	
	virtual IRCommand GetData()
	{
		CalcParity();
		return data;
	}
	
	virtual void Reset(){data = irtemp.GetTemplate(format);}
	
	virtual void CalcParity() = 0;
};

class Kirigamine : public IRsender
{
	private:
		
	public:
		enum AirFlow
		{
			AUTO = 0,
			LOW,
			MIDDLE,
			HIGH
		};
		
		enum AirDirection
		{
			HIGHEST = 5,
			MIDDLE_UP = 10,
			MIDDLE = 11,
			MIDDLE_DOWN = 24,
			LOWEST = 13,
			MOVE = 15,
			AUTO = 16
		};
		
		enum Mode
		{
			WARM,
			DRY_WEAK,
			DRY_NORMAL,
			DRY_STRONG,
			COOL
		}
	
		Kirigamine() : IRsender(IRtemplate::Format::AEHA)
		{
			data.size = 18;
			data.repeats = 2;
			
			//customer codes
			data.data[0] = 0xD3;
			data.data[1] = 0xC8;
			data.data[2] = 0x02<<4;	//only higher 4 bits
			
			//app data (constants)
			data.data[3] = 0x01;
			data.data[4] = 0x30;
		}
		
		void CalcParity()
		{
			//customer code parity (lower 4 bit only)
			data.data[2] |= (
									((data.data[0]&0xF0)>>4)
								xor (data.data[0]&0x0F)
								xor ((data.data[1]&0xF0)>>4)
								xor (data.data[1]&0x0F)
							);
			
			for(int i=0; i<data.size-2; i++)
				data.data[data.size-1] += data.data[i];
		}
		
		void setDefault()
		{
			setMode(COOL);
			setTemp(28);
			setAirFlow(AUTO);
			setAirDirection(MOVE);
			setInternalCleaning(true);
			setCurrentWeak(true);
			
		}
		
		void setMode(Mode mode)
		{
			switch(mode)
			{
				case COOL:
					copyBits(&data.data[6], 3<<3, 3, 4);
					copyBits(&data.data[8], 3<<1, 1, 2);
					break;
				
				case DRY_WEAK:
					copyBits(&data.data[6], 2<<3, 3, 4);
					copyBits(&data.data[8], 2<<1, 1, 2);
					break;
				
				case DRY_NORMAL:
					copyBits(&data.data[6], 2<<3, 3, 4);
					copyBits(&data.data[8], 1<<1, 1, 2);
					break;
				
				case DRY_STRONG:
					copyBits(&data.data[6], 2<<3, 3, 4);
					copyBits(&data.data[8], 0<<1, 1, 2);
					break;
				
				case WARM:
					copyBits(&data.data[6], 1<<3, 3, 4);
					copyBits(&data.data[8], 0<<1, 1, 2);
					break;
			}
		}
		
		void setPowerState(bool on)
		{
			copyBits(&data.data[5], (on?1:0)<<5, 5, 5);
		}
		
		void setTemp(int temp)
		{
			if(temp > 31)
				temp=31;
			else if(temp < 16)
				temp=16;
			
			data.data[7] = temp-16;
		}
		
		void setAirFlow(AirFlow mode)
		{
			copyBits(&data.data[9], mode, 0, 2);
		}
		
		void setAirDirection(AirDirection mode)
		{
			copyBits(&data.data[9], mode<<3, 3, 7);
		}
		
		void setTimer(bool off_timer, int minute)
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
		
		void setInternalCleaning(bool flg)
		{
			copyBits(&data.data[14], (flg?1:0)<<2, 2, 2);
		}
		
		void setPowerfullMode(bool flg)
		{
			copyBits(&data.data[15], (flg?1:0)<<4, 4, 4);
		}
		
		void setCurrentWeak(bool flg)
		{
			copyBits(&data.data[6], (flg?1:0)<<2, 2, 2);
		}
};


#endif //IR_BASE_H
