
#include <SPI.h>
#include <Ethernet.h>

union IRCommand
{
	struct
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
		char data[20];	
	};
	
	char raw[43];
};

inline void ZeroMemory(void* mem, int size)
{
	for(; size>0; size--)
		mem[size-1] =0;
}

IRsend irsend;

void SendIRCommand(IRCommand *com)
{
	unsigned short decoded_data[300];
	ZeroMemory(decoded_data, sizeof(decoded_data));
	
	unsigned short ptr=0;
	
//	for(char i=0; i<com.repeats; i++)
//	{
		//Create Leader data
		for(char j=0; com.leader[j] != 0; j++, ptr++)
		{
			decoded_data[ptr] = com.leader[j] * com.transmit;
		}
		
		//Create data LSB first sending
		for(char j=0; j<com.data_size; j++)
		{
			for(char bit=0; bit<8; bit++)
			{
				if(com.data[j] & (1 << bit))	//LSB first !!
				{
					//in case of 1
					for(char n=0; com.one[n] != 0; n++, ptr++)
					{
						decoded_data[ptr] = com.one[n] * com.transmit;
					}
				}
				else
				{
					//in case of 0
					for(char n=0; com.zero[n] != 0; n++, ptr++)
					{
						decoded_data[ptr] = com.zero[n] * com.transmit;
					}
				}
			}
		}
		
		//create Tailer
		decoded_data[ptr] = com.tail * com.transmit;
		ptr++;
//	}//for com.repeats
	
	//SendIR
	for(char i=0; i<com.repeats; i++)
		irsend.sendRaw(decoded_data, ptr, 38);
		
	Serial.print("data send. byte=");
	Serial.println(ptr, DEC);
	
}

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD
};
IPAddress ip(192, 168, 0, 123);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(50000);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

IRCommand command;

void loop() {
	// listen for incoming clients
	EthernetClient client = server.available();
	
	if (client) {
		Serial.println("new client");
		
		ZeroMemory(&command, sizeof(command));
		
		if(!client.connected() || client.available()<43)
		{
			Serial.println("Illigal Size data was recievd.");
			client.stop();
			return;
		}
		
		for(char i=0; i<43; i++)
		{
			char c = client.read();
			if(c == -1)
			{
				Serial.print("Could not read data. Byte=");
				Serial.println(i, DEC);
				client.stop();
				return;
			}
			command.raw[i] = c;
		}
		
		Serial.println("Sending IR...");
		SendIRCommand(&command);
		Serial.println("Finish to send.");
		client.stop();
		Serial.println("disconnect.");
	}
}
