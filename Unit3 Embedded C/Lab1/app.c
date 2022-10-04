#include <uart.h>

unsigned char string_buffer[100]= "Learn-In-Depth:<Abdallah>";
void main(void)
{
	Uart_Send_string(string_buffer);
}