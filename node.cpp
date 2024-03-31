#include <string>
#include <iostream>
#include "node.h"

using std::cout;
using std::endl;

Node::Node(): _letter("null"), _count(0) {
}
Node::Node(string letter, int count): _letter(letter), _count(count) {
}
Node::Node(string letter, int count, Node* left, Node* right): _letter(letter), _count(count), _left(left), _right(right) {
}
Node::~Node() {

}

Node& Node::operator=(const Node &rhs) {
    _letter = rhs._letter;
    _count = rhs._count;
    _left = rhs._left;
    _right = rhs._right;
    return *this;
}

