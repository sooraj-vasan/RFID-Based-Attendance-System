#include <reg51.h>
#include <string.h>

#define LCD P2          // LCD data pins on Port 2

sbit RS = P3^2;         // LCD RS pin on P3.2
sbit EN = P3^3;         // LCD EN pin on P3.3

// UART prototypes
void UART_Init();
char UART_Read();

// LCD prototypes
void LCD_Cmd(unsigned char cmd);
void LCD_Char(unsigned char dat);
void LCD_String(char *str);
void LCD_Init();
void delay_ms(unsigned int ms);

void main() {
    char tag[11];  // 10 characters + null
    unsigned char i;
    char start_byte;

    LCD_Init();
    UART_Init();

    LCD_String("Scan RFID Card");

    while(1) {
        // Wait for start of RFID data
        do {
            start_byte = UART_Read();
        } while(start_byte != 0x02 && start_byte != 0x0A);
        
        // Read 10 characters (actual Tag ID)
        for(i=0; i<10; i++) {
            tag[i] = UART_Read();
        }
        tag[10] = '\0';

        // Read and discard remaining bytes
        for(i=0; i<3; i++) {
            UART_Read();
        }

        LCD_Cmd(0x01);
        LCD_String("Tag ID:");
        LCD_Cmd(0xC0);
        LCD_String(tag);

        delay_ms(2000);
        LCD_Cmd(0x01);
        LCD_String("Scan Next...");
    }
}

/* UART Functions */
void UART_Init() {
    SCON = 0x50;   // Serial mode 1, REN enabled
    TMOD = 0x20;   // Timer1 Mode2
    TH1 = 0xFD;    // 9600 baud
    TR1 = 1;
}

char UART_Read() {
    while(RI == 0);
    RI = 0;
    return SBUF;
}

/* LCD Functions */
void LCD_Init() {
    delay_ms(20);
    LCD_Cmd(0x02);
    LCD_Cmd(0x28);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x06);
    LCD_Cmd(0x01);
    delay_ms(2);
}

void LCD_Cmd(unsigned char cmd) {
    RS = 0;
    LCD = (LCD & 0x0F) | (cmd & 0xF0);
    EN = 1; delay_ms(1); EN = 0;
    delay_ms(1);

    LCD = (LCD & 0x0F) | (cmd << 4);
    EN = 1; delay_ms(1); EN = 0;
    delay_ms(2);
}

void LCD_Char(unsigned char dat) {
    RS = 1;
    LCD = (LCD & 0x0F) | (dat & 0xF0);
    EN = 1; delay_ms(1); EN = 0;
    delay_ms(1);

    LCD = (LCD & 0x0F) | (dat << 4);
    EN = 1; delay_ms(1); EN = 0;
    delay_ms(2);
}

void LCD_String(char *str) {
    while(*str) {
        LCD_Char(*str++);
    }
}

/* Delay */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}