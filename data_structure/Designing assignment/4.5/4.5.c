#include"4.1.c"

void Replace(StringType *s,StringType t,StringType v)
{
    StringType result;
    
    result.ch=(char*)malloc(sizeof(char)*(s->length+1));//
    result.ch=NULL;
    result.length=0;

    int i=1,pos=1;
    while(pos=Index_KPM(*s,t,i)!=0)
    {
        pos=Index_KPM(*s,t,i);
        StringType pre=SubString(*s,i,pos-i);
        result=Concat(result,pre);
        result=Concat(result,v);
        i=pos+t.length;
    }
    if(i<s->length)
    {
        StringType later=SubString(*s,i,s->length-i+1);
        result=Concat(result,later);
    }

    StrAssign(s,result);
}

int main()
{
    StringType s,t,v;
    Create(&s);
    Create(&t);
    Create(&v);
    printf("before:\t%s\n",s.ch);
    Replace(&s,t,v);
    printf("after:\t%s\n",s.ch);

    return 0;
}