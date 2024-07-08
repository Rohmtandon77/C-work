#include <iostream>
using namespace std;

void matrixRandom(int m, int n){
  int matrix[m][n];
  for (int i=0; i<m; i++){
    for (int j=0; j<n; j++){
      int x= rand();
      matrix[i][j]=x;
      cout<<to_string(matrix[i][j])<<" ";
    };
    cout<<endl;
  };
};

void matrixDiagonal( ){
  
}

int main() {
  matrixRandom(4, 3);

  return 0;
}
