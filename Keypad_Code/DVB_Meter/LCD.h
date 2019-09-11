#ifndef LCD_H
#define LCD_H
/* RS Register Select pin */
#define RS_PIN                     P3.1
/* Display Enable pin */	
#define EN_PIN                     P3.0	
/* Data bus port */
#define DATA_PORT                  P6

void Display_Delay(int n);
void Delay(void);

void Init_lcd (void); 
void Write_com_lcd (unsigned char c); 
void Write_com_lcd1 (unsigned char c);
void Write_char_lcd (unsigned char c); 
void Write_string_lcd (const char *s); 
void Clear_lcd (void); 
void Goto_lcd (unsigned char pos);
void enable_e(void);
#endif