#ifndef MAX_HEAP_H
#define MAX_HEAP_H

template <typename T>
class MaxHeap{
  public:
    MaxHeap(int c);
    ~MaxHeap();
    void insert(T k);
    T getMax();
    void deleteMax();
    bool isEmpty(){ return m_size==0;}
  private:
    T* m_Heap;
    //how many things in heap
    int m_size;
    //what's max size of heap
    int m_cap;
    void fixHeap(int startIdx);
    int getLeftIdx(int i);
    int getRightIdx(int i);
    int getParentIdx(int i);

  };

template <typename T>
MaxHeap<T>::MaxHeap(int c){
  m_Heap = new T[c];
  m_size = 0;
  m_cap = c;
}

template <typename T>
MaxHeap<T>::~MaxHeap(){
  delete[] m_Heap;
}

template <typename T>
T MaxHeap<T>::getMax(){
  //TODO: check for empty heap
  return m_Heap[0];
}

template <typename T>
int MaxHeap<T>::getLeftIdx(int i){
  return (2*i)+1;
}

template <typename T>
int MaxHeap<T>::getRightIdx(int i){
  return (2*i)+2;
}

template <typename T>
int MaxHeap<T>::getParentIdx(int i){
  return (i-1)/2;
}

template <typename T>
void MaxHeap<T>::insert(T k){
  //TODO: make sure array isn't full
  m_Heap[m_size++] = k;
  int currIdx = m_size - 1;
  //make sure thing is still a heap
  while((currIdx!=0) && (m_Heap[currIdx] > m_Heap[getParentIdx(currIdx)])){
    T temp = m_Heap[currIdx];
    m_Heap[currIdx] = m_Heap[getParentIdx(currIdx)];
    m_Heap[getParentIdx(currIdx)] = temp;
    currIdx = getParentIdx(currIdx);

  }
}

template <typename T>
void MaxHeap<T>::deleteMax(){
  //TODO: check for empty heap
  if(m_size==1){
    --m_size;
    return;
  }else{
    m_Heap[0] = m_Heap[m_size-1];
    --m_size;
    fixHeap(0); //fix heap starting at root
  }
}

template <typename T>
void MaxHeap<T>::fixHeap(int startIdx){
  int left = getLeftIdx(startIdx);
  int right = getRightIdx(startIdx);
  int largest = startIdx;
  if(left < m_size && m_Heap[left] > m_Heap[startIdx]){
    largest = left;
  }
  if(right < m_size && m_Heap[right] > m_Heap[largest]){
    largest = right;
  }
  if(largest != startIdx){//have to swap with child
    T temp = m_Heap[startIdx];
    m_Heap[startIdx] = m_Heap[largest];
    m_Heap[largest] = temp;
    fixHeap(largest);
  }
}

#endif
