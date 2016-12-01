//
// uLCD_4DGL is a class to drive 4D Systems uLCD 144 G2
//
// Copyright (C) <2010> Stephane ROCHON <stephane.rochon at free.fr>
// Modifed for Goldelox processor <2013> Jim Hamblen
//
// uLCD_4DGL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// uLCD_4DGL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with uLCD_4DGL.  If not, see <http://www.gnu.org/licenses/>.

#include "uLCD_4DGL.h"
#include "drivers.h"
#include <String.h>

#define ARRAY_SIZE(X) sizeof(X)/sizeof(X[0])

//Serial pc(USBTX,USBRX);


//******************************************************************************************************
void uLCD_4DGL_Init(void){

    //_rst = 1;    // put RESET pin to high to start TFT screen
    reset();
    cls();       // clear screen
    current_col         = 0;            // initial cursor col
    current_row         = 0;            // initial cursor row
    current_color       = WHITE;        // initial text color
    current_orientation = IS_PORTRAIT;  // initial screen orientation
    current_hf = 1;
    current_wf = 1;
    set_font(FONT_7X8);                 // initial font
//   text_mode(OPAQUE);                  // initial texr mode
}

//******************************************************************************************************
void writeBYTE(char c)   // send a BYTE command to screen
{

     UART0_send(c);
    //wait_us(500);  //mbed is too fast for LCD at high baud rates in some long commands
}

//******************************************************************************************************
void writeBYTEfast(char c)   // send a BYTE command to screen
{

    UART0_send(c);
    //wait_ms(0.0);  //mbed is too fast for LCD at high baud rates - but not in short commands
}
//******************************************************************************************************
void freeBUFFER(void)         // Clear serial buffer before writing command
{

    //while (_cmd.readable()) _cmd.getc();  // clear buffer garbage
}

//******************************************************************************************************
int writeCOMMAND(char *command, int number)   // send several BYTES making a command and return an answer
{
    int i, resp = 0;
    freeBUFFER();
    writeBYTE(0xFF);
    for (i = 0; i < number; i++) {
        if (i<16)
            writeBYTEfast(command[i]); // send command to serial port
        else
            writeBYTE(command[i]); // send command to serial port but slower
    }
    //while (!_cmd.readable()) wait_ms(TEMPO);              // wait for screen answer
    //if (_cmd.readable()) resp = _cmd.getc();           // read response if any
    switch (resp) {
        case ACK :                                     // if OK return   1
            resp =  1;
            break;
        case NAK :                                     // if NOK return -1
            resp = -1;
            break;
        default :
            resp =  0;                                 // else return   0
            break;
    }

    return resp;
}

//**************************************************************************
void reset(void)    // Reset Screen
{
    //wait_ms(5);
    //_rst = 0;               // put RESET pin to low
    //wait_ms(5);         // wait a few milliseconds for command reception
    //_rst = 1;               // put RESET back to high
    //wait(3);                // wait 3s for screen to restart

    freeBUFFER();           // clean buffer from possible garbage
}
//******************************************************************************************************
int writeCOMMANDnull(char *command, int number)   // send several BYTES making a command and return an answer
{

    int i, resp = 0;
    freeBUFFER();
    writeBYTE(0x00); //command has a null prefix byte
    for (i = 0; i < number; i++) {
        if (i<16) //don't overflow LCD UART buffer
            writeBYTEfast(command[i]); // send command to serial port
        else
            writeBYTE(command[i]); // send command to serial port with delay
    }
    //while (!_cmd.readable()) wait_ms(TEMPO);              // wait for screen answer
    //if (_cmd.readable()) resp = _cmd.getc();           // read response if any
    switch (resp) {
        case ACK :                                     // if OK return   1
            resp =  1;
            break;
        case NAK :                                     // if NOK return -1
            resp = -1;
            break;
        default :
            resp =  0;                                 // else return   0
            break;
    }

    return resp;
}

//**************************************************************************
void cls(void)    // clear screen
{
    char command[1] = "";

    command[0] = CLS;
    writeCOMMAND(command, 1);
    current_row=0;
    current_col=0;
    current_hf = 1;
    current_wf = 1;
    set_font(FONT_7X8);                 // initial font
}

