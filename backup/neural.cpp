#include <iostream>
using namespace std;

struct node
{
	int a;	//係数
	int value;	//計算結果
};

#define V(_i,_x)	((_i) & (1<<(_x))?1:0)


char data[][9] = {
"11000100",
"11010011",
"01100100",
"10000000",
"00000000",
"00000100",
"00111000",
"00110000",
"01101100",
"00010010",
"00000000",
"00000000",
"00000000",
"00000000",
"00000000",
"00000000",
"00000000",
"11011011"
};

int main()
{
	node net[8];
	int itr=0;
	int a[8];
	

	for(a[0]=1; a[0]<0x20; a[0]++)
	for(a[1]=1; a[1]<0x20; a[1]++)
	for(a[2]=1; a[2]<0x20; a[2]++)
	for(a[3]=1; a[3]<0x20; a[3]++)
	for(a[4]=1; a[4]<0x20; a[4]++)
	for(a[5]=1; a[5]<0x20; a[5]++)
	for(a[6]=1; a[6]<0x20; a[6]++)
	for(a[7]=1; a[7]<0x20; a[7]++)
	#ifdef _OPENMP
//	#pragma omp parallel for
	#endif
	for(int n=-1; n<2; n+=2)
	{
		
		for(int i=0; i<8; i++)
		{
			net[i].value = data[0][i]-'0';
			net[i].a = a[i];
		}
	
	
		for(int sample=0; sample<17; sample++)
		{
			node tmp[8];	//do not use tmp.a[x]
			for(int j=0; j<8; j++)
				tmp[j].value = net[j].value;
			
			#ifdef _OPENMP
			#pragma omp parallel for
			#endif
			for(int i=0; i<8; i++)
			{

				net[i].value *= V(net[i].a, 8);
			
				net[i].value += (data[sample][i]-'0')*n;
				
				for(int j=0; j<8; j++)
					net[i].value += V(net[i].a, j) * tmp[j].value;
			
				if(net[i].value >= 1)
					net[i].value = 1;
				else
					net[i].value = 0;
			}
		}

		int parity =0;
		int calc = 0;
		
		for(int i=0; i<8; i++)
		{
			parity |= ((data[17][i]=='1')?1:0) << i;
			calc |= net[i].value << i;
		}
		
		if(parity == calc)
		{
			cout << "Candidate " << itr << endl;
			cout << "係数 0->7 = ";
			for(int i=0; i<7; i++)
				cout << std::hex << (int) a[i] << ", ";
			cout << endl;
			cout << "新規データ係数 = " << std::dec << n << endl;
			cout << "------------------" << endl;
			itr++;
		}
		
	}
	
	return 0;
}