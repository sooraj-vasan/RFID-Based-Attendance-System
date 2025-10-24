#include <REGX52.H>
#include <string.h>

// LCD Connections
sbit RS = P3^2;
sbit EN = P3^3;
#define LCD_DATA P2

// Function prototypes
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char dat);
void LCD_Init(void);
void LCD_String(const char *str);
void LCD_Clear(void);
void delay_ms(unsigned int ms);

void UART_Init(void);
unsigned char UART_Read(void);
void UART_Write(char c);
void UART_String(const char *str);

void checkStudent(const char *cardID);

// Use code memory for large strings (PROGMEM)
code char student1_ID[] = "310004A7C250";  // Card 1
code char student2_ID[] = "4E00754D2553";  // Card 2
code char student3_ID[] = "310004FAF03F";  // Card 3
code char student4_ID[] = "310004A752C0";  // Card 4

code char student1_name[] = "Radhika";
code char student2_name[] = "Sahil";
code char student3_name[] = "Arjun";
code char student4_name[] = "Priya";

//---------------- LCD Functions ----------------//
void LCD_Command(unsigned char cmd) {
    RS = 0;
    // High nibble
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd & 0xF0);
    EN = 1; delay_ms(2); EN = 0; delay_ms(2);
    // Low nibble
    LCD_DATA = (LCD_DATA & 0x0F) | ((cmd << 4) & 0xF0);
    EN = 1; delay_ms(2); EN = 0; delay_ms(2);
}

void LCD_Char(unsigned char dat) {
    RS = 1;
    // High nibble
    LCD_DATA = (LCD_DATA & 0x0F) | (dat & 0xF0);
    EN = 1; delay_ms(2); EN = 0; delay_ms(2);
    // Low nibble
    LCD_DATA = (LCD_DATA & 0x0F) | ((dat << 4) & 0xF0);
    EN = 1; delay_ms(2); EN = 0; delay_ms(2);
}

void LCD_Init(void) {
    delay_ms(50);
    LCD_Command(0x02); // Return home
    LCD_Command(0x28); // 4-bit, 2-line
    LCD_Command(0x0C); // Display on, cursor off
    LCD_Command(0x06); // Increment cursor
    LCD_Command(0x01); // Clear display
    delay_ms(5);
}

void LCD_String(const char *str) {
    while(*str) {
        LCD_Char(*str++);
    }
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    delay_ms(5);
}

//---------------- UART Functions ----------------//
void UART_Init(void) {
    TMOD = 0x20;    // Timer1, Mode2
    TH1 = 0xFD;     // 9600 baud @ 11.0592 MHz
    SCON = 0x50;    // 8-bit UART, REN enabled
    TR1 = 1;        // Start Timer1
}

unsigned char UART_Read(void) {
    while(RI == 0);
    RI = 0;
    return SBUF;
}

void UART_Write(char c) {
    SBUF = c;
    while(TI == 0);
    TI = 0;
}

void UART_String(const char *str) {
    while(*str) {
        UART_Write(*str++);
    }
}

//---------------- Delay ----------------//
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<123; j++);
}

// Custom string comparison for code memory strings
bit strcmp_code(const char *ram_str, const char *code_str) {
    while(*ram_str && *code_str) {
        if(*ram_str != *code_str)
            return 0;
        ram_str++;
        code_str++;
    }
    return (*ram_str == *code_str);
}

//---------------- Check Student ----------------//
void checkStudent(const char *cardID) {
    LCD_Clear();
    
    if(strcmp_code(cardID, student1_ID)) {
        LCD_String(student1_name);
        LCD_Command(0xC0);
        LCD_String("Present");
        UART_String(student1_name);
        UART_String(" - Present\r\n");
    }
    else if(strcmp_code(cardID, student2_ID)) {
        LCD_String(student2_name);
        LCD_Command(0xC0);
        LCD_String("Present");
        UART_String(student2_name);
        UART_String(" - Present\r\n");
    }
    else if(strcmp_code(cardID, student3_ID)) {
        LCD_String(student3_name);
        LCD_Command(0xC0);
        LCD_String("Present");
        UART_String(student3_name);
        UART_String(" - Present\r\n");
    }
    else if(strcmp_code(cardID, student4_ID)) {
        LCD_String(student4_name);
        LCD_Command(0xC0);
        LCD_String("Present");
        UART_String(student4_name);
        UART_String(" - Present\r\n");
    }
    else {
        LCD_String("Invalid Card");
        LCD_Command(0xC0);
        LCD_String("Try Again");
        UART_String("Unknown - Invalid\r\n");
    }
    delay_ms(3000);
    LCD_Clear();
    LCD_String("Scan Your Card");
}

//---------------- Main ----------------//
void main(void) {
    unsigned char i;
    char rfid_id[13];
    
    LCD_Init();
    UART_Init();

    LCD_String("Attendance System");
    LCD_Command(0xC0);
    LCD_String("Initializing...");
    delay_ms(2000);

    while(1) {
        LCD_Clear();
        LCD_String("Scan Your Card");
        
        // Clear UART buffer
        while(RI) {
            RI = 0;
            SBUF;
        }
        
        // Read 12 characters
        for(i = 0; i < 12; i++) {
            rfid_id[i] = UART_Read();
        }
        rfid_id[12] = '\0';
        
        checkStudent(rfid_id);
        
        // Add delay to prevent rapid multiple reads
        delay_ms(1000);
    }
}