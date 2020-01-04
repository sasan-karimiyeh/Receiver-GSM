#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>  
#include <string.h>
#include <messages.h>
#include <ctype.h>
#include <stdlib.h>
#include <date.h>
////////////////////////////////
#define fp      "x108B5"
#define pwr_on  PORTD.4
#define com     PORTC.5
#define up_down PORTC.4
#define led     PORTA.3
#define simcard PINC.3
////////////////////////////////
int op,credit,co,ti,tmin,l,logc;
bit w,x,v,si=0,res=0;
int rooz,mah,sal,minu,hour,year,day,mon;
const char enter=13;
const char dq=34;
const char ctrlz=26;
char *sms_rec_date,*sms_rec_num,*p1;
char *call_rec_num1,*call_rec_num2;
char masrec[100];
eeprom int mac,z,u,auc,log_count;
/*
auc= auto close
u=date and door situ set check
z=door situ
mac=main account
*/
eeprom unsigned int cn[208][2];
eeprom unsigned int log_data[30][3];
///////////////////////////////////
void getstr(char *str)
{
char ch = 0;
ch = getchar();
while((ch == 10) || (ch == 13) || (ch == 0))
 ch = getchar();
    
 while((ch != 10) && (ch != 13))
 {
 *str++ = ch;
 ch = getchar();
 }
 *str = 0;
}
///////////////////////////////////
int strnchr(char *str,char c,int d){
int a;
a=0;
 do{
 if(*str==c){d--;}
 if(*str==NULL){return (-1);}
 str++;
 a++;
 }
 while(d>0);
 a--;
 return(a);  
}
///////////////////////////////////
int find_account(char *str){
int a,b,i,c;
char buf[];
c=strlen(str);
 for(i=0;i<c;i++){
 if(isdigit(str[0])==0){goto loop1;}
 str++;
 }
str-=c;
str+=6;
a=atoi(str);
str-=5;
str[5]=NULL;
b=atoi(str);
if(a==0 && b==0){return(0);}
 for(i=0;i<208;i++){
  if(cn[i][1]==a){
  if(cn[i][0]==b){return(i+1);}
  }
 }
 loop1:
 return(0);
}
///////////////////////////////////
void dial_rec(void){
int a,b,d=0;
bit c=0;
char buf[];
char text3[100],*str;
char text4[100];
getstr(text3);       
if(!strncmp(text3,"NO CARRIER",10)){goto loop1;}
 if(!strncmp(text3,"RING",4)){
 d++;
 loop2:
 getstr(text3);
 if(!strncmp(text3,"+CLIP",5)){c=1;}
 if(!strncmp(text4,"NO CARRIER",10)){goto loop1;}
 else {goto loop2;}
 }
 
 if(!strncmp(text3,"+CLIP",5) && c==0){
 c=1;
 loop3:
 getstr(text4);
 if(!strncmp(text4,"NO CARRIER",10)){goto loop1;}
 if(!strncmp(text4,"RING",4)){d++;}
 else{goto loop3;}
 } 

 if(d==1){
  if(w==0){
  w=1;
  call_rec_num1=text3;
  a=strnchr(call_rec_num1,'\"',2);
  b=strnchr(call_rec_num1,'\"',1);
  b++;
  call_rec_num1+=b;
  call_rec_num1[a-b]=NULL;
  if(call_rec_num1[0]=='+'){call_rec_num1+=2;}
  call_rec_num1++;
  d=find_accunt(call_rec_num1);
  }
  
  else{
  w=0;
  call_rec_num2=text3;
  a=strnchr(call_rec_num2,'\"',2);
  b=strnchr(call_rec_num2,'\"',1);
  b++;
  call_rec_num2+=b;
  call_rec_num2[a-b]=NULL;
  if(call_rec_num2[0]=='+'){call_rec_num2+=2;}
  call_rec_num2++;
  d=find_accunt(call_rec_num1);
  }
  u=2;
  d=2;
  if(d>0 && u==2){
  printf("ATH%c",enter);
  //operation();
  }
 }
loop1:
}
///////////////////////////////////
void main (void){
int ab,ad,a;
char buf[],text3[100];
 if(res==0){
 DDRB=0xfb;
 PORTB.2=1;
 DDRD=0xf2;
 PORTD.2=1;
 DDRA=0xff;
 DDRC=0xf0;
 PORTC.0=1;
 pwr_on=1;               //off sim800
 com=0;
 UCSRA=0x00;             //serial config
 UCSRB=0x18;             //no parity,8 bits,1bit stop
 UCSRC=0x86;             //baud rate=9600
 UBRRH=0x00;             //no interrupts
 UBRRL=0x47;
 /*led=1;                  //led on
 l=1;                    //timer bits
 ti=0; */     
 lcd_init(16);
 lcd_clear();
 lcd_putsf("Barron          Electronics");
 delay_ms(500);  
 MCUCR=0x08;       //failing edge enable interrupts 1 & 2
 MCUCSR=0;         //failing edge enable interrupt 3
 GIFR=0x80;        //all interrupts flags enables
 GICR=0x80;        //all interrupts enables
  mac=0;
  if(mac<1){     //for first time,deleting all contacts
  log_count=0;
  mac=1;
  /* for(ab=0;ab<2;ab++){
   for(ad=0;ad<208;ad++){
   cn[ad][ab]=0;
   }   
  }*/
  lcd_clear();
  lcd_putsf("contacts deleted");
  delay_ms(4000);  
  }  
 if(z<1){u=4;z=3;}
  /*
  u==> door situ and date config
  if u==2 device ready
  if u>2  device not ready,date and/or door situ not set
  */
  //z==> door situ in micro   
 //start_up_sim900();          //configuring module
 TCCR2=0; 
 #asm("sei")
 }
 }
//////////////////////////////////////////
 interrupt[EXT_INT1] void receiver (void){
 char *str,buf[];
 char text3[15];
  lcd_clear();
 getstr(text3);

 lcd_puts(text3);
  if(!strncmp(text3,"+CMTI",5)){      //sms receive
  str=text3;               //co=massage storage address
  co=strnchr(str,',',1);
  co+=1;
  str+=co;
  co=atoi(str);
  lcd_clear();
  sprintf(buf,"Co=%d",co);
  lcd_puts(buf);
  delay_ms(3000);          
 // sms_rec(co);
  //if(co>=8){sms_storage_dell();}
  }
  
  if(!strcmp(text3,"RING")){          //ring receive
  dial_rec();
  }  
 }
 