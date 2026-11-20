#include "inteligencia.h"
#include <iostream>

int main() {
    Parametros parametros;

    for(int i = 0; i < 10; i++) {
        ajustarParametros(parametros, 30.0);
    }

    std::cout << "\nUmbral final: "
              << parametros.umbralAlerta << "%\n";

    return 0;
}
