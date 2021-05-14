# Problematic color detector for .svg

## Description

Inputs a .svg file and outputs every color found in it.

### v0.2 Updates

Now outputs every unique color in the file in 6 digit hexadecimal RGB.

### v1.0 Updates

"color" class added, now maps the colors inputted manually or from the svg file to any of the three main forms of colorblindness (each of the ones missing one of the three rod types). Then calculates all squared distances between these and says which would too close to a colorblind person.

Descriptions of the new class's functions are provided in the section on classes, and a description of how to use the program is next.


## Developer

Alex Richards

## Example

To run the program, give the following commands:

```
g++ --std=c++11 *.cpp -o cvp
./cvp
```

Here is an example of the program running while scanning for colors in an svg file:

```
g++ -std=c++11 *.cpp -o cvp; ./cvp
This program will scan a set of colors to determine whether any color combinations pose a problem with colorblindness.
Please enter the svg file to be opened or enter 'color' to enter a list of html or hexadecimal colors:
example.svg
These are the colors found in your file:
#192538
#ffffff
#f3e533
#ff7f00
#bf0000
#000000

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
t
These are the colors in your file with simulated Tritanopia:
#142828
#ffffff
#fed8d8
#ff7777
#bf0000
#000000
Pairs of colors from the file that are too similar with this form of colorblindness:
Moderate similarity: #192538, #000000
Moderate similarity: #ffffff, #f3e533

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
p
These are the colors in your file with simulated Protonopia:
#232338
#ffffff
#e7e733
#9f9f00
#545400
#000000
Pairs of colors from the file that are too similar with this form of colorblindness:
No problematic color combinations found!

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
n
Pairs of colors from the file that are too similar without considering colorblindness:
No problematic color combinations found!

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
q
```

Here is another example, manually entering colors:

```
g++ -std=c++11 *.cpp -o cvp; ./cvp
This program will scan a set of colors to determine whether any color combinations pose a problem with colorblindness.
Please enter the svg file to be opened or enter 'color' to enter a list of html or hexadecimal colors:
color
Please enter an html color or rgb color as in "orange" or "#FFA500" (or "quit" to end)
"orange"
Enter again without quotes please
green
Input accepted, please enter another color
red
Input accepted, please enter another color
blue
Input accepted, please enter another color
darkorange
Input accepted, please enter another color
#40ffEa
Input accepted, please enter another color
white
Input accepted, please enter another color
quit
#40ffEa
#FF0000
#FF8C00
#008000
#0000FF
#FFFFFF

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
p
These are the colors in your file with simulated Protonopia:
#ececeb
#737300
#a7a700
#757503
#0000ff
#ffffff
Pairs of colors from the file that are too similar with this form of colorblindness:
Moderate similarity: #40ffEa, #FFFFFF
High similarity: #FF0000, #008000

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
d
These are the colors in your file with simulated Deuteranopia:
#d8d8ed
#9c9c00
#bdbd00
#6a6a12
#0000ff
#ffffff
Pairs of colors from the file that are too similar with this form of colorblindness:
Moderate similarity: #40ffEa, #FFFFFF
Moderate similarity: #FF0000, #FF8C00

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
t
These are the colors in your file with simulated Tritanopia:
#4dfcfc
#ff0000
#ff8484
#2e7878
#006363
#ffffff
Pairs of colors from the file that are too similar with this form of colorblindness:
No problematic color combinations found!

What form of colorblindness do you want to examine?
Input the corresponding letter:
(p) Protanopia, lack of red-sensitive cones
(d) Deuteranopia, lack of green-sensitive cones
(t) Tritanopia, lack of blue-sensitive cones
(n) Normal vision, no colorblindness will be applied
(q) Quit, end program
q
```

### Running the program

First, the user will be prompted to name an svg file or to input color. If the former, the program will find that svg file and get all colors found in it and display those to the console.

If the user chose to input color, the program will prompt them to individually input hexadecimal or html colors. When the user inputs quit, the program displays all unique colors from the ones inputted in 6 digit hexadecimal.

After this, the program asks "What form of colorblindness do you want to examine?" To which the user can choose from Protanopia, Deuteranopia, Tritanopia, no colorblindness, or to stop running the program by inputting one of the letters shown by the program. 

Once one is chosen, the program will simulate the chosen colorblindness and respectively output how the colors appear to someone with that colorblindness so that they can easily be compared. It will then say which pairs of colors end up too close to each other, with a rating of high or moderate similarity. If no colorblindness mode was chosen the program simply does the calculation of distance. 

