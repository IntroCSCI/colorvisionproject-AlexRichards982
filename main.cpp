//Author: Alex Richards
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "color.h"
using namespace std;

vector <string> getcolorlist(string);
void displayVector(const vector <string> &);
void displayVector(const vector <color> &);
vector <string> createVector();
vector <string> convertRGBVector(const vector <string> &);
string convertThreeRGB(const string &);
bool RGBcheck(const string &);
bool uniqueItem(const vector <string> &, const string &);
bool stringEquals(const string &, const string &);
vector <string> convertHtmlColors(const vector <string> &);
vector <color> convToColorClass(const vector <string> &);
void colorBlindSim(const vector <color> &, char);
void colorDistance(const vector <color> &, const vector <color> & );

int main()
{
  string fileName;
  int fileLength;
  string svgCheck;
  vector <string> colorList;
  vector <string> colorListSlim;
  
  //get user input...
  cout << "This program will scan a set of colors to determine whether any color combinations pose a problem with colorblindness.\n";

  do{
    cout << "Please enter the svg file to be opened or enter 'color' to enter a list of html or hexadecimal colors:\n";
    getline(cin,fileName);
    fileLength = fileName.length();
    svgCheck = fileName.substr(fileLength-4,4);
  }while(svgCheck!=".svg" && fileName !="color" && fileName !="colors");

  //scan the chosen svg file for colors
  if(svgCheck==".svg"){
  colorList = getcolorlist(fileName);
    //if there are no colors in the file, end program
    if(colorList.size()==0){
      cout << "No colors found in " << fileName << endl;
      return 0;
    }

    cout << "These are the colors found in your file:\n";
    //trim down the list of colors to make formatting consistent
    //6-digit hexadecimal like #FFFFFF
    //as well as remove all duplicates
    colorListSlim = convertRGBVector(colorList);
    displayVector(colorListSlim);
  }

  //allow the user to input colors manually
  else if(stringEquals(fileName,"color") || stringEquals(fileName,"colors")){
    //same trimming as in last comment
    colorListSlim = convertRGBVector(createVector());
    displayVector(colorListSlim);
  }
  
  //convert list of colors to the color class which calculates
  //values which will be used in the next set of functions
  vector <color> RGBColor = convToColorClass(colorListSlim);

  //prompt the user to choose a form of colorblindness to convert
  //their colors to, and detect if any pair are too close together.
  //repeat until the user chooses to quit
  char blindType;
  do{
    cout << "\nWhat form of colorblindness do you want to examine?\n" << "Input the corresponding letter:\n";
    cout << "(p) Protanopia, lack of red-sensitive cones\n";
    cout << "(d) Deuteranopia, lack of green-sensitive cones\n";
    cout << "(t) Tritanopia, lack of blue-sensitive cones\n";
    cout << "(n) Normal vision, no colorblindness will be applied\n";
    cout << "(q) Quit, end program\n";
    do{
      if(!(cin >> blindType) && blindType != 'p' && blindType != 'd' && blindType != 't' && blindType != 'n' && blindType != 'q'){
        cout << "Invalid entry, please enter one of the above letters";
        cin.clear();
        cin.get();
      }
      else{
        blindType = (char) tolower(blindType);
      }
    }while(blindType != 'p' && blindType != 'd' && blindType != 't' && blindType != 'n' && blindType != 'q');

    //send the colors to simulate colorblindness and detect
    //problematic colors which appear too similarly
    if(blindType != 'q'){
      colorBlindSim(RGBColor,blindType);
    }
  }while(blindType != 'q');

  return 0;
}



