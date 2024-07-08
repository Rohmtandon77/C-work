#include <iostream>
#include <string>
#include <fstream>
#include "Model.h"
#include "Translator.h"
#include "FileProcessor.h"
using namespace std;

int main(){
  FileProcessor f;
  f.processFile("original.txt","Translation.html");

  return 0;
}
