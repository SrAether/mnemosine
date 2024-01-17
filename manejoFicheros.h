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
    std::vector<std::string> extraerFicheros(std::string nombreCarpeta, bool ocultos = false);
    void eliminarFichero(std::string nombreFichero);
    bool existeCarpeta(const std::string& nombreCarpeta);
    void verificacionInicial(const std::string& nombreCarpeta);
    void copiarFichero(const std::string& origen, const std::string& destino);
    void copiarCarpeta(const std::string& origen, const std::string& destino);
    bool compararStringConFichero(const std::string& string, const std::string& fichero);
    std::string extraerString(std::string& cadena, const std::string& dato);
    bool existeFichero(const std::string& nombreFichero);
    // --Metodo que realiza la copia de notas de un fichero a otro pero las procesa para cambiar las rutas de las imagenes de las notas
    void copiarFicheroNotas(const std::string& origen, const std::string& destino);
    // --Metodo que procesa las notas para cambiar las rutas de las imagenes
    void procesarNotas(std::string& entrada, std::string nuevaRuta, std::string viejaRuta);
    // --Metodo para extraer la fecha de creacion de un fichero
    std::string extraerFechaCreacion(const std::string& nombreFichero);
    // --Metodo para extraer la fecha de modificacion de un fichero
    std::string extraerFechaModificacion(const std::string& nombreFichero);

};
#endif // MANEJOFICHEROS_H
