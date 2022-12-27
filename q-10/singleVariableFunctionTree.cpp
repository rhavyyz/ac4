#include "node.cpp"
#include<math.h>

class SingleVariableFunctionTree
{
    private:
        std::string expression;

        Node* root;

        void structureTree()
        {
        //     root = new Node();

        //     int numberBegin = -1, numberSize=0;
        //     for(int i=0; i < expression.size(); i++)
        //     {
        //         if((expression[i] >= '0' && expression[i] <= '0') || expression[i] == '.')
        //         {
        //             if(numberBegin == -1) numberBegin = i;

        //             numberSize++;
        //             continue;
        //         }


        //     }
        }

        float useTreeWith(Node * node, float x)
        {
            if(node->getIsValue()) return node->getValue();

            char operation = node->getOperation();

            if(operation == 'x') return x;

            if(operation == 'L')
                return log(
                        useTreeWith(node->getLeft(), x)
                        );            
            if(operation == 'S')
                return sqrt(
                        useTreeWith(node->getLeft(), x)
                        );            
            
            float op1= useTreeWith(node->getLeft(), x),
                  op2= useTreeWith(node->getRight(), x);

            if(operation == '+') return op1 + op1;
        
            if(operation == '-') return op1 - op2;
            
            if(operation == '*') return op1 * op2; 

            if(operation == '/') return op1 / op2;
            
            if(operation == '^') return pow(op1, op2);
        }

        void purgeTree(Node* node)
        {
            if(node == NULL) return;

            purgeTree(node->getLeft());
            purgeTree(node->getRight());

            free(node);
        }

    public:
        SingleVariableFunctionTree(std::string expression)
        {
            this->expression = expression;
        }

        double operate(float x)
        {
            structureTree();

            float value = useTreeWith(root, x);
        
            purgeTree(root);

            return  value;
        }

        ~SingleVariableFunctionTree()
        {
            purgeTree(root);
        }
};