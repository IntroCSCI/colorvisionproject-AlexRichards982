# Problematic color detector for .svg

## Description

Inputs a .svg file and outputs every color found in it.

### v0.2 Updates

Now outputs every unique color in the file in 6 digit hexadecimal RGB.

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
#ffffff
#f3e533
#ff7f00
#bf0000
#000000
```

## C++ Guide

### Variables and Data Types

There are currently five strings used. First is `fileName` which takes in the user's input for the file they want to open. Next is `svgCheck` which is a substring of `fileName` consisting of the last four characters. This is used to detect whether the file ends in ".svg" so that the program only proceeds once a valid file name is entered. The last three are involved in the process of checking each line of the file to pick out the colors. The string `line` stores each line as it is being read, `colorScan` is a subline of line which begins right before a color will and contain the rest of line. This is used to locate the colors, which are stored in `colorName` and outputted.

The second variable type is fstream which I use once for `reader`. This is used to read the input file.

The third variable type is int, and is only used once for `fileLength` which stores the length of the string `fileName` so that we can define `svgCheck` to be the last four characters.

The final variable type is size_t which is used whenever I detect the position of a word or character in `line`. First is `colorDefStart` which stores the position of "stroke" or "fill" which always proceed a color. Finally is `colorDefEnd` which detects when a color name has ended. I use size_t as it can have a null value that indicates there is no instance of a particular word.

### Console Input and Output

When run, the program prompts the user for a fileName and will run when the user enters the name of a .svg file. If this file can't be found, the program will exist, but if it is not a .svg file the program will ask again. (TODO: make these two errors result in the same action from program)

The program will output to the console, line by line, each color found in the file. In the future it will ignore greyscale colors and colors like `none`.

### Decisions

There are a number of decisions in the file, one which I have discussed above is whether the input file ends in .svg, as naturally I do not want the program to accept anything else. Another decision is in `getcolorlist` where there are two formats for defining colors in svgs, i.e. `stroke="black"` and `stroke:black;`, and the program will detect which of those it is (or neither if `stroke` or `fill` is a part of a larger word) and extract the color accordingly (or not at all).

### Iteration

This program frequently uses iteration. One way is that it repeats the main program for each line in the .svg, and ends at the end of the document. Another is in `getcolorlist` where within each line of the .svg, it finds the first instance of `stroke` and gets the color from it, and then repeats until there are no more `stroke`s. It then repeats this with `fill`, allowing it to get every color from a given line. When dealing with vectors, there is usually a for loop which will have the program repeat a process for each element of the vector.

### File Input and Output

This program accepts a .svg file as input, which it then scans line by line. In addition, the html color conversion function uses a .csv where each line is an html color and then its rgb value like `DarkRed,#8B0000` as its reference for conversion.

### Arrays/Vectors

This program takes advantage of vectors as a way to store lists of strings. To name a couple of examples, first is `colorList` in `main`, which stores the raw output from the .svg file. This is the input for `convertRGBVector` which takes every unique RGB color, in the correct format, and adds them to a new vector of strings and outputs that. A number of the other functions will take a vector of strings as input, as seen in the next section.

### Functions

This program uses many functions. First is `getcolorlist` which inputs as a pass by reference an fstream reader, which it uses to extract the colors from the .svg. Currently it ignores colors used in gradients, but may parse the beginning and ending colors of them in the future.

Second is `displayVector` which inputs a vector of strings as a constant pass by reference and outputs each of those strings to the console, or a message if there are none. This is a void function because it does not output a variable.

Third is `createVector` which is not called by default (there is a commented out call for it at the end of `main`), and is a tool for testing. It allows you to input strings one at a time to make a vector of strings, which is the output of the function. The main use of this is to test the Html color converter as I could not find an .svg file with those named colors in it.

Fourth relies on other functions, so fifth is `convertThreeRGB` which inputs a 3 digit rgb code like `#0af` as a constant pass by references and outputs a string like `#00AAFF`.

Sixth is `RGBcheck` which simply checks if a string is 4 or 7 characters, starts with #, and consists of valid hexadecimal digits for the remaining characters, outputting a boolean that says whether this is the case. This uses constant pass by references for the string because it only outputs a boolean.

Seventh is `uniqueItem` which determines if a string is identical to one in a string of vectors, outputting a boolean corresponding to this. For the same reason as above it uses constant pass by references for both variables.

Eighth is `stringEquals` which inputs two strings and case insensitively determines if they are equal, outputting a boolean with this truth value. Again as constant pass by references for the same reason. This is used by the above function.

Ninth is `convertHtmlColors` which inputs a vector of strings as a constant pass by reference, and outputs a new vector. It does so by referencing the attached `Colorlist.csv` which is specially made to have an html color and then its rgb value like `Indigo,#4B0082`. The program then goes through the .csv line by line and sees if the color name matches any of the strings in the attached vector (using `stringEquals`) and then adds the corresponding RGB value to a vector of strings which is the function's eventual output.

Finally is `convertRGBVector` which is designed to take the raw data from `getcolorlist` and output the unique set of RGB colors found. It uses the above functions to convert everything to a consistent format of 6-digit rgb, while having no duplicates (although there is currently an inconsistency of values that started in the desired format can have non-capitalized letters).

There are actually no pass by values used in this program, and it instead uses constant pass by references for everything but an fstream which is a pass by reference that changes in `getcolorlist`. This is because most of the functions are taking as inputs vectors of strings or an fstream, which are large and therefore shouldn't be duplicated in memory. when they do take a different value, it is a string and in one case, the function is boolean and thus has no reason to edit the variable, or in the case of `convertThreeRGB` it just makes more sense to create an entirely new string while keeping the original as a reference.

### Classes

*Coming in version 1.0*
