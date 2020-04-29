#include "baseClass.h"

namespace nBaseClass
{
bool isCurrectIP(const char *ip)
{
    if (ip == NULL)
    {
        return false;
    }
    char temp[4];
    int count = 0;
    while (true)
    {
        int index = 0;
        while (*ip != '\0' && *ip != '.' && count < 4)
        {
            temp[index++] = *ip;
            ip++;
        }
        if (index >= 4)
        {
            return false;
        }

        temp[index] = '\0';
        int num = atoi(temp);
        if (!(num >= 0 && num <= 255))
        {
            return false;
        }
        count++;
        if (*ip == '\0')
        {
            if (count == 4)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            ip++;
        }
    }
}

}
