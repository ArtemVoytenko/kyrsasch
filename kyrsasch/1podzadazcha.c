 // 5 ВАРИАНТ ВОЙТЕНКО АРТЁМ

#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <math.h>
#define MY_EPSILON 0.000000001

double calculate_Y(double x, int* error);
double calculate_V(double x, int* error);
void print_table(double start, double end, double step, int function_choice);
void print_graph(double start, double end, double step, int function_choice);

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");
    int choice;
    double x_start, x_end, step;
    while (1)
    {
        puts("---- МЕНЮ ТАБУЛИРОВАНИЯ ФУНКЦИЙ ----");
        puts("0. Выход из программы");
        puts("1. Табулировать функцию Y(x)");
        puts("2. Табулировать функцию V(x)");
        puts("Ваш выбор:");
        if (scanf("%d", &choice) != 1)
        {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice == 0)
        {
            break;
        }
        if (choice != 1 && choice != 2)
        {
            printf("Неверный выбор! Попробуйте снова.\n\n");
            continue;
        }
        printf("Введите начало интервала: ");
        if (scanf("%lf", &x_start) != 1)
        {
            printf("Ошибка ввода!\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("Введите конец интервала: ");
        if (scanf("%lf", &x_end) != 1)
        {
            printf("Ошибка ввода!\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("Введите шаг табуляции: ");
        if (scanf("%lf", &step) != 1)
        {
            printf("Ошибка ввода!\n\n");
            while (getchar() != '\n');
            continue;
        }
        if (step <= 0)
        {
            printf("Ошибка: шаг должен быть больше нуля!\n\n");
            continue;
        }
        if (x_start >= x_end)
        {
            printf("Ошибка: начало интервала должно быть меньше конца!\n\n");
            continue;
        }
        if ((x_end - x_start) / step >= 200)
        {
            printf("Слишком много точек! Увеличьте шаг.\n\n");
            continue;
        }
        print_table(x_start, x_end, step, choice);
        puts("\n--- ГРАФИК ФУНКЦИИ ---\n");
        print_graph(x_start, x_end, step, choice);
        puts("\n");
    }
    puts("Программа завершена.");
    return 0;
}

double calculate_Y(double x, int* error)
{
    double result;
    double denominator;
    *error = 0;
    if (x <= 0)
    {
        *error = 1;
        return 0.0;
    }
    denominator = tan(exp(cos(sqrt(x))));
    if (fabs(denominator) < MY_EPSILON)
    {
        *error = 1;
        return 0.0;
    }
    result = (sin(x * x + 1.0 / x + pow(x, 1.0 / 3.0)) / denominator) * 0.000001;
    return result;
}

double calculate_V(double x, int* error)
{
    *error = 0;
    if (x > 2.5)
    {
        return sin(2.3 * x - 1);
    }
    else if (x >= 0 && x <= 2.5)
    {
        if (fabs(1 - x) < MY_EPSILON)
        {
            *error = 1;
            return 0.0;
        }
        return 1 - 3 * log(fabs(1 - x));
    }
    else
    {
        return 2 - x;
    }
}

void print_table(double start, double end, double step, int function_choice)
{
    double x, y;
    int error;
    puts("\n------------------------------------------");
    if (function_choice == 1)
    {
        puts("       ТАБЛИЦА ЗНАЧЕНИЙ Y(x)");
    }
    else
    {
        puts("       ТАБЛИЦА ЗНАЧЕНИЙ V(x)");
    }
    puts("------------------------------------------");
    puts("       X          |          F(X)");
    puts("------------------------------------------");
    for (x = start; x <= end + step * 0.000001; x += step)
    {
        if (function_choice == 1)
        {
            y = calculate_Y(x, &error);
        }
        else
        {
            y = calculate_V(x, &error);
        }
        if (error == 1)
        {
            printf(" %14.4lf | Не определено\n", x);
        }
        else
        {
            printf(" %14.4lf | %20.10lf\n", x, y);
        }
    }
    puts("------------------------------------------");
}

void print_graph(double start, double end, double step, int function_choice)
{
    double x, y;
    double ymin = 0, ymax = 0;
    double range;
    int error;
    int count = 0;
    int i, pos;
    for (x = start; x <= end + step * 0.000001; x += step)
    {
        if (function_choice == 1)
        {
            y = calculate_Y(x, &error);
        }
        else
        {
            y = calculate_V(x, &error);
        }
        if (error == 0)
        {
            if (count == 0)
            {
                ymin = y;
                ymax = y;
            }
            else
            {
                if (y < ymin)
                {
                    ymin = y;
                }
                if (y > ymax)
                {
                    ymax = y;
                }
            }
            count++;
        }
    }
    if (count == 0)
    {
        printf("Нет точек для построения графика.\n");
        return;
    }
    range = ymax - ymin;
    if (range < MY_EPSILON)
    {
        range = 1.0;
    }
    for (x = start; x <= end + step * 0.000001; x += step)
    {
        if (function_choice == 1)
        {
            y = calculate_Y(x, &error);
        }
        else
        {
            y = calculate_V(x, &error);
        }
        printf("%10.4lf | ", x);
        if (error == 1)
        {
            printf("Вне ОДЗ\n");
            continue;
        }
        pos = (int)((y - ymin) / range * 40);
        if (pos >= 40)
        {
            pos = 39;
        }
        if (pos < 0)
        {
            pos = 0;
        }
        for (i = 0; i < pos; i++)
        {
            printf(" ");
        }
        printf("*\n");
    }
}
