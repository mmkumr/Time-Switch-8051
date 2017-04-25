<b>Time-Switch-8051</b>

This project can be use for turning ON/OFF an AC 220v 50Hz device. 8051(89c51) microcontroller is used in this project. 16 x 2 Lcd display is used for displaying time.
    
   There is file in Time-Switch-8051/lcd.h by including this file in your C program file you can easily manupulate the lcd operations. Just by calling the below function :-
     
        Lcd4_Clear() :- To clear the display.
        Lcd4_Set_Cursor(int row, int column) :- This fuction is used to set row and column of the cursor on the LCD screen. By using this function we can change the position of the character or string displayed by Lcd functions.
        Lcd4_Write_Char(char) :- To write a character to LCD on the current position.
        Lcd4_Write_String(char *string) :- To write string to LCD on the current position.
        Lcd4_Shift_Right() :- To shift contents on the LCD right once without changing the data in the display RAM.
        Lcd4_Shift_Left() :- To shift contents on the LCD left once without changing the data in the display RAM.
       Note:- Lcd8 keyword will be used when we will use 8bit lcd mode   
If you want to simulate the circuit then install ISIS Proteous then goto git repo and click on Time-Switch 8051.pdsprj.

<b> Hardware </b>

Connect the circuit as per circuit diagram drawn in the image.

Burn the hex file to 8051 microcontroller. Hex file is present in the folder 'git repo/Time-Switch 8051.hex'.

Set the time using six button which are connected for increasing and decreasing of hours, minutes and seconds.

Turn on the enable switch.

Switch on the button which is connect to port1.0 pin of 8051 for keeping the AC device in ON condition intially and will be OFF after your setted time will complete. OFF the switch if you want to keep the device OFF at initial condition after setted time will complete it will remain ON until you turn OFF.
