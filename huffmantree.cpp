#include <string>
#include <iostream>
#include "huffmantree.h"
#include "vsarray.h"
#include "node.h"
#include "character.h"

using std::cout;
using std::endl;

HuffTree::HuffTree() {
}

HuffTree::~HuffTree() {
	HuffTree::BlowItUp(_root);
}

void HuffTree::BlowItUp(Node* node){
	if (node != nullptr && node->GetLNode() == nullptr && node->GetRNode() == nullptr) {
		delete node;
	}
	else if (node != nullptr) {
		BlowItUp(node->GetLNode());
		BlowItUp(node->GetRNode());
		delete node;
	}
}

void HuffTree::CreateTree(VSArray& freqs) {
    VSArray garbage(30);
	Character* char1;
	Character* char2;
	Character* newChar;
	Node* leftNode;
	Node* rightNode;
	Node* newNode;
	size_t i;

	while (freqs.Size() > 2) {
		i = 0;

		char1 = freqs.Remove(freqs.Size() - 1);
		char2 = freqs.Remove(freqs.Size() - 1);
        garbage.Insert(char1, garbage.Size());
        garbage.Insert(char2, garbage.Size());

		if(char1->GetNode() == nullptr) {
			newNode = new Node(char1->ToString(), char1->GetCount());
			char1->SetNode(newNode);
			leftNode = char1->GetNode();
		}
		else {
			leftNode = char1->GetNode();
		}

		if(char2->GetNode() == nullptr) {
			newNode = new Node(char2->ToString(), char2->GetCount());
			char2->SetNode(newNode);
			rightNode = char2->GetNode();
		}
		else {
			rightNode = char2->GetNode();
		}

		newChar = new Character(char1->ToString() + char2->ToString(), char1->GetCount() + char2->GetCount());
		newNode = new Node(leftNode->GetLetter() + rightNode->GetLetter(), leftNode->GetCount() + rightNode->GetCount(), leftNode, rightNode);
		newChar->SetNode(newNode);

		while (newChar->CompareTo(*freqs.Get(i)) <= 0 && i < freqs.Size()) {
			i++;
		}

		freqs.Insert(newChar, i);
	}

	char1 = freqs.Remove(1);
	char2 = freqs.Remove(0);
    garbage.Insert(char1, garbage.Size());
    garbage.Insert(char2, garbage.Size());

	leftNode = char1->GetNode();
	rightNode = char2->GetNode();

	newNode = new Node(leftNode->GetLetter() + rightNode->GetLetter(), leftNode->GetCount() + rightNode->GetCount(), leftNode, rightNode);

	_root = newNode;

}
/*
Node* HuffTree::CreateTreeRecursive(VSArray& freqs, size_t n) {
    if (n == 2) {
        Character* char1 = freqs.Remove(freqs.Size() - 1);
        Character* char2 = freqs.Remove(freqs.Size() - 1);

        if (char1->GetNode() == nullptr) {
            Node* newNode1 = new Node(char1->ToString(), char1->GetCount());
            char1->SetNode(newNode1);
        }

        if (char2->GetNode() == nullptr) {
            Node* newNode2 = new Node(char2->ToString(), char2->GetCount());
            char2->SetNode(newNode2);
        }

        Character* newChar = new Character(char1->ToString() + char2->ToString(), char1->GetCount() + char2->GetCount());
        Node* combinationNode = new Node(char1->ToString() + char2->ToString(), char1->GetCount() + char2->GetCount());
        newChar->SetNode(combinationNode);

        _root = newChar->GetNode();

        if (char1->GetValue() > char2->GetValue()) {
            return char1->GetNode();
        }
        else {
            return char2->GetNode();
        }
    }
    else {
        Character* char1 = freqs.Remove(freqs.Size() - 1);
        Character* char2 = freqs.Remove(freqs.Size() - 1);

        if (char1->GetNode() == nullptr) {
            Node* newNode1 = new Node(char1->ToString(), char1->GetCount());
            char1->SetNode(newNode1);
        }

        if (char2->GetNode() == nullptr) {
            Node* newNode2 = new Node(char2->ToString(), char2->GetCount());
            char2->SetNode(newNode2);
        }

        Character* newChar = new Character(char1->ToString() + char2->ToString(), char1->GetCount() + char2->GetCount());
        Node* combinationNode = new Node(char1->ToString() + char2->ToString(), char1->GetCount() + char2->GetCount());
        newChar->SetNode(combinationNode);

        freqs.Insert()

        Node* parent =
    }
}
*/
