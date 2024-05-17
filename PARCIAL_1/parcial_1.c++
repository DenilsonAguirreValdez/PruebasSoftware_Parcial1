#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert> 


std::vector<std::string> determinarRuta(bool tienda_abierta, bool ofertas_especiales, const std::vector<std::string>& productos) {
    // Inicialización
    std::vector<std::string> ruta;
    std::vector<std::string> pasos;
    std::unordered_map<std::string, std::unordered_set<std::string>> secciones = {
        {"lacteos", {"leche", "queso", "yogur"}},
        {"frutas_y_verduras", {"manzana", "banana", "lechuga"}},
        {"carnes", {"pollo", "res", "cerdo"}},
        {"ofertas", {"cereal", "detergente"}}
    };

    // Función para determinar la sección del primer producto
    auto determinarSeccion = [&](const std::string& producto) -> int {
        if (secciones["lacteos"].count(producto)) return 1;
        if (secciones["frutas_y_verduras"].count(producto)) return 2;
        if (secciones["carnes"].count(producto)) return 3;
        return 4;  // otras_secciones
    };

    // Condiciones If
    if (tienda_abierta) {
        pasos.push_back("Paso 1: La tienda está abierta.");

        if (ofertas_especiales) {
            // Añade la sección de ofertas a la ruta si hay ofertas especiales
            ruta.push_back("ofertas");
            pasos.push_back("Paso 2: Hay ofertas especiales - Añadir 'ofertas' a la ruta.");
        } else {
            // Añade una ruta estándar si no hay ofertas especiales
            ruta.push_back("entrada");
            pasos.push_back("Paso 2: No hay ofertas especiales - Añadir 'entrada' a la ruta.");
        }

        // Condición Switch
        std::string primer_producto = productos[0];
        switch (determinarSeccion(primer_producto)) {
            case 1:
                ruta.push_back("lacteos");
                pasos.push_back("Caso 1: El primer producto es de la sección 'lácteos' - Añadir 'lácteos' a la ruta.");
                break;
            case 2:
                ruta.push_back("frutas_y_verduras");
                pasos.push_back("Caso 2: El primer producto es de la sección 'frutas y verduras' - Añadir 'frutas y verduras' a la ruta.");
                break;
            case 3:
                ruta.push_back("carnes");
                pasos.push_back("Caso 3: El primer producto es de la sección 'carnes' - Añadir 'carnes' a la ruta.");
                break;
            case 4:
                ruta.push_back("otras_secciones");
                pasos.push_back("Caso 4: El primer producto es de 'otras secciones' - Añadir 'otras secciones' a la ruta.");
                break;
        }

        // Bucle While
        std::vector<std::string> productos_restantes = productos;
        int paso_num = 3;
        while (!productos_restantes.empty()) {
            std::string producto_actual = productos_restantes.front();
            productos_restantes.erase(productos_restantes.begin());
            for (const auto& seccion : secciones) {
                if (seccion.second.count(producto_actual)) {
                    if (std::find(ruta.begin(), ruta.end(), seccion.first) == ruta.end()) {
                        ruta.push_back(seccion.first);
                        pasos.push_back("Paso " + std::to_string(++paso_num) + ": Encontrar '" + producto_actual + "' en la sección '" + seccion.first + "' - Añadir '" + seccion.first + "' a la ruta.");
                    }
                }
            }
        }

        // Retorno de la ruta completa
        pasos.push_back("Ruta generada: ");
        for (const auto& seccion : ruta) {
            pasos.back() += seccion + " ";
        }
        return pasos;
    } else {
        return {"Paso 1: La tienda está cerrada."};
    }
}


    // COBERTURA 100%

void pruebaCamino1() {
    bool tienda_abierta = true;
    bool ofertas_especiales = false;
    std::vector<std::string> productos = {"leche", "pollo", "manzana", "cereal"};

    std::vector<std::string> resultado_esperado = {
        "Paso 1: La tienda está abierta.",
        "Paso 2: No hay ofertas especiales - Añadir 'entrada' a la ruta.",
        "Caso 1: El primer producto es de la sección 'lácteos' - Añadir 'lácteos' a la ruta.",
        "Paso 4: Encontrar 'pollo' en la sección 'carnes' - Añadir 'carnes' a la ruta.",
        "Paso 5: Encontrar 'manzana' en la sección 'frutas_y_verduras' - Añadir 'frutas_y_verduras' a la ruta.",
        "Paso 6: Encontrar 'cereal' en la sección 'ofertas' - Añadir 'ofertas' a la ruta.",
        "Ruta generada: entrada lácteos carnes frutas_y_verduras ofertas "
    };

    std::vector<std::string> ruta_generada = determinarRuta(tienda_abierta, ofertas_especiales, productos);
    assert(ruta_generada == resultado_esperado);
}

