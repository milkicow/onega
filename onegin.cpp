#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#define YA_PETUSHARA{                   \
    printf("sanya lox %d\n", __LINE__);  \
    fflush(stdout);                       \
}


void BufferText(FILE* f1, int* nstr, int* nlet);
void CreateArrays(int nstr, int nlet, char*** lines, char** buffer);
void FillArrays(FILE* f1, char** lines, char* buffer);
void PrintfArray(FILE* f2, char** lines, char* buffer, int nstr, int nlet);
void PrintfRevArray(FILE* f2, char** lines, char* buffer, int nstr, int nlet);
int StrCompare(char str1[], char str2[]);
int RevStrCompare(char str1[], char str2[]);
void StrSwap(char* str1, char* str2);
void StrSort(char** lines, char* buffer, int nstr);
void RevStrSort(char** lines, char* buffer, int nstr);


int main()
{   
    FILE* f1 = NULL;
    f1 = fopen("Hamlet.txt", "r");

    FILE* f2 = NULL;
    f2 = fopen("SortHamlet.txt", "w");

    FILE* f3 = NULL;
    f3 = fopen("RevSortHamlet.txt", "w");

    assert(f1 != NULL);
    assert(f2 != NULL);

    int nstr = 0;
    int nlet = 0;

    char** lines  = nullptr;
    char* buffer = nullptr;

    BufferText(f1, &nstr, &nlet);

    CreateArrays(nstr, nlet, &lines, &buffer);

    FillArrays(f1, lines, buffer);


    RevStrSort(lines, buffer, nstr);

    PrintfRevArray(f3, lines, buffer, nstr, nlet);

    printf("reverse sort completed\n");

    StrSort(lines, buffer, nstr);

    PrintfArray(f2, lines, buffer, nstr, nlet);

    printf("sort completed\n");



    fclose(f1);
    fclose(f2);

    free(lines);
    free(buffer);

    return 0;
}   

void BufferText(FILE* f1, int* nstr, int* nlet)
{   
    assert(f1);
    assert(nstr);
    assert(nlet);

    char ch = 0;
    if((ch = getc(f1)) != EOF)
    {
        *nstr = 1;
        rewind(f1);
    }
    while((ch = getc(f1)) != EOF)
    {
        (*nlet)++;
        if(ch == '\n')
        {
            (*nstr)++;
        }

    }
    printf("\nвсего строк (включая пустые) %d\n", *nstr);
    printf("буков (включая пробелы) %d\n", *nlet);
}//fread

void CreateArrays(int nstr, int nlet, char*** lines, char** buffer)
{   
    assert(lines);
    assert(buffer);

    *lines = (char**) calloc(nstr, sizeof(char*));
    *buffer = (char*) calloc(nlet + 1, sizeof(char));
    assert(lines);
    assert(buffer);
}

void FillArrays(FILE* f1, char** lines, char* buffer)
{   
    assert(lines);
    assert(buffer);
    assert(f1);

    rewind(f1);

    int ch = 0;

    char* start   = buffer;
    char* current = buffer;
    while((ch = getc(f1)) != EOF)
    {
        if (ch == '\n')
        {
            *current = '\0';
            *lines = start;
            lines++;

            start = current + 1;
        }
        else
        {
            *current = ch;
        }
        current++;
    }
}

int StrCompare(char str1[], char str2[])
{

    assert(str1);
    assert(str2);

    int i = 0;
    int j = 0;
    
    while(1)
    {   
        while(!isalpha(str1[i]) && (str1[i] != '\0')) 
        {
            i++;
        }
        while(!isalpha(str2[j]) && (str2[j] != '\0'))
        {
            j++;
        }
        if(str1[i] != str2[j]) break;
        if(str1[i] == '\0') break;
        i++;
        j++;
    }
    return(str1[i] - str2[j]);
}

