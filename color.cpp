//Author: Alex Richards
#include "color.h"
#include <string>
#include <sstream>
#include <cmath>

using std::string;
using std::stringstream;
using std::hex;
using std::pow;
using std::round;

double convLinearRGB(int);
int invLinearRGB(double);
vector <int> convertRGBColor(const string &);
string createHex(vector <int>);

/* Member variables
    // Hexidecimal color value
    string RGB;
    // RGB color space values, 0-255
    int red;
    int green;
    int blue;
    // LMS color space values, 0-1
    double lng;
    double med;
    double srt;
*/

// Input a string like #F9a67B
// Generate rest of class from this
color::color(string RGBInput) : RGB{RGBInput}
{
  vector <int> RGBVector = convertRGBColor(RGB);

  red = RGBVector[0];
  green = RGBVector[1];
  blue = RGBVector[2];

  double linRed = convLinearRGB(red);
  double linGreen = convLinearRGB(green);
  double linBlue = convLinearRGB(blue);

  lng = 0.31399022 * linRed + 0.63951294 * linGreen + 0.04649755 * linBlue;
  med = 0.15537241 * linRed + 0.75789446 * linGreen + 0.08670142 * linBlue;
  srt = 0.01775239 * linRed + 0.10944209 * linGreen + 0.87256922 * linBlue;
}

// Input a vector of three LMS colorspace values
// Generate rest of class from this
color::color(vector <double> LMSVector)
{
  // if the vector is too small fill in absent values with zero
  if(LMSVector.size() < 3){
    for(int i=0; i<3-LMSVector.size(); i++){
      LMSVector.push_back(0.0);
    }
  }
  // if the vector has values outside of [0,1], put them back in bounds
  for(int i=0; i < 3; i++){
    if(LMSVector[i] > 1.001){
      LMSVector[i] = 1.0;
    }
    else if(LMSVector[i] < -0.001){
      LMSVector[i] = 0.0;
    }
  }
  lng = LMSVector[0];
  med = LMSVector[1];
  srt = LMSVector[2];
  double linRed = 5.47221206 * lng - 4.6419601 * med + 0.16963708 * srt;
  double linGreen = -1.1252419 * lng + 2.29317094 * med - 0.1678952 * srt;
  double linBlue = 0.02980165 * lng - 0.19318073 * med + 1.16364789 * srt;
  red = invLinearRGB(linRed);
  green = invLinearRGB(linGreen);
  blue = invLinearRGB(linBlue);
  RGB = createHex({red,green,blue});
}

string color::getRGB()const{
  return RGB;
}

// convert LMS colors to Protanopia color blindness
vector <double> color::simProt()const{
  vector <double> LMSVector = {0.0,0.0,0.0};
  LMSVector[0] = 1.05118294 * med - 0.05116099 * srt;
  LMSVector[1] = med;
  LMSVector[2] = srt;

  return LMSVector;
}

// convert LMS colors to Deuteranopia color blindness
vector <double> color::simDeut()const{
  vector <double> LMSVector = {0.0,0.0,0.0};
  LMSVector[0] = lng;
  LMSVector[1] = 0.9513092 * lng + 0.04866992 * srt;
  LMSVector[2] = srt;

  return LMSVector;
}

// convert LMS colors to Tritanopia color blindness
vector <double> color::simTrit()const{
  vector <double> LMSVector = {0.0,0.0,0.0};
  LMSVector[0] = lng;
  LMSVector[1] = med;
  LMSVector[2] = -0.86744736 * lng + 1.86727089 * med;

  return LMSVector;
}

vector <int> convertRGBColor(const string & RGB){
  vector <int> RGBVector = {0,0,0};
  stringstream ss;
  for(int i=0; i<3; i++){
    ss << hex << RGB.substr(2*i+1,2);
    ss >> RGBVector[i];
    stringstream().swap(ss);
  }
  return RGBVector;
}

string createHex(vector <int> RGBVector){
  string outHex = "#";
  string tempHex;
  stringstream ss;
  for(int i=0; i<3; i++){
    if(RGBVector[i] > 255){
      RGBVector[i] = 255;
    }
    if(RGBVector[i] < 0){
      RGBVector[i] = 0;
    }
    ss << hex << RGBVector[i];
    ss >> tempHex;
    if(tempHex.size() == 1){
      outHex += "0";
    }
    outHex += tempHex;
    stringstream().swap(ss);
  }
  return outHex;
}

// Convert 0-255 RGB to 0-1 linear RGB
double convLinearRGB(int inCol){
  double outCol;
  if(inCol <= 10){
    outCol = inCol / 3294.6;
  }
  else{
    outCol = pow(((inCol / 255.0)+0.055) / 1.055 , 2.4);
  }

  return outCol;
}

// 0-1 linear RGB to Convert 0-255 RGB
int invLinearRGB(double inCol){
  int outCol;
  if(inCol <= 0.0031308){
    outCol = round(inCol * 3294.6);
  }
  else{
    outCol = round(255*(1.055*pow(inCol,0.41666) - 0.055));
  }
  return outCol;
}

// squared euclidean distance between two colors
int color::distance(const color & secCol) const{
  return pow(red-secCol.red,2) + pow(green-secCol.green,2) + pow(blue-secCol.blue,2);
}

