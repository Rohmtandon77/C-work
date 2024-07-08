#include <iostream>
#include "Model.h"
#include <string>
using namespace std;

//Default constructor
Model::Model(){
}

//Default destructor
Model::~Model(){
}

string Model::translateSingleConsonant(char c){
  string s="";
  s+= c;
  s+='o';
  s+= c;
  return s;
}

string Model::translateSingleVowel(char v){
  string s="";
  s+=v;
  return s;
}
