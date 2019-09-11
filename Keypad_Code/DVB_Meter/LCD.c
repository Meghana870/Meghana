


void Init_lcd (void) 
{ 

	RS_PIN = 0; // write control bytes
	Display_Delay(7000);
	
	Write_com_lcd1(2);
	enable_e();
	Display_Delay(7000);
	
	Write_com_lcd(0x28); // 4 bit mode, 
	Display_Delay(7000);
	
	Write_com_lcd(0x08); // display off
	Display_Delay(7000);
	
	Write_com_lcd(0x0C); // display on, blink curson off
	Display_Delay(7000);
	
	Write_com_lcd(0x06);// entry mode 
	Display_Delay(7000);
	
}

void Write_com_lcd1(unsigned char c)
{
	RS_PIN = 0;
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c >> 4);
	enable_e();
	//Display_Delay(39);
	
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c & 0x0F);
	enable_e();
	//Display_Delay(39);

}

void Write_com_lcd(unsigned char c)// send command to lcd 

{
	
	RS_PIN = 0; // write the command 
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c >> 4);
	enable_e();
	//Display_Delay(39);
	
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c & 0x0F);
	enable_e();
	//Display_Delay(39);
}

void Write_char_lcd(unsigned char c)
{

	RS_PIN = 1; // write charactsers
	DATA_PORT   = (DATA_PORT   & 0xF0) | (c >> 4);
	enable_e();
	//Display_Delay(39);
	
	DATA_PORT   = (DATA_PORT   & 0xF0) | (c & 0x0F);
	enable_e();
	Display_Delay(39);
} 

void Write_string_lcd(const char  *s)

{
	RS_PIN = 1; // write characters
	while(*s)
	Write_char_lcd(*s++);
	
}

void Clear_lcd(void)

{
	RS_PIN = 0;
	Write_com_lcd(0x80);
	Display_Delay(39);
}

void Goto_lcd(unsigned char pos)
{
	RS_PIN = 0;
	Write_com_lcd(0x80+pos);
}

void Display_Delay(int n)
{
	while(n--)
	{
		R_TMR_RJ0_Start();
		while ( TRJIF0 == 1U);
		R_TMR_RJ0_Stop();
	}	
	
}
void Delay(void)
{
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    Display_Delay(5000000);
    
}
void enable_e() {
EN_PIN=1;
NOP();
NOP();
NOP();
NOP();
NOP();
//#if 0
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
//#endif


EN_PIN= 0;
 
NOP();
NOP();
NOP();
NOP();
NOP();
//#if 0
NOP();
NOP();
NOP();
NOP();

NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
//#endif

}