In either case, the program then loops back to the prompt of type of colorblindness again and will do so until the quit option has been chosen.


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

A second example of a decision is when the user inputs a type of colorblindness to examine. The program will first not move on until a valid character is inputted, and second if it is 'q' for quit, it will end the program. Third, if it is one of the other four, it will pass this on to `colorBlindSim` which then decides which form of colorblindness to simulate or none at all based on that character.

### Iteration

This program frequently uses iteration. One example is that it repeats the main program for each line in the .svg, and ends at the end of the document. 

Another is in `getcolorlist` where within each line of the .svg, it finds the first instance of `stroke` and gets the color from it, and then repeats until there are no more `stroke`s. It then repeats this with `fill`, allowing it to get every color from a given line. When dealing with vectors, there is usually a for loop which will have the program repeat a process for each element of the vector.

A third example is `colorDistance`, which inputs a list of colors and needs to compare each pair of them. This is done with a for loop inside of another for loop so the function can compare color 0 to every other color, then color 1 to every other color but itself and color 0, and so on until each pair of different colors have been compared.

### File Input and Output

This program accepts a .svg file as input, which it then scans line by line. In addition, the html color conversion function uses a .csv where each line is an html color and then its rgb value like `DarkRed,#8B0000` as its reference for conversion.

### Arrays/Vectors

This program takes advantage of vectors as a way to store lists of strings. To name a couple of examples, first is `colorList` in `main`, which stores the raw output from the .svg file. This is the input for `convertRGBVector` which takes every unique RGB color, in the correct format, and adds them to a new vector of strings and outputs that. A number of the other functions will take a vector of strings as input, as seen in the next section.

The program also uses vectors to store lists of its unique class, color. This lets it easily manage multiple colors and lets the program use for loops whenever it needs to do something with each color.

### Functions

This program takes advantage of many functions to either consolidate functionality which will be used multiple times, preventing repeat code, or to make `main` cleaner by offloading long chunks of code to a different function. I will list each function, starting with its prototype(s) and then describing its use within this program.

`vector <string> getcolorlist(string);` Inputs the name of an svg file and then extracts the colors from it using an fstream. It unfortunately only parses strokes and fills, ignoring colors used in gradients or similar functions. The colors found are outputted as a vector of strings, including junk like `none` which is ignored in a later function.


`void displayVector (const vector <string> &);`
`void displayVector (const vector <color> &);`
Outputs every string in a vector of strings or every RGB value in a vector of colors to the console; used whenever the function displays a list of color values. 

It takes its input vector as a constant pass-by reference because it has no need to edit it, and this saves on memory (I will omit this detail in the future as it is for the same reason every time). 

It is a void function as does not need to output a variable, and it is also an overloaded function, with an alternate definition for vectors of colors, using a member function of that class to get the RGB value.


`vector <string> createVector();` 
The manual method of giving the program colors. It allows you to input strings one at a time to make a vector of strings, which is the output of the function. This allows the function to take your inputs of html or rgb colors to detect if there are any problematic pairs of colors.


`string convertThreeRGB(const string &);`
Takes an input of a string that is a 3 digit rgb codes like `#0af`. It converts this to a six digit one like `#00AAFF` which is outputted as a string. 

`bool RGBcheck(const string &);`
Checks if an inputted string is a valid hexadecimal code like `#a80` or `#FFA500`. Outputs a boolean to that effect.

`bool uniqueItem(const vector <string> &, const string &);` Determines if a string is identical to one already in a string of vectors, outputting a boolean corresponding to this.

`bool stringEquals(const string &, const string &);` A very useful function which can be found throughout the program that case insensitively decides if two strings are the same. For example, this allows the previous function to see `#00AAFF` and `#00aaff` as the same string. If they are the same in this way the function outputs true, if not then false.



`vector <string> convertHtmlColors(const vector <string> &);` Inputs a vector of strings, and for any strings that match an html color, it outputs a new vector with the rgb values corresponding to those colors. 

It does so by referencing the attached `Colorlist.csv` which is specially made to have an html color and then its rgb value like `Indigo,#4B0082`. The program then goes through the .csv line by line and sees if the color name matches any of the strings in the attached vector (using `stringEquals`) and then if a match is found, it adds that color's RGB value to a vector of strings which is the function's eventual output.


`vector <string> convertRGBVector(const vector <string> &);` This program takes a vector of strings, and for every string that is a 3 or 6 digit rgb or html color, the corresponding 6 digit rgb color is added to the output vector and any duplicates ignored.

