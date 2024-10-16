#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <mutex>
#include <iomanip>  // Para la salida formateada
#include <algorithm>  // Para ordenar los resultados
#include <ctime>  // Para obtener el tiempo actual

using namespace std;

mutex mtx;
int lugar = 0;  // Para controlar el lugar de llegada

// Estructura para almacenar el resultado de cada auto
struct Resultado {
    int id;
    int lugar;
};

// Vector global para almacenar los resultados
vector<Resultado> resultados;

void carrera(int id, int distancia_total) {
    int distancia_recorrida = 0;
    while (distancia_recorrida < distancia_total) {
        int avance = rand() % 10 + 1; // Avance entre 1 y 10 metros
        int tiempo = rand() % 400 + 100; // Pausa entre 100 y 500 ms

        this_thread::sleep_for(chrono::milliseconds(tiempo));

        distancia_recorrida += avance;
        if (distancia_recorrida > distancia_total) {
            distancia_recorrida = distancia_total;
        }

        // Bloquear para mostrar información de forma sincronizada
        mtx.lock();
        cout << "Auto" << id << " avanza " << avance << " metros (total: " 
             << distancia_recorrida << " metros)" << endl;
        mtx.unlock();
    }

    // Registrar el lugar de llegada
    mtx.lock();
    lugar++;
    cout << "\033[1;32mAuto" << id << " avanza " << (distancia_total - distancia_recorrida) << " metros y termina la carrera en el lugar " << lugar << "!\033[0m" << endl;
    resultados.push_back({id, lugar});
    mtx.unlock();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <distancia_total> <numero_autos>" << endl;
        return 1;
    }

    // Inicializar la semilla del generador de números aleatorios
    srand(time(0));

    int distancia_total = atoi(argv[1]);
    int numero_autos = atoi(argv[2]);

    cout << "Distancia total carrera: " << distancia_total << " metros" << endl;
    vector<thread> autos;

    for (int i = 0; i < numero_autos; ++i) {
        autos.push_back(thread(carrera, i, distancia_total));
    }

    for (auto& t : autos) {
        t.join();
    }

    // Mostrar los resultados finales en una tabla
    cout << "\nLugar\tAuto" << endl;
    cout << "-----------------" << endl;

    // Ordenar los resultados por lugar
    sort(resultados.begin(), resultados.end(), [](const Resultado& a, const Resultado& b) {
        return a.lugar < b.lugar;
    });

    // Imprimir los resultados
    for (const auto& resultado : resultados) {
        cout << resultado.lugar << "\tAuto" << resultado.id << endl;
    }

    return 0;
}
