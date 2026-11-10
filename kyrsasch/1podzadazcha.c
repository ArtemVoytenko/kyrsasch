#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    double x, y;

    printf("Введите x: ");
    scanf("%lf", &x);

    if (x > 0)
    {
        if (tan(exp(cos(sqrt(x)))) == 0)
        {
            printf("Ошибка: деление на ноль \n");
        }
        else
        {
            y = (sin(x * x + 1 / x + pow(x, 1.0 / 3.0)) / tan(exp(cos(sqrt(x))))) * 0.000001;
            printf("Y(x) = %lf", y);
        }
    }
    else
    {
        printf("x должен быть больше 0 \n");
    }

    return 0;
}       