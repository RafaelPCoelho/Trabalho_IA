#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

bool verificaEsperado(vector<int> &atual, int esperado)
{
    if (atual[1] == esperado)
    {
        return true;
    }
    if (atual[2] == esperado)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

bool verificaNoExplorado(int a, int b, vector<vector<int>> &explorados)
{

    // for (int i = 0; i < explorados.size(); i++)
    //{
    //     cout << explorados[i][0];
    //     cout << (" , ");
    //     cout << explorados[i][1];
    // }
    // cout << endl;
    for (int i = 0; i < explorados.size(); i++)
    {
        if (a == explorados[i][0] && b == explorados[i][1])
        {
            return false;
        }
    }
    return true;
}

bool confirmaResposta(vector<vector<int>> &explorados, vector<int> atual)
{
    for (int i = 0; i < explorados.size(); i++)
    {
        if (explorados[i] == atual)
            return false;
    }
    return true;
}

std::vector<int> ordens(vector<int> atual, int a, int b, vector<vector<int>> &explorados)
{
    vector<int> prox = atual;

    ///////ENCHE 1
    if (atual[0] != a && verificaNoExplorado(a, atual[1], explorados))
    {
        prox = {a, atual[1]};
        return prox;
    }
    ///////ENCHE 2
    if (atual[1] != b && verificaNoExplorado(atual[0], b, explorados))
    {
        prox = {atual[0], b};
        return prox;
    }

    /////JOGA O 2 PRO 1
    if (atual[0] != 0 && atual[1] != b && verificaNoExplorado((atual[0] - min(atual[0], b - atual[1])), (atual[1] + min(atual[0], b - atual[1])), explorados))
    {
        prox = {(atual[0] - min(atual[0], b - atual[1])), (atual[1] + min(atual[0], b - atual[1]))};
        return prox;
    }
    /////JOGA O 1 PRO 2
    if (atual[0] != a && atual[1] != 0 && verificaNoExplorado((atual[0] + min(atual[1], a - atual[0])), (atual[1] - min(atual[1], a - atual[0])), explorados))
    {
        prox = {(atual[0] + min(atual[1], a - atual[0])), (atual[1] - min(atual[1], a - atual[0]))};
        return prox;
    }

    ///////ESVAZIA 1
    if (atual[0] != 0 && verificaNoExplorado(0, atual[1], explorados))
    {
        prox = {0, atual[1]};
        return prox;
    }
    ///////ESVAZIA 2
    if (atual[1] != 0 && verificaNoExplorado(atual[0], 0, explorados))
    {
        prox = {atual[0], 0};
        return prox;
    }

    else
    {
        // cout << ("foi na 7");
        prox = {NULL};
        // cout << prox[0];
        return prox;
    }
}

void backtraking(int a, int b, int esperado)
{
    cout << endl
         << "Backtraking" << endl;
    vector<int> inicial = {0, 0};
    vector<int> atual = {inicial};
    vector<vector<int>> caminho;
    vector<vector<int>> explorados;
    vector<int> cabo = {0, 0};
    vector<int> falha = {NULL};
    bool venceu = false;

    while (!venceu)
    {
        caminho.push_back(atual);
        explorados.push_back(atual);
        if (ordens(atual, a, b, explorados) != falha)
        {
            atual = ordens(atual, a, b, explorados);
            // for (int i = 0; i < atual.size(); i++)
            //    cout << atual[i] << endl;
            if (verificaEsperado(atual, esperado))
            {
                caminho.push_back(atual);
                if (confirmaResposta(explorados, atual))
                    explorados.push_back(atual);
                venceu = true;
            }
        }
        else
        {
            for (int i = 0; i < caminho.size(); i++)
                // cout << caminho[i][0] << " " << caminho[i][1] << endl;

                caminho.pop_back();
            if (caminho[(caminho.size() - 1)] == inicial)
            {
                venceu = true;
            }
        }
    }
    if (verificaEsperado(atual, esperado))
    {
        // cout << ("Profundidade: " + caminho.size()) << endl;
        for (int i = 0; i < caminho.size(); i++)
        {
            cout << (" (");
            for (int j = 0; j < 2; j++)
            {
                cout << caminho[i][j];
                if (j == 0)
                    cout << (",");
            }
            cout << (")");
        }
        cout << endl;
        cout << ("Nos vizitados " + explorados.size()) << endl;
    }
    else
    {
        cout << ("Fracassou");
    }
}