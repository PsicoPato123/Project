    #include <iostream>
    #include <string>
    #include <ctime> //conocida por Web y ChatGPT
    #include "colors.h"
    #include <fstream>
    #include <cctype>
    #include "inteligencia.h"

    struct carro{
        std::string placa;
        time_t entrada;
        int fila, columna;
    };

void guardarVehiculos(carro* lista, int total);
 //funcion de guardado de los registros en un archivo de texto
 void archivo(std::string texto){
    std::ofstream file("registro.txt", std::ios::app);

    if(file.is_open()){
        file << texto << std::endl;
        std::cout << "Registro guardado correctamente.\n";
        file.close();
    }
    else{
        std::cout << "Error al abrir registro.txt\n";
    }
}
void EstructuraMapa(std::string** mapa, int fila, int columna){

    // Bordes o paredes
    for(int i = 0; i < fila; i++){
        for(int j = 0; j < columna; j++){
            mapa[i][j] = "P";
        }
    }
    // Calles de circulación
    for(int i = 1; i < fila - 1; i++){
        for(int j = 1; j < columna - 1; j++){
            mapa[i][j] = "V";
        }
    }
    // Cinco modulos de parqueadero
    for(int modulo = 0; modulo < 5; modulo++){
        int fila1 = 1 + modulo * 4;
        int fila2 = fila1 + 2;

        for(int j = 1; j <= 10; j++){
            mapa[fila1][j] = "L";
            mapa[fila2][j] = "L";
        }
    }
    // Accesos de circulacion a los modulos
        for(int i = 2; i < 20; i += 4){
            mapa[i][18] = "V";
}
    // Via principal de circulacion
        for(int i = 1; i < fila - 1; i++){
            mapa[i][19] = "v";
        } 
    // Entrada y salida
        mapa[0][12] = "E";
        mapa[fila - 1][columna - 2] = "S";
    // Conexion de entrada
        for(int j = 13; j < 20; j++){
            mapa[0][j] = ">";
        }
        mapa[fila - 1][19] = ">";

}
        //Creación de función que haga visible el mapa
    void MostrarMapa(std::string** mapa, int fila, int columna){
        std::ofstream file("Mapa.txt");
            //Se define la estructura y división del mapa
        std::cout << "\n   ";
            for(int j = 0; j < columna; j++){
            std::cout << j+1 << " ";  //número de columnas
                }
            std::cout << std::endl;

        for(int i = 0; i < fila; i++){
            char letra = 'A' + i; //Conversión de la letra conforme avanza (ChatGPT)
            std::cout << letra << " | ";

        for(int j = 0; j < columna; j++){
            //Brinda color al mapa segun el área
                if(mapa[i][j] == "P"){
                    std::cout<<GRAY<<"P "<<RESET;
                    file<<"P ";
                } else if(mapa[i][j] == "V"){
                    std::cout<<YELLOW<<"V "<<RESET;
                    file<<"V ";
                } else if(mapa[i][j] == "L"){
                    std::cout<<WHITE<<"L "<<RESET;
                    file<<"L ";
                }  else if(mapa[i][j] == ">"){
                    std::cout << GREEN << "> " << RESET;
                    file << "> "
                ;}  else if(mapa[i][j] == "<"){
                    std::cout << GREEN << "< " << RESET;
                    file << "< ";
                }else if(mapa[i][j] == "v"){
                    std::cout << GREEN << "v " << RESET;
                    file << "v ";
                } else if(mapa[i][j] == "E"){
                    std::cout<<BLUE<<"E "<<RESET;
                    file<<"E ";
                } else if(mapa[i][j] == "S"){
                    std::cout<<MAGENTA<<"S "<<RESET;
                    file<<"S ";
                } else if(mapa[i][j] == "O"){
                    std::cout<<CYAN<<"O "<<RESET;
                    file<<"O ";
                    }}
            std::cout << std::endl;
            file<<std::endl;
    }
    file.close();   
}
    //Función para contar los espacios disponibles 
    void Disponible (std::string** mapa, int fila, int columna){ 
        int libre = 0, ocupado= 0; 
        for(int i = 0; i < fila; i++){ 
            for(int j = 0; j < columna; j++){
                if(mapa[i][j] == "L") libre++; 
                else if(mapa[i][j] == "O") ocupado++;
    }} 

        int total = libre + ocupado;
                std::cout << "\nDisponibles: " << libre;
                std::cout << "\nOcupados: " << ocupado;
                std::cout << "\nTotal de parqueaderos: " << total << std::endl;

                double porcentaje = calcularOcupacion(ocupado, total);
                Estado estado = evaluarEstado(porcentaje);
                mostrarSemaforo(porcentaje, estado);
            }
    //Función para ingresar un vehículo al parqueadero
    void ingresovehiculo(std::string** mapa,carro* lista, int fila, int columna, int& total, Parametros& parametros){
        std::string placa, pos;
        std::cout << "Ingrese la placa del paticarro: ";
        std::cin >> placa;
        std::cout << "Ingrese la posición de parqueo (Ejemplo: A1): ";
        std::cin >> pos;
        for(int i = 0; i < total; i++){
            if(lista[i].placa == placa){
            std::cout << "Esta placa ya esta registrada.\n";
            return;
    }
}
       if(pos.length() < 2){
            std::cout << "Formato invalido\n";
            return;
}

    if(!isalpha(pos[0])){
            std::cout << "Formato invalido\n";
            return;
}

        for(int i = 1; i < pos.length(); i++){
            if(!isdigit(pos[i])){
            std::cout << "Formato invalido\n";
        return;
    } }
        time_t now = time(0);
        char* fecha = ctime(&now);

        std::string registro= "Entrada - Placa: " + placa +
                  " - Pos: " + pos + //posición
                  " - Hora: " + std::string(fecha); //hora

        char letra = toupper(pos[0]); // Extracción de la letra
        int numero = std::stoi(pos.substr(1)); // Extracción del número

        if(letra < 'A' || letra > 'J' || numero < 1 || numero > 10){
            std::cout << "Posicion invalida\n";
            return;
            }
// Convertir el código a coordenadas reales
        int filas = (letra - 'A') * 2 + 1;
        int columnas = (numero - 1) * 2 + 1;

        if(filas < 0 || filas >= fila || columnas < 0 || columnas >= columna){
            std::cout << "Posicion invalida\n";
            return;
        }
        if(mapa[filas][columnas] != "L"){
            std::cout << "No disponible :c\n";
            return;
        }

        //registro del vehiculo en el sistema
        if(total >= (fila * columna)){
            std::cout << "No hay capacidad para registrar mas vehiculos.\n";
            return;
        }
        mapa[filas][columnas] = "O"; // Marca el espacio como ocupado
        lista[total].placa = placa;
        lista[total].entrada = time(0);
        lista[total].fila = filas;
        lista[total].columna = columnas;
        total++; 
        archivo(registro);
        guardarVehiculos(lista, total);
        double porcentaje = calcularOcupacion(total, 100);
            registrarMetricas(total, 100, porcentaje); 
            ajustarParametros(parametros, porcentaje);

        std::cout << "Paticarro registrado con éxito :D" << std::endl;
    }
    //función para calcular la tarifa de acuerdo al tiempo de parqueo
    int calcularTarifa(carro* lista, int fila, int columna, int total){
        time_t salida = time(0); 
        for(int i = 0; i < total; i++){
            if(lista[i].fila == fila && lista[i].columna == columna){
                double horas = difftime(salida, lista[i].entrada)/3600; // Conversión a horas
                int tarifa = (horas * 6000); // Tarifa de $6000 por hora
                return tarifa;
            }
        }
        return 0; // Si no se encuentra el vehículo, no se cobra
    }
    //función para retirar un vehículo del parqueadero y cobro de tarifa 