void pruebaCamino2() {
    bool tienda_abierta = true;
    bool ofertas_especiales = false;
    std::vector<std::string> productos = {"manzana", "pollo", "leche", "cereal"};

    std::vector<std::string> resultado_esperado = {
        "Paso 1: La tienda está abierta.",
        "Paso 2: No hay ofertas especiales - Añadir 'entrada' a la ruta.",
        "Caso 2: El primer producto es de la sección 'frutas y verduras' - Añadir 'frutas y verduras' a la ruta.",
        "Paso 4: Encontrar 'pollo' en la sección 'carnes' - Añadir 'carnes' a la ruta.",
        "Paso 5: Encontrar 'leche' en la sección 'lacteos' - Añadir 'lacteos' a la ruta.",
        "Paso 6: Encontrar 'cereal' en la sección 'ofertas' - Añadir 'ofertas' a la ruta.",
        "Ruta generada: entrada frutas_y_verduras carnes lacteos ofertas "
    };

    std::vector<std::string> ruta_generada = determinarRuta(tienda_abierta, ofertas_especiales, productos);
    assert(ruta_generada == resultado_esperado);
}

void pruebaCamino3() {
    bool tienda_abierta = true;
    bool ofertas_especiales = false;
    std::vector<std::string> productos = {"pollo", "manzana", "leche", "cereal"};

    std::vector<std::string> resultado_esperado = {
        "Paso 1: La tienda está abierta.",
        "Paso 2: No hay ofertas especiales - Añadir 'entrada' a la ruta.",
        "Caso 3: El primer producto es de la sección 'carnes' - Añadir 'carnes' a la ruta.",
        "Paso 4: Encontrar 'manzana' en la sección 'frutas_y_verduras' - Añadir 'frutas_y_verduras' a la ruta.",
        "Paso 5: Encontrar 'leche' en la sección 'lacteos' - Añadir 'lacteos' a la ruta.",
        "Paso 6: Encontrar 'cereal' en la sección 'ofertas' - Añadir 'ofertas' a la ruta.",
        "Ruta generada: entrada carnes frutas_y_verduras lacteos ofertas "
    };

    std::vector<std::string> ruta_generada = determinarRuta(tienda_abierta, ofertas_especiales, productos);
    assert(ruta_generada == resultado_esperado);
}


void pruebaCamino4() {
    bool tienda_abierta = true;
    bool ofertas_especiales = false;
    std::vector<std::string> productos = {"cereal", "pollo", "leche", "manzana"};

    std::vector<std::string> resultado_esperado = {
        "Paso 1: La tienda está abierta.",
        "Paso 2: No hay ofertas especiales - Añadir 'entrada' a la ruta.",
        "Caso 4: El primer producto es de 'otras secciones' - Añadir 'otras secciones' a la ruta.",
        "Paso 4: Encontrar 'pollo' en la sección 'carnes' - Añadir 'carnes' a la ruta.",
        "Paso 5: Encontrar 'leche' en la sección 'lacteos' - Añadir 'lacteos' a la ruta.",
        "Paso 6: Encontrar 'manzana' en la sección 'frutas_y_verduras' - Añadir 'frutas_y_verduras' a la ruta.",
        "Ruta generada: entrada otras_secciones carnes lacteos frutas_y_verduras "
    };

    std::vector<std::string> ruta_generada = determinarRuta(tienda_abierta, ofertas_especiales, productos);
    assert(ruta_generada == resultado_esperado);
}


void pruebaCamino5() {
    bool tienda_abierta = true;
    bool ofertas_especiales = true;
    std::vector<std::string> productos = {"manzana", "pollo", "leche", "cereal"};

    std::vector<std::string> resultado_esperado = {
        "Paso 1: La tienda está abierta.",
        "Paso 2: Hay ofertas especiales - Añadir 'ofertas' a la ruta.",
        "Paso 4: Encontrar 'pollo' en la sección 'carnes' - Añadir 'carnes' a la ruta.",
        "Paso 5: Encontrar 'leche' en la sección 'lacteos' - Añadir 'lacteos' a la ruta.",
        "Paso 6: Encontrar 'manzana' en la sección 'frutas_y_verduras' - Añadir 'frutas_y_verduras' a la ruta.",
        "Paso 7: Encontrar 'cereal' en la sección 'ofertas' - Añadir 'ofertas' a la ruta.",
        "Ruta generada: ofertas carnes lacteos frutas_y_verduras ofertas "
    };

    std::vector<std::string> ruta_generada = determinarRuta(tienda_abierta, ofertas_especiales, productos);
    assert(ruta_generada == resultado_esperado);
}


void pruebaCamino6() {
    bool tienda_abierta = false;
    bool ofertas_especiales = false;
    std::vector<std::string> productos = {"manzana", "pollo", "leche", "cereal"};

    std::vector<std::string> resultado_esperado = {
        "Paso 1: La tienda está cerrada."
    };

    std::vector<std::string> ruta_generada = determinarRuta(tienda_abierta, ofertas_especiales, productos);
    assert(ruta_generada == resultado_esperado);
}