vector <string> getcolorlist(string svgName){
  fstream reader;
  string line;
  string colorScan;
  size_t colorDefStart;
  size_t colorDefEnd;
  string colorName;
  vector <string> colorList = {};
    //try to open the file...
  reader.open(svgName, ios::in | ios::out );
  
  if( reader.is_open() ){
    while( !reader.eof() ){
      getline(reader,line);
      //cout << line << endl;
      if(line.size() > 11){
        //detect colors after 'stroke'
        colorDefStart = line.find("stroke");
        colorScan = line.substr(colorDefStart+6);       //iteratively decreasing substring so that multiple colors can be detected in one line

        while(colorDefStart != string::npos && colorDefStart < line.length()) {
          if(colorScan[0]=='='){
            colorScan = colorScan.substr(2);
            colorDefEnd = colorScan.find("\"");
            colorName = colorScan.substr(0,colorDefEnd);
            //cout << colorName << endl;
            colorList.push_back(colorName);
          }
          else if(colorScan[0]==':'){
            colorScan = colorScan.substr(1);
            colorDefEnd = colorScan.find(";");
            colorName = colorScan.substr(0,colorDefEnd);
            //cout << colorName << endl;
            colorList.push_back(colorName);
          }
        
          colorDefStart = colorScan.find("stroke");
          colorScan = colorScan.substr(colorDefStart+6);
        }
        //detect colors after 'fill'
        colorDefStart = line.find("fill");
        colorScan = line.substr(colorDefStart+4);       //iteratively decreasing substring so that multiple colors can be detected in one line

        while(colorDefStart != string::npos && colorDefStart < line.length()) {
          // cout << colorScan << endl;
          if(colorScan[0]=='='){
            colorScan = colorScan.substr(2);
            colorDefEnd = colorScan.find("\"");
            colorName = colorScan.substr(0,colorDefEnd);
            //cout << colorName << endl;
            colorList.push_back(colorName);
          }
          else if(colorScan[0]==':'){
            colorScan = colorScan.substr(1);
            colorDefEnd = colorScan.find(";");
            colorName = colorScan.substr(0,colorDefEnd);
            //cout << colorName << endl;
            colorList.push_back(colorName);
          }

          colorDefStart = colorScan.find("fill");
          colorScan = colorScan.substr(colorDefStart+4);
        }
      }
    }
  }
  //display an error if it doesn't open, or display the file's contents if it does
  else{
    cout << "Could not open " << svgName << endl;
  }  
  reader.close();
  return colorList;
}

void displayVector(const vector <string> & list){
  if(list.size()==0){
    cout << "Vector is empty" << endl;
    return;
  }
  for(int i=0; i < list.size(); i++){
    cout << list[i] << endl;
  }
  return;
}

void displayVector(const vector <color> & list){
  for(int i=0; i < list.size(); i++){
    cout << list[i].getRGB() << endl;
  }
}


vector <string> createVector(){
  vector <string> colorList;
  string color;
  cout << "Please enter an html color or rgb color as in \"orange\" or \"#FFA500\" (or \"quit\" to end)\n";
  do{
    getline(cin, color);
    if(color[0]=='\"'){
      cout << "Enter again without quotes please\n";
    }
    else if(!stringEquals(color, "quit")){
      colorList.push_back(color);
      cout << "Input accepted, please enter another color\n";
    }
  }while(!stringEquals(color, "quit"));
  return colorList;
}


vector <string> convertRGBVector(const vector <string> & colorList){
  // input a list of strings with 6 or 3 character RGB codes, html colors, or other and output a list of the 6 character RGB codes without repeats that correspond to those when applicable.
  vector <string> RGBList;
  vector <string> HtmlColorList;
  string newRGB;
  for(int i=0; i < colorList.size(); i++){
    // extract all hexadecimal rgb colors
    newRGB = "-1";
    if(RGBcheck(colorList[i])){
      if(colorList[i].size() == 7){
        newRGB = colorList[i];
      }
      else if(colorList[i].size() == 4){
        newRGB = convertThreeRGB(colorList[i]);
      }
    if(newRGB != "-1" && uniqueItem(RGBList,newRGB)){
      RGBList.push_back(newRGB);
    }
    }
    // extract all html colors, exclude calls for linear gradients and "none"
    else if(toupper(colorList[i][0]) != 'U' && toupper(colorList[i][0]) >='A' && toupper(colorList[i][0]) <='Y' && !stringEquals(colorList[i],"none")){
      HtmlColorList.push_back(colorList[i]);
    }
  }
  if(HtmlColorList.size()>0){
    vector <string> HtmlcolorListSlim;
    HtmlcolorListSlim = convertHtmlColors(HtmlColorList);
    for(int i=0; i < HtmlcolorListSlim.size(); i++){
      if(uniqueItem(RGBList,HtmlcolorListSlim[i])){
        RGBList.push_back(HtmlcolorListSlim[i]);
      }
    }
  }
  return RGBList;
}

