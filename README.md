# !!!Replace with your unique project name!!!

## Description

Inputs a .svg file and outputs every color found in it.

### v0.2 Updates

*Coming soon*

### v1.0 Updates

*Coming soon*


## Developer

Alex Richards

## Example

To run the program, give the following commands:

```
g++ --std=c++11 *.cpp -o cvp
./cvp
```

Here is an example of the program running:

```
Please enter the svg file to be opened:
example.svg
#192538
[further colors follow]
```

## C++ Guide

### Variables and Data Types

There are currently six strings used. First is 'filename' which takes in the user's input for the file they want to open. Next is 'svgcheck' which is a substring of 'filename' consisting of the last four characters. This is used to detect whether the file ends in ".svg" so that the program only proceeds once a valid file name is entered. The last four are involved in the process of checking each line of the file to pick out the colors. The string 'line' stores each line as it is being read, 'subline' and 'colorscan' are each sublines of line which begin right before a color will and contain the rest of line. These two are used to locate the colors, which are stored in 'colorname' and outputted.

The second variable type is fstream which I use once for 'reader'. This is used to read the input file.

The third variable type is int, and is only used once for 'filel' which stores the length of the string 'filename' so that we can define 'svgcheck' to be the last four characters.

The final variable type is size_t which is used whenever I detect the position of a word or character in 'line'. First is 'position' which stores the position of "stroke" or "fill" which always proceed a color. Then is 'subposition' which detects when a color name has ended. I use size_t as it can have a null value that indicates there is no instance of a particular word.

### Console Input and Output

When run, the program prompts the user for a filename and will run when the user enters the name of a .svg file. If this file can't be found, the program will exist, but if it is not a .svg file the program will ask again. (TODO: make these two errors result in the same action from program)

The program will output to the console, line by line, each color found in the file. In the future it will ignore greyscale colors and colors like 'none'.

### Decisions

There are a number of decisions in the file, one which I have discussed above is whether the input file ends in .svg, as naturally I do not want the program to accept anything else. Another decision is that there are two formats for defining colors in svgs, i.e. `stroke="black"` and `stroke: black;`, and the program will detect which of those it is (or neither if 'stroke' or 'fill' is a part of a larger word) and extract the color accordingly (or not at all).

### Iteration

This program has two levels if iteration. The first is that it repeats the main program for each line in the .svg, and ends at the end of the document. The second is within each line, it finds the first instance of 'stroke' and gets the color from it, and then repeats until there are no more 'stroke's. It then repeats this with 'fill', allowing it to get every color from a given line.

### File Input and Output

This program accepts a .svg file as input, which it then scans line by line.

### Arrays/Vectors

*Coming in version 0.2*

### Functions

*Coming in version 0.2*

### Classes

*Coming in version 1.0*
