#include "manejoFicheros.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <filesystem>

ManejoFicheros::ManejoFicheros()
{

}

ManejoFicheros::~ManejoFicheros()
{

}

void ManejoFicheros::escribirFichero(std::string nombreFichero, std::string texto)
{
    std::ofstream fichero(nombreFichero);
    if (!fichero.is_open())
    {
        throw std::runtime_error("No se pudo abrir el fichero");
    }
    fichero << texto;
    fichero.close();
}

std::string ManejoFicheros::leerFichero(std::string nombreFichero)
{
    std::ifstream fichero(nombreFichero);
    if (!fichero.is_open())
    {
        throw std::runtime_error("No se pudo abrir el fichero");
    }
    std::string texto;
    std::string linea;
    while (std::getline(fichero, linea))
    {
        texto += linea + "\n";
    }
    fichero.close();
    return texto;
}

std::vector<std::string> ManejoFicheros::extraerFicheros(std::string nombreCarpeta)
{
    std::vector<std::string> archivos;

    // Leemos la carpeta ficheros y guardamos los nombres de todos los archivos
    // creamos un puntero DIR
    DIR *dir; // puntero a la carpeta
    struct dirent *ent; // estructura para los elementos dentro de la carpeta

    // Abrimos la carpeta
    dir = opendir(nombreCarpeta.c_str());
    if (dir == nullptr)
    {
        throw std::runtime_error("No se pudo abrir la carpeta");
    }
    // Lee los archivos dentro de la carpeta
    while ((ent = readdir(dir)) != nullptr) {
        std::string nombreArchivo = ent->d_name;

        // Ignora los directorios "." y ".."
        if (nombreArchivo != "." && nombreArchivo != "..") {
            archivos.push_back(nombreArchivo);
        }
    }

    // Cerramos la carpeta
    closedir(dir);

    return archivos;

}


void ManejoFicheros::eliminarFichero(std::string nombreFichero)
{
    try {
        std::filesystem::remove_all(nombreFichero);
    } catch (const std::exception& e) {
        throw std::runtime_error("No se pudo eliminar el fichero");
        //std::cerr << "Error al eliminar el directorio: " << e.what() << std::endl;

    }

}


bool ManejoFicheros::existeCarpeta(const std::string& ruta)
{
    struct stat info;
    if(stat(ruta.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}




void ManejoFicheros::verificacionInicial(const std::string& nombreCarpeta) {
    try {
        // Verificamos si la carpeta existe
        if (!std::filesystem::exists(nombreCarpeta)) {
            // Si no existe, la creamos
            std::filesystem::create_directory(nombreCarpeta);
            //std::cout << "Carpeta creada: " << nombreCarpeta << std::endl;
        } else {
            //std::cout << "La carpeta ya existe: " << nombreCarpeta << std::endl;
        }
    } catch (const std::exception& e) {
        //std::cerr << "Error al verificar/inicializar la carpeta: " << e.what() << std::endl;
        throw std::runtime_error("No se pudo verificar/inicializar la carpeta");
    }
}


void ManejoFicheros::copiarFichero(const std::string& origen, const std::string& destino) {
    try {
        std::filesystem::copy_file(origen, destino, std::filesystem::copy_options::overwrite_existing);
        //std::cout << "Archivo copiado de " << origen << " a " << destino << std::endl;
        // cerramos el fichero

    } catch (const std::exception& e) {
        throw std::runtime_error("No se pudo copiar el fichero");
        //std::cerr << "Error al copiar el archivo: " << e.what() << std::endl;
    }
}


bool ManejoFicheros::compararStringConFichero(const std::string& string, const std::string& fichero) {
    try {
        std::string textoFichero = leerFichero(fichero);
        if (textoFichero == string) {
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        throw std::runtime_error("No se pudo comparar el string con el fichero");
        //std::cerr << "Error al comparar el string con el fichero: " << e.what() << std::endl;
    }
}