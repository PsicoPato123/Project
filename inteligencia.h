#ifndef INTELIGENCIA_H
#define INTELIGENCIA_H

#include <string>

enum class Estado {
    VERDE,
    AMARILLO,
    ROJO
};
struct Parametros {
    double umbralAlerta = 80.0;
    double tiempoMaxEspera = 10.0;
};

double calcularOcupacion(int ocupados, int capacidad);
Estado evaluarEstado(double ocupacion);
std::string nombreEstado(Estado estado);

void mostrarSemaforo(double ocupacion, Estado estado);

void registrarMetricas(int ocupados, int capacidad, double ocupacion);
void analizarMetricas();
void ajustarParametros(Parametros& parametros, double ocupacion);
void guardarParametros(const Parametros& parametros);
void cargarParametros(Parametros& parametros);
#endif