#include <reg52.h>
#include "lcd.h"
#include <stdio.h>
#include <string.h>
//LCD
sbit RS = P0^0;
sbit EN = P0^1;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;
//Switches
sbit hoursp = P3^0;
sbit hoursn = P3^1;
sbit minutesp = P3^2;
sbit minutesn = P3^3;
sbit secondsp = P3^4;
sbit secondsn = P3^5;
sbit enable = P3^6;
sbit relay = P3^7;// For deciding to keep a device initially ON or OFF
sbit signal = P1^0;//This bit used for sending 0 or 1 to transistor for activating relay

char* itoa(int n,char s[]) {
    int i = 0 ,k = 0,td = n;
    char temp;
    // converting Integer to String
    loop:
    {
        s[i++] = n % 10 + '0';// n + '0' can convert the number in n to ASCII number
    } if((n /= 10) > 0) {
        goto loop;
    }
    //Reversing
    if(td > 9) {
            temp = s[0];
            s[0] = s[1];
            s[1] = temp;
            s[2] = '\0';
    }
		else {
			s[1] = '\0';
		}
    return s;
}

void Delay(unsigned int a) {
	unsigned int j,i;
		for(i=0;i<a;i++) 
			for(j=0;j<1275;j++) ;
}
int main() {
    int hh = 0,mm = 0,ss = 0;
    char strh[3],strm[3],strs[3];
    /*
     * P3^0 = Hours+ switch
     * P3^1 = Hours- switch
     * P3^2 = Minutes+ switch
     * P3^3 = Minutes- switch
     * P3^4 = Seconds+ switch
     * P3^5 = Seconds- switch
     * P3^6 = Starting timer switch
	 * P3^7 = Relay control switch
	 * P1^0 = Transistor circuit connected
     */
    Lcd4_Init();
    Lcd4_Clear();
    Lcd4_Set_Cursor(1,1);
    Lcd4_Write_String("Time switch");
    //Detecting which switch is pressed
    start:
    if(hoursp == 0) {
        hour:
        hh++;
        itoa(hh,strh);
        Delay(50);
        goto here;
    }
    else if(hoursn == 0) {
        hh--;
        if(hh < 0) {
            hh = 0;
            strh[0] = '0';
            strh[1] = ' ';
            goto start;
        }
        itoa(hh,strh);
        Delay(50);
        goto here;
    }
    else if(minutesp == 0) {
        minute:
        mm++;
        if(mm > 59) {
            strm[0] = '0';
            strm[1] = ' ';
            mm = 0;
            goto hour;
        }
        itoa(mm,strm);
        Delay(50);
        goto here;
    }
    else if(minutesn == 0) {
        mm--;
        if(mm < 0) {
            mm = 0;
            strm[0] = '0';
            strm[1] = '0';
            goto start;
        }
        itoa(mm,strm);
        Delay(50);
        goto here;
    }
    else if(secondsp == 0) {
        ss++;
        if(ss > 59) {
            strs[0] = '0';
            strs[1] = ' ';
            ss = 0;
            goto minute;
        }
        itoa(ss,strs);
        Delay(50);
        goto here;
    }
    else if(secondsn == 0) {
        ss--;
        if(ss < 0) {
            ss = 0;
            strs[0] = '0';
            strs[1] = '0';
            goto start;
        }
        itoa(ss,strs);
        Delay(50);
        goto here;
    }
    // This while loop will start when enable switch is on. This while loop will work as timer
    signal = 0;
    while(enable == 0) {
        int status = 0;
        if(relay == 0) {
            status = 1;
            signal = 1;
        }
        else {
            status = 0;
            signal = 0;
        }
        if(ss > 0) {
            --ss;
            Delay(100);
        }
        else if(ss == 0 && mm > 0) {
            Delay(100);
             --mm;
             ss = 59;
        }
        else if(mm == 0 && hh > 0) {
            --hh;
            mm = 59;
        }
        else if(hh == 0 && mm == 0 && ss == 0) {
            signal = !status;
        }
        if(hh < 10) {
            strh[1] = ' ';
        }
        if(mm < 10) {
            strm[1] = ' ';
        }
        if(ss < 10) {
            strs[1] = ' ';
        }
        itoa(hh,strh);
        itoa(mm,strm);
        itoa(ss,strs);
        goto here;
    }
    //End of detection which switch has pressed
    goto start;//This line will execute until any switch is pressed.
    { // when any switch is pressed then this block of code will execute
      here:
      Lcd4_Clear();
      Lcd4_Set_Cursor(1,1);
      Lcd4_Write_String(strh);
      Lcd4_Set_Cursor(1,3);
      Lcd4_Write_Char(':');
      Lcd4_Set_Cursor(1,4);
      Lcd4_Write_String(strm);
      Lcd4_Set_Cursor(1,6);
      Lcd4_Write_Char(':');
      Lcd4_Set_Cursor(1,7);
      Lcd4_Write_String(strs);
      goto start;
     }
  
}
