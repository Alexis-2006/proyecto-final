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
void mostrarEstado(const Especie &otorongo, const Especie &lobo, const Especie &venado);
void simularCiclo(Especie &otorongo, Especie &lobo, Especie &venado);
void reproducir(Especie &especie);
void cazar(Especie &depredador, Especie &presa);
void cazarFurtiva(Especie &otorongo, Especie &lobo);

int main() {
    srand(static_cast<unsigned>(time(0))); // cantidad de las especiaes 

    Especie otorongo = {"Otorongo", 20, 2, 1};
    Especie lobo = {"Lobo", 30, 3, 1};
    Especie venado = {"Venado", 50, 5, 2};

    int opcion;
    string pass;
    int intentos = 0;
//generamos el login
    cout << "Ingrese la contraseña: ";
    do {
        
        cin >> pass;
        intentos++;

        if (intentos > 2) {
            cout << "Acceso denegado ☻" << endl;
            exit(1);
        } else if (pass == "123") {
            cout << "Contraseña correcta ↓↓↓\n";
            break;
        }
        cout<<"contraseña incorrecta, intente denuevo \n";
    } while (true);

    // Menú
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarEstado(otorongo, lobo, venado);
                break;
            case 2:
                simularCiclo(otorongo, lobo, venado);
                break;
            case 3:
                cazarFurtiva(otorongo, lobo);
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

void mostrarEstado(const Especie &otorongo, const Especie &lobo, const Especie &venado) {
    cout << "\nEstado actual del ecosistema:\n";
    cout << otorongo.nombre << " - Población: " << otorongo.poblacion << endl;
    cout << lobo.nombre << " - Población: " << lobo.poblacion << endl;
    cout << venado.nombre << " - Población: " << venado.poblacion << endl;
}
/*en esta opcion los animales e pueden reproducir entre ellos 
en este caso el co depredador no mpuene matar al depredador */
void simularCiclo(Especie &otorongo, Especie &lobo, Especie &venado) {
    reproducir(otorongo);
    reproducir(lobo);
    reproducir(venado);
    cazar(otorongo, venado);
    cazar(lobo, venado);

    if (otorongo.poblacion < 0) otorongo.poblacion = 0;
    if (lobo.poblacion < 0) lobo.poblacion = 0;
    if (venado.poblacion < 0) venado.poblacion = 0;

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
    depredador.poblacion += presasCazadas / 2; // Cada presa mejora la supervivencia del depredador
    cout << depredador.nombre << " ha cazado " << presasCazadas << " " << presa.nombre << "." << endl;
}
/*los animales son atacados son atacados por el sador y ellos pueden 
atacar al casador pero pueden escaparce o ser matados por el casador */
void cazarFurtiva(Especie &otorongo, Especie &lobo) {
    int atacante = rand() % 2; // 0 para Otorongo, 1 para Lobo
    int resultado = rand() % 2; // 0 para cazador gana, 1 para animal gana

    if (atacante == 0) {
        cout << "Caza furtiva con Otorongo...\n";
        if (resultado == 0) {
            otorongo.poblacion--;
            cout << "El cazador ha matado a un Otorongo.\n";
        } else {
            cout << "¡El Otorongo ha atacado al cazador y escapado!\n";
        }
    } else {
        cout << "Caza furtiva con Lobo...\n";
        if (resultado == 0) {
            lobo.poblacion--;
            cout << "El cazador ha matado a un Lobo.\n";
        } else {
            cout << "¡El Lobo ha atacado al cazador y escapado!\n";
        }
    }
}
