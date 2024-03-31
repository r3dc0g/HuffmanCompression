#ifndef NODE_H
#define NODE_H

#include <string>
using std::string;

class Node {
private:
	string _letter;
	int _count;
	Node* _left = nullptr;
	Node* _right = nullptr;
public:
	Node();
	Node(string letter, int count=1);
	Node(string letter, int count, Node* left, Node* right);
	~Node();
	string GetLetter()const {return _letter;}
	int GetCount()const {return _count;}
	Node* GetLNode()const {return _left;}
	Node* GetRNode()const {return _right;}
	void SetLetter(string letter) {_letter = letter;}
	void SetCount(int count) {_count = count;}
	void SetLNode(Node* node) {_left = node;}
	void SetRNode(Node* node) {_right = node;}
    Node& operator=(const Node& rhs);

};

#endif
