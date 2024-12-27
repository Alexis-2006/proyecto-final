#include <iostream> 
#include <cstdlib> 
#include <ctime> 
using namespace std; 
struct Especie { 
    string nombre; 
    int poblacion; 
    int tasaReproduccion; 
    int tasaMortalidad; 
}; 

void mostrarMenu(); 
void mostrarEstado(const Especie &depredador, const Especie &presa); 
void simularCiclo(Especie &depredador, Especie &presa); 
void reproducir(Especie &especie); 
void cazar(Especie &depredador, Especie &presa); 
void cazarFurtiva(Especie &depredador); 

int main() { 
    srand(static_cast<unsigned>(time(0))); // Para generar números aleatorios 
 
    Especie depredador = {"Otorongo", 10, 2, 1}; 
    Especie presa = {"Venado", 50, 5, 2}; 
 
    int opcion; 
    do { 
        mostrarMenu(); 
        cin >> opcion; 
        switch (opcion) { 
            case 1: 
                mostrarEstado(depredador, presa); 
                break; 
            case 2: 
                simularCiclo(depredador, presa); 
                break; 
            case 3: 
                cazarFurtiva(depredador); 
                break; 
            case 4: 
                cout << "Saliendo del programa..." << endl; 
                break; 
            default: 
                cout << "Opción no válida. Intente de nuevo." << endl; 
        } 
    } while (opcion != 4); 
 
    return 0; 
} 
 
void mostrarMenu() { 
    cout << "\n--- Simulación de Ecosistema ---\n"; 
    cout << "1. Mostrar estado actual\n"; 
    cout << "2. Simular un ciclo\n"; 
    cout << "3. Simular caza furtiva de depredadores\n"; 
    cout << "4. Salir\n"; 
    cout << "Seleccione una opción: "; 
} 

void mostrarEstado(const Especie &depredador, const Especie &presa) { 
    cout << "\nEstado actual del ecosistema:\n"; 
    cout << depredador.nombre << " - Población: " << depredador.poblacion << endl; 
    cout << presa.nombre << " - Población: " << presa.poblacion << endl; 
} 

 

void simularCiclo(Especie &depredador, Especie &presa) { 
    reproducir(depredador); 
    reproducir(presa); 
    cazar(depredador, presa);
    if (depredador.poblacion < 0) depredador.poblacion = 0; 
    if (presa.poblacion < 0) presa.poblacion = 0; 
    cout << "\nSe ha completado un ciclo de simulación.\n"; 

} 

void reproducir(Especie &especie) { 
    int nuevosIndividuos = (rand() % (especie.tasaReproduccion + 1)); 
    especie.poblacion += nuevosIndividuos; 
    cout << especie.nombre << " se ha reproducido. Nuevos individuos: " << nuevosIndividuos << endl; 

} 

void cazar(Especie &depredador, Especie &presa) { 

    int presasCazadas = (rand() % (depredador.tasaMortalidad + 1)); 
    presa.poblacion -= presasCazadas; 
    depredador.poblacion += presasCazadas / 2; // Supongamos que cada presa cazada mejora la supervivencia de depredadores 
    cout << depredador.nombre << " ha cazado " << presasCazadas << " " << presa.nombre << "." << endl; 
} 

void cazarFurtiva(Especie &depredador) { 
    int cazados = (rand() % 3) + 1; 
    depredador.poblacion -= cazados; 
    cout << "Caza furtiva: " << cazados << " " << depredador.nombre << " han sido cazados ilegalmente.\n"; 
} 
