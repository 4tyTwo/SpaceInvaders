//#include "MyVectror.h"
//
//
//template <class T>
//MyVectror<T>::MyVectror()
//{
//}
//
//template <class T>
//void MyVectror<T>::grow(int grow_by) {
//  if (grow_by < 0)
//    grow_by = 1;
//  T* tmp = new T[count+grow_by];
//  for (int i = 0; i < count; i++)
//    tmp[i] = data[i];
//  data = tmp;
//  allocated += num;
//  delete tmp;
//}
//
//template <class T>
//MyVectror<T>::~MyVectror()
//{
//  delete data;
//}
