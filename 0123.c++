#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>
using namespace std;

// Constantes globales
const int TASAS_REPRODUCCION_PRED = 3;
const int TASAS_MORTALIDAD_PRED = 2;

// Excepción personalizada
class SimulacionException : public exception {
    string mensaje;

public:
    explicit SimulacionException(const string &mensaje) : mensaje(mensaje) {}
    const char *what() const noexcept override {
        return mensaje.c_str();
    }
};

// Clase base: Especie
class Especie {
protected:
    string nombre;
    int poblacion;
    int tasaReproduccion;
    int tasaMortalidad;
    vector<int> historialPoblacion;

public:
    Especie(string nombre, int poblacion, int tasaReproduccion = TASAS_REPRODUCCION_PRED, int tasaMortalidad = TASAS_MORTALIDAD_PRED)
        : nombre(nombre), poblacion(poblacion), tasaReproduccion(tasaReproduccion), tasaMortalidad(tasaMortalidad) {
        historialPoblacion.push_back(poblacion);
    }

    virtual void reproducir() {
        int nuevosIndividuos = (rand() % (tasaReproduccion + 1));
        poblacion += nuevosIndividuos;
        cout << nombre << " se ha reproducido. Nuevos individuos: " << nuevosIndividuos << endl;
    }

    virtual void cazar(Especie &presa) {
        int presasCazadas = (rand() % (tasaMortalidad + 1));
        presa.poblacion -= presasCazadas;
        poblacion += presasCazadas / 2;
        cout << nombre << " ha cazado " << presasCazadas << " " << presa.nombre << "." << endl;
    }

    void registrarPoblacionHistorial() {
        historialPoblacion.push_back(poblacion);
    }

    int calcularPromedio() const {
        int suma = 0;
        for (int p : historialPoblacion) {
            suma += p;
        }
        return historialPoblacion.empty() ? 0 : suma / historialPoblacion.size();
    }

    static void cazarFurtiva(Especie &otorongo, Especie &lobo) {
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

    friend class Simulacion;
};

// Subclase Depredador
class Depredador : public Especie {
public:
    Depredador(string nombre, int poblacion, int tasaReproduccion = TASAS_REPRODUCCION_PRED, int tasaMortalidad = TASAS_MORTALIDAD_PRED)
        : Especie(nombre, poblacion, tasaReproduccion, tasaMortalidad) {}

    void cazar(Especie &presa) override {
        cout << nombre << " está cazando... ";
        Especie::cazar(presa);
    }
};

// Subclase Herbivoro
class Herbivoro : public Especie {
public:
    Herbivoro(string nombre, int poblacion, int tasaReproduccion, int tasaMortalidad = 0)
        : Especie(nombre, poblacion, tasaReproduccion, tasaMortalidad) {}

    void reproducir() override {
        cout << nombre << " se reproduce rápidamente por ser herbívoro.\n";
        Especie::reproducir();
    }

    void cazar(Especie &presa) override {
        cout << nombre << " no caza porque es herbívoro.\n";
    }
};

// Clase Simulacion
class Simulacion {
private:
    Depredador otorongo;
    Depredador lobo;
    Herbivoro venado;

public:
    Simulacion()
        : otorongo("Otorongo", 20, 2, 1),
          lobo("Lobo", 30, 3, 1),
          venado("Venado", 50, 5, 0) {}

    void mostrarEstado() {
        cout << "\nEstado actual del ecosistema:\n";
        cout << otorongo.nombre << " - Poblacion: " << otorongo.poblacion
             << ", Promedio historico: " << otorongo.calcularPromedio() << endl;
        cout << lobo.nombre << " - Poblacion: " << lobo.poblacion
             << ", Promedio historico: " << lobo.calcularPromedio() << endl;
        cout << venado.nombre << " - Poblacion: " << venado.poblacion
             << ", Promedio historico: " << venado.calcularPromedio() << endl;
    }

    void simularCiclo() {
        otorongo.reproducir();
        lobo.reproducir();
        venado.reproducir();
        otorongo.cazar(venado);
        lobo.cazar(venado);

        if (otorongo.poblacion < 0) otorongo.poblacion = 0;
        if (lobo.poblacion < 0) lobo.poblacion = 0;
        if (venado.poblacion < 0) venado.poblacion = 0;

        otorongo.registrarPoblacionHistorial();
        lobo.registrarPoblacionHistorial();
        venado.registrarPoblacionHistorial();

        cout << "\nSe ha completado un ciclo de simulación.\n";
    }

    void cazarFurtiva() {
        Especie::cazarFurtiva(otorongo, lobo);
    }
};

// Manejo de usuarios
string usuarioRegistrado = "";
string contrasenaRegistrada = "";

void registrarUsuario() {
    if (!usuarioRegistrado.empty()) {
        cout << "Ya existe un usuario registrado. No es posible registrar otro.\n";
        return;
    }

    cout << "Ingrese un nombre de usuario: ";
    cin >> usuarioRegistrado;

    cout << "Ingrese una contrasena: ";
    cin >> contrasenaRegistrada;

    cout << "Usuario registrado con exito.\n";
}

bool iniciarSesion() {
    if (usuarioRegistrado.empty()) {
        cout << "No hay usuarios registrados. Por favor, registre un usuario primero.\n";
        return false;
    }

    string usuario, contrasena;
    cout << "Ingrese su nombre de usuario: ";
    cin >> usuario;

    cout << "Ingrese su contrasena: ";
    cin >> contrasena;

    if (usuario == usuarioRegistrado && contrasena == contrasenaRegistrada) {
        cout << "Inicio de sesion exitoso. ¡Bienvenido!\n";
        return true;
    } else {
        cout << "Usuario o contrasena incorrectos.\n";
        return false;
    }
}

void mostrarMenu() {
    cout << "\n--- Simulacion de Ecosistema ---\n";
    cout << "1. Mostrar estado actual\n";
    cout << "2. Simular un ciclo\n";
    cout << "3. Simular caza furtiva de depredadores\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Simulacion simulacion;

    int opcion;

    // Menú para registro e inicio de sesión
    do {
        cout << "\nMenu de usuario:\n";
        cout << "1. Registrarse\n";
        cout << "2. Iniciar sesion\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarUsuario();
                break;
            case 2:
                if (iniciarSesion()) {
                    goto simulacionMenu;
                }
                break;
            case 3:
                cout << "Saliendo del programa.\n";
                return 0;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 3);

simulacionMenu:
    // Menú de simulación del ecosistema
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                simulacion.mostrarEstado();
                break;
            case 2:
                simulacion.simularCiclo();
                break;
            case 3:
                simulacion.cazarFurtiva();
                break;
            case 4:
                cout << "Saliendo de la simulación...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}