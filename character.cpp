#include "character.h"
#include "node.h"

#include <string>
#include <sstream>
#include <iostream>
using std::string;
using std::stringstream;
using std::cout;
using std::endl;

Character::Character(): _value("null"), _count(1), _node(nullptr) {
}

Character::Character(string character): _value(character), _count(1), _node(nullptr) {
}

Character::Character(string character, int count): _value(character), _count(count), _node(nullptr) {
}

Character::~Character() {
    //delete _node;
}
Character& Character::operator=(const Character& rhs) {
    cout << "Calling = operator on Character" << endl;
	_value = rhs._value;
	_count = rhs._count;
	delete _node;
	_node = new Node(rhs.GetNode()->GetLetter(), rhs.GetNode()->GetCount(), rhs.GetNode()->GetLNode(), rhs.GetNode()->GetRNode());
    return *this;
}
bool Character::GreaterThan(const Character& rhs)const {
	if (this == &rhs) {
		return false;
	}
	auto rhsPtr = dynamic_cast<const Character*>(&rhs);
	if (rhsPtr == nullptr) {
		return false;
	}
	if (_count == rhsPtr->_count) {
		if (_value == rhsPtr->_value) {
			return false;
		}
		return _value > rhsPtr->_value;
	}
	return _count > rhsPtr->_count;
}
bool Character::LessThan(const Character& rhs)const {
	if (this == &rhs) {
		return false;
	}
	auto rhsPtr = dynamic_cast<const Character*>(&rhs);
	if (_count == rhsPtr->_count) {
		if (_value == rhsPtr->_value) {
			return false;
		}
		return _value < rhsPtr->_value;
	}
	return _count < rhsPtr->_count;
}
int Character::CompareTo(const Character& rhs)const {
	if (this == &rhs) {
		return 0;
	}
	auto rhsPtr = dynamic_cast<const Character*>(&rhs);
	if (rhsPtr == nullptr) {
		return -1;
	}
	if (_count == rhsPtr->_count) {
		if (_value.size() > rhsPtr->_value.size()) {
			return -1;
		}
		else if (_value.size() == rhsPtr->_value.size()) {
			if (_value > rhsPtr->_value) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	else if (_count > rhsPtr->_count) {
		return 1;
	}
	else if (_count < rhsPtr->_count){
		return -1;
	}
	else {
		return 0;
	}

	return 0;
}
string Character::ToString()const{
	stringstream retVal;
	retVal << _value;
	return retVal.str();
}
string Character::ToJSON()const{
	stringstream retVal;
	if (_value == "CR" || _value == "LF") {
		retVal << "{element: " << _value << ", frequency: " << _count << "}";
	}
	else {
		retVal << "{element:  " << _value << ", frequency: " << _count << "}";
	}
	return retVal.str();
}
string Character::ToEncodeTable()const {
	stringstream retVal;
	if (_value == "CR" || _value == "LF") {
		retVal << "{key: " << _value << ", code: " << _code << "}";
	}
	else {
		retVal << "{key:  " << _value << ", code: " << _code << "}";
	}
	return retVal.str();
}
string Character::GetValue()const{
	return _value;
}
void Character::SetValue(string value){
	_value = value;
}
int Character::GetCount()const{
	return _count;
}
void Character::SetCount(int count) {
	_count = count;
}
Node* Character::GetNode()const {
	return _node;
}
string Character::GetCode()const {
	return _code;
}
void Character::SetNode(Node* node) {
	_node = node;
}
void Character::SetCode(string code) {
	_code = code;
}
Character* Character::Clone()const{
	return new Character(_value);
}
bool Character::Equals(const Character& rhs)const{
	if (this == &rhs){
		return true;
	}
	auto rhsPtr = dynamic_cast<const Character*>(&rhs);
	if (rhsPtr == nullptr) {
		return false;
	}
	return _value == rhsPtr->_value;
}
