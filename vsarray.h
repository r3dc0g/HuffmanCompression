#include "list.h"

#ifndef ADT_LIST_FULL_VSARRAY_H
#define ADT_LIST_FULL_VSARRAY_H


#include "character.h"
#include "list.h"

#include <string>
using std::string;

class VSArray : public List{
	Character** _data;
	size_t _capacity;
	double _delta;

	void Resize();
public:
	VSArray(size_t capacity, double increasePercentage = 0.5);
	virtual ~VSArray();
    VSArray(const VSArray&);
    VSArray& operator=(const VSArray&);
	virtual bool Insert(Character* element, size_t position);
	virtual int IndexOf(const Character* element)const;
	virtual Character* Remove(size_t position);
	virtual Character* Get(size_t position)const;
	virtual string ToString()const;
	virtual void Clear();
	size_t GetCapacity()const;

};


#endif //ADT_LIST_FULL_VSARRAY_H
