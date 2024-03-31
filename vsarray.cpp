//
// Created by Arias Arevalo, Carlos on 5/6/20.
// Edited by Crites, Garrett  on 5/13/21
//

#include "character.h"
#include "vsarray.h"

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

VSArray::VSArray(size_t capacity, double increasePercentage) : _capacity(static_cast<int>(capacity)), _delta(increasePercentage) {
	_data = new Character*[capacity];
	for (size_t i = 0; i < _capacity; ++i) {
		_data[i] = nullptr;
	}
	_size = 0;
}
VSArray::VSArray(const VSArray& list){
	for (size_t i = 0; i < _size; ++i) {
		delete _data[i];
	}
	delete[] _data;
	_size = 0;

	for (size_t i = 0; i < list.Size(); ++i) {
        VSArray::Insert(list.Get(i), i);
	}
}
VSArray::~VSArray(){
    this->VSArray::Clear();
    delete[] _data;

}
VSArray& VSArray::operator=(const VSArray& rhs){

    for (size_t i = 0; i < _size; i++) {
        delete _data[i];
    }
    delete[] _data;

    _data = new Character*[rhs._capacity];

    for (size_t i = 0; i < rhs.Size(); ++i) {
        VSArray::Insert(rhs.Get(i), i);
    }

	return *this;
}

bool VSArray::Insert(Character* element, size_t position){

	if (position > _capacity) {
		return false;
	}
	else if (position > _size) {
		return false;
	}
	else if (position == _size && position == _capacity) {
		Resize();
		_data[position] = element;
		_size++;
		return true;
	}
	else {
		if (_size + 1 > _capacity) {
			Resize();
			_size++;
			for (size_t i = _size - 1; i > position; --i) {
				_data[i] = _data[i - 1];
			}
			_data[position] = element;
			return true;
		}
		else {
			++_size;
			for (size_t i = _size - 1; i > position; --i) {
				_data[i] = _data[i - 1];
			}
			_data[position] = element;
			return true;
		}
	}

	return false;
}
int VSArray::IndexOf(const Character* element)const{

	for (size_t i = 0; i < _size; ++i) {
		if (_data[i]->Equals(*element)) {
			return static_cast<int>(i);
		}
	}

	return -1;
}
Character* VSArray::Remove(size_t position){

	if (position >= _capacity) {
		return nullptr;
	}
	else if (position >= _size) {
		return nullptr;
	}
	else {
		Character* retVal = _data[position];
		for (size_t i = position; i < _size; ++i) {
			_data[i] = _data[i + 1];
		}
		--_size;
		return retVal;
	}
}
Character* VSArray::Get(size_t position)const{
	if (position >= _size) {
		return nullptr;
	}
	else {
		return _data[position];
	}
}
string VSArray::ToString()const{
	return "";
}
void VSArray::Clear(){

	for (size_t i = 0; i < _size; ++i) {
		delete _data[i];
	}

	_size = 0;
}

void VSArray::Resize() {

	size_t newCapacity = _capacity + (_capacity * _delta);
	auto data = new Character*[newCapacity];
	for (size_t i = 0; i < _size; ++i) {
		data[i] = _data[i];
	}
    delete[] _data;
    _data = data;
	_capacity = newCapacity;
}

size_t VSArray::GetCapacity() const {
	return _capacity;
}
