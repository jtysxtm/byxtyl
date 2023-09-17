#define _CRT_SECURE_NO_WARNINGS // 禁用警告
#include <stdio.h>

// 递归函数来计算累加和
int sum(int n) 
{
    if (n == 1) 
    {
        return 1; // 基本情况：当n为1时，返回1
    }
    else 
    {
        return n + sum(n - 1); // 递归调用，将n与1到n-1的累加和相加
    }
}

int main() 
{
    int number;

    // 从用户输入获取number的值
    printf("请输入一个正整数：");
    scanf_s("%d", &number);

    if (number < 1)
    {
        printf("请输入一个正整数。\n");
        return 1; // 如果用户输入的不是正整数，程序退出并返回错误代码
    }

    printf("从1到%d的整数的累加和是 %d\n", number, sum(number));

    return 0;
}
