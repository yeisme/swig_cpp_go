package main

/*
#cgo CFLAGS: -I../
#cgo windows LDFLAGS: -L../ -lcalculator -lstdc++
#cgo windows LDFLAGS: -Wl,--allow-multiple-definition
*/
import "C"
import (
	"fmt"
	calculator "swig_cpp_go"
)

func main() {
	// 创建一个新的Calculator实例
	calc := calculator.NewCalculator()
	defer calculator.DeleteCalculator(calc)

	// 测试基本数学运算
	fmt.Println("数学运算测试:")
	fmt.Printf("10 + 5 = %.2f\n", calc.Add(10, 5))
	fmt.Printf("10 - 5 = %.2f\n", calc.Subtract(10, 5))
	fmt.Printf("10 * 5 = %.2f\n", calc.Multiply(10, 5))
	fmt.Printf("10 / 5 = %.2f\n", calc.Divide(10, 5))

	// 获取操作计数
	fmt.Printf("\n总执行操作次数: %d\n", calc.GetOperationCount())
}
