#include <iostream>
#include <string>
#include "FileProcessor.h"
#include "Translator.h"
#include "Model.h"
using namespace std;
#include <fstream>

//default constructor
FileProcessor::FileProcessor(){
}

//default destructor
FileProcessor::~FileProcessor(){
}


//processFile
void FileProcessor::processFile(string InpF, string OutpF){
  //reading the text file first

  fstream OrigFile;

  string ss;


  //translating the text file to Robber language
  Translator t;

  //putting the translation into the html file
  ofstream TransFile;
  TransFile.open(OutpF);
  TransFile<<"<!DOCTYPE html>"<<endl;
  TransFile<<"<html>"<<endl;
  TransFile<<"<head>"<<endl;
  string title= "Robber Language Translation";
  TransFile<<"<title>"<<title<<"</title>"<<endl;
  TransFile<<"</head>"<<endl;
  TransFile<<"<body>"<<endl;
  TransFile<<"<p>";

  OrigFile.open(InpF);
  if(OrigFile.is_open()){
    while(getline(OrigFile, ss)){
      TransFile<<"<b>"<<ss<<"</b>"<<"<br />";
    }
    OrigFile.close();
  }

  TransFile<<"<br />"<<endl;

  OrigFile.open(InpF);
  if(OrigFile.is_open()){
    while(getline(OrigFile, ss)){
      string Tr=t.translateEnglishSentence(ss);
      TransFile<<"<i>"<<Tr<<"</i>"<<"<br />";;
    }
    OrigFile.close();
  }
  TransFile<<"</p>"<<endl;
  TransFile<<"</body>"<<endl;
  TransFile<<"<html>";
  TransFile.close();

}
