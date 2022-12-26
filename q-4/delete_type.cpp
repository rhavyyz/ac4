#include "node.cpp"
#include <iostream>

namespace binaryTree
{
    class DeleteType
    {
        protected: 
            Node* &findToRemove(int value, Node* &node);
        public:
            virtual bool deleteValue(int value, Node* & node);
    };

    class ReinsertionDelete : public DeleteType
    {
        protected:
            Node* &findToRemove(int value, Node* node)
            {
                if(node == NULL) return node;

                if(node->getValue() > value)
                {
                    Node* &res = findToRemove(value, node->getLeft());
                    if(res == node->getLeft()) node->setLeft(NULL);
                    return res;
                }
                if(node->getValue() < value)
                {
                    Node* &res = findToRemove(value, node->getRight());
                    if(res == node->getRight()) node->setRight(NULL);
                    return res;
                }                
                return node;
            }
        private:
            void reinsertNode(Node* toAdd, Node* &node)
            {
                if(toAdd == NULL) return;

                int value = toAdd->getValue();
                if(node == NULL)
                {
                    node = toAdd;
                    return;
                }
                if(value > node->getValue()) return reinsertNode(toAdd, node->getRight());
                if(value < node->getValue()) return reinsertNode(toAdd, node->getLeft());
            }
        public:
            bool deleteValue(int value, Node* & root)
            {
                Node* &node = findToRemove(value, root);
                if (node == NULL) return false;

                reinsertNode(node->getLeft(), root);
                reinsertNode(node->getRight(), root);
                return true;
            }
    };

    class SubstitutionDelete : public DeleteType
    {
        private:
            Node* & privDeleteValue(int value, Node* &node)
            {
                if(node == NULL) return node;

                if(value > node->getValue())
                {
                    Node* &res = privDeleteValue(value, node->getRight());
                    if(res == node->getRight()) node->setRight(NULL);   
                    return res;
                }
                if(value < node->getValue())
                {
                    Node* &res = privDeleteValue(value, node->getLeft());
                    if(res == node->getLeft()) node->setLeft(NULL);   
                    return res;
                }

                // Quando node->getValue() == value
                // Tenta trocar o elemento com o maior 
                if(node->getRight() != NULL)
                {
                    node->setValue(node->getRight()->getValue());
                    node->getRight()->setValue(value);
                    return privDeleteValue(value, node->getRight());
                }
                // Caso nao exista elemento maior se troca com um menor
                if(node->getLeft() != NULL)
                {
                    node->setValue(node->getLeft()->getValue());
                    node->getLeft()->setValue(value);
                    return privDeleteValue(value, node->getLeft());
                }

                // Nao tem elementos
                free(node);
                return node;
            }
        public:
            bool deleteValue(int value, Node* & root)
            {
                return privDeleteValue(value, root) != NULL;                
            }
    };


}