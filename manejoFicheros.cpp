#include "manejoFicheros.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <filesystem>
#include <algorithm>
#include <ctime>

//#include <algorithm> // Para std::trim
#include <cctype>    // Para std::isspace

// para debug
#include <iostream>

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

// std::vector<std::string> ManejoFicheros::extraerFicheros(std::string nombreCarpeta)
// {
//     std::vector<std::string> archivos;

//     // Leemos la carpeta ficheros y guardamos los nombres de todos los archivos
//     // creamos un puntero DIR
//     DIR *dir; // puntero a la carpeta
//     struct dirent *ent; // estructura para los elementos dentro de la carpeta

//     // Abrimos la carpeta
//     dir = opendir(nombreCarpeta.c_str());
//     if (dir == nullptr)
//     {
//         throw std::runtime_error("No se pudo abrir la carpeta");
//     }
//     // Lee los archivos dentro de la carpeta
//     while ((ent = readdir(dir)) != nullptr) {
//         std::string nombreArchivo = ent->d_name;

//         // Ignora los directorios "." y ".."
//         if (nombreArchivo != "." && nombreArchivo != "..") {
//             archivos.push_back(nombreArchivo);
//         }
//     }

//     // Cerramos la carpeta
//     closedir(dir);

//     return archivos;

// }


bool compararFechas(const std::string &archivo1, const std::string &archivo2, const std::string &nombreCarpeta) {
    struct stat atributos1, atributos2;
    std::string rutaArchivo1 = nombreCarpeta + "/" + archivo1;
    std::string rutaArchivo2 = nombreCarpeta + "/" + archivo2;

    stat(rutaArchivo1.c_str(), &atributos1);
    stat(rutaArchivo2.c_str(), &atributos2);

    return atributos1.st_mtime < atributos2.st_mtime;
}

std::vector<std::string> ManejoFicheros::extraerFicheros(std::string nombreCarpeta, bool ocultos) {
    std::vector<std::string> archivos;

    // Leemos la carpeta ficheros y guardamos los nombres de todos los archivos
    DIR *dir;
    struct dirent *ent;

    dir = opendir(nombreCarpeta.c_str());
    if (dir == nullptr) {
        throw std::runtime_error("No se pudo abrir la carpeta");
    }

    while ((ent = readdir(dir)) != nullptr) {
        std::string nombreArchivo = ent->d_name;

        if (nombreArchivo != "." && nombreArchivo != "..") {
            archivos.push_back(nombreArchivo);
        }
    }

    closedir(dir);

    // Ordenar los archivos por fecha de creación
    std::sort(archivos.begin(), archivos.end(), [nombreCarpeta](const std::string &a, const std::string &b) {
        return compararFechas(a, b, nombreCarpeta);
    });

    // Eliminar los archivos ocultos
    if (!ocultos) {
        archivos.erase(std::remove_if(archivos.begin(), archivos.end(), [](const std::string &archivo) {
            return archivo[0] == '.';
        }), archivos.end());
    }

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
        //std::filesystem::copy_file(origen, destino, std::filesystem::copy_options::overwrite_existing);
        //std::cout << "Archivo copiado de " << origen << " a " << destino << std::endl;
        // cerramos el fichero

        // copiamos el archivo
        std::filesystem::copy(origen, destino, std::filesystem::copy_options::overwrite_existing);

    } catch (const std::exception& e) {
        throw std::runtime_error("No se pudo copiar el fichero");
        //std::cerr << "Error al copiar el archivo: " << e.what() << std::endl;
    }
}


bool ManejoFicheros::compararStringConFichero(const std::string& str, const std::string& fichero) {
    try {
        std::string textoFichero = leerFichero(fichero);

        // Eliminar espacios en blanco al principio y al final
        std::string textoFicheroTrimmed;
        for (char c : textoFichero) {
            if (!std::isspace(c)) {
                textoFicheroTrimmed += c;
            }
        }

        std::string strTrimmed;
        for (char c : str) {
            if (!std::isspace(c)) {
                strTrimmed += c;
            }
        }

        // Realizar la comparación
        return (textoFicheroTrimmed == strTrimmed);
    } catch (const std::exception& e) {
        // Si no se puede leer el fichero, devuelve false y lanza una excepción
        std::cerr << "No se pudo comparar el string con el fichero: " << e.what() << std::endl;
        return false;
    }
}

