#include "Menus.h"


int main()
{
    setlocale(LC_ALL, "Rus");

    int n, cont = 1;

    Start();
    while (cont)
    {
        n = Mode();
        cont = Game(n);
    }
    return 0;
}
       