#include <reg52.h>
#include <lcd.h>
#include <stdio.h>
#include <string.h>

sbit RS = P0^0;
sbit EN = P0^1;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;

sbit RB0 = P3^0;
sbit RB1 = P3^1;
sbit RB2 = P3^2;
sbit RB3 = P3^3;
sbit RB4 = P3^4;
sbit RB5 = P3^5;
sbit RB6 = P3^6;
sbit RB7 = P3^7;
sbit RC0 = P1^0;
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

void Delay(int a)
{
	int j;
  int i;
  for(i=0;i<a;i++)
  {
    for(j=0;j<100;j++)
    {
    }
  }
}
int main() {
    int hh = 0,mm = 0,ss = 0;
    char strh[3],strm[3],strs[3];
    /*
     * P3^0 = Hours+
     * P3^1 = Hours-
     * P3^2 = Minutes+
     * P3^3 = Minutes-
     * P3^4 = seconds+
     * P3^5 = seconds-
     * P3^6 = Starting timer
		 * P3^7 = Relay control
		 * P1^0 = Transistor circuit connected
     */
    Lcd4_Init();
    //Detecting which switch is pressed
    start:
    if(RB0 == 0) {
        hour:
        hh++;
        itoa(hh,strh);
        Delay(500);
        goto here;
    }
    else if(RB1 == 0) {
        hh--;
        if(hh < 0) {
            hh = 0;
            strh[0] = '0';
            strh[1] = ' ';
            goto start;
        }
        itoa(hh,strh);
        Delay(500);
        goto here;
    }
    else if(RB2 == 0) {
        minute:
        mm++;
        if(mm > 59) {
            strm[0] = '0';
            strm[1] = ' ';
            mm = 0;
            goto hour;
        }
        itoa(mm,strm);
        Delay(500);
        goto here;
    }
    else if(RB3 == 0) {
        mm--;
        if(mm < 0) {
            mm = 0;
            strm[0] = '0';
            strm[1] = '0';
            goto start;
        }
        itoa(mm,strm);
        Delay(500);
        goto here;
    }
    else if(RB4 == 0) {
        ss++;
        if(ss > 59) {
            strs[0] = '0';
            strs[1] = ' ';
            ss = 0;
            goto minute;
        }
        itoa(ss,strs);
        Delay(500);
        goto here;
    }
    else if(RB5 == 0) {
        ss--;
        if(ss < 0) {
            ss = 0;
            strs[0] = '0';
            strs[1] = '0';
            goto start;
        }
        itoa(ss,strs);
        Delay(500);
        goto here;
    }
    // This while loop will start when enable switch is on. This while loop will work as timer
    RC0 = 0;
    while(RB6 == 0) {
        int status = 0;
        if(RB7 == 0) {
            status = 1;
            RC0 = 1;
        }
        else {
            status = 0;
            RC0 = 0;
        }
        if(ss > 0) {
            --ss;
            Delay(1000);
        }
        else if(ss == 0 && mm > 0) {
            Delay(1000);
             --mm;
             ss = 59;
        }
        else if(mm == 0 && hh > 0) {
            --hh;
            mm = 59;
        }
        else if(hh == 0 && mm == 0 && ss == 0) {
            RC0 = !status;
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
  
  return 0;
}