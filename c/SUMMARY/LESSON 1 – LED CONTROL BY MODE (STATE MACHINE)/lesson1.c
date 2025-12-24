#include <REGX51.h>
#include <string.h>
#include <stdio.h>

sbit led0 = P1^0;
sbit led1 = P1^1;

#define sel_port P2
#define seg_port P0

unsigned int mode0 = 0,mode1 = 0;


unsigned char selected = 0;
unsigned int stick_ms = 0;

static int last_mode0, last_mode1 = -1; 
static unsigned long start_mode0, start_mode1;
unsigned long elapsed0, elapsed1;

static unsigned char change = 0; 

volatile char rdata;
volatile bit flag;

unsigned char pattern[] = {
    0x3f,0x06,0x5b,0x4f,0x66,
    0x6d,0x7d,0x07,0x7f,0x6f
};
unsigned char buffer_mode[2];
unsigned char display_buffer[2];
char buffer[10];
unsigned char rx_idx = 0;


void init (void) {
    TMOD = 0x21;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = 0xFD;

    TH0 = 0xD8; //10ms
    TL0 = 0xF0;
	
		TI = 1;
    TR0 = 1;
		TR1 = 1;
    EX1 = 1;
    IT1 = 1;

    EX0 = 1;
    IT0 = 1;
	
    ET0 = 1;
		ES = 1;
    EA = 1;
		
		last_mode0 = -1; 
    last_mode1 = -1;
}

void timer0_isr ( void) interrupt 1 {
		
		static unsigned int toggle = 0;
    TH0 = 0xD8;
    TL0 = 0xF0;
    stick_ms++;
	
		// --- Logic Quet LED ---
    sel_port = 0xFF; 
    
    if (toggle == 0) {
				sel_port = (0x04)<<2;   
        seg_port = display_buffer[0]; 
            
        toggle = 1;
    } else {
				sel_port = (0x02)<<2;   
        seg_port = display_buffer[1]; 
            
        toggle = 0;
    }

}

void int0_isr (void ) interrupt 0 {
    if ( selected == 0){
        mode0++;
        if (mode0 > 2 ){
            mode0 = 0;
        }
			}
    else {
        mode1 ++;
        if (mode1 > 2) {
            mode1 = 0;
        }
      }
 }

void int1_isr (void ) interrupt 2 {
    selected = !selected;
}
void send_char(char c) {
    while (!TI);
    TI = 0;
    SBUF = c;
}

void send_string(char *str) {
    while (*str) {
        send_char(*str);
        str++;
    }
}
void uart_isr(void) interrupt 4 {
    if (RI) {
        char c = SBUF;
        RI = 0;
        send_char(c);  // Echo
        
        if (c == '\r' || c == '\n') {
            buffer_mode[rx_idx] = '\0';
            rx_idx = 0;
            flag = 1;
        } else if (rx_idx < 9) {
            buffer_mode[rx_idx++] = c;
        }
    }
}



void mode_sel(void) {
		// control led0
		if (mode0 != last_mode0) {
				start_mode0 = stick_ms;
				last_mode0 = mode0;
				change = 1;
		}

		elapsed0 = stick_ms - start_mode0;

		if (mode0 == 0) {
				led0 = 1; 
		} 
		else if (mode0 == 1) {
			
				led0 = (elapsed0 < 100) ? 0 : 1;
		} 
		else if (mode0 == 2) {
				led0 = (elapsed0 % 100 < 50) ? 0 : 1;
		}
		
		//control led1
				if (mode1 != last_mode1) {
				start_mode1 = stick_ms;
				last_mode1 = mode1;
				change = 1;
		}

		elapsed1 = stick_ms - start_mode1;

		if (mode1 == 0) {
				led1 = 1; 
		} 
		else if (mode1 == 1) {
			
				led1 = (elapsed1 < 100) ? 0 : 1;
		} 
		else if (mode1 == 2) {
				led1 = (elapsed1 % 100 < 50) ? 0 : 1;
		}

	}
void update_buffer() {
    display_buffer[0] = pattern[mode0]; 
    display_buffer[1] = pattern[mode1]; 
}
void command ( void){
	if (change){
			send_string("=====================\r\n");
			send_string("mode0=");
			send_char(mode0 +'0');
			send_string("\r\n");
			send_string("mode1=");
			send_char(mode1 +'0');
			send_string("\r\n");
			change = 0;
			send_string("=====================\r\n");
	}
}
void uart_handler(void) {
    unsigned char new_mode;
    unsigned char value;
    bit error = 0;
    
    
    
    if (strlen(buffer_mode) != 2) {
        error = 1;
    }
    
    if (!error) {
        if (buffer_mode[0] < '0' || buffer_mode[0] > '1') {
            error = 1;
        } else {
            new_mode = buffer_mode[0] - '0';
        }
    }
    
    if (!error) {
        if (buffer_mode[1] < '0' || buffer_mode[1] > '2' ){
            error = 1;
        } else {
            value =  (buffer_mode[1] - '0');
        }
    }
    
    
    if (error) {
        send_string("\r\nERROR: Format MX, M=0-1, X=0-1-2\r\n");
    } else {
				if ( new_mode == 0){
						selected =0;
						mode0 = value;
				}
        else if ( new_mode ==1){
						selected =1;
						mode1 = value;
				}
        
        send_string("OK\r\n");
    }
}

void main  (void){
    init();
		send_string("=====================\r\n");
	send_string("0: TAT\r\n");
	send_string("1: SANG 1S ROI TAT\r\n");
	send_string("2: SANG TAT CHU KI 1S\r\n");
		send_string("=====================\r\n");
	
    while (1)
		{
			if (flag){
				
			flag = 0;
			uart_handler();
				
		}
			mode_sel();
			update_buffer();
			command();
		}
}