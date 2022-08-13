#include <iostream>
#include "backtraking.h"

using namespace std;

int main()
{
    int a, b;
    int esperado;
    cout << "Vaso A:";
    cin >> a;
    cout << "Vaso B:";
    cin >> b;
    cout << "Resultado esperado:";
    cin >> esperado;

    clock_t begin, end;

    begin = clock();
    backtraking(a, b, esperado);
    end = clock();

    cout << "time: " << (end - begin) / CLOCKS_PER_SEC * 1000 << endl;
    return 0;
}