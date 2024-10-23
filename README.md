# C Expression Parser and Graph Plotter

## Overview
This project implements a calculator and graph plotter in C. The program receives a mathematical expression as input (in the form of a string), parses it into lexemes, converts it into Reverse Polish Notation (RPN), and then builds a graph by calculating the y-values for each x-point. The graph is drawn line by line within a 25x80 field.

## Features
- Parse mathematical expressions into lexemes.
- Convert expressions into Reverse Polish Notation for easier evaluation.
- Plot a graph of the expression, calculating y-values for x in the range of 0 to 4π.
- Graph is drawn within a 25x80 field using stars for points and dots for empty spaces.

## Files

- `Makefile` – Used to compile the project.
- `calc.c` – Contains the core conversion and calculation logic.
- `drawing.c` – Handles drawing the graph in the console.
- `graph.c` – Manages the graph plotting process.
- `lexemes.c` – Handles parsing the expression into lexemes.
- `stack.c` – Implements a stack data structure for handling RPN conversion and evaluation.

## Usage

1. **Build the project**: run `make` (unix) or `mingw32-make` (win) in the `src` folder.
2. **Run the program**: run the executable `build/graph` and provide a mathematical expression.

## Example
Given the input expression `sin(x)`, the program will output a graph showing the sine wave over the interval from 0 to 4π.

![sin(x) graph](msc/sin(x).jpg)

