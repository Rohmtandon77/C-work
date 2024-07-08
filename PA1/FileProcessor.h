#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
using namespace std;

class FileProcessor{
public:
  FileProcessor();
  ~FileProcessor();
  void processFile(string InpF, string OutpF);
};

#endif
