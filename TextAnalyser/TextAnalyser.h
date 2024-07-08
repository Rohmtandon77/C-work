#ifndef TEXT_ANALYZER_H  // header guard: prevents C++ header files from being included multiple times
#define TEXT_ANALYZER_H

#include <string>

class TextAnalyzer{
    public:
      TextAnalyzer();   // default constructor
      ~TextAnalyzer();  // destructor
      int countVowels(std::string str);
};

#endif
