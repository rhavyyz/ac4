#include "node.cpp"
#include<math.h>
#include<fstream>


using std::string;

const float log_10 = log(10);

class SingleVariableFunctionTree
{
    private:
        string expression;

        Node* root = NULL;

        // Desaloca recursivamente a arvore
        void purgeTree(Node* node)
        {
            if(node == NULL) return;

            purgeTree(node->getLeft());
            purgeTree(node->getRight());

            free(node);
        }

        bool nothingAtRight(string expression, int pos)
        {
            while(pos < expression.size() && expression[pos] == ')')
                pos++;

            return expression.size() == pos;
        }

        // Objetivo e formatar a string com a expressao e ir repassando recursivamente substrings que representam valores de 
        // para preencher os nos filhos
        void structureTree(string expression, Node* &node)
        {
            if(expression.size() == 0)
                return;

            if(node == NULL)
                node = new Node();

            // Operacao que se foi identificada durante a leitura da substring
            char operation = '\0';

            float value = 0;
            // Valores usados para representar o comeco e fim da substring do primeiro termo de uma expressao
            int begin=-1,end = -1;


            // Caso comece com um valor numerico
            if(expression[0] >= '0' && expression[0] <= '9')
            {
                for(begin = 0,end = 1; 
                    
                    expression.size() >= end &&
                    (expression[end] >= '0' && expression[end] <= '0')  ||
                    expression[end] == '.';
                    
                    end++)
                { }

                if(end != expression.size() - 1)
                    end--;

                value = std::stof(expression.substr(begin, end-begin + 1));
            }

            // Caso a primeira operacao seja logaritmo ou raiz quadrada 
            // Ex doq deseja ser feito
            // string completa: log(x+12)
            // substring que procuramos: x+12
            else if(expression[0] == 'L' || expression[0] == 'S' ||
                    expression[0] == 'l' || expression[0] == 's'   )
            {

                operation = expression[0];

                int numberOfBrackets = 0;
                end = 1;

                bool first = true;

                while(true)
                {
                    if (expression[end] == '(')
                    {
                        numberOfBrackets++;
                        if(first)
                        {
                            begin=end+1;
                            first = false;
                        }
                    }
                    
                    else if (expression[end] == ')')
                    {
                        numberOfBrackets--;

                        if(numberOfBrackets == 0)
                            break; 
                    }

                    end++;

                    if(end >= expression.size())
                        throw "Nao foram fechados todos os parenteses";
                    
                }
                end--;
            }
            // Caso a expressao seja do tipo:
            // (x+1010)
            // buscamos a substring
            // x+1010
            else if(expression[0] == '(')
            {
                int numberOfBrackets = 1;
                
                // nao e uma operacao de verdade, apenas para informar que primeiramente se achou um parenteses
                operation = '(';
                begin = 1;
                end = 1;

                while(true)
                {
                    if (expression[end] == '(')
                        numberOfBrackets++;
                    else if (expression[end] == ')')
                    {
                        numberOfBrackets--;

                        if(numberOfBrackets == 0)
                            break;
                    }

                    end++;

                    if(end >= expression.size())
                        throw "Nao foram fechados todos os parenteses";
                }
                end--;
            }
            // Caso se comece com um x apenas marcamos a substring como a posicao inicial
            else if(expression[0] == 'x')
            {
                operation = 'x';
                begin = 0;
                end = 0;
            }


            // Caso nao exista nenhum caractere relevante para a direita da substring
            // entao delegamos o no atual para realizar a operacao dessas substring
            // isso so e possivel caso 
            // string for de um dos tipos
            // -(substr)
            // -x
            // -12
            // -log(algo)
            // -sqrt(algo)
            if(nothingAtRight(expression, end+1))
            {
                node->setOperation(operation);

                // Caso o valor seja apenas um numero
                if(operation == '\0')
                {
                    // Apenas e preciso sinalizar quando isValue for true
                    // ja que por padrao sao instanciados como false
                    node->setIsValue(true);
                    node->setValue(value);

                    return;
                }

                if(operation == 'x') return;
                
                string str = ((end - begin+1) ? expression.substr(begin, end - begin+1) : "");

                // Caso estjam apenas sendo retirados os parenteses mais externos de modo
                // (substr)
                // entao se e refeito o precesso no mesmo ponteiro porem apenas com a substring
                if(operation == '(')
                {
                    node->setOperation('\0'); 
                    structureTree(str, node);
                    return; // <----
                }

                // Caso nao tenha entrado em nenhum dos if's acima a string expression
                // representa uma operacao de logaritmo ou raiz quadrada
                // sendo assim  

                structureTree(str, node->getLeft());

                return; // <------
            }

            // Caso a string nao entre no if acima isso quer dizer que existem caracteres caracteres
            // relevantes a esquerda da susbtring
            // portanto a string representa uma operacao que tem 2 elementos
            // ou seja + - / * ou ^

            int secBegin = end;

            // while que encerra em cima da posicao do operador
            while(secBegin < expression.size() &&
                  expression[secBegin] != '+' &&
                  expression[secBegin] != '-' &&
                  expression[secBegin] != '/' &&
                  expression[secBegin] != '*' &&
                  expression[secBegin] != '^')
                secBegin++;
            
            operation = expression[secBegin];
            
            // Passa a se referir a posicao onde se inicia a substring do segundo elemento da operacao
            secBegin++;
            node->setOperation(operation);

            string str1 = ((end - begin + 1) ? expression.substr(begin, end - begin + 1) : ""),
                   str2 = ((expression.size() - end - 2) ? expression.substr(secBegin, expression.size() - secBegin ) : "");

            structureTree(str1, node->getLeft());
            structureTree(str2, node->getRight());
        }

        // Realiza as operacoes de forma recursiva da arvore usando o valor
        // de x passado como parametro
        float useTreeWith(Node * node, float x)
        {
            if(node->getIsValue()) return node->getValue();

            char operation = node->getOperation();

            if(operation == 'x') return x;

            float op1= useTreeWith(node->getLeft(), x);

            if(operation == 'L' || operation == 'l')
                return log(op1)/log_10;            
            if(operation == 'S' || operation == 's')
                return sqrt(op1);            
        
            float op2= useTreeWith(node->getRight(), x);

            if(operation == '+') return op1 + op1;
        
            if(operation == '-') return op1 - op2;
            
            if(operation == '*') return op1 * op2; 

            if(operation == '/') return op1 / op2;
            
            if(operation == '^') return pow(op1, op2);

            return 0;
        }

    public:
        SingleVariableFunctionTree(std::string expression)
        {
            this->expression = expression;

            structureTree(expression, root);
        }

        ~SingleVariableFunctionTree() { purgeTree(root); }

        // Metodo que retorna o valor obtido por f(x)
        double operate(float x) { return useTreeWith(root, x); }
};

int main()
{
    SingleVariableFunctionTree* tree = new SingleVariableFunctionTree(
        "(3*Log(2*sqrt(x)))-(x-6)/Log(4*x^0.5)"
    );

    std::ofstream file;
    file.open("output.txt");

    for(float i : (float[]) {4, 21, -12.7})
    {
        float value = tree->operate(i);
        std::cout<< i << " --> " << value << '\n';
        file<< i << " --> " << value << '\n';
    }

    file.close();
    return 0;
}