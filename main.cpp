//Author: Alex Richards
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector <string> getcolorlist(fstream &);
void displayVector(const vector <string> &);
vector <string> convertRGBVector(const vector <string> &);
string convertThreeRGB(const string &);
bool RGBcheck(const string &);
bool uniqueItem(const vector <string> &, const string &);
bool stringEquals(const string &, const string &);
vector <string> convertHtmlColors(const vector <string> &);

int main()
{
  string fileName;
  int fileLength;
  string svgCheck;
  vector <string> colorList;

  //get user input...
  do{
    cout << "Please enter the svg file to be opened:\n";
    getline(cin,fileName);
    fileLength = fileName.length();
    svgCheck = fileName.substr(fileLength-4,4);
  }while(svgCheck!=".svg");

  //try to open the file...
  fstream reader;
  reader.open(fileName, ios::in | ios::out );
  
  if( reader.is_open() ){
    colorList = getcolorlist(reader);
  }
  //display an error if it doesn't open, or display the file's contents if it does
  else{
    cout << "Could not open " << fileName << endl;
    return 0;
  }

  if(colorList.size()==0){
    cout << "No colors found in " << fileName << endl;
    return 0;
  }

  // displayVector(convertRGBVector(colorList));
  displayVector(colorList);
  
  /*
  vector <string> colorList;
  string color;
  do{
    cout << "What do you want to do (or quit to end)?\n";
    getline(cin, color);
    if(color != "quit"){
      colorList.push_back(color);
    }
  }while(color != "quit");
  displayVector(convertHtmlColors(colorList));
  */
  return 0;
}

vector <string> getcolorlist(fstream & reader){
  string line;
  string colorScan;
  size_t colorDefStart;
  size_t colorDefEnd;
  string colorName;
  vector <string> colorList;
    
    while( !reader.eof() ){
      getline(reader,line);
      //cout << line << endl;
      if(line.size() > 11){
        //detect colors after 'stroke'
        colorDefStart = line.find("stroke");
        colorScan = line.substr(colorDefStart+6);       //iteratively decreasing substring so that multiple colors can be detected in one line

        while(colorDefStart != string::npos && colorDefStart < line.length()) {
          if(colorScan[0]=='=' || colorScan[0]==':'){
            colorScan = colorScan.substr(2);
            colorDefEnd = min(colorScan.find("\""),colorScan.find (";"));
            colorName = colorScan.substr(0,colorDefEnd);
            //cout << colorName << endl;
            colorList.push_back(colorName);
          }
          else{
            break;
          }
        
          colorDefStart = colorScan.find("stroke");
          colorScan = colorScan.substr(colorDefStart+6);
        }
        //detect colors after 'fill'
        colorDefStart = line.find("fill");
        colorScan = line.substr(colorDefStart+4);       //iteratively decreasing substring so that multiple colors can be detected in one line

        while(colorDefStart != string::npos && colorDefStart < line.length()) {
          if(colorScan[0]=='=' || colorScan[0]==':'){
            colorScan = colorScan.substr(2);
            colorDefEnd = min(colorScan.find("\""),colorScan.find(";"));
            colorName = colorScan.substr(0,colorDefEnd);
            //cout << colorName << endl;
            colorList.push_back(colorName);
          }
          else{
            break;
          }

          colorDefStart = colorScan.find("fill");
          colorScan = colorScan.substr(colorDefStart+4);
        }
      }
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

vector <string> convertRGBVector(const vector <string> & colorList){
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
    vector <string> HtmlColorListConv;
    HtmlColorListConv = convertHtmlColors(HtmlColorList);
    for(int i=0; i < HtmlColorListConv.size(); i++){
      if(uniqueItem(RGBList,HtmlColorListConv[i])){
        RGBList.push_back(HtmlColorListConv[i]);
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