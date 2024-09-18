extern void config_vic_for_eint0(void);
extern void config_eint0(void);
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(char *ptr);
extern unsigned char uart0_rx(void);
extern void uart0_hexa(int num);
extern void uart0_binary(int num);
void uart0_rx_string(char *p,int max_bytes);
