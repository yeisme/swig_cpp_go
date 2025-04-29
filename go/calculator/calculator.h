#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{
  public:
    Calculator();
    ~Calculator();

    // 基本数学运算
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);

    // 状态跟踪
    int getOperationCount();

  private:
    int operationCount;
};

#endif