void retirovehiculo(std::string** mapa, carro* lista, int fila, int columna, int& total, Parametros& parametros){
    int opcion;
    std::string dato;

    std::cout << "\n¿Cómo desea buscar el paticarro?\n";
    std::cout << "1. Por placa\n";
    std::cout << "2. Por puesto\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

        if(opcion != 1 && opcion != 2){
            std::cout << "Opcion invalida.\n";
            return;
        }
        if(opcion == 1){
            std::cout << "Ingrese la placa: ";
        }
        else{
            std::cout << "Ingrese el puesto (Ejemplo A1): ";
        }
        std::cin >> dato;

    bool encontrado = false;
    bool coincide = false;     
        // Cálculo de tarifa
        for(int i = 0; i < total; i++){
            if(opcion == 1){
            coincide = (lista[i].placa == dato);
            }
            else if(opcion == 2){

                if(dato.length() < 2){
                    std::cout << "Formato de puesto invalido.\n";
                    return;
                }

                char letra = toupper(dato[0]);
                int numero = std::stoi(dato.substr(1));

                if(letra < 'A' || letra > 'J' || numero < 1 || numero > 10){
                    std::cout << "Puesto invalido.\n";
                    return;
                }

                int f = (letra - 'A') * 2 + 1;
                int c = (numero - 1) * 2 + 1;

                coincide = (lista[i].fila == f && lista[i].columna == c);
            }
            if(coincide){
                int f = lista[i].fila;
                int c = lista[i].columna;

                int costo = calcularTarifa (lista, f, c, total);
                std::string placaRetirada = lista[i].placa;
                
                mapa[f][c] = "L"; // Libera el puesto

                std::cout << "Paticarro de placa " << placaRetirada<< " retirado del parqueadero." << std::endl;

                std::cout << "Valor a pagar: $" << costo << "\n";

                // Eliminar vehículo de la lista
                lista[i] = lista[total - 1];
                total--;

                guardarVehiculos(lista, total);

                // Registrar la salida en el historial
                time_t now = time(0);
                char* fecha = ctime(&now);

                double horas = costo/6000.0;

                std::string registro = "SALIDA - Placa: " + placaRetirada +
                    " - Tiempo: " + std::to_string(horas) +
                    " horas - Pago: $" + std::to_string(costo) +
                    " - Hora: " + std::string(fecha);

                archivo(registro);

                // Registrar ocupacion actualizada en el sistema inteligente
                double porcentaje = calcularOcupacion(total, 100);
                registrarMetricas(total, 100, porcentaje);
                ajustarParametros(parametros, porcentaje);

                encontrado = true;
                break;
            }
        }
           if(!encontrado){
           std::cout << "No se encontro el paticarro solicitado."<< std::endl;}
         }
    
         //Creación de menú
    int menu(std::string** mapa, int fila, int columna,carro* lista, int& total, Parametros& parametros){
        int opt;
        std::cout<<"Bienvenido a tu Pati-adero Cuack"<<std::endl;
        do{ 
        std::cout<<"1. Ingresar Pati-vehiculo"<<std::endl;
        std::cout<<"2. Retirar Pati-vehiculo"<<std::endl;
        std::cout<<"3. Revisar Pati-espacios"<<std::endl;
        std::cout<<"4. Mostrar Pati-mapa"<<std::endl;
        std::cout<<"5. Informe historico de patiocupacion\n";
        std::cout<<"6. Pati-salida\n";
        std::cout<<"Selecciona una Pati-opcion: \n";
        std::cin>>opt;

        switch (opt){
        case 1:
        ingresovehiculo(mapa,lista,fila, columna, total, parametros);
            break;
        case 2: 
        retirovehiculo(mapa, lista, fila, columna, total, parametros);
            break;
        case 3:
        Disponible(mapa, fila, columna);
            break;
        case 4:
        MostrarMapa(mapa, fila, columna);
            break;
        case 5:
        analizarMetricas();
            break;
        case 6:
        std::cout<<"Hasta luego visitante ^w^ ";
        break;
        default:
        std::cout<<"Opción inválida X.X \n"; RESET;  
            break;};}
        while (opt !=6); 
        return 0;
        }

