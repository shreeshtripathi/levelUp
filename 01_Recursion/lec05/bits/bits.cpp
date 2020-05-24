#include <iostream>
#include <vector>
using namespace std;

int offToOn(int num, int k)
{
    int mask = (1 << k);
    return (num | mask);
}

int onToOff_01(int num, int k)
{
    int mask = (~(1 << k)); //1's compliment of mask.
    return (num & mask);
}

int onToOff_02(int num, int k)
{
    int mask = (1 << k); //1's compliment of mask.
    if ((num & mask) == 0)
        return num;
    else
        return (num ^ mask);
}

// in JAVA we can  use triple right shift, it will ensure to append 0
// from right side
int countAllSetBits_02(unsigned int num)
{
    int count = 0;
    while (num != 0)
    {
        if ((num & 1) != 0)
            count++;
        num >>= 1;
    }
}

int countAllSetBits_03(int num)
{
    int count = 0;
    while (num != 0)
    {
        count++;
        num &= (num - 1);
    }
    return count;
}

//~~~~~~~~~~~~leetcode 191 ~~~~~~~~~~~~~~~~~~
// count of 1 in binary digit of a number
int hammingWeight(int n)
{
    int count = 0;
    while (n != 0)
    {
        count++;
        n = (n & (n - 1));
    }
    return count;
}

//~~~~~~~~~~~~leetcode 231 ~~~~~~~~~~~~~~~~~~
// a number of of power two or not
bool isPowerOfTwo(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

//~~~~~~~~~~~~leetcode 338 ~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~leetcode 260 ~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~leetcode 137 ~~~~~~~~~~~~~~~~~~

void leetcode()
{
}

int main()
{
    leetcode();
    return 0;
}