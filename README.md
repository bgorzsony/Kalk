# Kalk
Simple programmable calculator written in C++
Homework for Basics of Programming 2 class

It can interpret simple commands and evaluate mathematical expressions to perform various calculations.

## Usage

There are 5 registers that can be used: a,b,c,i,j

Each line can contain one command. The commands are the following:

| Command | Description |
| --- | --- |
| let \<register\> = \<expression\>| Sets the value of the register |
| goto \<line\>| Jumps to the given line |
| print \<expression\> | Prints the value of the expression to the standar output |
| input \<register\> | Reads a value from the standar input into the register |
| if (\<expression\>) \<command\> | Standard if statement, runs the command if the expression evaluates to true  |

Mathematical operators that can be used: +,-,*,/,%,^,sqrt(),abs(),log(),sin(),cos(),tan()

Logical operators that can be used: ==,!=,<,>,&&,||,<=,>=

## Examples

We could print out the first 10 Fibonacci numbers with this code:

```
let a = 0
let i = 0
let b = 1
let c = 1
let c = a + b
let a = b
let b = c
print b
let i = i+1
if (i < 10) goto 5
```

It produces the following output:

```
1
2
3
5
8
13
21
34
55
89
```

Print all of the divisor of a given number:

```
input a
print 1
let i = 2
if((a % i) == 0) print i
let i = i + 1
if(i < a) goto 4
print a
```

For the number 12 the output is the following:

```
a= 12
1
2
3
4
6
12
```









