/*
 * Title:		ADT List class Declaration
 * Purpose:		An abstract class implementation of the ADT List
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */
#ifndef LIST_H
#define LIST_H

#include "character.h"

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

class List : public Character{
protected:			// Protected to be able to increase size on insert
	size_t _size;
public:
	List();
	virtual ~List();
	// Pure Virtual methods to be implemented on concrete classes
	virtual bool Insert(Character* element, size_t position) = 0;
	virtual int IndexOf(const Character* element)const = 0;
	virtual Character* Remove(size_t position) = 0;
	virtual Character* Get(size_t position)const = 0;
	virtual string ToString()const = 0;
	virtual void Clear() = 0;

	size_t Size()const;
	bool IsEmpty()const;

};


#endif
