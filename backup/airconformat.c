
11000100
11010011
01100100
10000000
00000000
00000000
00111000
00110000
01101100
00011110
00000000
00000000
00000000
00000000
00100000

11000100
11010011
01100100
10000000
00001100
00000000
00111000
00110000
01100000
00011110
00000000
00000000
00000000
00000000
00100000
00000000
00000000
11110111

void MirrorBit(unsigned char &a)
{
	unsigned char buf = a;
	a=0;
	for(int i=0; i<8; i++)
		a |= (buf & (1<<(7-i)));
}

struct onkyo
{
	on = {0x4b, 0xc0, 0x20, 0xdf};
	off = {0x4b, 0x20, 0xe2, 0x1d};
	vol up = {0x4b, 0cc0, 0x40, 0xbf};
	vol down = {0x4b, 0xc0, 0xc0, 0x3f};
	
};

struct AirCon
{
	//ON 28 C, cooler, airflow=auto, air-direction=highest, low-current
	Leader	8T on, 4T off;
	short Custmer code = 0b1100 0100 1101 0011 = 0xC8D3;
	parity 4bit = xor of Custmer code(4 bits) = 0b0110 = 0x6;
	data 0		=   0b 0100;		//2
	//		   bit low 0123 4567 top
	char data[] = {	0b 1000 0000,	//1 (not 0x80, but 0x01)
					0b 0000 0000,	//0
					0b 0000 0100,	//32	on or off
					0b 0011 1000,	//28	current, mode select
					0b 0011 0000,	//12	templerature, lowest 16C as 0b0 + x
					0b 0110 1100,	//54	mode(cooler, warmer, dry)
					0b 0001 0010,	//18	//air flow (lower 0-3= airflow, 4-7=direction)
					0b 0000 0000,
					0b 0000 0000,	//off timer hour (in 10min as 1, if set 1h=60min, so 6 is this section)
					0b 0000 0000,	//on timer hour(same above)
					0b 0000 0000,	//timer mode
					0b 0000 0000,	//internal cleann
					0b 0000 0000,
					0b 0000 0000,
					0b 1101 1011,	//check 0xDB (Add ALL DATA in char.)
					};
	Trail 31T ;
	repeat_once;
	
	//off
	char data[3] = 	0b 0000 0000;
		data[15] =	0b 1101 1101;
	
	//28->29 C
		data[5] =	0b 1011 0000;	//13	+ 16C(lowest temp)
		data[15]=	0b 0011 1011;
	
	//30 C, current low
		data[5] =	0b 0111 0000;	//14
		data[15]=	0b 1011 1011;
					
	//current max, airflow auto
		data[4]=	0b 0001 1000;
		data[15]=	0b 1110 1011;
	
	//airflow slowest
		data[7] = 	0b 1001 0010;
		data[15]=	0b 0011 1011;
	
	//airflow middle
		data[7]=	0b 0101 0010;
		data[15]=	0b 1011 1011;
		
	//airflow highest, direction highest
		data[7] =	0b 1101 0100;
		data[15]=	0b 0111 1011;
	//direction middle up
		data[7]=	0b 0000 1010;
		data[15]=	0b 1100 0111;
	
	//direction middle
		data[7] = 	0b 0001 1010;
		data[15]=	0b 1101 0111;
	
	//direction middle down
		data[7]=	0b 0000 0011;
		data[15]=	0b 1100 1111;
		
	//direction lowest
		data[7]=	0b 0001 0110;
		data[15]=	0b 1101 1111;
	
	//direction move
		data[7] = 	0b 0001 1110;
		data[15]=	0b 1101 0000;
	
	//direction auto
		data[7]=	0b 0000 0001;
		data[15]=	0b 1100 1000;
	
	//powerful mode
		data[13]=	0b 0000 1000;
		data[15]=	0b 1101 0111;
	
