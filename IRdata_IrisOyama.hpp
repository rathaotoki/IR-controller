#ifndef IRdata_IrisOyama_format_H
#define IRdata__IrisOyama_format_H

#include "IRdata_template.hpp"

class IRdata_IrisOyama : public IRdata_base
{
	private:
		
	
	protected:
		char parity;
		int data_size;
	
	public:
		IRdata_IrisOyama(char _parity=0, int total_size=1)
			: IRdata_base(IRtemplate::Format::IrisOyama), parity(_parity), data_size(total_size)
		{
			data.data_size = data_size;
		}
		
		virtual	void CalcParity()
		{
			retry:
			for(int i=0; i<data_size-1; i++)
				parity ^= data.data[i];
			
			if(parity&(1<<7))
			{
				data.data[data.data_size-2] = data.data[0];
				goto retry;
			}
			
			data.data[data.data_size-1] = parity;
		}
};

#endif //IRdata_IrisOyama_format_H
