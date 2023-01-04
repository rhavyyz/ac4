#include <iostream>

namespace binaryTree
{
    class Node
    {
        private:
            Node* left, *right;
            int value;
        public:
            Node* & getLeft() {  return left;  }
            Node* & getRight() {  return right;  }
            int getValue() {  return value;  }
            void setLeft(Node* value) {  this->left = value;  }
            void setRight(Node* value) {  this->right = value;  }
            void setValue(int value) {  this->value=value;  }
            Node(int value)
            { 
                this->value=value;
                left=NULL;
                right=NULL;
            }
    }; 
}