	//dry mode, normal temp
		data[4]=	0b 0010 1000;
		data[5]=	0b 0001 0000;	//8+16=24
		data[6]=	0b 0100 1100;
		data[15]=	0b 1010	0110;
		
	//drymode, strong, diff fron above (shortage 2 bits!!)
		data[6]=	0b 0000 1100;
		data[14]=	0b 0000 00; //???
		data[15]=	0b 1001 0011;
	
	//drymode weak (shortage 1 bit!!) diff drymode, normal temp.
		data[6]=	0b 0010 1100;
		data[15]=	0b ?011 0011; //bit 0 is abnormal timelength
	
	//warmer, 18C	(shortage 2 bit!!)
		data[4]=	0b 0011 0000;
		data[5]=	0b 0100 0000;
		data[6]=	0b 0000 1100;
		data[14]=	0b 0000 00;
		data[15]=	0b 1101 1101;
	
	//timer off after 2 h
		data[9]=	0b 0011 0000;
		data[11]=	0b 1100 0000;
		data[15]=	0b 0101 0111;
	
	//tiemr off after 2.5h
		data[9]=	0b 1111 0000;
		data[11]=	0b 1100 0000;
		data[15]=	0b 1011 0111;
		
	//timer off after 3h
		data[9]=	0b 0100 1000;
		data[11]=	0b 1100 0000;
		data[15]=	0b 0000 1111;
		
	//timer off 3.5h
		data[9]=	0b 1010 1000;
		data[15]=	0b 1100 1111;
	
	//timer off 4h
		data[9]=	0b 0001 1000;
		data[15]=	0b 0110 1111;
	
	//timer off 0.5 h
		data[9]=	0b 1100 0000;
	
	//timer on 1h
		data[10]=	0b 0110 0000;
		data[11]=	0b 1010 0000;
		data[15]=	0b 0110 0111;
	
	//internal clean
		data[12]=	0b 0010 0000;
		data[15]=	0b 1111 1011;
		
};

struct Light
{
	
};

enum light
{
	//ch1
	memory	= {0xb1, 0xc0, 0xea, 0x72},
	all		= {0x8d, 0x63, 0x69, 0xd6},
	off		= {0x64, 0x88, 0xff, 0x00},
	brighter= {0x4f, 0x6e, 0xad, 0x56},
	darker	= {0x85, 0xab, 0x83, 0x12},
	set		= {0x6c, 0xf5, 0x38, 0xa8},
	sunner	= {0x88, 0xc2, 0xb7, 0x56},
	bulb	= {0x3c, 0x72, 0x27, 0x94},
	sleep1	= {0x15, 0xe4, 0x06, 0x70},
	sleep2	= {0x2c, 0xb0, 0xdf, 0x54},
	sleepoff= {0x81, 0x39, 0xf8, 0xf2},
	night	= {0xee, 0xda, 0xd3, 0xd4},
	eco		= {0x28, 0xaf, 0xd6, 0x92},
	
	//ch2
	memory	= {0x94, 0x63, 0x4a, 0x14},
	all		= {0xb0, 0x8a, 0x3d, 0xa0},
	off		= {0x29, 0x83, 0xc5, 0x96},
	brighter= {0x1a, 0xc6, 0xd8, 0x20},
	darker	= {0x1b, 0x03, 0x3f, 0x14},
	set		= {0xce, 0xf1, 0xba, 0x5e},
	sunner	= {0x8f, 0x3a, 0x6e, 0x20},
	bulb	= {0xbd, 0x64, 0x03, 0xac},
	sleep1	= {0x9e, 0xc9, 0x7d, 0x16},
	sleep2	= {0xe0, 0xa0, 0x66, 0x22},
	sleepoff= {0x27, 0xf4, 0x89, 0x94},
	night	= {0xfa, 0x10, 0x73, 0xa2},
	eco		= {0x40, 0xe1, 0x09, 0x94},
	
	
};