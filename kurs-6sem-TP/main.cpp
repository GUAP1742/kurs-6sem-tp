#include "Menus.h"

using namespace sf;

int main()
{
#if MODE == 0

    setlocale(LC_ALL, "Rus");

    int n, cont = 1;

    Start();
    while (cont)
    {
        n = Mode();
        cont = Game(n);
    }

    return 0;

#elif MODE == 1

    int n, cont = 1;

    Start();
    while (cont)
    {
        while (MainMenu());
        n = Mode();
        cont = Game(n);
    }

    return 0;

#endif
}

       