//Author: Alex Richards
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  string fileName;
  int fileLength;
  string svgCheck;

  //get user input...
  do {
    cout << "Please enter the svg file to be opened:\n";
    cin >> fileName;
    fileLength = fileName.length();
    svgCheck = fileName.substr(fileLength-4,4);
  }while(svgCheck!=".svg");

  //try to open the file...
  fstream reader;
  reader.open(fileName, ios::in | ios::out );
  
  if( reader.is_open() ){
    string line;
    string colorScan;
    size_t colorDefStart;
    size_t colorDefEnd;
    string colorName;
    
    while( !reader.eof() ){
      getline(reader,line);
      //detect colors after 'stroke'
      colorDefStart = line.find("stroke");
      colorScan = line.substr(colorDefStart+6);       //iteratively decreasing substring so that multiple colors can be detected in one line

      while(colorDefStart != string::npos && colorDefStart < line.length()) {
        if(colorScan[0]=='='){
          colorScan = colorScan.substr(2);
          colorDefEnd = colorScan.find("\"");
          colorName = colorScan.substr(0,colorDefEnd);
          cout << colorName << endl;
        }
        else if(colorScan[0]==':'){
          colorScan = colorScan.substr(2);
          colorDefEnd = colorScan.find(";");
          colorName = colorScan.substr(0,colorDefEnd);
          cout << colorName << endl;
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
        if(colorScan[0]=='='){
          colorScan = colorScan.substr(2);
          colorDefEnd = colorScan.find("\"");
          colorName = colorScan.substr(0,colorDefEnd);
          cout << colorName << endl;
        }
        else if(colorScan[0]==':'){
          colorScan = colorScan.substr(2);
          colorDefEnd = colorScan.find(";");
          colorName = colorScan.substr(0,colorDefEnd);
          cout << colorName << endl;
        }
        else{
          break;
        }

        colorDefStart = colorScan.find("fill");
        colorScan = colorScan.substr(colorDefStart+4);
      }
    }
    reader.close();
  }

  //display an error if it doesn't open, or display the file's contents if it does
  else{
    cout << "Could not open " << fileName << endl;
  }




  return 0;
}