This function is designed to take the raw data from `getcolorlist` and `createVector` to output the unique set of RGB colors found. It uses the above functions to convert everything to a consistent format of 6-digit rgb, while having no duplicate colors.

`vector <color> convToColorClass(const vector <string> &);` This function takes the list of 6-digit rgb values from the previous function and makes a vector of colors from them. This uses the first constructor of the color class which calculates the other values from the rgb value inputted, and the program will need these other values.

`void colorBlindSim(const vector <color> &, char);` Takes a type of colorblindness (or none) as a character and a vector of colors as input. The function then creates a new vector of colors which are mapped to how they are perceived with that kind of colorblindness, and displays those colors to the console (that part is skipped if no colorblindness was chosen). It then gives that vector and its input vector to the following program.

`void colorDistance(const vector <color> &, const vector <color> & );` This program takes a list of colorblind-adjusted colors and calculates the squared distance between every pair, treating the three 0-255 color values as dimensions in euclidean space. 

If any of these distances are less than 5000 the program takes the corresponding original colors from its second input and outputs to the console that these colors ended up appearing too similar. It says they are highly similar if the distance is under 500 and moderately similar if it is from 501 to 5000 (These numbers are a bit arbitrary but I tried to overestimate so that false positives are included rather than false negatives excluded).



### Classes

This program includes a new class called color. I will explain the member variables as well as the member functions. The member variables are held private as they should not be edited once created, only viewed for specific calculations necessary for the program. In fact, the only one that can be accessed directly is the hexadecimal color value. This has three different views of the same color, which each need to be used in different ways by the program.

The more mathematical functionality of this class is based the following research webpage, and reading it is recommended for understanding how this class functions.

https://ixora.io/projects/colorblindness/color-blindness-simulation-research/


**Member Variables (Private)**

`string RGB;` This is a 6-digit hexadecimal like `#f3e533`

`int red;` `int green;` `int blue;` These are integers that range from 0 to 255 and correspond to the same color as the hexadecimal number.


`double lng;` `double med;` `double srt;` These are LMS color space values which are real numbers from 0 to 1. They more accurately represent how light is perceived by cone cells, and are therefore needed to convert colors to how they would be seen by those with colorblindness.

https://en.wikipedia.org/wiki/LMS_color_space


**Constructors (Public)**

`color(string);` This function constructs an object of the color class from an input string. It sets the input string as `RGB` and then derives the other values from this color, using the below stack exchange answer to get `red`, `green`, and `blue` from the hexadecimal with the function `convertRGBColor`. 

Then, it uses the research webpage for the mathematical conversion from that to the LMS values. It first uses the function `convLinearRGB` to convert each color to linear RGB, and then has a hardcoded matrix mutiplication to map those three values to `lng`, `med`, and `srt`.

https://stackoverflow.com/questions/20034297/decimal-to-hex-conversion-c-built-in-function

`color(vector <double>);` This constructor takes in a vector of the three LMS values and constructs an object of this class from there, using similar conversions outlined in the same places mentioned above. 

It first checks whether the input vector is appropriate in size, and whether the numbers are within the appropriate range of 0 to 1. If either is untrue, it adds values of zero to the vector or sets the incorrect number to the closest bound. 

Then it largely does the inverse of what the first constructor did, multiplying by the inverse matrix to get the linear RGB and then `invLinearRGB` to get the integer `red`, `green`, and `blue` values from them. 

Finally it inputs those three values to `createHex` to get the hexadecimal code, which it sets as `RGB`.



**Member Functions (Public)**

`string getRGB()const;` Outputs the value `RGB` from the input color.

`vector <double> simProt()const` Takes `lng`, `med`, `srt` and preforms a matrix multiplication to map these to how the color is percieved by someone with Protanopia, or a lack of L cones, those most sensitive to red light. The three new values are outputted as a vector, which the second constructor can take in to get the corresponding RGB values.

`vector <double> simDeut()const;` Exactly the same as above but for Deuteranopia, which is a lack of M cones, those most sensitive to green light.

`vector <double> simTrit()const;` Is again the same but for Tritanopia, which is a lack of S cones, those most sensitive to blue light.

`int distance(const color &) const;` Inputs two colors, one outside of parentheses one inside, and gets the squared distance between them, calculating `(red1-red2)^2 + (green1-green2)^2 + (blue1-blue2)^2`. This treats the three colors as coordinates in three dimensional space and each color as a point, and finds the square of the distance between those points (so as to avoid a square root unnecessary for my purposes). This seemed the best option for me of the ones described by the following wikipedia page.

https://en.wikipedia.org/wiki/Color_difference