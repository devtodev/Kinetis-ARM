/*
 * utils.c
 *
 *  Created on: Dec 26, 2015
 *      Author: Karl
 */

#include "utils.h"

char stopChar(char value);

unsigned int strLen(char *value)
{
	unsigned int i = 0;

	while ((i < 512) && (!stopChar(value[i])))
		i++;

	return i;
}


void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strLen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


void setLCD(char *data)
{
	vfnLCD_Write_Msg(data);
}

char stopChar(char value)
{
	return (value == EOS);
}

// que pasa si encuentro mas de los que estan dimensionados en la respuesta

int find(char *text, char *word, int *rtas)
{
	unsigned int indexRtas = 0;
	unsigned int index = 0;
	unsigned int equals = 0;
	unsigned int wordLen = strLen(word);
	unsigned char count = 0;
	//unsigned int textLen = length(text);

	rtas[indexRtas] = EOIL;
	while ((!stopChar(text[index])))
	{
		equals = (word[equals] == text[index])? equals+1 : 0;
		if (equals == wordLen)
		{
			rtas[indexRtas] = index-wordLen+1;
			equals = 0;
			indexRtas++;
			count++;
			rtas[indexRtas] = EOIL;
		}
		index++;
	}

	return indexRtas;
}

// return char len
int strsub(char *text, int init, int end, char *rta)
{
	int index = 0;
	if (init > end) return 0;
	while ((init+index <= end) && (text[init] != EOS))
	{
		rta[index] = text[init+index];
		index++;
	}
	rta[index] = EOS;

	return index;
}

