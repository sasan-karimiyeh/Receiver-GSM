

void getstr(char *str)
{
    char ch = 0;
    l=3;
    ti=0;
    tmin=0;
    TCCR2=0x07;
    ch = getchar();
    while((ch == 10) || (ch == 13) || (ch == 0))
        ch = getchar();
    
    while((ch != 10) && (ch != 13))
    {
        *str++ = ch;
        ch = getchar();
    }
    *str = 0;
    TCCR2=0;
}






int getnstr(char *str , int n)
{
    char ch = 0, counter = 0;
    ch = getchar();
    while((ch == 10) || (ch == 13) || (ch == 0)) {
        ch = getchar();                           
        if((counter++ == n))
            return 0;
    }
    
    while((ch != 10) && (ch != 13))
    {
        *str++ = ch;
        ch = getchar();
    }
    *str = 0;  
    
    return 1;
}








