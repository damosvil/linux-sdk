#ifndef ARRAY_H
#define ARRAY_H

#include "../n_object.h"
#include "collection_exception.h"
#include <stdlib.h>

template <class T>
class Collection : public NObject {

public:
	Collection();
	Collection(int size);
	Collection(const T t[]);
	Collection(const Collection<T> &c);
	virtual ~Collection();

	void Add(T o);
	void AddRange(T t[]);
	void AddRange(Collection<T> &c);
	void Remove(T o);
	void RemoveAt(int ix);
	void RemoveFirst();
	void RemoveLast();
	void DeleteAndRemoveAt(int ix);
	void DeleteAndRemoveFirst();
	void DeleteAndRemoveLast();
	void InsertAt(int ix, T o);
	void Compact();
	void Clear();
	void DeleteAndClear();
	int Count();
	bool Contains(T o);
	void QuickSort(int (*COMPARER)(const void *u, const void *v));
	int BinarySearchIx(T o, int (*COMPARER)(const void *u, const void *v));
	
	
	T &First();
	T &Last();
	T &operator [](int ix);
	
	//int Compare(static Collection<T> &c)
	
protected:
	void ensureCapacity(int capacity);

private:
	T *objects;
	int size;
	int numObjects;

};

template<class T>
Collection<T>::Collection()
{
	size = 1;
	objects = new T[size];
	numObjects = 0;	
}

template<class T>
Collection<T>::Collection(int size)
{
	this->size = size < 4 ? 4 : size;
	objects = new T[size];
	numObjects = 0;
}

template<class T>
Collection<T>::Collection(const T t[])
{
	int tsize = 0;
	T *tt = (T *)t;
	while (*tt++) tsize++;
	
	size = tsize > 0 ? tsize : 1;
	objects = new T[size];
	numObjects = tsize;
	
	tt = (T *)t;
	T *oo = objects;
	while (*tt) *oo++ = *tt++;
}

template<class T>
Collection<T>::Collection(const Collection<T> &c)
{
	size = c.size > 0 ? c.size : 1;
	objects = new T[size];
	numObjects = c.numObjects;
	
	for (int i=0; i<numObjects; i++) 
		objects[i] = c.objects[i];
}

template<class T>
Collection<T>::~Collection()
{
	delete objects;
}

template<class T>
void Collection<T>::ensureCapacity(int capacity)
{
	if (capacity < size) return;
	
	T *p = new T[2 * capacity];
	for (int i = 0; i < numObjects; i++) p[i] = objects[i];
	delete objects;
	objects = p;
	size = 2 * capacity;
}

template<class T>
void Collection<T>::Add(T o)
{
	ensureCapacity(numObjects + 1);
	objects[numObjects++] = o;
}

template<class T>
void Collection<T>::AddRange(T t[])
{
	T *tt = t;
	while (*tt) Add(*tt++);
}

template<class T>
void Collection<T>::AddRange(Collection<T> &c)
{
	size = numObjects + c.numObjects;
	if (size < 1) size = 1;
	T *q = new T[size + c.size];
	for (int i=0; i<numObjects; i++) q[i] = objects[i];
	for (int i=0; i<c.numObjects; i++) q[i + numObjects] = c.objects[i];
	delete objects;
	objects = q;
	numObjects += c.numObjects;
}

template<class T>
void Collection<T>::Remove(T o)
{
	for (int i=0; i<numObjects; i++) {
		if (objects[i] != o) continue;
		numObjects--;
		for (int j = 0; j < numObjects; j++) objects[j] = objects[j + 1];
		break;
	}
}

template<class T>
void Collection<T>::RemoveAt(int ix)
{
	if (ix < 0 || ix >= numObjects) throw new CollectionException((Text)"Index out of bounds", __FILE__, __LINE__, __func__);
	numObjects--;
	for (int i = ix; i<numObjects; i++) objects[i] = objects[i + 1];
}

template<class T>
void Collection<T>::RemoveFirst()
{
	RemoveAt(0);
}

template<class T>
void Collection<T>::RemoveLast()
{
	RemoveAt(numObjects - 1);
}

template<class T>
void Collection<T>::DeleteAndRemoveAt(int ix)
{
	if (ix < 0 || ix >= numObjects) throw new CollectionException("Index out of bounds", __FILE__, __LINE__, __func__);
	if (is_pointer<T>::value) delete objects[ix];
	RemoveAt(ix);
}

template<class T>
void Collection<T>::DeleteAndRemoveFirst()
{
	if (numObjects < 1) throw new CollectionException("Atempting to delete an item which doesn't exist", __FILE__, __LINE__, __func__);
	if (is_pointer<T>::value) delete objects[0];
	RemoveAt(0);
}

template<class T>
void Collection<T>::DeleteAndRemoveLast()
{
	if (numObjects < 1) throw new CollectionException("Atempting to delete an item which doesn't exist", __FILE__, __LINE__, __func__);
	if (is_pointer<T>::value) delete objects[numObjects - 1];
	RemoveAt(numObjects - 1);
}

template<class T>
void Collection<T>::InsertAt(int ix, T o)
{
	if (ix < 0 || ix > numObjects) throw new CollectionException("Index out of allowed bounds.", __FILE__, __LINE__, __func__);
	ensureCapacity[numObjects + 1];
	for (int i = ix; i<numObjects; i++) objects[i + 1] = objects[i];
	objects[ix] = o;
	numObjects++;
}

template<class T>
T &Collection<T>::First()
{
	if (numObjects < 1) throw new CollectionException("Atempting to get the first item in an empty collection", __FILE__, __LINE__, __func__);
	return objects[0];
}

template<class T>
T &Collection<T>::Last()
{
	if (numObjects < 1) throw new CollectionException("Atempting to get the last item in an empty collection", __FILE__, __LINE__, __func__);
	return objects[numObjects - 1];
}

template<class T>
void Collection<T>::Clear()
{
	delete objects;
	size = 1;
	objects = new T[size];
	numObjects = 0;
}

template<class T>
void Collection<T>::DeleteAndClear()
{
	if (is_pointer<T>::value) for (int i=0; i<numObjects; i++) delete objects[i];
	Clear();
}

template<class T>
void Collection<T>::Compact()
{
	if (size == numObjects || numObjects < 1) return;
	T *q = new T[numObjects];
	for (int i=0; i<numObjects; i++) q[i] = objects[i];
	delete objects;
	objects = q;
	size = numObjects;
}

template<class T>
int Collection<T>::Count()
{
	return numObjects;
}

template<class T>
bool Collection<T>::Contains(T o)
{
	for (int i=0; i<numObjects; i++) {
		if (o == objects[i]) return true;
	}
	
	return false;
}

template<class T>
void Collection<T>::QuickSort(int (*COMPARER)(const void *u, const void *v))
{
	qsort(objects, numObjects, sizeof(objects[0]), COMPARER);
}

template<class T>
int Collection<T>::BinarySearchIx(T o, int (*COMPARER)(const void *u, const void *v))
{
	void *p = bsearch(&o, objects, numObjects, sizeof(objects[0]), COMPARER);
	if (p == NULL) return -1;
	return ((unsigned long)p - (unsigned long)objects) / sizeof(objects[0]);
}

template<class T>
T &Collection<T>::operator[](int ix)
{
	if (ix < 0 || ix > numObjects) new CollectionException("Index out of bounds", __FILE__, __LINE__, __func__);
	return objects[ix];
}


#endif // ARRAY_H