//**************************************************************************
int version(void)    // get API version
{

    char command[2] = "";
    command[0] = '\x00';
    command[1] = VERSION;
    return readVERSION(command, 2);
}

//**************************************************************************
void baudrate(int speed)    // set screen baud rate
{
    char command[3]= "";
	  int newbaud = BAUD_9600;
	  int i, resp = 0;

    
    writeBYTE(0x00);
    command[0] = BAUDRATE;
    command[1] = 0;
    switch (speed) {
        case  110 :
            newbaud = BAUD_110;
            break;
        case  300 :
            newbaud = BAUD_300;
            break;
        case  600 :
            newbaud = BAUD_600;
            break;
        case 1200 :
            newbaud = BAUD_1200;
            break;
        case 2400 :
            newbaud = BAUD_2400;
            break;
        case 4800 :
            newbaud = BAUD_4800;
            break;
        case 9600 :
            newbaud = BAUD_9600;
            break;
        case 14400 :
            newbaud = BAUD_14400;
            break;
        case 19200 :
            newbaud = BAUD_19200;
            break;
        case 31250 :
            newbaud = BAUD_31250;
            break;
        case 38400 :
            newbaud = BAUD_38400;
            break;
        case 56000 :
            newbaud = BAUD_56000;
            break;
        case 57600 :
            newbaud = BAUD_57600;
            break;
        case 115200 :
            newbaud = BAUD_115200;
            break;
        case 128000 :
            newbaud = BAUD_128000;
            break;
        case 256000 :
            newbaud = BAUD_256000;
            break;
        case 300000 :
            newbaud = BAUD_300000;
            speed = 272727;
            break;
        case 375000 :
            newbaud = BAUD_375000;
            speed = 333333;
            break;
        case 500000 :
            newbaud = BAUD_500000;
            speed = 428571;
            break;
        case 600000 :
            newbaud = BAUD_600000;
            break;
        case 750000 : //rates over 600000 are not documented, but seem to work
            newbaud = BAUD_750000;
            break;
        case 1000000 :  
            newbaud = BAUD_1000000;
            break;
        case 1500000 :
            newbaud = BAUD_1500000;
            break;
        case 3000000 :
            newbaud = BAUD_3000000;
            break;
        default   :
            newbaud = BAUD_9600;
            speed = 9600;
            break;
    }

    
    freeBUFFER();
    command[1] = (char)(newbaud >>8);
    command[2] = (char)(newbaud % 256);
    //wait_ms(1);
    for (i = 0; i <3; i++) writeBYTEfast(command[i]);      // send command to serial port
    for (i = 0; i<10; i++) //wait_ms(1); 
    //dont change baud until all characters get sent out
    //_cmd.baud(speed);                                  // set mbed to same speed
    i=0;
    //while ((!_cmd.readable()) && (i<25000)) {
    //    wait_ms(TEMPO);           // wait for screen answer - comes 100ms after change
    //    i++; //timeout if ack character missed by baud change
    //}
    //if (_cmd.readable()) resp = _cmd.getc();           // read response if any
    switch (resp) {
        case ACK :                                     // if OK return   1
            resp =  1;
            break;
        case NAK :                                     // if NOK return -1
            resp = -1;
            break;
        default :
            resp =  0;                                 // else return   0
            break;
    }
}

//******************************************************************************************************
int readVERSION(char *command, int number)   // read screen info and populate data
{

    int i, temp = 0, resp = 0;
    char response[5] = "";

    freeBUFFER();

    for (i = 0; i < number; i++) writeBYTE(command[i]);    // send all chars to serial port

    //while (!_cmd.readable()) wait_ms(TEMPO);               // wait for screen answer

    //while (_cmd.readable() && resp < ARRAY_SIZE(response)) {
        //temp = _cmd.getc();
        //response[resp++] = (char)temp;
    //}
    switch (resp) {
        case 2 :                                           // if OK populate data and return 1
            //revision  = response[0]<<8 + response[1];
            resp      = 1;
            break;
        default :
            resp =  0;                                     // else return 0
            break;
    }
    return resp;
}

