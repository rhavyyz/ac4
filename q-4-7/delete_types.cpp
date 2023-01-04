#include "node.cpp"

namespace binaryTree
{
    class DeleteType
    {
        protected: 
            Node* &findToRemove(int value, Node* &node);
        public:
            virtual bool deleteValue(int value, Node* & node);
    };

    // Resposta da questao 7
    class SubstitutionDelete : public DeleteType
    {
        private:
            Node* & lower(Node* &node)
            {
                if(node->getLeft() == NULL) return node;

                return lower(node->getLeft());
            }
            Node* & higher(Node* &node)
            {
                if(node->getRight() == NULL) return node;

                return higher(node->getRight());
            }
        public:
            bool deleteValue(int value, Node* & node)
            {
                if(node == NULL) return false;

                if(node->getValue() > value)
                    return deleteValue(value, node->getLeft());                
                
                if(node->getValue() < value)
                    return deleteValue(value, node->getRight());

                // node.getValue() == value

                // Caso nao existam filhos elementos entao o no apenas e eliminado
                if(node->getLeft() == NULL && node->getLeft() == NULL)
                {
                    free(node);
                    node = NULL;
                    return true;
                }

                // Por padrao substitui com o maior elemento da esquerda
                if(node->getLeft() != NULL)
                {
                    Node* & toDel = higher(node->getLeft());
                    
                    node->setValue(toDel->getValue());

                    return deleteValue(toDel->getValue(), toDel);
                }


                // Caso nao existam elementos a esquerda entao
                // Se substitui pelo menor elemento a direita
                Node* & toDel = lower(node->getRight());

                node->setValue(toDel->getValue());

                return deleteValue(toDel->getValue(), toDel);
            }
    };

    class ReinsertionDelete : public DeleteType
    {
        protected:
            Node* findToRemove(int value, Node* node)
            {
                if(node == NULL) return node;

                if(node->getValue() > value)
                {
                    Node* res = findToRemove(value, node->getLeft());
                    if(res == node->getLeft()) node->setLeft(NULL);
                    return res;
                }
                if(node->getValue() < value)
                {
                    Node* res = findToRemove(value, node->getRight());
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
                Node* node = findToRemove(value, root);
                if (node == NULL) return false;

                reinsertNode(node->getLeft(), root);
                reinsertNode(node->getRight(), root);
                return true;
            }
    };

}