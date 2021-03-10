//Author: PUT YOUR NAME HERE
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  string filename;
  fstream reader;
  string line;
  string subline;
  int filel;
  string svgcheck;
  size_t position;
  size_t subposition;
  string colorscan;
  string colorname;
  //get user input...

  do {
    cout << "Please enter the svg file to be opened:\n";
    cin >> filename;
    filel = filename.length();
    svgcheck = filename.substr(filel-4,4);
  }while(svgcheck!=".svg");

  //try to open the file...
  reader.open(filename, ios::in | ios::out );
  
  if( reader.is_open() ){
    while( !reader.eof() ){
      getline(reader,line);
      //detect colors after 'stroke'
      position = line.find("stroke");
      subline = line.substr(position+6); //iteratively decreasing substring so that multiple colors can be detected in one line
      while(position != string::npos && position < line.length()) {
        if(subline[0]=='='){
          colorscan = subline.substr(2);
          subposition = colorscan.find("\"");
          colorname = colorscan.substr(0,subposition);
          cout << colorname << endl;
        }
        else if(subline[0]==':'){
          colorscan = subline.substr(2);
          subposition = colorscan.find(";");
          colorname = colorscan.substr(0,subposition);
          cout << colorname << endl;
        }
        else{
          break;
        }
        position = subline.find("stroke");
        subline = subline.substr(position+6);
      }
      //detect colors after 'fill'
      position = line.find("fill");
      subline = line.substr(position+4); //iteratively decreasing substring so that multiple colors can be detected in one line
      while(position != string::npos && position < line.length()) {
        if(subline[0]=='='){
          colorscan = subline.substr(2);
          subposition = colorscan.find("\"");
          colorname = colorscan.substr(0,subposition);
          cout << colorname << endl;
        }
        else if(subline[0]==':'){
          colorscan = subline.substr(2);
          subposition = colorscan.find(";");
          colorname = colorscan.substr(0,subposition);
          cout << colorname << endl;
        }
        else{
          break;
        }
        position = subline.find("fill");
        subline = subline.substr(position+4);
      }
    }
    reader.close();
  }

  //display an error if it doesn't open, or display the file's contents if it does
  else{
    cout << "Could not open " << filename << endl;
  }




  return 0;
}
