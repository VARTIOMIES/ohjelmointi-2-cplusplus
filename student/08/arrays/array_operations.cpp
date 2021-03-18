#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int max=0;
    for (int i =0;i<size;i++,itemptr++)
    {
        if (*itemptr>max)
        {
            max = *itemptr;
        }
    }
    return max;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int max = 0;
    for (int* position = itemptr ;*position<*endptr; position++)
    {
        if (*position>max)
        {
            max=*position;
        }
    }
    return max;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while(itemptr<endptr)
    {
        *targetptr = *itemptr;
        itemptr++;
        targetptr++;
    }
}


void reverse(int *leftptr, int *rightptr)
{
    rightptr--;
    while (leftptr<rightptr)
    {
        int temp = 0;
        temp = *rightptr;
        *rightptr = *leftptr;
        *leftptr=temp;
        leftptr++;
        rightptr--;
    }
}