string convertThreeRGB(const string & RGB){
  //take something like #f80 and output #ff8800
  string RGBout = "#";
  for(int i=1; i<=3; i++){
    RGBout.push_back(RGB[i]);
    RGBout.push_back(RGB[i]);
  }
  return RGBout;
}

bool RGBcheck(const string & RGB){
  // check if it is "#nnnnnn" or "#nnn"
  if(RGB[0] == '#' && (RGB.size() == 4 || RGB.size() == 7)){
    // check if each character is valid hexadecimal
    for(int i=1; i < RGB.size(); i++){
      if(!((RGB[i] >='0' && RGB[i] <='9') || (toupper(RGB[i]) >='A' && toupper(RGB[i]) <='F'))){
        return 0;
      }
    }
    return 1;
  }
  else{
    return 0;
  }
}

bool uniqueItem(const vector <string> & list, const string & item){
  // check if a string does not match any element of a vector
  if(list.size()>0){
    for(int i=0; i < list.size(); i++){
      if(stringEquals(list[i],item)){
        return 0;
      }
    }
  }
  return 1;
}

bool stringEquals(const string & a, const string & b){
  // See whether two strings are equal while ignoring capitalization
  int asize = a.size();
  if(asize == b.size()){
    for(int i=0; i < asize; i++){
      if(toupper(a[i]) != toupper(b[i])){
        return 0;
      }
    }
      return 1;
  }
  return 0;
}

vector <string> convertHtmlColors(const vector <string> & colorNameList){
  // take a list of strings, and for each html color named in the string output its corresponding RGB color. Requires Colorlist.csv.
  vector <string> colorRGB;
  fstream reader;
  string line;
  int colorNameEnd;
  string colorName;

  reader.open("Colorlist.csv", ios::in | ios::out );
  if( reader.is_open() ){
    while( !reader.eof() ){
      getline(reader,line);
      colorNameEnd = line.find(",");
      colorName = line.substr(0,colorNameEnd);
      for(int i=0; i < colorNameList.size(); i++){
        if(stringEquals(colorNameList[i],colorName)){
          colorRGB.push_back(line.substr(colorNameEnd+1,7));
          break;
        }
      }
    }
  }
  reader.close();
  return colorRGB;
}

vector <color> convToColorClass(const vector <string> & inColors){
  vector <color> RGBColor = {};
  for(int i=0; i < inColors.size(); i++){
    color newColor{inColors[i]};
    RGBColor.push_back(newColor);
  }
  return RGBColor;
}

void colorBlindSim(const vector <color> & inColors, char type){
  if(type != 'n'){
    vector <color> simColors = {};
    if(type == 'p'){
      cout << "These are the colors in your file with simulated Protonopia:" << endl;
      for(int i=0; i < inColors.size(); i++){
        color newColor{inColors[i].simProt()};
        simColors.push_back(newColor);
      }
    }
    else if(type == 'd'){
      cout << "These are the colors in your file with simulated Deuteranopia:" << endl;
      for(int i=0; i < inColors.size(); i++){
        color newColor{inColors[i].simDeut()};
        simColors.push_back(newColor);
      }
    }
    else if(type == 't'){
      cout << "These are the colors in your file with simulated Tritanopia:" << endl;
      for(int i=0; i < inColors.size(); i++){
        color newColor{inColors[i].simTrit()};
        simColors.push_back(newColor);
      }
    }
    displayVector(simColors);
    cout << "Pairs of colors from the file that are too similar with this form of colorblindness:" << endl;
    colorDistance(simColors,inColors);
  }
  else{
    cout << "Pairs of colors from the file that are too similar without considering colorblindness:" << endl;
    colorDistance(inColors,inColors);
  }
}

void colorDistance(const vector <color> & simColors, const vector <color> & inColors){
  int dist;
  int counter = 0;
  for(int i=0; i < simColors.size()-1; i++){
    for(int j=i+1; j < simColors.size(); j++){
      dist = simColors[i].distance(simColors[j]);
      if(dist <= 500){
        cout << "High similarity: " << inColors[i].getRGB();
        cout << ", " << inColors[j].getRGB() << endl;
        counter = 1;
      }
      else if(dist <= 5000){
        cout << "Moderate similarity: " << inColors[i].getRGB();
        cout << ", " << inColors[j].getRGB() << endl;
        counter = 1;
      }
    }
  }
  if(counter == 0){
    cout << "No problematic color combinations found!" << endl;
  }
}