#include "delete_types.cpp"

using std::cout;

namespace binaryTree
{
    // Arvore binaria de busca capaz de realizar os dois tipos de delecao
    // Bastando declarar o tipo de delecao que deseja usar em seguida com 
    // os metodos useSubstitutionDelete() e useReinsertionDelete()
    // OBS: originalmente usa delecao por substituicao
    class BinaryTree
    {
        protected:
            Node* root;

        private:
            // Responsavel pela operacao de delecao, para tornar a classe 
            // generalizavel para binary trees com susbtituicao e sem 
            // substituicao na delecao
            DeleteType* del; 

            bool privInsert(int value, Node* &node)
            {
                if(node == NULL)
                {
                    node = new Node(value);

                    return true;
                }

                if(value > node->getValue()) return privInsert(value, node->getRight());
                if(value < node->getValue()) return privInsert(value, node->getLeft());
                return false;
            }

            void privShowInOrder(Node* node)
            {
                if(node == NULL) return;
                privShowInOrder(node->getLeft());
                cout << node->getValue() << '\n';
                privShowInOrder(node->getRight());
            }

            void erase(Node* node)
            {
                if(node == NULL) return;

                erase(node->getLeft());
                erase(node->getRight());

                free(node);
            }

            Node*& privFind(int value, Node* node)
            {
                if(node == NULL) return node;

                if(node->getValue() > value) return privFind(value, node->getLeft());
                if(node->getValue() < value) return privFind(value, node->getRight());
                return node;
            }

        public:

            BinaryTree() { root = NULL; useSubstitutionDelete(); }

            bool insert(int value) { return privInsert(value, root); }

            void showInOrder() { cout << '\n'; return privShowInOrder(root); }

            Node* & find(int value) { return privFind(value, root); }

            bool deleteValue(int value) { del->deleteValue(value, root); }

            ~BinaryTree() { erase(root); free(del); }

            void useSubstitutionDelete() { del = new SubstitutionDelete(); }

            void useReinsertionDelete() { del = new ReinsertionDelete(); }

    };
}

int main()
{



}