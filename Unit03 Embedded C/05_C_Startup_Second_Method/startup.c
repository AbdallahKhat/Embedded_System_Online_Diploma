/* startup.c
Eng. Abdallah Khater
*/

#include <stdint.h>

extern int main(void);

void Rest_Handler(void);

void Default_Handler()
{
	Rest_Handler();
}

void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void H_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;

//booking 1024 B located by .bss through un initialiyed array of int 256 Elem. (256*4=1024)
static unsigned long stack_top[256] ;

void (* const g_p_fn_vectors[])() __attribute__((section(".vectors"))) =
{
	(void (*)()) (stack_top + sizeof(stack_top)),
	&Rest_Handler,
	&NMI_Handler,
	&H_Fault_Handler,
};

extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;

void Rest_Handler(void)
{
	/*Copy data from ROM to RAM*/
	int i;
	unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
	unsigned char* P_src = (unsigned char*)&_E_text;
	unsigned char* P_dst = (unsigned char*)&_S_DATA;
	for(i=0 ; i < DATA_size ; i++ ){
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++) ;
	}

	/*init the .bss with zero*/
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_dst = (unsigned char*)&_S_bss;
	for(i=0 ; i < bss_size ; i++ ){
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}
	/*jump to main*/
	main();
}