void StrSwap(char* str1, char* str2)
{   
    assert(str1);
    assert(str2);

    char temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void StrSort(char** lines, char* buffer, int nstr)
{
    assert(lines);
    assert(buffer);

    for(int nPass = 0; nPass < nstr; nPass++)
    {
        for(int i = 0; i < (nstr - 2); i++)
        {
            if(StrCompare(lines[i], lines[i + 1]) > 0)
            {
                char* change;
                change = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = change;
            }
        }
    }
}   

int RevStrCompare(char str1[], char str2[])
{
    assert(str1);
    assert(str2);

    int i = strlen(str1) - 1;
    int j = strlen(str2) - 1;

    while(1)
    {   
        while(!isalpha(str1[i]) && (str1[i] != '\0')) 
        {
            i--;
        }
        while(!isalpha(str2[j]) && (str2[j] != '\0'))
        {
            j--;
        }

        if(str1[i] != str2[j]) break;
        if(str1[i] == '\0') break;
        i--;
        j--;
    }
    return(str1[i] - str2[j]);
}

void RevStrSort(char** lines, char* buffer, int nstr)
{
    assert(lines);
    assert(buffer);

    for(int nPass = 0; nPass < nstr; nPass++)
    {
        for(int i = 0; i < (nstr - 2); i++)
        {   
            if(RevStrCompare(lines[i], lines[i + 1]) > 0)
            {   
                char* change;
                change = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = change;
            }
        }
    }
}

void PrintfArray(FILE* f2 ,char** lines, char* buffer, int nstr, int nlet)
{   
    assert(f2);
    assert(lines);
    assert(buffer);

    int countLet = 0;
    char* current = *lines;

    for(int i = 0; i < (nstr - 1) ; i++)
    {
        for(; *current != '\0'; current++)
        {   
            if(isalpha(*current))
            {
                countLet++;
            }
        }
        if(countLet)
        {   
            fprintf(f2, "%s\n", *lines);
        }
        lines++;
        current = *lines;
        countLet = 0;
    }
}

void PrintfRevArray(FILE* f2, char** lines, char* buffer, int nstr, int nlet)
{
    assert(f2);
    assert(lines);
    assert(buffer);

    int countLet = 0;
    char* current = *lines;

    for(int i = 0; i < (nstr - 1) ; i++)
    {
        for(; *current != '\0'; current++)
        {   
            if(isalpha(*current))
            {
                countLet++;
            }
        }
        if(countLet)
        {   
            fprintf(f2, "%80s\n", *lines);
        }
        lines++;
        current = *lines;
        countLet = 0;
    }
}







/*char outGabarage[nlet];
    for(int k = 0; k < nlet; k++)
    {
        outGabarage[k] = lines[k];
    }
*/


/*void StrCompRev(char str1[], char str2[])
{
    assert(str1);
    assert(str2);

    int i;


    while(1)
    {
        if(str1[i] != str2[i]) break;
        if(str1[i] == '\0') break;
        i--;
    }
    return(str1[i] - str2[i]);

}*/

/*void BufferText(FILE* fp, int* nstr, int* nlet)
{

    while(*fp != '\0')
    {
        if (*fp == '\n')
        {   
            ++fp;
            *strings = fp;
            strings++;
        }
        else
        {
            *buffer = *fp;
        }

        *(fp++);
        i++;
    }
    printf("считано %d i символов", i);
}*/

/*int StrCompare(char* str1, char* str2)
{   
    assert(str1);
    assert(str2);

    while(1)
    {
        if(*str1 != *str2) break;
        if(*str1 != '\0') break;
        str1++;
        str2++;
    }
    return(*str1 - *str2);

}*/

/*void PrintfArray(FILE* f2 ,char** lines, char* buffer, int nstr, int nlet)
{   
    assert(f2);
    assert(lines);

    int countLet = 0;
    char* current = buffer;

    YA_PETUSHARA;

    for(int i = 0; i < (nstr - 1) ; i++)
    {
        fprintf(f2, "%s\n", *lines);
        lines++;
    }
}*/