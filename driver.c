#include <LPC21xx.H>
#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
#define sw3 ((IOPIN0>>16)&1)

#define led (7<<17)
#define led1 (1<<17)
#define led2 (1<<18)
#define led3 (1<<19)
void EINT0_Handler(void) __irq{
    int r=U0IIR;
    r=(r>>1)&7;
	
    VICVectAddr=0;
}

void config_vic_for_eint0(void)
{
    VICIntSelect=0;
    VICVectCntl0=14|(1<<5);
    VICVectAddr0=(unsigned int)EINT0_Handler;
    VICIntEnable=(1<<14);
}

void config_eint0(void)
{
    U0IER=1;
}

void uart0_init(unsigned int baud)
{
	unsigned int result=0;
	int a[5]={15,60,30,15,15};
	unsigned int pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	PINSEL0|=5;
	U0LCR=0X83;
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=3;
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(char *ptr)
{
	while(*ptr)
	{
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}
}

#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_hexa(int num)
{
	unsigned char temp;
    uart0_tx('0');
    uart0_tx('X');

    temp=(((num>>4)&0x0f));
	if(temp<10)
	{
	 	uart0_tx(temp+48);
	}
	else
	{
		uart0_tx(temp+55);
	}

    temp=((num&0x0f));
	if(temp<10)
	{
	 	uart0_tx(temp+48);
	}
	else
	{
		uart0_tx(temp+55);
	}
}


void uart0_binary(int num)
{
    int pos,c;
    for(pos=7;pos>=0;pos--)
    {
        c=num>>pos&1;
        if(c)
            uart0_tx(49);
        else
            uart0_tx(48);        
    }
}

