#include "checker.h"
#include <iostream>

int checkNum(int num)
{
    int ret = 0;
    if (num > 0)
    {
        ret = 1;
    }
    else if (num == 0)
    {
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    std::cout << __func__ << ":" << __LINE__ << " param=" << num << " result=" << ret << std::endl;
    return ret;
}
