#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
using namespace std;

class Translator{
public:
  Translator();
  ~Translator();
  string translateEnglishWord(string x);
  string translateEnglishSentence(string y);
  int main();
};

#endif
