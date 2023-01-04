#include <vector>

#include "../q-4/tree.cpp"

using std::vector;


namespace binaryTree
{
    class BinaryTreeWithOrder : public BinaryTree
    {

        private:
            vector<int>* privAscendentOrder(Node* node, vector<int>* vec = NULL)
            {
                if(node == NULL)
                {
                    if(vec == NULL)
                        vec = new vector<int>();

                    return vec;
                }

                privAscendentOrder(node->getLeft(), vec);

                vec->push_back(node->getValue());

                privAscendentOrder(node->getRight(), vec);
            }  

        public:

            // Retorna um vetor dinamico com os valores dos elementos ordenados de forma ascendente
            vector<int> AscendentOrder()
            {
                vector<int>* vec = privAscendentOrder(root);

                return (*vec);
            }



    };
}