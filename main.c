#include<lpc21xx.h>
#include"header.h"
#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
#define sw3 ((IOPIN0>>16)&1)

#define led (3<<17)
#define led1 (1<<17)
#define led2 (1<<18)

main()
{
	unsigned char cmd;
	uart0_init(9600);
	config_vic_for_eint0();
	config_eint0();
	IODIR0|=led;

	while(1)
	{	
		uart0_tx_string("\r\nmenu");
		uart0_tx_string("\r\na.led1 ON");
		uart0_tx_string("\r\nb.led1 OFF");
		uart0_tx_string("\r\nc.FAN ON");
		uart0_tx_string("\r\nd.FAN OFF");
		uart0_tx_string("\r\ne.BOTH OFF");
		uart0_tx_string("\r\nf.BOTH ON");
		uart0_tx_string("\r\ng.manual mode");

		cmd=uart0_rx();

		switch(cmd)
		{
			case 'a':
				IOCLR0|=led1;
				break;
			case 'b':
				IOSET0|=led1;
				break;
			case 'c':
				IOCLR0|=led2;
				break;
			case 'd':
				IOSET0|=led2;
				break;
			case 'e':
				IOSET0|=led1;
				IOSET0|=led2;
				break;
			case 'f':
				IOCLR0|=led1;
				IOCLR0|=led2;
				break;
			case 'g':
				while(1)
				{
					if(sw1==0)
					{
						while(sw1==0);
						if(IOSET0&(led1))
							IOCLR0|=led1;
						else
							IOSET0|=led1;
					}
					if(sw2==0)
					{
						while(sw2==0);
						if(IOSET0&(led2))
							IOCLR0|=led2;
						else
							IOSET0|=led2;
					}
					if(sw3==0)
					{
						while(sw3==0);

						break;
					}
				}
		}

	}
}


