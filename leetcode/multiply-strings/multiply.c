#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t K = 8;
enum { MAXLEN = 100 };

static void String2IntVectorGrouped(const char* s, long long int* result, size_t* resultLen)
{
    *resultLen = 0;
    const size_t len = strlen(s);
    const char* it = s + len - 1;
    while (it + 1 != s)
    {
        int num = 0;
        long long int mul = 1;
        for (size_t i = 0; i < K; ++i)
        {
            if (it + 1 != s)
            {
                num += mul*(*it - '0');
                mul *= 10;
                --it;
            }
            else
            {
                break;
            }
        }
        result[*resultLen] = num;
        ++(*resultLen);
    }
}

size_t aLen;
long long int a[MAXLEN];
size_t bLen;
long long int b[MAXLEN];
size_t result1000Len;
long long int result1000[MAXLEN];
size_t resultLen;
int result[MAXLEN];
char sResult[MAXLEN];

static char ZERO[] = "0";

char* multiply(char* num1, char* num2)
{
    size_t num1len = strlen(num1);
    size_t num2len = strlen(num1);

    if (num1len < 7 && num2len < 7)
    {
        long long int a = atoll(num1);
        long long int b = atoll(num2);
        sprintf(sResult, "%lld", a*b);
        return sResult;
    }

    String2IntVectorGrouped(num1, a, &aLen);
    String2IntVectorGrouped(num2, b, &bLen);

    result1000Len = aLen + bLen + 1;
    memset(result1000, 0, sizeof(result1000[0])*result1000Len);
    for (size_t i = 0; i < aLen; ++i)
    {
        for (size_t j = 0; j < bLen; ++j)
        {
            result1000[i + j] += a[i]*b[j];
        }
    }

    for (size_t i = 0; i + 1 < result1000Len; ++i)
    {
        static const long long int MUL = 100000000;
        result1000[i + 1] += result1000[i]/MUL;
        result1000[i] %= MUL;
    }

    resultLen = K*result1000Len;
    for (size_t i = 0; i < result1000Len; ++i)
    {
        int num = result1000[i];
        size_t index = K*i;
        for (size_t j = 0; j < K; ++j)
        {
            result[index++] = num % 10;
            num /= 10;
        }
    }

    int index = -1;
    for (int i = resultLen - 1; i >= 0; --i)
    {
        if (result[i])
        {
            index = i;
            break;
        }
    }

    if (-1 == index)
    {
        return ZERO;
    }

    sResult[index + 1] = 0;
    for (int i = 0; i <= index; ++i)
    {
        sResult[i] = result[index - i] + '0';
    }

    return sResult;
}

int main()
{
    printf("%s\n", multiply("121", "21"));
	return 0;
}