void guardarVehiculos(carro* lista, int total){
    std::ofstream archivoVehiculos("vehiculos.txt");

    if(!archivoVehiculos.is_open()){
        std::cout << "No se pudo guardar los vehiculos.\n";
        return;
    }
    for(int i = 0; i < total; i++){
        archivoVehiculos << lista[i].placa << " "
                << lista[i].entrada << " "
                << lista[i].fila << " "
                << lista[i].columna << "\n";
    }
    archivoVehiculos.close();
}
void cargarVehiculos(std::string** mapa, carro* lista, int fila, int columna, int& total){
    std::ifstream archivoVehiculos("vehiculos.txt");
    if(!archivoVehiculos.is_open()){
        return;
    }

    std::string placa;
    time_t entrada;
    int f, c;

    while(archivoVehiculos >> placa >> entrada >> f >> c){
        if(total >= fila * columna){
            break;
        }
        if(f < 0 || f >= fila || c < 0 || c >= columna){
            continue;
        }
        if(mapa[f][c] != "L"){
            continue;
        }

        lista[total].placa = placa;
        lista[total].entrada = entrada;
        lista[total].fila = f;
        lista[total].columna = c;

        mapa[f][c] = "O";
        total++;
    }
    archivoVehiculos.close();
}
    int main (){  
        //Creación del mapa dinámico
        int fila =22; 
        int columna=22;
        std::string** mapa = new std::string*[fila];
        carro* lista = new carro[fila*columna]; // Lista para registrar los vehículos, tamaño máximo igual al número de espacios
        int total = 0; // Contador de vehículos registrados
        Parametros parametros;
        cargarParametros(parametros);
        
        for(int i = 0; i < fila; i++){
            mapa[i] = new std::string[columna];
        }

        //Aplicación de funciones
        EstructuraMapa(mapa,fila, columna);
        cargarVehiculos(mapa, lista, fila, columna, total); // Carga los vehículos registrados previamente
        menu(mapa, fila, columna, lista, total, parametros);

        for(int i = 0; i < fila; i++){
        delete[] mapa[i];
        }
        delete[] mapa;
        delete[] lista;
        return 0;
    }