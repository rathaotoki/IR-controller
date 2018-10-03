#ifndef IRdata_AEHA_format_H
#define IRdata_AEHA_format_H

#include "IRdata_template.hpp"

class IRdata_AEHA : public IRdata_base
{
	private:
		
	
	protected:

	
	public:
		IRdata_AEHA()
			: IRdata_base(IRtemplate::Format::AEHA)
		{
			
		}
		
		virtual	void CalcParity()
		{
			data.data[2] |= (
						((data.data[0]&0xF0)>>4)
					xor (data.data[0]&0x0F)
					xor ((data.data[1]&0xF0)>>4)
					xor (data.data[1]&0x0F)
				);
			
			AppCalcParity();
		}
		
		void setCustomerCode(unsigned short code)
		{
			//Little endian
			data.data[0] = (char)(0x00FF & code);
			data.data[1] = (char)(0xFF00 & code);
		}
		
		virtual void AppCalcParity() = 0;
		
		void setDataSize(int size)
		{
			if(size > IRDATA_MAX_SIZE)
				size=20;
			
			data.data_size = size;
		}
};

#endif //IRdata_AEHA_format_H
