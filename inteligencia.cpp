#include <iostream>
#include "inteligencia.h"
#include <fstream>
#include <ctime>

double calcularOcupacion(int ocupados, int capacidad) {
    if(capacidad <= 0) {
        return 0.0;
    }
    double porcentaje = (static_cast<double>(ocupados) / capacidad) * 100;

    return porcentaje;
}

Estado evaluarEstado(double ocupacion) {

    if(ocupacion >= 90.0) {
        return Estado::ROJO;
    }
    else if(ocupacion >= 70.0) {
        return Estado::AMARILLO;
    }
    else {
        return Estado::VERDE;
    }
}

std::string nombreEstado(Estado estado) {

    switch(estado) {
        case Estado::VERDE:
            return "VERDE";

        case Estado::AMARILLO:
            return "AMARILLO";

        case Estado::ROJO:
            return "ROJO";

        default:
            return "DESCONOCIDO";
    }
}
void mostrarSemaforo(double ocupacion, Estado estado) {

    std::cout << "\n========== SEMAFORO DEL PARQUEADERO ==========\n";

    std::cout << "Ocupacion actual: " << ocupacion << "%\n";

    std::cout << "Estado: " << nombreEstado(estado) << "\n";

    std::cout << "==============================================\n";
}

void registrarMetricas(int ocupados, int capacidad, double ocupacion) {
    std::ofstream archivo("metricas.txt", std::ios::app);
    if(!archivo.is_open()) {
        std::cout << "Error al abrir el archivo de metricas.\n";
        return;
    }

    time_t ahora = time(nullptr);
    archivo << ahora << ";"
            << ocupados << ";"
            << capacidad << ";"
            << ocupacion << "\n";

    archivo.close();
}

void analizarMetricas() {
    std::ifstream archivo("metricas.txt");

    if(!archivo.is_open()) {
        std::cout << "No se pudo abrir el historial.\n";
        return;
    }
    double ocupacion;
    double ocupacionMaxima = 0.0;
    double sumaOcupacion = 0.0;

    int ocupados;
    int capacidad;
    int cantidadRegistros = 0;
    time_t fecha;

    char separador;

while(archivo >> fecha >> separador
              >> ocupados >> separador
              >> capacidad >> separador
              >> ocupacion) {

    if(ocupacion > ocupacionMaxima) {
        ocupacionMaxima = ocupacion;
    }

    sumaOcupacion += ocupacion;
    cantidadRegistros++;
}
if(cantidadRegistros == 0) {
    std::cout << "No hay registros historicos.\n";
    archivo.close();
    return;
}

double promedio = sumaOcupacion / cantidadRegistros;

std::cout << "\n======= INFORME HISTORICO =======\n";

std::cout << "Cantidad de registros: "
          << cantidadRegistros << "\n";

std::cout << "Ocupacion maxima: "
          << ocupacionMaxima << "%\n";

std::cout << "Ocupacion promedio: "
          << promedio << "%\n";

std::cout << "=================================\n";
archivo.close();
}


void ajustarParametros(Parametros& parametros, double ocupacion) {

    if(ocupacion >= parametros.umbralAlerta) {

        parametros.umbralAlerta -= 5.0;

        if(parametros.umbralAlerta < 60.0) {
            parametros.umbralAlerta = 60.0;
        }

        std::cout << "Ocupacion elevada. " << "Se aumento la prevencion.\n";
    }

    else if(ocupacion < 50.0) {

        parametros.umbralAlerta += 2.0;
        if(parametros.umbralAlerta > 85.0) {
            parametros.umbralAlerta = 85.0;
        }

        std::cout << "Ocupacion baja. "<< "Se redujo la prevencion.\n";
    }
    std::cout << "Nuevo umbral preventivo: "<< parametros.umbralAlerta << "%\n";
    guardarParametros(parametros);
}
void guardarParametros(const Parametros& parametros) {

    std::ofstream archivo("parametros.txt");

    if(!archivo.is_open()) {
        std::cout << "Error al guardar los parametros.\n";
        return;
    }

    archivo << parametros.umbralAlerta << "\n";
    archivo << parametros.tiempoMaxEspera << "\n";

    archivo.close();
}
void cargarParametros(Parametros& parametros) {

    std::ifstream archivo("parametros.txt");

    if(!archivo.is_open()) {
        std::cout << "No existe historial de parametros. "
                  << "Se utilizaran los valores iniciales.\n";
        return;
    }

    archivo >> parametros.umbralAlerta;
    archivo >> parametros.tiempoMaxEspera;

    if(!archivo || parametros.umbralAlerta < 60.0 ||
       parametros.umbralAlerta > 85.0 ||
       parametros.tiempoMaxEspera <= 0) {

        parametros.umbralAlerta = 80.0;
        parametros.tiempoMaxEspera = 10.0;

        std::cout << "Parametros invalidos. "
                  << "Se restauraron los valores iniciales.\n";
    }
    archivo.close();
}
