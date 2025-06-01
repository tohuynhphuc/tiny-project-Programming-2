# Linear System and Regression Project

## Group Members
1. 10423048 - Đào Gia Hưng
2. 10423053 - Nguyễn Hà Khải
3. 10423056 - Nguyễn Duy Khánh
4. 10423077 - Trần Ninh Nhật Minh
5. 10423093 - Tô Huỳnh Phúc
6. 10423097 - Ninh Hoàng Quân

## Major: CSE2023

## Class: Programming 2  

## Project Overview
This project is divided into two parts:

### Part A: Matrix Operations and Linear Systems

The main goal of Part A is to develop a system of classes to handle matrix operations and solve linear systems of equations. The key components include:

1. **Vector Class**
   - Implement memory management with constructors and destructors.
   - Overload assignment, unary, and binary operators for vector operations.
   - Overload square bracket and round bracket operators with bounds checking and 1-based indexing.

2. **Matrix Class**
   - Includes constructors, destructors, and memory management.
   - Overload operators for matrix operations (addition, subtraction, multiplication).
   - Implement methods for determinant, inverse, and pseudo-inverse calculations.
   - Overload the round bracket operator with 1-based indexing for matrix access.
   
3. **LinearSystem Class**
   - A class to represent a linear system of equations (Ax = b).
   - Implement a `Solve` method using Gaussian elimination with pivoting.
   - Derived class `PosSymLinSystem` to solve symmetric positive definite systems using the conjugate gradient method.
   
4. **Handling Ill-posed Problems**
   - Implement solutions for under-determined or over-determined systems using the Moore-Penrose inverse and/or Tikhonov regularization.

### Part B: Linear Regression for CPU Performance Prediction

In Part B, you will apply linear regression to predict relative CPU performance based on several attributes from a dataset. This part involves:

1. **Dataset**: [UCI Computer Hardware Dataset](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
   - 209 instances with 10 features.
   - 6 predictive attributes, 2 non-predictive attributes, and 1 goal field for linear regression prediction.

2. **Linear Regression Model**: 
   - Implement the linear regression model for predicting the relative performance of CPUs based on the formula:
   PRP = x1 * MYCT + x2 * MMIN + x3 * MMAX + x4 * CACH + x5 * CHMIN + x6 * CHMAX

   
3. **Evaluation**: 
   - Split the dataset into training (80%) and testing (20%) sets.
   - Evaluate the model using the Root Mean Square Error (RMSE) criterion.

## Files and Structure

- `Vector.h` / `Vector.cpp`: Implementations for the Vector class.
- `Matrix.h` / `Matrix.cpp`: Implementations for the Matrix class.
- `LinearSystem.h` / `LinearSystem.cpp`: Implementations for the LinearSystem and PosSymLinSystem classes.
- `LinearRegression.h` / `LinearRegression.cpp`: Implementations for the Linear Regression part.
- `README.md`: Overview and instructions for the project.

## Compilation and Execution
1. Clone the repository to an empty local directory:
```bash
$ git clone git@github.com:tohuynhphuc/tiny-project-Programming-2.git
```

2. Compile the project using a C++ compiler (in this case we used g++):
```bash
$ g++ main.cpp tests.cpp LinearSystem.cpp Matrix.cpp PosSymLinSystem.cpp Vector.cpp -o main
```
**Note:** `tests.cpp`, `LinearSystem.cpp`, `Matrix.cpp`, `PosSymLinSystem.cpp`, and `Vector.cpp` are all dependencies for `main.cpp`. They contain essential structure and function definitions required to run the program.

3. After which a `main.exe` executable will be created. You can run the executable with:
```bash
$ ./main
```

4. `main.exe` composes of 30 custom tests to verify various functionalities of the classes and methods implemented in the project. Output and test results will be displayed in the console.

## License

This project is licensed under the GNU v3 GENERAL PUBLIC LICENSE - see the [LICENSE](LICENSE) file for details.