std::string ManejoFicheros::extraerString(std::string& cadena, const std::string& dato) {
    try {
        std::size_t pos = cadena.find(dato);
        if (pos != std::string::npos) {
            cadena.erase(pos, dato.length());
            return cadena;
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("No se pudo extraer el string");
        //std::cerr << "Error al extraer el string: " << e.what() << std::endl;
    }
    return "";
}

bool ManejoFicheros::existeFichero(const std::string& nombreFichero) {
    try {
        if (std::filesystem::exists(nombreFichero)) {
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        throw std::runtime_error("No se pudo verificar si existe el fichero");
        //std::cerr << "Error al verificar si existe el fichero: " << e.what() << std::endl;
        return false;
    }
}


void ManejoFicheros::copiarFicheroNotas(const std::string& origen, const std::string& destino)
{
    // primero abrimos el fichero origen
    // verificamos que exista el fichero de origen
    if (!this->existeFichero(origen))
    {
        throw std::runtime_error("No existe el fichero de origen");
    }
    // abrimos el fichero origen y extraemos sus ficheros de notas
    std::vector<std::string> ficheros = this->extraerFicheros(origen);
    // creamos un vector de string que contendra los nombres de los ficheros de notas
    std::vector<std::string> ficherosNotas;
    // recorremos el vector de ficheros de notas y verificamos que sean ficheros de notas
    for (std::string fichero : ficheros)
    {
        // extraemos el nombre de la nota es decir lo que esta despues del ultimo /
        std::string nombreNota = fichero.substr(fichero.find_last_of("/") + 1);
        //std::cout << "nombreNota: " << nombreNota << std::endl;
        // las notas tienen extension .tak por lo que añádimos .tak al nombre de la nota
        nombreNota += ".tak";
        // mostramos como queda fichero mas nombre nota
        //std::cout << "fichero + nombreNota: " << fichero + "/" + nombreNota << std::endl;
        // verificamos que exista el fichero de nota lo que implica que sea una nota
        if (this->existeFichero(origen + "/" + fichero + "/" + nombreNota))
        {
            // añadimos el nombre de la nota al vector de ficheros de notas
            ficherosNotas.push_back(origen + "/" + fichero + "/" + nombreNota);
        }
    }
    // creamos la carpeta de destino
    this->verificacionInicial(destino);
    // llamamos al metodo que procesa las notas
    for (std::string fichero : ficherosNotas)
    {
        // extraemos el texto de la nota
        std::string textoNota = this->leerFichero(fichero);
        // procesamos el texto de la nota
        //this->procesarNotas(textoNota, destino, origen);
        // el origen es la ruta de fichero hasta el ultimo /
        std::string origenNota = fichero.substr(0, fichero.find_last_of("/"));
        this->procesarNotas(textoNota, destino, origenNota);
        // creamos el fichero de la nueva nota
        // extraemos el nombre de la nota
        //std::string nombreNota = fichero.substr(fichero.find_last_of("/") + 1);
        // creamos el fichero de la nota en la nueva ruta
        //std::string nuevaNota = destino + "/" + nombreNota;
        // creamos la carpeta de la nota
        //this->verificacionInicial(
    }
}

void ManejoFicheros::procesarNotas(std::string& entrada, std::string nuevaRuta, std::string viejaRuta)
{

    // nueva ruta
    std::cout << "nuevaRuta: " << nuevaRuta << std::endl;
    // vieja ruta
    std::cout << "viejaRuta: " << viejaRuta << std::endl;
    // extraemos el nombre de la nota que es lo que se encuentra despues del ultimo /
    std::string nombreNota = viejaRuta.substr(viejaRuta.find_last_of("/") + 1);
    std::cout << "nombreNota: " << nombreNota << std::endl;
    // creamos la carpeta de la nota en la nueva ruta
    std::string nuevaCarpeta = nuevaRuta + "/" + nombreNota;
    std::cout << "nuevaCarpeta: " << nuevaCarpeta << std::endl;
    this->verificacionInicial(nuevaCarpeta);

    // copiamos todo el contenido de la carpeta de la nota a la nueva carpeta para mover las imagenes
    this->copiarCarpeta(viejaRuta, nuevaCarpeta);

     // es momento de procesar el texto de la nota, la nota contiene texto en html
    // ya temos el texto de la nota en la variable entrada
    // tenemos que iterar sobre el texto de la nota y extraer las imagenes
    // las imagenes estan entre <img src=" y "
    // buscamos el primer <img src="

    // extraemos el tamaño del texto de la nota
    int tamanoEntrada = entrada.length();
    // creamos un nuevo string que contendra el texto de la nota procesado
    std::string textoProcesado = "";

    // creamos un entero que guardara la posicion de la ocurrencia actual
    int posActual = 0;



    // ciclo para modificar el texto de la nota
    while (true)
    {
        // demos tener en cuenta que es lo que se planea remplazar
        // pretendemos remplarazar el contenido de la cadena viejaRuta por nuevaRuta
        // por lo que debemos buscar la cadena viejaRuta dentro de la cadena entrada
        // buscamos la primera ocurrencia de viejaRuta a partir de la posicion actual
        int posImg = entrada.find(viejaRuta, posActual);
        // verificamos que la posicion no sea -1
        if (size_t(posImg) == std::string::npos)
        {
            // si es -1 significa que no se encontro ninguna ocurrencia
            // por lo que salimos del ciclo
            break;
        }
        // si no es -1 significa que se encontro una ocurrencia
        // pasamos la cadena desde posActual hasta posImg a la variable textoProcesado
        textoProcesado += entrada.substr(posActual, posImg - posActual);
        // agregamos la nueva ruta
        textoProcesado += nuevaRuta + "/" + nombreNota;
        // refrescamos la posicion actual añádiendole el tamaño de la vieja ruta
        posActual = posImg + viejaRuta.length();

    }


    // agregamos el texto restante
    textoProcesado += entrada.substr(posActual, tamanoEntrada - posActual);


    // mostramos el texto de entrada
    std::cout << "entrada: " << entrada << std::endl;
    // mostrar el texto procesado
    std::cout << "textoProcesado: " << textoProcesado << std::endl;

    // escribimos el texto procesado en el fichero de la nota
    this->escribirFichero(nuevaCarpeta + "/" + nombreNota + ".tak", textoProcesado);


}


void ManejoFicheros::copiarCarpeta(const std::string& source, const std::string& destination) {
    std::filesystem::path sourcePath(source);
    std::filesystem::path destinationPath(destination);

    for (const auto& entry : std::filesystem::directory_iterator(sourcePath)) {
        const auto target = destinationPath / entry.path().filename();
        try {
            if (std::filesystem::is_directory(entry.status())) {
                std::filesystem::create_directory(target);
                copiarCarpeta(entry.path().string(), target.string());
            } else {
                std::filesystem::copy(entry, target, std::filesystem::copy_options::overwrite_existing);
            }
        } catch (const std::exception& e) {
            // Manejo de errores, puedes imprimir un mensaje o lanzar una excepción según tu necesidad.
            std::cerr << "Error al copiar: " << e.what() << std::endl;
        }
    }
}


std::string ManejoFicheros::extraerFechaCreacion(const std::string& nombreFichero)
{
    struct stat info;
    if (stat(nombreFichero.c_str(), &info) != 0) {
        return "";
    }

    // Obtener la fecha de creación en formato legible
    std::time_t tiempoCreacion = info.st_ctime;
    std::tm* tiempoInfo = std::localtime(&tiempoCreacion);

    // Formatear la fecha en una cadena legible
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempoInfo);

    return std::string(buffer);
}


std::string ManejoFicheros::extraerFechaModificacion(const std::string& nombreFichero)
{
    struct stat info;
    if (stat(nombreFichero.c_str(), &info) != 0) {
        return "";
    }

    // Obtener la fecha de modificación en formato legible
    std::time_t tiempoModificacion = info.st_mtime;
    std::tm* tiempoInfo = std::localtime(&tiempoModificacion);

    // Formatear la fecha en una cadena legible
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempoInfo);

    return std::string(buffer);
}
