#define _CRT_SECURE_NO_WARNINGS // ���þ���
#include <stdio.h>

// �ݹ麯���������ۼӺ�
int sum(int n) 
{
    if (n == 1) 
    {
        return 1; // �����������nΪ1ʱ������1
    }
    else 
    {
        return n + sum(n - 1); // �ݹ���ã���n��1��n-1���ۼӺ����
    }
}

int main() 
{
    int number;

    // ���û������ȡnumber��ֵ
    printf("������һ����������");
    scanf_s("%d", &number);

    if (number < 1)
    {
        printf("������һ����������\n");
        return 1; // ����û�����Ĳ����������������˳������ش������
    }

    printf("��1��%d���������ۼӺ��� %d\n", number, sum(number));

    return 0;
}
