#ifndef MANEJOFICHEROS_H
#define MANEJOFICHEROS_H
#include <string>
#include <vector>
class ManejoFicheros
{
public:
    ManejoFicheros();
    ~ManejoFicheros();
    void escribirFichero(std::string nombreFichero, std::string texto);
    std::string leerFichero(std::string nombreFichero);
    std::vector<std::string> extraerFicheros(std::string nombreCarpeta);
    void eliminarFichero(std::string nombreFichero);
    bool existeCarpeta(const std::string& nombreCarpeta);
    void verificacionInicial(const std::string& nombreCarpeta);
    void copiarFichero(const std::string& origen, const std::string& destino);
    bool compararStringConFichero(const std::string& string, const std::string& fichero);
};
#endif // MANEJOFICHEROS_H
