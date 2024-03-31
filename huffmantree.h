#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "node.h"
#include "vsarray.h"


class HuffTree {
private:
	Node* _root = nullptr;

public:
	HuffTree();
	~HuffTree();
	void CreateTree(VSArray&);
    Node* CreateTreeRecursive(VSArray& freqs, size_t n);
	void SetRoot(Node* node) {_root = node;}
	Node* GetRoot()const {return _root;}
	void BlowItUp(Node* node);
};

#endif

