#pragma once
template <class T> class MyVector
{
public:
  MyVector() {
    count = allocated = 0;
    data = NULL;
  }

  MyVector(MyVector<T>& vect) {
    for (auto i = 0; i < vect.size(); i++)
      add(vect[i]);
  }

  MyVector(int size) {
    count = 0;
    data = new T [size];
    allocated = size;
  }

  void add(const T item) {
    if (count >= allocated)
      grow((count/2)+1);
    data[count++] = item;
  }

  T& get(int index) {
    index = (index>= 0 && index<count)? index : 0;
    return data[index];
  }

  void set(int index, T* item) {
    data[index] = item;
  }
  
  T& operator[](int index) {
    return data[index];
  }
  
  void pop() {
    --count;
    if (allocated > count * 1.5 && count > 2)
      memoryClear();
  }
  
  void memoryClear() {
    T* tmp = new T[count+2];
    for (auto i = 0; i < count; i++)
      tmp[i] = data[i];
    data = tmp;
    delete [] tmp;
    allocated = count+2;
}

  void erase(int index) {
    if (index < 0 || index > count - 1)
      return;
    for (auto i = index; i < count - 1; i++) {
      data[i] = data[i + 1];
    }
    --count;
    if (allocated > count * 1.5 && count > 2)
      memoryClear();
  }

  inline  int size() { return count; };

  void clear() {
    count = 0;
  }

  ~MyVector() {
  }
private:
  void grow(int grow_by=8){
    if (grow_by < 0)
      grow_by = 1;
    T* tmp = new T[count + grow_by];
    for (auto i = 0; i < count; i++)
      tmp[i] = data[i];
    data = tmp;
    allocated += grow_by;
  }

  T* data;
  int count,allocated;
};