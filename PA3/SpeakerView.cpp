#ifndef SpeakerView_H
#define SpeakerView_H
#include <iostream>
#include <string>
#include MonoStack_H

class SpeakerView{
  public:
    SpeakerView();
    ~SpeakerView();
    string Read(string InpF); // Reads the file, puts everything into a string
    arr[] ColumnMaker(string s); // Takes in the string from above and separates it by the columns
    int StackMaker(arr[] column); // Takes each column, and adds it to a stack, then returns the length (aka how many people see)

  private:

}
