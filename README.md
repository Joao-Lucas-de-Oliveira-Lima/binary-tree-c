# Equation Solver Using Binary Tree

This project implements a binary tree to solve mathematical equations read from a text file. The binary tree structure is used to represent and evaluate the equation.

## Compilation and Execution

### Prerequisites
- Windows Environment
- [MinGW](https://sourceforge.net/projects/mingw/)

1. From the root directory of the project, run:
```bash
gcc binary_tree/binary_tree.c main.c -o main.exe
```

2. Execute the compiled file with:
```
main.exe
```

## How It Works

1. **Reading the File**: The program reads `equation.txt` line by line, storing each line in a vector of `linha` structures, which contain the string and the tabulation level.
2. **Building the Tree**: The binary tree is built recursively from the vector of lines, respecting the tabulation levels to define the hierarchy of nodes.
3. **Calculating the Equation**: The tree is traversed in post-order to calculate the value of the equation. Each node is evaluated based on the operator or operand it contains, and the result is stored in the root of the tree.
4. **Printing and Deallocating**: The tree is printed and dynamically deallocated after the calculation.

## Rules for Functioning

- The `equation.txt` file must be in the same directory as the executable.
- The file must contain the equation formatted with operators and operands in tabulation levels.
- Each tabulation level represents a level in the tree. For example, a line with one tab is a child of the previous line with no tabs.
- Each node must have appropriate children depending on the operators used (`+`, `-`, `*`, `/`, `min`, `max`).

## Operators

- **Binary Operators**: These operators require two operands (left and right children).
  - `+` (addition)
  - `-` (subtraction)
  - `*` (multiplication)
  - `/` (division)
  - `min` (minimum)
  - `max` (maximum)

- **Unary Operators**: These operators require only one operand (either left or right child).
  - `-` (negation, when only one child is present)

## Example of `equation.txt`

The equation: `max((8 + 4), min(9, 8))`, with output 12, should be written in `equation.txt` as follows:

```plaintext
max
    +
        8
        4
    min
        8
        9
```
> Note: Do not place a newline at the end. Each line in the file should represent a node in the tree; otherwise, it will generate inconsistent results.

