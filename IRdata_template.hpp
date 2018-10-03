#ifndef IRdata_template_H
#define IRdata_template_H

#include <vector>

#ifndef IRDATA_MAX_SIZE
#	define IRDATA_MAX_SIZE	20
#endif

struct IRCommand
{
	char repeats;			//how many times sending this?
	
	//signal pattern
	unsigned short transmit;	//=T, base time in us
	char leader [10];			//pattern in T	data must finish by 0
	char one[4];				//in T	as above
	char zero[4];				//in T
	char tail;					//in T
	
	//signal data
	char data_size;	//in bytes
	char data[IRDATA_MAX_SIZE];	
} __attribute__ ((__packed__));
 
class IRtemplate
{
	private:
		std::vector<IRCommand> config;
	
	public:
		enum struct Format
		{
			NEC = 0,		//NECフォーマット
			AEHA,			//家電協フォーマット
			SONY,			//SONTフォーマット
			IrisOyama,		//アイリスオーヤマフォーマット
			
			num_AvailableFormats	//put this at last
		};
		
	IRtemplate();
	virtual IRCommand GetTemplate(Format f){return config.at(static_cast<int>(f));}
};

class IRdata_base
{
	protected:
		IRCommand data;
		IRtemplate::Format format;
		IRtemplate irtemp;

	public:
		IRdata_base(IRtemplate::Format f)
		{
			format = f;
			data = irtemp.GetTemplate(format);
		}
	
		virtual IRCommand GetData()
		{
			CalcParity();
			return data;
		}
	
		virtual void Reset(){data = irtemp.GetTemplate(format);}
	
		virtual void CalcParity() = 0;
};

#endif //IRdata_template_H
