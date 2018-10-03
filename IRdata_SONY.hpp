#ifndef IRdata_SONY_format_H
#define IRdata_SONY_format_H

#include "IRdata_template.hpp"

class IRdata_SONY : public IRdata_base
{
	private:
		
	
	protected:

	
	public:
		IRdata_SONY()
			: IRdata_base(IRtemplate::Format::SONY)
		{
			
		}
		
		virtual	void CalcParity()
		{
			return;
		}
};

#endif //IRdata_SONY_format_H
