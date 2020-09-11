#include "Menus.h"

using namespace sf;

int main()
{
    setlocale(LC_ALL, "Rus");

    int n, cont = 1;

    Start();
    while (cont)
    {
#if MODE == 1
        while (MainMenu());
#endif
        n = Mode();
        cont = Game(n);
    }

    return 0;
}

       