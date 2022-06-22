/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 5/13/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/
//Fdlnaaa bs n3ml lcd w nshtreeeha 
#include <mega16a.h>
// Alphanumeric LCD functions
#include <alcd.h>
#include <delay.h>
// Declare your global variables here
eeprom int inputLength=0;
eeprom int lockSemaphore=0;
eeprom char lock[50];
eeprom char checkLock[50];
eeprom int checkLength=0;
char getNum(){
    char num;
	if(PINC.7==1&&PINC.6==0&&PINC.5==1&&PINC.4==0)num='0';
	else if(PINC.7==0&&PINC.6==0&&PINC.5==0&&PINC.4==1)num='1';
	else if(PINC.7==0&&PINC.6==0&&PINC.5==1&&PINC.4==0)num='2';
	else if(PINC.7==0&&PINC.6==0&&PINC.5==1&&PINC.4==1)num='3';
	else if(PINC.7==0&&PINC.6==1&&PINC.5==0&&PINC.4==0)num='4';
	else if(PINC.7==0&&PINC.6==1&&PINC.5==0&&PINC.4==1)num='5';
	else if(PINC.7==0&&PINC.6==1&&PINC.5==1&&PINC.4==0)num='6';
	else if(PINC.7==0&&PINC.6==1&&PINC.5==1&&PINC.4==1)num='7';
	else if(PINC.7==1&&PINC.6==0&&PINC.5==0&&PINC.4==0)num='8';
	else if(PINC.7==1&&PINC.6==0&&PINC.5==0&&PINC.4==1)num='9';
	return num;
}
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{      
    char c=getNum();
    lcd_putchar(c); 
// Place your code here

    if(PINB.1==0){     //normal mode                          
        checkLock[checkLength] = c;
         
        if(lock[checkLength] != checkLock[checkLength]){    
        char buf[10]="Error";   
            delay_ms(200);
            lcd_clear();     
             
            //DISPLAY Error IN LCD 
            
            PORTC|=(1<<PORTC1);
            lcd_puts(buf); 
            delay_ms(1000);
            PORTC&=(0<<PORTC1);     
            checkLength=0;
            lcd_clear();
        } else {
            checkLength++;
            if(checkLength == inputLength) {    
                char buf[10]="Success";
                delay_ms(200);
                lcd_clear();
                
                //DISPLAY Success IN LCD 
                
                PORTC|=(1<<PORTC2);
                lcd_puts(buf);
                delay_ms(1000);
                PORTC&=(0<<PORTC2);
                checkLength=0;
                lcd_clear();
            }
        }
        
        

    }else{ //programming mode 
    if(lockSemaphore==1){
        lock[inputLength]=c; 
        //DISPLAY in LCD
        inputLength++;
        checkLength=0;
        }
    }
}

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
// Place your code here
    PORTC|=(1<<PORTC0);
    if(lockSemaphore==0){
        inputLength=0;
        checkLength=0;
        lockSemaphore=1;
    }
       
}
//eeprom int clearSemaphore=0;
void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=Out Bit1=Out Bit0=Out 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (1<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=T Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);


// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 11.719 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 2 s
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(1<<ICNC1) | (1<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x5B;
OCR1AL=0x8D;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: Off
// INT2: Off
GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (1<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")
DDRB.1=0;
while (1)
      {
      // Place your code here
// Place your code here
        if(PINB.1){
            TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
        } 
        else{
            lockSemaphore=0;
            PORTC&=0<<PORTC0;  
            lcd_clear();
            while(PINB.1==0){     
                TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
            }
        
        }   
      }
}
