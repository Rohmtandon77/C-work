#include <iostream>
#include "Translator.h"
#include <string>
using namespace std;

//Default constructor
Translator::Translator(){
}

//Default destructor
Translator::~Translator(){
}

string Translator::translateEnglishWord(string w){
  string EndW="";
  for(int i=0; i<w.size();++i){
    char letter=w[i];
    switch(letter){
      case 'A':
      case 'E':
      case 'I':
      case 'O':
      case 'U':
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        EndW+=letter;
        break;
      default:
        EndW+=letter;
        EndW+='o';
        EndW+=letter;
        break;
    }
  }
  return EndW;
}

string Translator::translateEnglishSentence(string s){
  string EndS="";
  for(int i=0; i<s.size();++i){
    char letter=s[i];
    if(isalpha(letter)){
      switch(letter){
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
          EndS+=letter;
          break;
        default:
          EndS+=letter;
          EndS+='o';
          EndS+=letter;
          break;
      }
    }
    else{
      EndS+=letter;
    }
  }
  return EndS;
}

int Translator::main(){
  string r="Hello Rohm!";
  cout<<translateEnglishSentence(r);

  return 0;
}
