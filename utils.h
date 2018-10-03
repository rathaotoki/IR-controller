
/*
	copy data to dest only specified bits between lower and higher.
	both end are included.

	eg)
		data = 0b11001100;
		dest = 0b00010111;
		copyBits(&dest, data, 3, 6); //-> dest=0b10010100;
*/
inline void copyBits(char *dest, char data, int lower=0, int higher=7)
{
	if(dest == nullptr)
		return;
	
	if(lower > higher)
		return;
	
	for(int i=lower; i <= higher; i++)
	{
		char MASK = (1<<i);
		
		if(data & MASK)
		{
			//data bit = 1
			*dest |= MASK;
		}
		else
		{
			//data bit = 0
			*dest &= ~MASK;
		}
	}
}