//****************************************************************************************************
void background_color(int color)              // set screen background color
{
    int red5, green6, blue5;
	  char command[3]= "";                                  // input color is in 24bits like 0xRRGGBB

    command[0] = BCKGDCOLOR;

    red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void textbackground_color(int color)              // set screen background color
{
	  int red5, green6, blue5;
    char command[3]= "";                                  // input color is in 24bits like 0xRRGGBB

    command[0] = TXTBCKGDCOLOR;

    red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void display_control(char mode)     // set screen mode to value
{
    char command[3]= "";

    command[0] = DISPCONTROL;
    command[1] = 0;
    command[2] = mode;

    if (mode ==  ORIENTATION) {
        switch (mode) {
            case LANDSCAPE :
                current_orientation = IS_LANDSCAPE;
                break;
            case LANDSCAPE_R :
                current_orientation = IS_LANDSCAPE;
                break;
            case PORTRAIT :
                current_orientation = IS_PORTRAIT;
                break;
            case PORTRAIT_R :
                current_orientation = IS_PORTRAIT;
                break;
        }
    }
    writeCOMMAND(command, 3);
    set_font(current_font);
}
//****************************************************************************************************
void display_power(char mode)     // set screen mode to value
{
    char command[3]= "";

    command[0] = DISPPOWER;
    command[1] = 0;
    command[2] = mode;
    writeCOMMAND(command, 3);
}
//****************************************************************************************************
void set_volume(char value)     // set sound volume to value
{
    char command[2]= "";

    command[0] = SETVOLUME;
    command[1] = value;

    writeCOMMAND(command, 2);
}


//******************************************************************************************************
int getSTATUS(char *command, int number)   // read screen info and populate data
{

    int i, temp = 0, resp = 0;
    char response[5] = "";

    freeBUFFER();

    for (i = 0; i < number; i++) writeBYTE(command[i]);    // send all chars to serial port

    //while (!_cmd.readable()) wait_ms(TEMPO);    // wait for screen answer

    //while (_cmd.readable() && resp < ARRAY_SIZE(response)) {
    //    temp = _cmd.getc();
    //    response[resp++] = (char)temp;
    //}
    switch (resp) {
        case 4 :
            resp = (int)response[1];         // if OK populate data
            break;
        default :
            resp =  -1;                      // else return   0
            break;
    }

    return resp;
}

void set_font_size(char width, char height)     // set font size
{
    if (current_orientation == IS_PORTRAIT) {
        current_fx = width;
        current_fy = height;
    } else {
        current_fy = height;
        current_fx = width;
    }
    max_col = current_w / (current_fx*current_wf);
    max_row = current_h / (current_fy*current_hf);
}

//****************************************************************************************************
void set_font(char mode)     // set font - system or SD media
{
    char command[3]= "";

    command[0] = SETFONT;
    command[1] = 0;
    command[2] = mode;

    current_font = mode;

    if (current_orientation == IS_PORTRAIT) {
        current_w = SIZE_X;
        current_h = SIZE_Y;
    } else {
        current_w = SIZE_Y;
        current_h = SIZE_X;
    }

    switch (mode) {
        case FONT_5X7 :

            current_fx = 6;
            current_fy = 8;
            break;
        case FONT_7X8 :
            current_fx = 7;
            current_fy = 8;
            break;
        case FONT_8X8 :
            current_fx = 8;
            current_fy = 8;
            break;
        case FONT_8X12 :
            current_fx = 8;
            current_fy = 12;
            break;
        case FONT_12X16 :
            current_fx = 12;
            current_fy = 16;
            break;
        default:
            current_fx = 8;
            current_fy = 8;
    }

    max_col = current_w / (current_fx*current_wf);
    max_row = current_h / (current_fy*current_hf);

    writeCOMMAND(command, 3);
}



//****************************************************************************************************
void text_mode(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTMODE;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void text_bold(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTBOLD;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void text_italic(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTITALIC;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void text_inverse(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTINVERSE;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void text_underline(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTUNDERLINE;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void text_width(char width)     // set text width
{
    char command[3]= "";

    command[0] = TEXTWIDTH;
    command[1] = 0;
    command[2] = width;
    current_wf = width;
    max_col = current_w / (current_fx*current_wf);
    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void text_height(char height)     // set text height
{
    char command[3]= "";

    command[0] = TEXTHEIGHT;
    command[1] = 0;
    command[2] = height;
    current_hf = height;
    max_row = current_h / (current_fy*current_hf);
    writeCOMMAND(command, 3);
}


//****************************************************************************************************
void text_char(char c, char col, char row, int color)     // draw a text char
{
    char command[6]= "";
	  int red5, green6, blue5;
    command[0] = 0xE4; //move cursor
    command[1] = 0;
    command[2] = row;
    command[3] = 0;
    command[4] = col;
    writeCOMMAND(command, 5);

    command[0] = 0x7F;  //set color

    red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color
    writeCOMMAND(command, 3);

    command[0] = TEXTCHAR;  //print char
    command[1] = 0;
    command[2] = c;
    writeCOMMAND(command, 3);

}


//****************************************************************************************************
void text_string(char *s, char col, char row, char font, int color)     // draw a text string
{

    char command[1000]= "";
    int size = strlen(s);
    int i = 0;
    int red5, green6, blue5;
	
    set_font(font);

    command[0] = 0xE4; //move cursor
    command[1] = 0;
    command[2] = row;
    command[3] = 0;
    command[4] = col;
    writeCOMMAND(command, 5);

    command[0] = 0x7F;  //set color
    red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color
    writeCOMMAND(command, 3);

    command[0] = TEXTSTRING;
    for (i=0; i<size; i++) command[1+i] = s[i];
    command[1+size] = 0;
    writeCOMMANDnull(command, 2 + size);
}



//****************************************************************************************************
void locate(char col, char row)     // place text curssor at col, row
{
    char command[5] = "";
    current_col = col;
    current_row = row;
    command[0] = MOVECURSOR; //move cursor
    command[1] = 0;
    command[2] = current_row;
    command[3] = 0;
    command[4] = current_col;
    writeCOMMAND(command, 5);
}

//****************************************************************************************************
void color(int color)     // set text color
{
    char command[5] = "";
	  int red5, green6, blue5;
    current_color = color;
    command[0] = 0x7F;  //set color

    red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color
    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void putc(char c)      // place char at current cursor position
//used by virtual printf function _putc
{
	  //while (!((UART0->S1)&(UART_S1_TDRE_MASK)));  
	  //UART0->D = dato;
    char command[6] ="";
    if(c<0x20) {
        if(c=='\n') {
            current_col = 0;
            current_row++;
            command[0] = MOVECURSOR; //move cursor to start of next line
            command[1] = 0;
            command[2] = current_row;
            command[3] = 0;
            command[4] = current_col;
            writeCOMMAND(command, 5);
        }
        if(c=='\r') {
            current_col = 0;
            command[0] = MOVECURSOR; //move cursor to start of line
            command[1] = 0;
            command[2] = current_row;
            command[3] = 0;
            command[4] = current_col;
            writeCOMMAND(command, 5);
        }
        if(c=='\f') {
            cls(); //clear screen on form feed
        }
    } else {
        command[0] = PUTCHAR;
        command[1] = 0x00;
        command[2] = c;
        writeCOMMAND(command,3);
        current_col++;
    }
    if (current_col == max_col) {
        current_col = 0;
        current_row++;
        command[0] = MOVECURSOR; //move cursor to next line
        command[1] = 0;
        command[2] = current_row;
        command[3] = 0;
        command[4] = current_col;
        writeCOMMAND(command, 5);
    }
    if (current_row == max_row) {
        current_row = 0;
        command[0] = MOVECURSOR; //move cursor back to start
        command[1] = 0;
        command[2] = current_row;
        command[3] = 0;
        command[4] = current_col;
        writeCOMMAND(command, 5);
    }
}


//****************************************************************************************************
void puts(char *s)     // place string at current cursor position
{

    text_string(s, current_col, current_row, current_font, current_color);

    current_col += strlen(s);

    if (current_col >= max_col) {
        current_row += current_col / max_col;
        current_col %= max_col;
    }
    if (current_row >= max_row) {
        current_row %= max_row;
    }
}

