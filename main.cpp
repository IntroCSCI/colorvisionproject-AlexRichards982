//Author: PUT YOUR NAME HERE
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  string filename;
  fstream reader;
  string line = "";
  int l;
  string svgcheck;
  size_t position;
  //get user input...

  do {
    cout << "Please enter the svg file to be opened:\n";
    cin >> filename;
    l = filename.length();
    svgcheck = filename.substr(l-4,4);
    cout << svgcheck << endl ;
  }while(svgcheck!=".svg");

  //try to open the file...
  reader.open(filename, ios::in | ios::out );
  
  if( reader.is_open() ){
    while( !reader.eof() ){
      getline(reader,line);
      cout << line << endl;
      

    }
    reader.close();
  }

  //display an error if it doesn't open, or display the file's contents if it does
  else{
    cout << "Could not open " << filename << endl;
  }




  return 0;
}
