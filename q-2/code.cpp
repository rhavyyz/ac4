#include<iostream>
#include <vector>

using std::vector;

/*

Implementacao da classe Graph para o caso apresentado na questao foi feita na funcao 
main deste mesmo arquivo, iniciando na linha 174

*/

// Durante a implementacao dessa classe e outras durante a atividade
// criamos um metodo publico que dispara um outro metodo privado
// para que a recursoes fossem usadas de forma adequada e/ou nao se 
// fosse possivel abusar do metodos para realizar operacoes ilogicas
class Graph
{
    private:
        // A classe vector natural do C++ ja e inicializada assim que declarada
        // portanto nao e necessario declarar um construtor para a classe 
        // Graph
        vector<vector<int>> graph;

        // Vetor dinamico auxiliar que guarda todos os nos ja visitados anteriormente
        // com o objetivo de evitar loops infinitos ao percorrer o grafo
        vector<int> visited;

        bool privHasPath(int begin, int end)
        {
            if(begin ==end)
                return true;

            for(int & element : visited)
            {
                if(element != begin) continue; 
                return false;
            }

            visited.push_back(begin);

            for(int &element : graph[begin])
            {
                if(privHasPath(element, end)) return true;
            }

            return false;
        }

        // Retorna um vetor mostrando um possivel caminho de begin para end na ordem inversa.
        // Caso nao exista um caminho e retornado um vetor sem elementos
        // Nao obrigatoriamente esses e o caminho mais rapido por ter sido usada uma abordagem de DFS
        vector<int> privFindPath(int begin, int end)
        {

            if(begin ==end) 
            {
                vector<int> vec;
                vec.push_back(begin);
                return vec;
            }

            for(int & element : visited)
            {
                if(element != begin) continue; 
                
                vector<int> vec;
                return vec;
            }

            visited.push_back(begin);

            for(int &element : graph[begin])
            {
                vector<int> vec = privFindPath(element, end);
                if(vec.size() == 0) continue;

                vec.push_back(begin);
                return vec;
            }

            vector<int> vec;
            return vec;
        }

    public:
        bool isConnected()
        {
            for(int i=0; i < graph.size(); i++)
            {
                for(int c=i+1; c < graph.size(); c++)
                {
                    bool path1 = hasPath(i, c);
                    bool path2 = hasPath(c, i);
                    if(!path1 || !path2) return false;
                }
            }

            return true;
        }

        bool isStronglyConnected()
        {
            for(int i=0; i < graph.size(); i++)
            {
                bool ok = true;
                for(int c=0; c < graph.size(); c++)
                {
                    bool path1 = hasPath(i, c);
                    bool path2 = hasPath(c, i);
                    if(!path1 || !path2) ;
                    {
                        ok = false;
                        break;
                    }
                }
                if(ok) return true;
            }

            return false;
        }

        bool hasPath(int begin,int end)
        {
            visited.clear();

            return privHasPath(begin, end);
        }

        vector<int> findPath(int begin, int end)
        {   
            visited.clear();

            return privFindPath(begin, end);
        }


        // Gera espaco para as arestas de um novo vertice no grafo
        // e retorna o numero pelo qual ele sera indicado
        int newNode()
        {
            graph.resize(graph.size() + 1);
            return graph.size() - 1;
        }

        // Gera espaco para uma quantidade qtd de novos vertices no grafo
        // retornando o maior valor que representa um vertice
        int newNodes(int qtd)
        {
            graph.resize(graph.size() + qtd);
            return graph.size() - 1;
        }

        int NOfNodes()
        {
            return graph.size();
        }

        bool newEdge(int begin, int end)
        {
            if(begin >= graph.size() || begin < 0|| end < 0 || end >= graph.size())
                return false;

            for(int &element: graph[begin])
            {
                if(element == end) return false;
            }

            graph[begin].push_back(end);

            return true;
        }

        bool deleteEdge(int begin, int end)
        {
            if(begin >= graph.size() || begin < 0|| end < 0 || end >= graph.size())
                return false;


            for(int i=0; i < graph[begin].size(); i++)
            {
                if(graph[begin][i] != end) continue;

                int lastEdgePos = graph[begin].size() - 1;

                graph[begin][i] = graph[begin][lastEdgePos];
                graph[begin].pop_back();

                return true;
            }

            return false;
        }
};

// Usando a classe Graph para representar o grafo demonstado na questao
int main()
{
    Graph* graph = new Graph();

    graph->newNodes(11);
    // Os vertices serao representados pelos numeros 
    // indicados na imagem auxiliar no mesmo diretorio

    // 0
    graph->newEdge(0, 1);
    graph->newEdge(0, 3);
    graph->newEdge(0, 2);

    //1
    graph->newEdge(1, 0);
    graph->newEdge(1, 4);
    graph->newEdge(1, 5);

    //2
    graph->newEdge(2, 3);
    graph->newEdge(2, 4);
    graph->newEdge(2, 5);

    //3
    graph->newEdge(3, 0);
    graph->newEdge(3, 2);
    graph->newEdge(3, 4);
    graph->newEdge(3, 6);

    //4
    graph->newEdge(4, 1);
    graph->newEdge(4, 2);
    graph->newEdge(4, 6);

    //5
    graph->newEdge(5, 1);
    graph->newEdge(5, 6);

    //6
    graph->newEdge(6, 3);
    graph->newEdge(6, 4);
    graph->newEdge(6, 5);
    graph->newEdge(6, 7);

    //7
    graph->newEdge(7, 3);

    //8
    graph->newEdge(8, 9);
    
    //9
    graph->newEdge(9, 6);

    //10
    graph->newEdge(10, 9);
    graph->newEdge(10, 8);


    std::cout << "Is connected? :"<<(graph->isConnected() ? "true" : "false");
    std::cout << "\nIs strongly connected? :"<<(graph->isStronglyConnected() ? "true\n" : "false\n");
    


    return 0;
}