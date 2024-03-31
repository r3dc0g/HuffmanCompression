#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "node.h"
using std::string;

class Character {
		string _value;
		int _count;
		string _code;
		Node* _node;

	public:
		Character();
		Character(string character);
		Character(string character, int count);
		~Character();
		string ToString()const;
		string ToJSON()const;
		string ToEncodeTable()const;
		string GetValue()const;
		int GetCount()const;
		Node* GetNode()const;
		string GetCode()const;
		void SetValue(string);
		void SetCount(int);
		void SetNode(Node* node);
		void SetCode(string code);
		Character* Clone()const;
		Character& operator=(const Character& rhs);
		bool Equals(const Character& rhs)const;
		bool GreaterThan(const Character& rhs)const;
		bool LessThan(const Character& rhs)const;
		int CompareTo(const Character& rhs)const;
};

#endif
