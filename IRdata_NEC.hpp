#ifndef IRdata_NEC_format_H
#define IRdata_NEC_format_H

#include "IRdata_template.hpp"

static void ZeroMemory(void *dest, int size)
{
	for(int i=0; i<size; i++)
		((char*)dest)[i]=0;
}

class IRdata_NEC : public IRdata_base
{
	private:
		
	
	protected:

	
	public:
		IRdata_NEC()
			: IRdata_base(IRtemplate::Format::NEC)
		{
			data.data_size = 4;
		}
		
		virtual	void CalcParity()
		{
			data.data[3] = ~data.data[2];
		}
		
		void setCustomerCode(unsigned short code)
		{
			//Little endian
			data.data[0] = (char)(0x00FF & code);
			data.data[1] = (char)((0xFF00 & code)>>8);
		}
		
		void setSendData(unsigned char _data)
		{
			data.data[2] = _data;
		}
		
		IRCommand GetRepeatData()
		{
			IRCommand var;
			
			ZeroMemory(&var, sizeof(var));
			
			var.repeats=1;
			var.transmit = 562;
			var.leader[0] = 16;
			var.leader[1] = 4;
			var.leader[2] = 1;
			var.leader[3] = 192;	//108 ms
			
			return var;
		}
};

#endif //IRdata_NEC_format_H
