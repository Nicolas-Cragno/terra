#include "Juego.h"
#include "Menu.h"

int main() {
    Juego juego;
    //juego.iniciar();
    Menu menu(juego);
    menu.mostrar();
    return 0;
}
