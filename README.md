# Linear Programming Based on C language

## you can use it to solve linear programming problems

### How to use it?

1. Before you inout your problem, you should normalized it as a matrix
2. Use CMake to build project
3. Input your matrix and get the solution

### Normalization

The linear problem is:
```math
$$\begin{cases}
        \min \quad z \\
        s.t. \quad \bf{A} \leq \vec b
    \end{cases}$$
```
And then, you should make inequality sign to be a equal sign, which means you need to add slack variables to every rows.

- An example to normalization
```math
  $$\begin{cases}
        \min \quad z \\
        s.t. \quad \bf{A} \leq \vec b
    \end{cases}$$
```
    that is
```math
    $$\begin{cases}
                \min \quad z = -6x_1+3x_2-3x_3 \\
                s.t. \quad 2x_1 + x_2 &\leq& 8 \\
                    \qquad -4x_1 -2x_2 + 3x_3 &\leq& 14 \\
                    \qquad x_1 -2x_2+x_3 &\leq& 18 \\
                    \qquad \vec x \geq 0
            \end{cases}$$
```
    after add slack variables $x_4, x_5, x_6$ that is
```math
    $$\begin{cases}
                \min \quad z = -6x_1+3x_2-3x_3 \\
                s.t. \quad 2x_1 + x_2 + x_4&=& 8 \\
                    \qquad -4x_1 -2x_2 + 3x_3 +x_5 &=& 14 \\
                    \qquad x_1 -2x_2+x_3 +x_6 &=& 18 \\
                    \qquad \vec x \geq 0
            \end{cases}$$
```
    and then, the matrix is
```math
    $$\begin{matrix}
      &x_1 & x_2 & x_3 & x_4 & x_5 & x_6 & RHS \\
      &2   & 1   & 0   & 1   & 0   & 0   & 8 \\
      &-4  & -2  & 3   & 0   & 1   & 0   & 14 \\
      &1   & -2  & 1   & 0   & 0   & 1   & 18 \\
    \end{matrix}$$
```
    and the object function is
```math
    $$\begin{matrix}
    6 & -3 & 3 & 0 & 0 & 0 & 0
    \end{matrix}
    $$
```
    but the RHS col must be all positive numbers, meaning that we need multiply -1 to some rows.

### Build Project

1. Install CMake
2. Use ```cd LinProg``` to enter the directory
3. Use ```mkdir cbuild``` to create a subdirectory and ```cd cbild``` to enter the subdirectory
4. Use ```cmake ..``` to configure project
5. Use ```cmake --build .``` to build project
6. Use ```./linprog``` to initiate project

### Use Project

After ```./linprog``` to initiate project, then input the matrix (only numbers) and the obj, then get the solution.
