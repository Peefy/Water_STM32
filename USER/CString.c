#include "CString.h"

char * CStringCopy(char *destination , char * source)
{
   while(*destination++ = *source++);
   return(destination-1);
}

char *CStringConnact(char *target,char * source)
{
   char *original=target;
   while(*target)
   target++;
   while(*target++ = *source++);
   return(original);
}

int CStringLetterFirstIndexOf( char*string, char letter)
{
   char *original=string;
   while((*string!=letter)&&(*string))
   string++;
   return(string-original);
}

int CStringLetterLastIndexOf(char *string,char letter)
{
   char *original=string;
   char *ptr=NULL;
   while(*string)
   {
      if(*string==letter)
         ptr=string;
      string++;
   }
   return((*ptr)?ptr-original:string-original);
}

char *CStringAfterLetterFisrt(char *string, char letter)
{
   char *ptr=NULL;
   while(*string)
   {
      if(*string==letter)
      ptr=string;
      string++;
   }
   return (ptr);
}

char *CStringAfterLetterLast( char *string, char letter)
{
   while((*string!=letter)&&(*string))
   string++;
   return (string);

}

int CStringLetterCount(const char *string,char letter)
{
    int count=0;
    while(*string)
    if(*string++ ==letter)
       count++;
    return(count);
}

bool CStringContainsLetter( char *string,char letter)
{
	  return CStringLetterCount(string,letter)>0?true:false;
}

char * CStringSubString( char *s1, char *s2)
{
    int  i,j,k;
    for(i=0; s1[i]; i++)
         for(j=i,k=0; s1[j]==s2[k]; j++,k++)
                 if(!s2[k+1])
                       return(s1+i);
    return(NULL);
}

bool CStringContainsSubString(char *s1,char *s2)
{
    return CStringSubString(s1,s2) == NULL?false:true;
}

char *CStringReserse(char *string)
{
    char *original=string;
    char *forward=string;
    char tmp;
    while(*string)
        string++;
    while(forward<string)
    {
        tmp=*(--string);
        *string=*forward;
        *forward++=tmp;
    }
    return(original);
}

int CStringCompare(const char *s1, const char *s2)
{
    while((*s1==*s2)&&(*s1))
    {
          s1++;
          s2++;
    }
    if((*s1==*s2)&&(!*s1))
         return(0);
    else if((*s1)&&(!*s2))
         return(-1);
    else if((!*s1)&&(*s2))
         return(1);
    else
        return((*s1>*s2)?-1:1);

}

unsigned int CStringFirstOneLetterNotInSecondIndexOf(const char *s1, const char *s2)//
{
    int i,j;
    for(i=0;*s1;i++,s1++)
    {
        for(j=0; s2[j]; j++)
            if(*s1==s2[j])
               break;
        if(s2[j]==NULL)
            break;
    }
    return(i);

}

char * CStringRemoveSubString(char *string, char *substring)//
{
    int  i,j,k,loc=-1;
    for(i=0; string[i]&&(loc==-1); i++)
          for(j=i,k=0; string[j]==substring[k]; j++,k++)
                 if(!substring[k+1])
                       loc=i;
    if(loc!=-1)
    {
       for(k=0; substring[k];k++)
          for(j=loc;i=loc+k,string[i]; j++, i++)
                 string[j]=string[i];
       string[i]=NULL;
    }
    return(string);
}

int CStringLenth(char * string)
{
	char * origin = string;
	while(*string)
    string++;
	return string - origin;
}

char *CStringReplaceSubString(char *source, char *old , char *news)//
{
     char *original=source;
     char temp[256];
     int old_length=CStringLenth(old);
     int  i,j,k,location=-1;
         for(i=0; source[i]&&(location==-1); i++){}
             for(j=i,k=0; source[j]==old [k]; j++,k++)
                   if(!old [k+1])
                       location=i;
      if(location!=-1)
      {
           for(j=0;j<location;j++)
                  temp[j]=source[j];
           for(i=0;news[i];i++,j++)
                  temp[j]=news[i];
           for(k=location+old_length;source[k];k++,j++)
                   temp[j]=source[k];
           temp[j]=NULL;
          for(i=0; source[i]=temp[i];i++){}
      }
      return(original);
} 

char *CStringToUpper(char *string)//
{
		int  i;
    for(i=0; string[i]; i++)
		{
				if(string[i]>= 'a' && string[i]<= 'z')
					string[i] -= ('a'-'A');
		}
		return string;
} 

char *CStringToLower(char *string) //
{
				int  i;
    for(i=0; string[i]; i++)
		{
				if(string[i]>= 'A' && string[i]<= 'Z')
					string[i] += ('a'-'A');
		}
		return string;
} 
