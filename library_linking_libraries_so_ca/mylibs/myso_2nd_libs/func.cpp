#include "func.h"
#include <iostream>
#include "checker.h"

int calcFunc(int x, int y)
{
    checkNum(x);
    checkNum(y);
    int sum;
    sum = x + y;
    std::cout << __func__ << ":" << __LINE__ << " result=" << sum << std::endl;
    return sum;
}
