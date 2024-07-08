#ifndef MODEL_H
#define MODEL_H

#include <string>
using namespace std;

class Model{
public:
  Model();
  ~Model();
  string translateSingleConsonant(char c);
  string translateSingleVowel(char c);
};

#endif
