#include <iostream>
#include <math.h>

void isPowOfTwo(double num)
{
    if (num <= 0)
    {
        std::cout << "NO" << std::endl;
        return;
    }
    if (num < 2)
    {
        while (num < 2)
            num *= 2;
        if (num == 2)
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
        return;
    }

    while (fmod(num, 2) == 0)
        num /= 2;
    if (num == 1)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
}

int main()
{
    double n;
    std::cout << "Enter a number: ";
    std::cin >> n;

    isPowOfTwo(n);

    return 0;
}
