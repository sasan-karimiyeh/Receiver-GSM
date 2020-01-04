void mil2shm (int day,int mon,int year,int *rooz,int *mah,int *sal){
int a,i;
bit b;
char month[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
if(year%4==0){month[1]=29;}
if(year%4==1){b++;}
a=0;
 for(i=0;i<mon-1;i++){          //calculate day of year
 a+=month[i];
 }
 a+=day;
 
 if(a<=79){                     //iranian old year
 a=a+10+b;
  if(a%30==0){
  *mah=9+(a/30);
  *sal=year+78;
  *rooz=30;
  }
  
  if(a%30!=0){
  *rooz=a%30;
  *mah=10+(a/30);
  *sal=year+78;
  }
  goto loop1; 
 }
 
 if(a>79){        //Iranian new year
 a-=79;
  if(a<=186){     //in first half of Iranian new year
   if(a%31==0){
   *mah=a/31;
   *sal=year+79;
   *rooz=31;
   }

   if(a%31!=31){
   *rooz=a%31;
   *mah=1+(a/31);
   *sal=year+79;
   } 
  }
  
  if(a>186){     //in second half of Iranian new year
  a-=186;
   if(a%30==0){
   *mah=6+(a/30);
   *sal=year+79;
   *rooz=30;
   }

   if(a%30!=30){
   *rooz=a%30;
   *mah=7+(a/30);
   *sal=year+79;
   }
  }
 } 
 loop1:
}

void shm2mil (int rooz,int mah,int sal,int *day,int *mon,int *year){
int a,i;
bit b,c;
int month[9]={ 30, 31, 30, 31, 31, 30, 31, 30, 31};
if(sal%4==3){b++;}             //leap year in georgian
a=0;
 for(i=0;i<mah-1;i++){
 a=a+(31-(i/6));
 }
 a+=rooz;                      //calculate day of year 
 if(a<=(286+b)){               //in old year of georgian
 *year=sal-79;
 if(*year%4==0){c++;}
 if(a<(12+c)){*mon=3;*day=a+20-c;}
  if(a>=(12+c)){
  a-=(11+c);
  i=0;
   for(i=0;a>30;i++){
   a-=month[i];
   if(a==0){a+=month[i];goto loop1;}
   }
   loop1:
   *mon=4+i;
   *day=a;
  }
 } 
 
 if(a>(286+b)){                //in new year of georgian
 *year=sal-78;
 a-=(286+b);
 if(*year%4==0){c++;}
 if(a>(59+c)){*mon=3;*day=a-(59+c);}    
 if(a<32){*mon=1;*day=a;}
 if(31<a && a<(58+c)){*mon=2;*day=a-31;} 
 }
}
