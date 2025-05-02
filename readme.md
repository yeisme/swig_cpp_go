# SWIG C++/Go 互操作示例项目

## 项目概述

这个项目展示了如何使用SWIG（Simplified Wrapper and Interface Generator）实现C++和Go语言之间的互操作。项目通过一个简单的计算器类（Calculator）演示了如何将C++代码包装成Go可以调用的形式，并在Go环境中使用这些功能。

## 技术背景

- **SWIG**：一个能够连接C/C++与多种高级编程语言的工具，本项目中用于C++和Go的互操作
- **C++**：实现核心功能的底层语言
- **Go**：调用C++库的高级语言
- **FFI（Foreign Function Interface）**：不同编程语言之间的互操作机制

## 项目结构

```
swig_cpp_go/
├── src/                    # C++源代码目录
│   ├── calculator.h        # C++头文件
│   ├── calculator.cpp      # C++实现文件
│   └── calculator.i        # SWIG接口文件
├── go/                     # Go代码目录
│   └── calculator/         # 生成的Go包
│       ├── cmd/            # Go命令行应用
│       │   └── main.go     # Go主程序
│       ├── calculator.go   # SWIG生成的Go包装代码
│       ├── calculatorGO_wrap.cxx # SWIG生成的C包装代码
│       └── go.mod          # Go模块定义
├── CMakeLists.txt          # CMake构建文件
└── README.md               # 项目文档
```

## 依赖项

要构建和运行此项目，您需要安装以下软件：

- CMake (3.10+)
- C++编译器（支持C++11）
- SWIG (4.0+)
- Go (1.16+)
- 适用于您平台的构建工具（Make、Ninja等）

## 构建指南

### 1. 克隆仓库

```bash
git clone https://github.com/yeisme/swig_cpp_go.git
cd swig_cpp_go
```

### 2. 构建C++库

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

这将生成必要的库文件并将它们复制到Go包目录中。

### 3. 构建Go程序

```bash
cd go/calculator/cmd
go build -o calculator_demo.exe
```

### 4. 运行示例

```bash
./calculator_demo.exe
```

## 使用示例

在Go中使用C++实现的计算器：

```go
// 创建计算器实例
calc := calculator.NewCalculator()
defer calculator.DeleteCalculator(calc)

// 执行基本运算
result := calc.Add(10, 5)
fmt.Printf("10 + 5 = %.2f\n", result)

// 获取操作计数
count := calc.GetOperationCount()
fmt.Printf("操作次数: %d\n", count)
```

## 项目工作原理

1. **SWIG接口定义**：在`calculator.i`文件中定义需要导出的C++接口
2. **代码生成**：SWIG根据接口定义生成Go和C++包装代码
3. **编译与链接**：将C++代码编译为共享库
4. **Go调用**：Go代码通过CGo机制调用生成的包装函数，间接调用C++实现

## 实现细节

### C++类设计

`Calculator`类实现了四则运算功能，并跟踪执行的操作次数：

- `add`, `subtract`, `multiply`, `divide`: 基本数学运算方法
- `getOperationCount`: 获取已执行的操作次数

### SWIG接口

SWIG接口文件声明了需要包装的C++头文件，SWIG会自动为所有公共方法生成对应的Go函数。

### Go包装

生成的Go代码提供了面向Go开发者的友好接口，包括：

- 构造和析构函数：`NewCalculator()`, `DeleteCalculator()`
- 封装的方法调用：`Add()`, `Subtract()`, `Multiply()`, `Divide()`, `GetOperationCount()`

## 常见问题与解决方案

### 内存管理

在Go中使用C++对象时，需要手动管理内存。确保在不再需要对象时调用`DeleteCalculator()`函数，或使用`defer`语句确保资源被释放。

### 错误处理

C++代码中的异常不会自动转换为Go错误。对于可能失败的操作（如除以零），需要在C++或Go代码中添加适当的检查。

### 跨平台兼容性

在不同平台上构建时可能需要调整构建设置。特别是Windows用户可能需要修改CGo链接参数。
