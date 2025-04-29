#include "calculator.h"

Calculator::Calculator() : operationCount(0)
{
}

Calculator::~Calculator()
{
}

double Calculator::add(double a, double b)
{
    operationCount++;
    return a + b;
}

double Calculator::subtract(double a, double b)
{
    operationCount++;
    return a - b;
}

double Calculator::multiply(double a, double b)
{
    operationCount++;
    return a * b;
}

double Calculator::divide(double a, double b)
{
    operationCount++;
    if (b == 0)
        return 0; // 避免除零错误
    return a / b;
}

/**
 * @brief 获取操作计数器的值
 *
 * @return 当前操作计数器的值
 * @note 该函数不会增加操作计数器的值。
 */
int Calculator::getOperationCount()
{
    return operationCount;
}
