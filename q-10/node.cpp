#include<iostream>

class Node
{
    private:         
        /*
            L - log base 2 (deve conter apenas um elemento a esquerda, por ser funcao)
            S - raiz quadrada (Deve conter apenas um elemento a esquerda, por ser funcao)
            * - multiplicacao
            / - divisao
            ^ - exponenciacao
            - - subtracao
            + - adicao

            x - transformar o no em questao no valor de X
        */
        char operation;
        float value;
        bool isValue;

        Node* right, * left;

        public:
            Node* & getRight() { return right; }
            Node* & getLeft() { return left; }
            char getOperation() { return operation; }
            bool getIsValue() { return isValue; }
            float getValue() { return value; }

            void setRight(Node* right){ this->right = right; }
            void setLeft(Node* left) { this->left = left; }
            void setIsValue(bool isValue) { this->isValue = isValue; }
            void setValue(float value) { this->value = value; }
            void setOperation(char operation) { this->operation = operation; }

};