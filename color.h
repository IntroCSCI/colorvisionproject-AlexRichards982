//HEADER file (interface) for email class
#ifndef COLOR_H //Pre-processor directives
#define COLOR_H
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class color{
  private:
    // Hexidecimal color value
    string RGB;
    // RGB color space values, 0-255
    int red;
    int green;
    int blue;
    // LMS color space values
    double lng;
    double med;
    double srt;

  public:
    //constructors
    color(string);
    color(vector <double>);
    //member functions
    string getRGB()const;
    vector <double> simProt()const;
    vector <double> simDeut()const;
    vector <double> simTrit()const;
    int distance(const color &) const;

};

#endif