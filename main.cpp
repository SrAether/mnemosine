#include <QApplication>

// para la interfaz grafica
#include "ventana.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ventana w;
    //w.setWindowIcon(QIcon("/home/aether/Proyectos/Mnemosine/iconos/botonOcultar.png"));
    w.show();
    return a.exec();
}
