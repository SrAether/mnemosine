#include "ventana.h"
#include "manejoFicheros.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QScrollArea>
#include <QLabel>
#include <QFileDialog>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QTextDocumentFragment>
#include <QTextDocument>
#include <QStyleFactory>
// para fuente
#include <QFont>
#include <QFontDialog>
// para color
#include <QColor>
#include <QColorDialog>
// para debug
#include <iostream>
#include <QIcon>
#include <QPixmap>
#include <QSize>
// para eliminar la nota
#include <QMessageBox>
// temporizador para etiqueta accion
#include <QTimer>

// para eventos de teclas
#include <QKeyEvent>

// para imagenes
#include <QImage>
#include <QPixmap>
#include <QBuffer>

#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QTextFragment>


//
#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextImageFormat>
#include <QResizeEvent>
#include <QPixmap>
#include <QDebug>
// para imprimir
#include <QPrinter>
#include <QPrintDialog>

// para sonido
#include <QtMultimedia/QMediaPlayer>


Ventana::Ventana(QWidget *parent)
    : QWidget{parent}
{
    // colocamos el icono de la aplicacion
    this->setWindowIcon(QIcon{"./iconos/MNEMOSINE.ico"});
    // colocamos el icono de la aplicacion en caso de encontrarnos en wayland
    this->setWindowIconText("MNEMOSINE");


    // primero creamos la fuente
    fuente = new QFont{"Orbitron", 12};

    puedoRedimensionarImagenes = true;

    // mostrar notas ocultas
    mostrarNotasOcultas = false;

    // mostrar fechas
    mostrarFechasNotas = true;

    // ruta de carpeta
    nombreCarpeta = "/notas/";

    // ruta de carpeta de configuracion
    nombreCarpetaConfiguracion = new std::string{"./configuracion/"};

    // etiqueta de nombre
    std::string nombre = "Mnemosine";

    // etiqueta de configuracion
    configuracion = "configuracion";

    // etiqueta fecha creacion
    //fechaCreacion = "Fecha de creacion: ";
    // etiqueta fecha modificacion
    fechaModificacion = "Fecha de modificacion: ";

    // etiqueta de accion
    std::string accion = "Se acaba de abrir una nota";


    // --TEMPORIZADORES--
    // temporizador para etiqueta accion de configuracion
    temporizadorAccionConfiguracion = new QTimer{this}; // creamos el temporizador para la accion de configuracion
    temporizadorAccionConfiguracion->setSingleShot(true); // para que solo se ejecute una vez

    // temporizador para etiqueta accion
    temporizadorAccion = new QTimer{this}; // creamos el temporizador para la accion
    temporizadorAccion->setSingleShot(true); // para que solo se ejecute una vez


    // luego creamos el frame que contendra todo
    frame = new QFrame{};
    // le damos estilo cyberpunk con color morado azulado de fondo al frame

    // le damos un fondo oscuro con un gradiente que vaya de azul a purpura
    this->setStyleSheet(QString::fromUtf8("QWidget {\n"
                                          "    /* Establecer un fondo oscuro con un gradiente que vaya de azul a p\303\272rpura */\n"
                                          "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
                                          "                                stop:0 rgb(16, 16, 32), stop:1 rgb(64, 0, 128));\n"
                                          "    /* A\303\261adir un borde con un color ne\303\263n para darle ese aspecto vibrante cyberpunk */\n"
                                          "    border: 0px solid rgb(0, 255, 255);\n"
                                          "padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                          "    /* Aplicar una sombra para dar profundidad */\n"
                                          "    box-shadow: 0 0 8px rgb(0, 255, 255);\n"
                                          "    /* Establecer el color de los textos de la ventana*/\n"
                                          "    color: rgb(0, 255, 255); /* Un color de ne\303\263n brillante */\n"
                                          "}\n"
                                          "QPushButton {\n"
                                          "    color: rgb(224, 224, 224);\n"
                                          "    text-shadow: 0 0 4px rgb(0, 255, 255);\n"
                                          "    border: 1px solid rgb(64, 64, 128);\n"
                                          "    transition: transform 0.1s ease; /* Agrega una transición suave para el efecto de transformación */"

                                          "}\n"
                                          "QPushButton:hover {\n"
                                          "    border-color: rgb(0, 255, 255);\n"
                                          "    background-color: rgb(64, 0, 128);\n"
                                          "    color: rgb(255, 255, 255);\n"
                                          "    text-shadow: 0 0 6px rgb(0, 255, 255);\n"
                                          "    transform: scale(1.1); /* Aumenta ligeramente el tamaño del botón */"
                                          "}\n"
                                          ));


    // luego creamos el frame que contendra el menu
    frameMenu = new QFrame{frame};
    frameMenu->setStyleSheet(QString::fromUtf8("QWidget {\n"
                                               "    /* Establecer un fondo oscuro con un gradiente que vaya de azul a p\303\272rpura */\n"
                                               "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
                                               "                                stop:0 rgb(16, 16, 32), stop:1 rgb(64, 0, 128));\n"
                                               "    /* A\303\261adir un borde con un color ne\303\263n para darle ese aspecto vibrante cyberpunk */\n"
                                               "    border: 1px solid rgb(0, 255, 255);\n"
                                               "    border-radius: 5px; /* Esquinas redondeadas para un aspecto moderno */\n"
                                               "    padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                               "    /* Aplicar una sombra para dar profundidad */\n"
                                               "    box-shadow: 0 0 8px rgb(0, 255, 255);\n"
                                               "}\n"
                                               "\n"
                                               "/* Estilizar botones con un efecto de ne\303\263n al pasar el rat\303\263n por encima */\n"
                                               "QPushButton {\n"
                                               "    color: rgb(224, 224, 224);\n"
                                               "    text-shadow: 0 0 4px rgb(0, 255, 255);\n"
                                               "    border: 1px solid rgb(64, 64, 128);\n"
                                               "    transition: transform 0.1s ease; /* Agrega una transición suave para el efecto de transformación */\n"
                                               "}\n"
                                               "\n"
                                               "QPushButton:hover {\n"
                                               "    border-color: rgb(0, 255, 255);\n"
                                               "    background-color: rgb(64, 0, 128);\n"
                                               "    color: rgb(255, 255, 255);\n"
                                               "    text-shadow: 0 0 6px rgb(0, 255, 255);\n"
                                               "    transform: scale(1.1); /* Aumenta ligeramente el tamaño del botón */\n"
                                               "}\n"
                                               "\n"
                                               "QLabel {\n"
                                               "    /* Colo"
                                               "r de texto y sombra */\n"
                                               "    color: rgb(0, 255, 255); /* Un color de ne\303\263n brillante */\n"
                                               "    text-shadow: 1px 1px rgb(0, 128, 128); /* Sombra para darle profundidad al texto */\n"
                                               "\n"
                                               "    /* Fuente y tama\303\261o */\n"
                                               "    font-family: 'Orbitron', sans-serif; /* Cambia a tu fuente deseada si Orbitron no est\303\241 disponible */\n"
                                               "    font-size: 14pt; /* Ajusta el tama\303\261o seg\303\272n tus necesidades */\n"
                                               "    font-weight: bold; /* Fuente en negrita para un impacto visual fuerte */\n"
                                               "\n"
                                               "    /* Otras propiedades de estilo */\n"
                                               "    background-color: rgba(0, 0, 0, 0.5); /* Fondo semitransparente */\n"
                                               "    border: 1px solid rgb(0, 255, 255); /* Borde con un color de ne\303\263n */\n"
                                               "    padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                               "    border-radius: 5px; /* Esquinas redondeadas para un aspecto moderno */\n"
                                               "}\n"
                                               "\n"
                                               "QListWidget {\n"
                                               "    /* Color de texto y sombra */\n"
                                               "    color: rgb(0, 255, 255); /* Un color de ne\303\263n brillante */\n"
                                               "    text-shadow: 1px 1px rgb(0, 128, 128); /* Sombra para darle profundidad al texto */\n"
                                               "\n"
                                               "    /* Fuente y tama\303\261o */\n"
                                               "    font-family: 'Orbitron', sans-serif; /* Cambia a tu fuente deseada si Orbitron no est\303\241 disponible */\n"
                                               "    font-size: 10pt; /* Ajusta el tama\303\261o seg\303\272n tus necesidades */\n"
                                               "    font-weight: bold; /* Fuente en negrita para un impacto visual fuerte */\n"
                                               "\n"
                                               "    /* Otras propiedades de estilo */\n"
                                               "    background-color: rgba(0, 0, 0, 0.5); /* Fondo semitransparente */\n"
                                               "    border: 0px solid rgb(0, 255, 255); /* Borde con un color de ne\303\263n */\n"
                                               "    padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                               "    border-radius: 5px; /* Esquinas redondeadas para un aspecto moderno */\n"
                                               "}\n"));


    // luego creamos el frame que contendra el contenido
    frameContenido = new QFrame{frame};
    frameContenido->setStyleSheet(QString::fromUtf8("QWidget {\n"
                                                    "    /* Establecer un fondo oscuro con un gradiente que vaya de azul a p\303\272rpura */\n"
                                                    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
                                                    "                                stop:0 rgb(16, 16, 32), stop:1 rgb(64, 0, 128));\n"
                                                    "    /* A\303\261adir un borde con un color ne\303\263n para darle ese aspecto vibrante cyberpunk */\n"
                                                    "    border: 1px solid rgb(0, 255, 255);\n"
                                                    "    border-radius: 5px; /* Esquinas redondeadas para un aspecto moderno */\n"
                                                    "    padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                                    "    /* Aplicar una sombra para dar profundidad */\n"
                                                    "    box-shadow: 0 0 8px rgb(0, 255, 255);\n"
                                                    "}\n"
                                                    "QFrame {\n"
                                                    "    /* Fondo y borde */\n"
                                                    "    background-color: rgb(0, 0, 0); /* Un fondo oscuro para facilitar la lectura */\n"
                                                    "    border: 2px solid rgb(0, 255, 255); /* Borde de color ne\303\263n */\n"
                                                    "    border-radius: 10px; /* Esquinas redondeadas */\n"
                                                    "\n"
                                                    "    /* Espaciado */\n"
                                                    "    padding: 2px; /* Espaciado interno para que el texto no toque el borde */\n"
                                                    "}\n"
                                                    "\n"
                                                    "QTextEdit {\n"
                                                    "    /* Color de texto y fondo */\n"
                                                    "    color: rgb(180, 180, 180); /* Color claro para el texto, pero no puro blanco */\n"
                                                    "    background-color: rgba(0, 0, 0, 0.3); /* Fondo ligeramente transparente para un efecto cyberpunk */\n"
                                                    "\n"
                                                    "    /* Fuente y tama\303\261o */\n"
                                                    "    font-family: 'Orbitron', 'Courier New', monospace; /* Fuente de ancho fijo para alinear el texto */\n"
                                                    "    font-size: 12pt; /* Tama\303\261o de fuente adecuado para la lectura */\n"
                                                    "\n"
                                                    "    /* Sombra para el texto */\n"
                                                    "    text-shadow: 1px 1px rgb(0, 128, 128); /* Sombra suave para hacer resaltar el texto */\n"
                                                    "}\n"
                                                    "/* Estilizar botones con un efecto de ne\303\263n al pasar el rat\303\263n por encima */\n"
                                                    "QPushButton {\n"
                                                    "    color: rgb(224, 224, 224);\n"
                                                    "    text-shadow: 0 0 4px rgb(0, 255, 255);\n"
                                                    "    border: 1px solid rgb(64, 64, 128);\n"
                                                    "    transition: transform 0.1s ease; /* Agrega una transición suave para el efecto de transformación */\n"
                                                    "}\n"
                                                    "\n"
                                                    "QPushButton:hover {\n"
                                                    "    border-color: rgb(0, 255, 255);\n"
                                                    "    background-color: rgb(64, 0, 128);\n"
                                                    "    color: rgb(255, 255, 255);\n"
                                                    "    text-shadow: 0 0 6px rgb(0, 255, 255);\n"
                                                    "    transform: scale(1.1); /* Aumenta ligeramente el tamaño del botón */\n"
                                                    "}\n"
                                                    "\n"
                                                    ""));


    // luego creamos el frame que contendra las opciones de configuracion
    frameConfiguracion = new QFrame{frame};
    frameConfiguracion->setStyleSheet(QString::fromUtf8("QWidget {\n"
                                                        "    /* Establecer un fondo oscuro con un gradiente que vaya de azul a p\303\272rpura */\n"
                                                        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
                                                        "                                stop:0 rgb(16, 16, 32), stop:1 rgb(64, 0, 128));\n"
                                                        "    /* A\303\261adir un borde con un color ne\303\263n para darle ese aspecto vibrante cyberpunk */\n"
                                                        "    border: 1px solid rgb(0, 255, 255);\n"
                                                        "    border-radius: 5px; /* Esquinas redondeadas para un aspecto moderno */\n"
                                                        "    padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                                        "    /* Aplicar una sombra para dar profundidad */\n"
                                                        "    box-shadow: 0 0 8px rgb(0, 255, 255);\n"
                                                        "}\n"
                                                        "QFrame {\n"
                                                        "    /* Fondo y borde */\n"
                                                        "    background-color: rgb(0, 0, 0); /* Un fondo oscuro para facilitar la lectura */\n"
                                                        "    border: 2px solid rgb(0, 255, 255); /* Borde de color ne\303\263n */\n"
                                                        "    border-radius: 10px; /* Esquinas redondeadas */\n"
                                                        "\n"
                                                        "    /* Espaciado */\n"
                                                        "    padding: 2px; /* Espaciado interno para que el texto no toque el borde */\n"
                                                        "}\n"
                                                        "\n"
                                                        "QTextEdit {\n"
                                                        "    /* Color de texto y fondo */\n"
                                                        "    color: rgb(180, 180, 180); /* Color claro para el texto, pero no puro blanco */\n"
                                                        "    background-color: rgba(0, 0, 0, 0.3); /* Fondo ligeramente transparente para un efecto cyberpunk */\n"
                                                        "\n"
                                                        "    /* Fuente y tama\303\261o */\n"
                                                        "    font-family: 'Orbitron', 'Courier New', monospace; /* Fuente de ancho fijo para alinear el texto */\n"
                                                        "    font-size: 12pt; /* Tama\303\261o de fuente adecuado para la lectura */\n"
                                                        "\n"
                                                        "    /* Sombra para el texto */\n"
                                                        "    text-shadow: 1px 1px rgb(0, 128, 128); /* Sombra suave para hacer resaltar el texto */\n"
                                                        "}\n"
                                                        "/* Estilizar botones con un efecto de ne\303\263n al pasar el rat\303\263n por encima */\n"
                                                        "QPushButton {\n"
                                                        "    color: rgb(224, 224, 224);\n"
                                                        "    text-shadow: 0 0 4px rgb(0, 255, 255);\n"
                                                        "    border: 1px solid rgb(64, 64, 128);\n"
                                                        "    transition: transform 0.1s ease; /* Agrega una transición suave para el efecto de transformación */\n"
                                                        "}\n"
                                                        "\n"
                                                        "QPushButton:hover {\n"
                                                        "    border-color: rgb(0, 255, 255);\n"
                                                        "    background-color: rgb(64, 0, 128);\n"
                                                        "    color: rgb(255, 255, 255);\n"
                                                        "    text-shadow: 0 0 6px rgb(0, 255, 255);\n"
                                                        "    transform: scale(1.1); /* Aumenta ligeramente el tamaño del botón */\n"
                                                        "}\n"
                                                        "\n"
                                                        ""));
    frameConfiguracion->hide();


    // luego cargamos las imagenes de los botones
    iconoOcultar = new QPixmap{"./iconos/botonOcultar.png"};
    iconoMostrar = new QPixmap{"./iconos/botonAmpliar.png"};
    iconoNuevaNota = new QPixmap{"./iconos/botonNuevaNota.png"};
    iconoGuardarNota = new QPixmap{"./iconos/botonGuardarNota.png"};
    iconoEliminarNota = new QPixmap{"./iconos/botonEliminarNota.png"};
    iconoAgregarImagen = new QPixmap{"./iconos/botonAgregarImagen.png"};
    iconoCambiarFuente = new QPixmap{"./iconos/botonCambiarFuente.png"};
    iconoCambiarColor = new QPixmap{"./iconos/botonCambiarColor.png"};
    iconoCambiarColorFondo = new QPixmap{"./iconos/botonCambiarColorFondo.png"};
    iconoConfiguracion = new QPixmap{"./iconos/botonConfiguracion.jpeg"};
    iconoImprimir = new QPixmap{"./iconos/botonImprimir.jpeg"};
    // --ICONOS CONFIGURACION--
    iconoSeleccionarRutaBoveda = new QPixmap{"./iconos/botonCarpeta.jpeg"};
    iconoSeleccionarNombreBoveda = new QPixmap{"./iconos/botonBoveda.jpeg"};
    iconoMostrarNotasOcultas = new QPixmap{"./iconos/botonMostrarNotasOcultas.jpeg"};





    // fijamos el tamaño de los botones (iconos de los mismos)
    tamBoton = 50;

    // --AREA DE INICIALIZACION DE BOTONES--

    // boton ocultar <-- FRAME MENU
    botonOcultar = new QPushButton{frameMenu};
    botonOcultar->setGeometry(0, 0, tamBoton, tamBoton);
    botonOcultar->setFont(*fuente);
    botonOcultar->setIcon(QIcon{*iconoOcultar});
    botonOcultar->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonOcultar->setMaximumSize(tamBoton, tamBoton);
    botonOcultar->setToolTip("Ocultar lista de notas \n Ctrl + O");

    // boton mostrar <-- FRAME CONTENIDO
    botonMostrar = new QPushButton{frameContenido};
    botonMostrar->setGeometry(5, 10, tamBoton, tamBoton);
    botonMostrar->setFont(*fuente);
    botonMostrar->setIcon(QIcon{*iconoMostrar});
    botonMostrar->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonMostrar->setMaximumSize(tamBoton, tamBoton);
    botonMostrar->setToolTip("Mostrar lista de notas \n Ctrl + M");
    botonMostrar->hide();


    // boton nueva nota <-- FRAME MENU
    botonNuevaNota = new QPushButton{frameMenu};
    botonNuevaNota->setGeometry(0, 50, tamBoton, tamBoton);
    botonNuevaNota->setFont(*fuente);
    botonNuevaNota->setIcon(QIcon{*iconoNuevaNota});
    botonNuevaNota->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonNuevaNota->setMaximumSize(tamBoton, tamBoton);
    botonNuevaNota->setToolTip("Nueva nota \n Ctrl + N");

    // boton guardar nota <-- FRAME MENU
    botonGuardarNota = new QPushButton{frameMenu};
    botonGuardarNota->setGeometry(0, 100, tamBoton, tamBoton);
    botonGuardarNota->setFont(*fuente);
    botonGuardarNota->setIcon(QIcon{*iconoGuardarNota});
    botonGuardarNota->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonGuardarNota->setMaximumSize(tamBoton, tamBoton);
    botonGuardarNota->setToolTip("Guardar \n Ctrl + S");

    // boton guardar nota 2 <-- FRAME CONTENIDO
    botonGuardarNota2 = new QPushButton{frameContenido};
    botonGuardarNota2->setGeometry(0, 100, tamBoton, tamBoton);
    botonGuardarNota2->setFont(*fuente);
    botonGuardarNota2->setIcon(QIcon{*iconoGuardarNota});
    botonGuardarNota2->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonGuardarNota2->setMaximumSize(tamBoton, tamBoton);
    botonGuardarNota2->setToolTip("Guardar \n Ctrl + S");
    botonGuardarNota2->hide();

    // boton eliminar nota <-- FRAME MENU
    botonEliminarNota = new QPushButton{frameMenu};
    botonEliminarNota->setGeometry(0, 150, tamBoton , tamBoton);
    botonEliminarNota->setFont(*fuente);
    botonEliminarNota->setIcon(QIcon{*iconoEliminarNota});
    botonEliminarNota->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonEliminarNota->setMaximumSize(tamBoton, tamBoton);
    botonEliminarNota->setToolTip("Eliminar nota \n Ctrl + E");

    // boton eliminar nota 2 <-- FRAME CONTENIDO
    botonEliminarNota2 = new QPushButton{frameContenido};
    botonEliminarNota2->setGeometry(0, 150, tamBoton, tamBoton);
    botonEliminarNota2->setFont(*fuente);
    botonEliminarNota2->setIcon(QIcon{*iconoEliminarNota});
    botonEliminarNota2->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonEliminarNota2->setMaximumSize(tamBoton, tamBoton);
    botonEliminarNota2->setToolTip("Eliminar nota \n Ctrl + E");
    botonEliminarNota2->hide();

    // boton para agregar imagen <-- FRAME MENU
    botonAgregarImagen = new QPushButton{frameMenu};
    botonAgregarImagen->setGeometry(0, 200, tamBoton, tamBoton);
    botonAgregarImagen->setFont(*fuente);
    botonAgregarImagen->setIcon(QIcon{*iconoAgregarImagen});
    botonAgregarImagen->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonAgregarImagen->setMaximumSize(tamBoton, tamBoton);
    botonAgregarImagen->setToolTip("Insertar imagen \n Ctrl + I");

    // boton para agregar imagen 2 <-- FRAME CONTENIDO
    botonAgregarImagen2 = new QPushButton{frameContenido};
    botonAgregarImagen2->setGeometry(0, 200, tamBoton, tamBoton);
    botonAgregarImagen2->setFont(*fuente);
    botonAgregarImagen2->setIcon(QIcon{*iconoAgregarImagen});
    botonAgregarImagen2->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonAgregarImagen2->setMaximumSize(tamBoton, tamBoton);
    botonAgregarImagen2->setToolTip("Insertar imagen \n Ctrl + I");
    botonAgregarImagen2->hide();

    // boton para cambiar la fuente <-- FRAME CONTENIDO
    botonCambiarFuente = new QPushButton{frameContenido};
    botonCambiarFuente->setGeometry(0, 250, tamBoton, tamBoton);
    botonCambiarFuente->setFont(*fuente);
    botonCambiarFuente->setIcon(QIcon{*iconoCambiarFuente});
    botonCambiarFuente->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonCambiarFuente->setMaximumSize(tamBoton, tamBoton);
    botonCambiarFuente->setToolTip("Tipo de fuente \n Ctrl + F");
    botonCambiarFuente->hide();

    // boton para cambiar color de texto <-- FRAME CONTENIDO
    botonCambiarColor = new QPushButton{frameContenido};
    botonCambiarColor->setGeometry(0, 300, tamBoton, tamBoton);
    botonCambiarColor->setFont(*fuente);
    botonCambiarColor->setIcon(QIcon{*iconoCambiarColor});
    botonCambiarColor->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonCambiarColor->setMaximumSize(tamBoton, tamBoton);
    botonCambiarColor->setToolTip("Color de texto \n Ctrl + G");
    botonCambiarColor->hide();

    // boton para cambiar color de fondo (resaltar texto) <-- FRAME CONTENIDO
    botonCambiarColorFondo = new QPushButton{frameContenido};
    botonCambiarColorFondo->setGeometry(0, 350, tamBoton, tamBoton);
    botonCambiarColorFondo->setFont(*fuente);
    botonCambiarColorFondo->setIcon(QIcon{*iconoCambiarColorFondo});
    botonCambiarColorFondo->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonCambiarColorFondo->setMaximumSize(tamBoton, tamBoton);
    botonCambiarColorFondo->setToolTip("Resaltar texto \n Ctrl + H");
    botonCambiarColorFondo->hide();

    // boton para imprimir <-- FRAME CONTENIDO
    botonImprimir = new QPushButton{frameContenido};
    botonImprimir->setGeometry(0, 400, tamBoton, tamBoton);
    botonImprimir->setFont(*fuente);
    botonImprimir->setIcon(QIcon{*iconoImprimir});
    botonImprimir->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonImprimir->setMaximumSize(tamBoton, tamBoton);
    botonImprimir->setToolTip("Imprimir \n Ctrl + P");
    botonImprimir->hide();


    // boton para configuracion <-- FRAME CONTENIDO
    botonConfiguracion = new QPushButton{frameContenido};
    botonConfiguracion->setGeometry(0, 400, tamBoton, tamBoton);
    botonConfiguracion->setFont(*fuente);
    botonConfiguracion->setIcon(QIcon{*iconoConfiguracion});
    botonConfiguracion->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonConfiguracion->setMaximumSize(tamBoton, tamBoton);
    botonConfiguracion->setToolTip("Configuracion \n Ctrl + C");
    botonConfiguracion->hide();


    // --BOTONES CONFIGURACION--

    // boton para seleccionar ruta boveda
    botonSeleccionarRutaBoveda = new QPushButton{frameConfiguracion};
    botonSeleccionarRutaBoveda->setGeometry(0, 0, tamBoton, tamBoton);
    botonSeleccionarRutaBoveda->setFont(*fuente);
    botonSeleccionarRutaBoveda->setIcon(QIcon{*iconoSeleccionarRutaBoveda});
    botonSeleccionarRutaBoveda->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    //botonSeleccionarRutaBoveda->setMaximumSize(tamBoton, tamBoton);
    botonSeleccionarRutaBoveda->setMaximumHeight(tamBoton);
    botonSeleccionarRutaBoveda->setToolTip("Seleccionar ruta de la boveda");
    botonSeleccionarRutaBoveda->hide();

    // boton para seleccionar nombre boveda
    botonSeleccionarNombreBoveda = new QPushButton{frameConfiguracion};
    botonSeleccionarNombreBoveda->setGeometry(0, 50, tamBoton, tamBoton);
    botonSeleccionarNombreBoveda->setFont(*fuente);
    botonSeleccionarNombreBoveda->setIcon(QIcon{*iconoSeleccionarNombreBoveda});
    botonSeleccionarNombreBoveda->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonSeleccionarNombreBoveda->setMaximumHeight(tamBoton);
    botonSeleccionarNombreBoveda->setToolTip("Seleccionar nombre de la boveda");
    botonSeleccionarNombreBoveda->hide();

    // boton para ocultar la configuración
    botonOcultarConfiguracion = new QPushButton{frameConfiguracion};
    botonOcultarConfiguracion->setGeometry(0, 50, tamBoton, tamBoton);
    botonOcultarConfiguracion->setFont(*fuente);
    botonOcultarConfiguracion->setIcon(QIcon{*iconoOcultar});
    botonOcultarConfiguracion->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonOcultarConfiguracion->setMaximumSize(tamBoton, tamBoton);
    botonOcultarConfiguracion->hide();


    // boton para mostrar las notas ocultas
    botonMostrarNotasOcultas = new QPushButton{frameConfiguracion};
    botonMostrarNotasOcultas->setGeometry(0, 100, tamBoton, tamBoton);
    botonMostrarNotasOcultas->setFont(*fuente);
    botonMostrarNotasOcultas->setIcon(QIcon{*iconoMostrarNotasOcultas});
    botonMostrarNotasOcultas->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonMostrarNotasOcultas->setMaximumHeight(tamBoton);
    botonMostrarNotasOcultas->setToolTip("Mostrar notas ocultas \" Ctrl + 0 (Cero) \"");
    //botonMostrarNotasOcultas->hide();


    // boton para mostrar las fechas de creacion y modificacion
    botonMostrarFechas = new QPushButton{frameConfiguracion};
    botonMostrarFechas->setGeometry(0, 150, tamBoton, tamBoton);
    botonMostrarFechas->setFont(*fuente);
    botonMostrarFechas->setIcon(QIcon{*iconoMostrarNotasOcultas});
    botonMostrarFechas->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonMostrarFechas->setMaximumHeight(tamBoton);
    botonMostrarFechas->setToolTip("Mostrar fechas de creacion y modificacion de las notas");
    botonMostrarFechas->setText("Mostrar fechas");




    // --ETIQUETAS--

    // --ETIQUETAS CONTENIDO--

    // luego creamos la etiqueta del nombre de la nota
    etiquetaNombre = new QLabel{QString::fromStdString(nombre), frameContenido};
    etiquetaNombre->setFont(*fuente);
    etiquetaNombre->hide();

    // luego creamos la etiqueta de accion de la nota
    etiquetaAccion = new QLabel{QString::fromStdString(accion), frameContenido};
    etiquetaAccion->setFont(*fuente);
    etiquetaAccion->hide();

    // // creamos la etiqueta con la fecha de creacion de la nota
    // etiquetaFechaCreacion = new QLabel{QString::fromStdString(fechaCreacion), frameContenido};
    // etiquetaFechaCreacion->setFont(*fuente);
    // //etiquetaFechaCreacion->hide();

    // creamos la etiqueta con la fecha de modificacion de la nota
    etiquetaFechaModificacion = new QLabel{QString::fromStdString(fechaModificacion), frameContenido};
    etiquetaFechaModificacion->setFont(*fuente);
    //etiquetaFechaModificacion->hide();



    // le damos estilo cyberpunk con color morado azulado
    etiquetaNombre->setStyleSheet(QString::fromUtf8("QLabel {\n"
                                                    "    /* Color de texto y sombra */\n"
                                                    "    color: rgb(0, 255, 255); /* Un color de ne\303\263n brillante */\n"
                                                    "    text-shadow: 1px 1px rgb(0, 128, 128); /* Sombra para darle profundidad al texto */\n"
                                                    "\n"
                                                    "    /* Fuente y tama\303\261o */\n"
                                                    "    font-family: 'Orbitron', sans-serif; /* Cambia a tu fuente deseada si Orbitron no est\303\241 disponible */\n"
                                                    "    font-size: 14pt; /* Ajusta el tama\303\261o seg\303\272n tus necesidades */\n"
                                                    "    font-weight: bold; /* Fuente en negrita para un impacto visual fuerte */\n"
                                                    "\n"
                                                    "    /* Otras propiedades de estilo */\n"
                                                    "    background-color: rgba(0, 0, 0, 0.5); /* Fondo semitransparente */\n"
                                                    "    border: 1px solid rgb(0, 255, 255); /* Borde con un color de ne\303\263n */\n"
                                                    "    padding: 5px; /* Espaciado interior para que el texto no toque los bordes */\n"
                                                    "    border-radius: 5px; /* Esquinas redondeadas para un aspecto moderno */\n"
                                                    "}"));




    // --ETIQUETAS CONFIGURACION--

    // luego creamos la etiqueta de la ruta de la boveda
    etiquetaConfiguracion = new QLabel{QString::fromStdString(configuracion), frameConfiguracion};
    etiquetaConfiguracion->setFont(*fuente);
    // le damos un alto maximo para que no se expanda
    etiquetaConfiguracion->setMaximumHeight(tamBoton);
    etiquetaConfiguracion->hide();
    // luego creamos la etiqueta con el nombre de la boveda
    etiquetaAccionConfiguracion = new QLabel{QString::fromStdString(accionConfiguracion), frameConfiguracion};
    etiquetaAccionConfiguracion->setFont(*fuente);
    // le damos un alto maximo para que no se expanda
    etiquetaAccionConfiguracion->setMaximumHeight(tamBoton);
    etiquetaAccionConfiguracion->hide();



    // creamos el layout de los botones del frameMenu
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(botonOcultar);
    buttonLayout->addWidget(botonNuevaNota);
    buttonLayout->addWidget(botonGuardarNota);
    buttonLayout->addWidget(botonEliminarNota);
    buttonLayout->addWidget(botonAgregarImagen);

    // luego creamos la lista de notas
    listaNotas = new QListWidget{frameMenu};
    listaNotas->setFont(*fuente);

    // QScrollArea para la lista de notas
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(listaNotas);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumWidth(300);

    // Layout vertical en frameMenu que incluye botones y scroll area
    QVBoxLayout *menuLayout = new QVBoxLayout(frameMenu);
    menuLayout->addLayout(buttonLayout);
    menuLayout->addWidget(scrollArea, 1); // El scroll area se expande



    // Configuración del contenido de la nota
    contenidoNota = new QTextEdit{frameContenido};
    contenidoNota->setFont(*fuente);
    contenidoNota->setMinimumSize(600, 400);
    //contenidoNota->setMinimumSize(300, 300);

    // Layout para frameContenido
    QVBoxLayout *contentLayout = new QVBoxLayout(frameContenido);
    QHBoxLayout *contentLayout2 = new QHBoxLayout;
    //QHBoxLayout *contentLayout3 = new QHBoxLayout;
    // CONTENT LAYOUT 2
    contentLayout2->addWidget(botonMostrar);
    contentLayout2->addWidget(botonGuardarNota2);
    contentLayout2->addWidget(botonEliminarNota2);
    contentLayout2->addWidget(botonAgregarImagen2);
    contentLayout2->addWidget(botonCambiarFuente);
    contentLayout2->addWidget(botonCambiarColor);
    contentLayout2->addWidget(botonCambiarColorFondo);
    contentLayout2->addWidget(botonImprimir);
    contentLayout2->addWidget(botonConfiguracion);
    contentLayout2->addWidget(etiquetaNombre);
    contentLayout2->addWidget(etiquetaAccion);
    contentLayout2->addStretch(1);
    contentLayout2->addWidget(etiquetaFechaModificacion);
    //contentLayout->setMargin(0);
    contentLayout->addLayout(contentLayout2);
    // CONTENT LAYOUT 3
    //contentLayout3->addWidget(etiquetaFechaCreacion);
    //contentLayout3->addStretch(1);
    //contentLayout3->addWidget(etiquetaFechaModificacion);
    //contentLayout->addLayout(contentLayout3);
    contentLayout->addWidget(contenidoNota);


    // // Layout para frameConfiguracion
    // QVBoxLayout *configuracionLayout = new QVBoxLayout(frameConfiguracion);
    // QHBoxLayout *configuracionLayout2 = new QHBoxLayout;
    // configuracionLayout2->addWidget(botonOcultarConfiguracion);
    // configuracionLayout2->addStretch(1);
    // configuracionLayout2->addWidget(etiquetaConfiguracion);
    // configuracionLayout2->addWidget(etiquetaAccionConfiguracion);
    // configuracionLayout2->addStretch(1);
    // configuracionLayout->addLayout(configuracionLayout2);
    // configuracionLayout->addWidget(botonSeleccionarRutaBoveda);
    // configuracionLayout->addWidget(botonSeleccionarNombreBoveda);
    // //configuracionLayout->addWidget(botonOcultarConfiguracion);
    // configuracionLayout->addStretch(1);

    // Layout para frameConfiguracion
    QVBoxLayout *configuracionLayout = new QVBoxLayout(frameConfiguracion);
    QHBoxLayout *configuracionLayout2 = new QHBoxLayout;
    configuracionLayout2->addWidget(botonOcultarConfiguracion);  // Botón a la izquierda
    configuracionLayout2->addWidget(etiquetaConfiguracion);      // Etiqueta en el centro
    configuracionLayout2->addStretch(1);                         // Espacio elástico entre la etiqueta y el siguiente widget
    configuracionLayout2->addWidget(etiquetaAccionConfiguracion); // Widget siguiente (etiquetaAccionConfiguracion)
    configuracionLayout2->addStretch(1);
    configuracionLayout->addLayout(configuracionLayout2);
    configuracionLayout->addWidget(botonSeleccionarRutaBoveda);
    configuracionLayout->addWidget(botonSeleccionarNombreBoveda);
    configuracionLayout->addWidget(botonMostrarNotasOcultas);
    configuracionLayout->addWidget(botonMostrarFechas);
    configuracionLayout->addStretch(1);

    // Layout principal de la ventana
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(frameMenu);
    mainLayout->addWidget(frameContenido); // El contenido se expande
    mainLayout->addWidget(frameConfiguracion); // El contenido se expande



    // Ajustamos las proporciones del menu y el contenido
    mainLayout->setStretchFactor(frameMenu, 1);
    mainLayout->setStretchFactor(frameContenido, 4);



    // conectamos los botones
    connect(botonOcultar, SIGNAL(clicked()), this, SLOT(ocultarMenu()));
    connect(botonMostrar, SIGNAL(clicked()), this, SLOT(mostrarMenu()));
    connect(botonNuevaNota, SIGNAL(clicked()), this, SLOT(nuevaNota()));
    connect(botonGuardarNota, SIGNAL(clicked()), this, SLOT(guardarNota()));
    connect(botonGuardarNota2, SIGNAL(clicked()), this, SLOT(guardarNota()));
    connect(botonEliminarNota, SIGNAL(clicked()), this, SLOT(eliminarNota()));
    connect(listaNotas, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(seleccionarNota()));
    connect(botonEliminarNota2, SIGNAL(clicked()), this, SLOT(eliminarNota()));
    connect(botonAgregarImagen, SIGNAL(clicked()), this, SLOT(insertarImagen()));
    connect(botonAgregarImagen2, SIGNAL(clicked()), this, SLOT(insertarImagen()));
    connect(botonCambiarFuente, SIGNAL(clicked()), this, SLOT(cambiarFuente()));
    connect(botonCambiarColor, SIGNAL(clicked()), this, SLOT(cambiarColor()));
    connect(botonCambiarColorFondo, SIGNAL(clicked()), this, SLOT(cambiarColorFondo()));
    connect(botonConfiguracion, SIGNAL(clicked()), this, SLOT(actualizarConfiguracion()));
    connect(botonOcultarConfiguracion, SIGNAL(clicked()), this, SLOT(ocultarConfiguracion()));
    connect(botonSeleccionarRutaBoveda, SIGNAL(clicked()), this, SLOT(seleccionarRutaBoveda()));
    connect(botonSeleccionarNombreBoveda, SIGNAL(clicked()), this, SLOT(seleccionarNombreBoveda()));
    connect(botonMostrarNotasOcultas, SIGNAL(clicked()), this, SLOT(mostrarNotasOcultass()));
    connect(botonMostrarFechas, SIGNAL(clicked()), this, SLOT(mostrarFechas()));
    connect(botonImprimir, SIGNAL(clicked()), this, SLOT(imprimir()));


    // CONEXION DE TEMPORIZADORES DE ETIQUETAS
    connect(temporizadorAccionConfiguracion, SIGNAL(timeout()), this, SLOT(ocultarEtiquetaAccionConfiguracion()));
    connect(temporizadorAccion, SIGNAL(timeout()), this, SLOT(ocultarEtiquetaAccion()));

    // actualizamos la lista de notas
    verificacionInicial();
    actualizarListaNotas();

    //setFocusPolicy(Qt::StrongFocus);
}


void Ventana::ocultarMenu()
{

    // ocultamos el menu
    frameMenu->hide();
    // frameContenido->setGeometry(0, 0, 1860, 1080);
    // contenidoNota->setGeometry(60, 0, 1860, 1080);
    botonMostrar->show();
    botonGuardarNota2->show();
    botonEliminarNota2->show();
    botonAgregarImagen2->show();
    botonCambiarFuente->show();
    botonCambiarColor->show();
    botonCambiarColorFondo->show();
    botonImprimir->show();
    botonConfiguracion->show();
    etiquetaNombre->show();


    // cambiamos el nombre de la nota
    if (listaNotas->currentItem() != nullptr)
    {
        etiquetaNombre->setText(listaNotas->currentItem()->text());
    } else {
        etiquetaNombre->setText(const_cast<char*>("Mnemosine"));
    }
    redimensionarImagenes();

    contenidoNota->setFocus();


}

void Ventana::mostrarMenu()
{

    // mostramos el menu
    frameMenu->show();
    // frameContenido->setGeometry(300, 0, 1620, 1080);
    // contenidoNota->setGeometry(0, 0, 1620, 1080);
    botonMostrar->hide();
    botonGuardarNota2->hide();
    botonEliminarNota2->hide();
    etiquetaNombre->hide();
    botonAgregarImagen2->hide();
    botonCambiarFuente->hide();
    botonCambiarColor->hide();
    botonCambiarColorFondo->hide();
    botonConfiguracion->hide();
    botonImprimir->hide();

    // redimensionamos las imagenes
    redimensionarImagenes();


    // regresamos el foco a la nota
    contenidoNota->setFocus();

}

void Ventana::ocultarConfiguracion()
{
    // ocultamos el frame de configuracion
    frameConfiguracion->hide();
    // mostramos el frame de contenido
    frameContenido->show();
    // mostramos el frame menu
    //frameMenu->show();
    mostrarMenu();
    // regresamos el foco a la nota
    contenidoNota->setFocus();
}

void Ventana::mostrarConfiguracion()
{
    // mostramos el frame de configuracion
    frameConfiguracion->show();
    // ocultamos el frame menu
    frameMenu->hide();
    // ocultamos el frame de contenido
    frameContenido->hide();
    // regresamos el foco a la nota
    //contenidoNota->setFocus();
    // mostrmaos los botonoes de configuracion
    botonSeleccionarRutaBoveda->show();
    botonSeleccionarNombreBoveda->show();
    etiquetaConfiguracion->show();
    etiquetaAccionConfiguracion->show();
    botonOcultarConfiguracion->show();
}

void Ventana::nuevaNota()
{
    // primero pedimos el nombre de la nota
    bool ok;
    QString nombreNota = QInputDialog::getText(this, "Nueva Nota", "Nombre de la nota:", QLineEdit::Normal, "", &ok);


    // es necesario tener un control de excepciones para evitar cierres inesperados
    try
    {
        // debido a que se va a crear una carpeta y un fichero es necesario verificar que el nombre no contenga caracteres especiales
        // verificamos si el nombre contiene caracteres especiales
        //if (nombreNota.contains(QRegExp("[\\/:*?\"<>|]")))
        if (nombreNota.contains(QRegularExpression("[\\/:*?\"<>|]") ))
        {
            // mostramos que no se puede crear una nota con ese nombre
            mostrarEtiquetaAccion("No se puede crear una nota con ese nombre");
            return;
        }


        if (ok && !nombreNota.isEmpty())
        {
            // verificamos si no existe una nota con el mismo nombre
            ManejoFicheros fichero;

            if (fichero.existeCarpeta(nombreCarpeta + nombreNota.toStdString()))
            {
                // mostramos que ya existe una nota con el mismo nombre
                mostrarEtiquetaAccion("Ya existe una nota con el mismo nombre");
                return;
            }

            // creamos una carpeta con el nombre de la nota dentro de esta guardaremos la nota y los archivos relacionados a la misma

            fichero.verificacionInicial(nombreCarpeta + nombreNota.toStdString());

            // luego creamos la nota
            fichero.escribirFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak" , "");
            // luego actualizamos la lista de notas
            actualizarListaNotas();
            // luego seleccionamos la nota
            // actualizamos el current item de la lista
            listaNotas->setCurrentRow(0);
            // luego seleccionamos la nota
            seleccionarNota();
            // damos el foco a la nota
            contenidoNota->setFocus();
        }

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        mostrarEtiquetaAccion("Error al crear la nota");
    }



}

void Ventana::actualizarListaNotas()
{
    // vamos a verificar ficheros por lo que es necesario usar un try catch
    try {
        // primero limpiamos la lista
        listaNotas->clear();
        // luego la actualizamos
        ManejoFicheros fichero;
        // mostramos el nombre de la carpeta de ntoas
        //std::cout << "NOMBRE DE CARPETA DE NOTASAAASSASA" << nombreCarpeta << std::endl;
        std::vector<std::string> notas = fichero.extraerFicheros(nombreCarpeta, mostrarNotasOcultas);
        // for (const std::string &nota : notas)
        // {
        //     listaNotas->addItem(QString::fromStdString(nota));
        // }
        // recorremos el arreglo de notas en orden decendente
        for (int i = notas.size() - 1; i >= 0; i--)
        {
            listaNotas->addItem(QString::fromStdString(notas[i]));
        }
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
    }

}

void Ventana::guardarNota()
{
    // Verificamos si tenemos un ítem de la lista seleccionado
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota que guardar");
        return;
    }
    // vamos a verificar ficheros por lo que es necesario usar un try catch
    try {

        // Primero obtenemos el nombre de la nota seleccionada
        QString nombreNota = listaNotas->currentItem()->text();

        // Luego obtenemos el contenido de la nota en formato HTML
        QString contenido = contenidoNota->toHtml();

        // Luego guardamos la nota
        ManejoFicheros fichero;
        //fichero.escribirFichero(nombreCarpeta + nombreNota.toStdString(), contenido.toStdString());
        fichero.escribirFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak", contenido.toStdString());
        mostrarEtiquetaAccion("Nota guardada");
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
    }

}

void Ventana::eliminarNota()
{
    // verificamos si tenemos un item de la lista seleccionado
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota que eliminar");
        return;
    }

    // puesto que vamos a eliminar ficheros es necesario hacerlo dentro de un try catch
    try {
        // obtenemos el nombre de la nota seleccionada
        QString nombreNota = listaNotas->currentItem()->text();
        // verificamos si nombreNota contiene algun valor
        if (nombreNota.isEmpty())
        {
            // no hay una nota seleccionada
            mostrarEtiquetaAccion("No hay una nota que eliminar");
            return;
        }
        else
        {
            // preguntamos si esta seguro de eliminar la nota
            QMessageBox::StandardButton respuesta;
            //respuesta = QMessageBox::question(this, "Eliminar Nota", "¿Esta seguro de eliminar la nota? ", QMessageBox::Yes | QMessageBox::No);
            // preguntamos si queremos eliminar la nota y mencionamos el nombre de la misma
            respuesta = QMessageBox::question(this, "Eliminar Nota", "¿Esta seguro de eliminar la nota \n \"" + nombreNota + "\"?", QMessageBox::Yes | QMessageBox::No);
            if (respuesta == QMessageBox::No)
            {
                return;
            }

            // luego eliminamos la nota
            ManejoFicheros fichero;
            fichero.eliminarFichero(nombreCarpeta + nombreNota.toStdString()/* + ".txt"*/);
            // luego actualizamos la lista de notas
            actualizarListaNotas();
            // actualizamos la nota actual
            nombreNotaActual = "";
            // luego borramos el area de texto
            contenidoNota->clear();
            // luego mostramos la accion
            mostrarEtiquetaAccion("Nota eliminada");
        }
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
    }


}

void Ventana::seleccionarNota()
{
    // verificamos si tenemos un item de la lista seleccionado
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccionada");
        return;
    }
    // vamos a verificar ficheros por lo que es necesario usar un try catch
    try {
        // primero obtenemos el nombre de la nota seleccionada
        QString nombreNota = listaNotas->currentItem()->text();
        ManejoFicheros fichero;
        // vamos a verificar si hubo cambios en la nota actual para guardarlos, si los hubo
        // primero verificamos que la nota actual no este vacia
        if (contenidoNota->toHtml() != "")
        {
            // verificamos si no es la primera entrada ya que en esta nombreNotaActual esta vacia
            if (nombreNotaActual != "")
            {
                // verificamos si se modifico la nota actual

                if (!fichero.compararStringConFichero(contenidoNota->toHtml().toStdString(), (nombreCarpeta + nombreNotaActual.toStdString() + "/" + nombreNotaActual.toStdString() + ".tak")))
                {
                    // mostramos en consola que deberiamos guardar la nota
                    std::cout << "deberiamos guardar la nota" << std::endl;
                    // luego guardamos la nota
                    fichero.escribirFichero(nombreCarpeta + nombreNotaActual.toStdString() + "/" + nombreNotaActual.toStdString() + ".tak", contenidoNota->toHtml().toStdString());
                }
            }
        }

        // verificamos si existe el fichero de la nota
        if (!fichero.existeFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak"))
        {
            // mostramos que la nota no existe
            mostrarEtiquetaAccion("La nota no existe, posiblemente creaste esta carpeta manualmente");
            nombreNota = nombreNotaActual;
            return;
        }


        // Actualizamos el nombre de la nota actual
        nombreNotaActual = nombreNota;
        // mostramos el nombre en consola
        //std::cout << nombreNota.toStdString() << std::endl;
        // luego obtenemos el contenido de la nota
        std::string contenido = fichero.leerFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak");
        // luego mostramos el contenido de la nota
        contenidoNota->setHtml(QString::fromStdString(contenido));
        // luego mostramos la accion
        mostrarEtiquetaAccion("Nota seleccionada");

        // en caso de que se deban mostrar las fechas de creacion y modificacion
        if (mostrarFechasNotas)
        {
            // mostramos la fecha de creacion
            //etiquetaFechaCreacion->setText(QString::fromStdString(fichero.extraerFechaCreacion(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak")));
            // mostramos la fecha de modificacion
            etiquetaFechaModificacion->setText(QString::fromStdString(fichero.extraerFechaModificacion(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak")));
        } else {
            // mostramos la fecha de creacion
            //etiquetaFechaCreacion->setText("");
            // mostramos la fecha de modificacion
            etiquetaFechaModificacion->setText("");

        }

        // redimensionamos las imagenes de la nota
        redimensionarImagenes();
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
    }
}

void Ventana::verificacionInicial(bool iteracion)
{
    // verificamos si existe la carpeta notas
    ManejoFicheros fichero;

    // mostramos el estado de primeraVez
    //std::cout << "iteracion: " << iteracion << std::endl;
    // vamos a verificar ficheros por lo que es necesario usar un try catch
    try {

        // verificamos si existe la carpeta de configuracion
        if (!fichero.existeCarpeta(*nombreCarpetaConfiguracion))
        {
            // si no existe la creamos
            fichero.verificacionInicial(*nombreCarpetaConfiguracion);
            std::cout << "creando carpeta configuracion" << std::endl;

            // -- BLOQUE DE OBTENCION DE RUTA DE LA CARPETA DE NOTAS -----------------------------------------------------------------------------------------------------------------
            // generamos un dialogo para pedir la ubicacion de la carpeta de notas
            QString nombreCarpeta = QFileDialog::getExistingDirectory(this, tr("Por favor seleccione en que ruta le gustaria tener su boveda"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            std::string config;
            // verificamos si se ingreso un nombre
            if (!nombreCarpeta.isEmpty())
            {
                // creamos el archivo de configuracion
                config = "rutaCarpetaBoveda: \"" + nombreCarpeta.toStdString();
                config += "\"\n";
                //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
            } else {
                // creamos el archivo de configuracion
                //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", "./notas/");
                config = "rutaCarpetaBoveda: \"./\"\n";
            }


            // -- BLOQUE DE OBTENCION DE NOMBRE DE LA CARPETA DE NOTAS -----------------------------------------------------------------------------------------------------------------
            // generamos un dialogo para pedir el nombre de la carpeta de notas
            bool ok = false;
            QString boveda;
            // ciclo que se sera ejecutado hasta que se ingrese un nombre valido
            while(!ok)
            {
                boveda = QInputDialog::getText(this, "Configuracion", "Nombre de la carpeta de notas:", QLineEdit::Normal, "", &ok);
                // verificamos si se ingreso un nombre
                // vamos a crear un un fichero por lo que el nombre no debe contener caracteres especiales
                if (boveda.contains(QRegularExpression("[\\/:*?\"<>|]") ))
                {
                    // mostramos que no se puede crear una nota con ese nombre
                    //mostrarEtiquetaAccion("No se puede crear una nota con ese nombre");
                    // mostramos un dialogo de error
                    QMessageBox::critical(this, "Error", "No se puede crear una nota con ese nombre");
                    ok = false;
                }
            }

            if (ok && !boveda.isEmpty())
            {
                // creamos el archivo de configuracion
                config += "nombreCarpetaBoveda: \"/" + boveda.toStdString() + "/\"\n";
                //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
            } else {
                // creamos el archivo de configuracion
                config += "nombreCarpetaBoveda: \"notas/\"\n";
                //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
            }

            // añadimos una clausula para mostrar la fecha de modificacion por defecto no
            config += "mostrarFechasNotas: \"false\"\n";
            // añadimos una clausula para mostrar las notas ocultas por defecto no
            //config += "mostrarNotasOcultas: \"false\"\n";

            // luego creamos el archivo de configuracion
            fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);

        }
        // else {
        //     std::cout << "Se encontro una carpeta de configuracion --- soy la linea 1066 " << std::endl;
        // }




        // verificamos si existe el archivo de configuracion
        if (!fichero.existeFichero(*nombreCarpetaConfiguracion + "configuracion.tak"))
        {
            // llamamos al metodo para actualizar la ruta de la carpeta de la boveda
            seleccionarRutaBoveda();
            // llamamos al metodo para actualizar el nombre de la carpeta de la boveda
            seleccionarNombreBoveda();
            // llamamos el metodo para ocultar la configuracion
            ocultarConfiguracion();
        }

        // luego leemos el archivo de configuracion
        std::string configuracion = fichero.leerFichero(*nombreCarpetaConfiguracion + "configuracion.tak");

        // -- BLOQUE DE OBTENCION DE LA RUTA DE LA CARPETA DE NOTAS --
        // luego obtenemos el nombre de la carpeta de notas
        rutaCarpetaNotas = fichero.extraerString(configuracion, "rutaCarpetaBoveda: \"");
        // tomamos el contenido de configuración hasta el salto de linea
        rutaCarpetaNotas = rutaCarpetaNotas.substr(0, rutaCarpetaNotas.find("\""));
        //std::cout << "rutaCarpetaNotas: " << rutaCarpetaNotas << std::endl;


        // -- BLOQUE DE OBTENCION DEL NOMBRE DE LA CARPETA DE NOTAS --
        // Obtenemos el nombre de la carpeta de notas
        nombreCarpeta = fichero.extraerString(configuracion, rutaCarpetaNotas + "\"\nnombreCarpetaBoveda: \"");
        nombreCarpeta = nombreCarpeta.substr(0, nombreCarpeta.find("\""));
        //std::cout << "nombreCarpeta: " << nombreCarpeta << std::endl;


        // --BLOQUE DE OBTENCION DE LA CLAUSULA PARA MOSTRAR LAS FECHAS DE MODIFICACION--
        // Obtenemos la clausula para mostrar las fechas de modificacion

        std::string mostrarFechas = fichero.extraerString(configuracion, nombreCarpeta + "\"\nmostrarFechasNotas: \"");
        mostrarFechas = mostrarFechas.substr(0, mostrarFechas.find("\""));
        std::cout << "mostrarFechas: " << mostrarFechas << std::endl;
        if (mostrarFechas == "false")
        {
            mostrarFechasNotas = false;
            etiquetaFechaModificacion->hide();
        } else {
            mostrarFechasNotas = true;
        }




        // unimos la ruta de la carpeta de notas con el nombre de la carpeta de notas
        nombreCarpeta = rutaCarpetaNotas + nombreCarpeta;
        // std::cout << "Ruta de la carpeta de notas: " << rutaCarpetaNotas << std::endl;
        // std::cout << "nombreCarpeta: " << nombreCarpeta << std::endl;

        if (!fichero.existeCarpeta(nombreCarpeta))
        {
            // si no existe la creamos
            fichero.verificacionInicial(nombreCarpeta);
            //std::cout << "creando carpeta contenedor" << std::endl;
            if (!iteracion) // si es una iteracion interna
                QMessageBox::information(this, "Bienvenido", "Bienvenido a Mnemosine\n\nPara comenzar cree una nueva nota");
            // y creamos una nota que explica los comandos basicos
            // primero creamos la carpeta de la nota
            //fichero.verificacionInicial(nombreCarpeta + "comandosBasicos");
            // luego creamos la nota
            //fichero.escribirFichero(nombreCarpeta + "comandosBasicos/comandosBasicos.tak" , "Comandos Basicos: \n\nCtrl + S: Guardar nota\nCtrl + N: Crear nueva nota\nCtrl + E: Eliminar nota\nCtrl + I: Insertar imagen\nCtrl + Q: Salir de la aplicacion\nCtrl + O: Ocultar menu\nCtrl + M: Mostrar menu\nCtrl + A: Seleccionar todo\nCtrl + Z: Deshacer");
            //fichero.escribirFichero(nombreCarpeta + "comandosBasicos/comandosBasicos.tak" , "<h1>Comandos Basicos:</h1><br><br><h2>Ctrl + S: Guardar nota</h2><br><h2>Ctrl + N: Crear nueva nota</h2><br><h2>Ctrl + E: Eliminar nota</h2><br><h2>Ctrl + I: Insertar imagen</h2><br><h2>Ctrl + Q: Salir de la aplicacion</h2><br><h2>Ctrl + O: Ocultar menu</h2><br><h2>Ctrl + M: Mostrar menu</h2><br><h2>Ctrl + A: Seleccionar todo</h2><br><h2>Ctrl + B: Negritas</h2><br><h2>Ctrl + Z: Deshacer</h2>");

        } else {
            std::cout << "Se encontro un contenedor" << std::endl;
        }
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
    }
}

void Ventana::insertarImagen()
{

    // verificamos si nos encontramos dentro de un archivo de texto
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccionada");
        return;
    }
    // guardamos la posicion del cursor de la nota
    QTextCursor cursor = contenidoNota->textCursor();

    // guardamos el estilo de texto actual para luego restaurarlo
    QTextCharFormat formatoActual = contenidoNota->currentCharFormat();

    // mostramos en la terminal que estamos intentando insertar una imagen
    std::cout << "insertando imagen" << std::endl;

    // preparamos un bloque de excepcion para capturar errores
    try
    {
        // obtenemos la ruta de la imagen
        QString rutaImagen = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "/home", tr("Images (*.png *.xpm *.jpg)"));
        // si la ruta a la imagen no esta vacia
        if (!rutaImagen.isEmpty())
        {


            // hacemos una copia de la imagen en la carpeta de la nota
            // primero obtenemos el nombre de la nota seleccionada
            QString nombreNota = listaNotas->currentItem()->text();
            // luego verificamos que nombreNota no este vacio
            if (nombreNota.isEmpty())
            {
                return;
            }
            // luego verificamos que exista la carpeta nota
            ManejoFicheros fichero;
            if (!fichero.existeCarpeta(nombreCarpeta + nombreNota.toStdString()))
            {
                // si no existe la creamos
                fichero.verificacionInicial(nombreCarpeta + nombreNota.toStdString());
                std::cout << "creando carpeta nota" << std::endl;
                // y creamos una nota
                fichero.escribirFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak" , "");
            } else {
                std::cout << "Se encontro una nota" << std::endl;
            }
            // luego copiamos la imagen
            fichero.copiarFichero(rutaImagen.toStdString(), nombreCarpeta + nombreNota.toStdString() + "/" + rutaImagen.split("/").last().toStdString());

            // Insertar la imagen usando un formato de imagen HTML
            // Obtener la ruta completa de la imagen
            QString imagePath = (nombreCarpeta + nombreNota.toStdString() + "/" + rutaImagen.split("/").last().toStdString()).c_str();

            // Especificar la anchura deseada (ajustar según tus necesidades)
            int anchuraDeseada = 300; // por ejemplo, ajusta este valor según tus necesidades

            // Crear la etiqueta de imagen con la ruta y la anchura
            QString htmlImage = QString("<img src='%1' width='%2'/>").arg(imagePath).arg(anchuraDeseada);
            std::cout << htmlImage.toStdString() << std::endl;
            // Insertar la imagen usando el formato de imagen HTML
            contenidoNota->textCursor().insertHtml(htmlImage);
            // Insertar la imagen usando el formato de imagen HTML
            //contenidoNota->textCursor().insertHtml(htmlImage);

            // Opcionalmente, podrías querer añadir un salto de línea después de la imagen
            contenidoNota->textCursor().insertHtml("<br>");

            // restauramos el estilo de texto
            contenidoNota->setCurrentCharFormat(formatoActual);
        }
        // volvemos a colocar el cursor en la nota
        contenidoNota->setTextCursor(cursor);
        // restauramos el estilo de texto
        contenidoNota->setCurrentCharFormat(formatoActual);
        // regresamos el foco
        contenidoNota->setFocus();
        // redimencionamos las imagenes
        redimensionarImagenes();
        // restauramos el estilo de texto
        contenidoNota->setCurrentCharFormat(formatoActual);
        // mostramos la accion
        mostrarEtiquetaAccion("Imagen insertada");

    }
    catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
    }

}

void Ventana::keyPressEvent(QKeyEvent *event){
    // Verifica si se presionó Control + S
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
        // Si es así, llama al método para guardar la nota
        guardarNota();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_N) {
        // Si es así, llama al método para crear una nueva nota
        nuevaNota();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_E) {
        // Si es así, llama al método para eliminar la nota
        eliminarNota();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_I) {
        // Si es así, llama al método para insertar una imagen
        insertarImagen();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Q) {
        // Si es así, llama al método para salir de la aplicación
        //QApplication::quit();
        close();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_O) {
        // Si es así, llama al método para ocultar el menú
        ocultarMenu();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_M) {
        // Si es así, llama al método para mostrar el menú
        mostrarMenu();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_A) {
        // Si es así, llama al método para mostrar el menú
        contenidoNota->selectAll();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Z) {
        // Si es así, llama al método para mostrar el menú
        contenidoNota->undo();
        event->accept(); // Indica que el evento ha sido manejado
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_B) {
       // Si es así, llama al método para poner negritas
       QTextCharFormat fmt;
       fmt.setFontWeight(contenidoNota->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
       contenidoNota->mergeCurrentCharFormat(fmt);
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_F) {
       // Si es así, llama al método para cambiar la fuente
       cambiarFuente();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_G) {
       // si es así, llama al método para cambiar el color de texto
       cambiarColor();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_H) {
       // si es así, llama al método para cambiar el color de fondo
       cambiarColorFondo();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_0) {
       // si es así, llamamos al metodo para mostrar notas ocultas
       mostrarNotasOcultas = !mostrarNotasOcultas;
       actualizarListaNotas();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Equal){
       // si es así, aumentamos el tamaño de la fuente Qt::Key_Plus
       aumentarTamFuente();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Minus){
       // si es así, reducimos el tamaño de la fuente
       disminuirTamFuente();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_P){
       // si es así, imprimimos la nota
       imprimir();
       event->accept();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Up)
    {
       // si es así, seleccionamos la letra siguiente partiendo del cursor
       // mostramos en consola que estamos intentando usar el atajo
       //std::cout << "seleccionando letra derecha" << std::endl;
       //seleccionarLetraDerecha();
       aumentarZoom();
       event->accept();

    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Down)
    {
       // si es así, seleccionamos la letra siguiente partiendo del cursor
       // mostramos en consola que estamos intentando usar el atajo
       //std::cout << "seleccionando letra izquierda" << std::endl;
       //seleccionarLetraIzquierda();
       disminuirZoom();
       event->accept();

    } else {
       // muestra que tecla se presiono
       std::cout << event->key() << std::endl;
        event->ignore(); // Ignora el evento
    }
    // verificamos si se presiono la tecla control sumada a la tecla flecha derecha
    // if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Right) {
    //     // si es así, llamamos al metodo para seleccionar la nota siguiente
    //     seleccionarNotaSiguiente();
    //     event->accept();
    // }
    // control + flecha izquierda
    // else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Left) {

}

void Ventana::cambiarFuente()
{
    // Verificar si hay un ítem seleccionado en listaNotas
    if (!listaNotas->currentItem())
    {
        // No hay nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccioanda");
        return;
    }
    // Obtener el cursor de texto actual
    QTextCursor cursor = contenidoNota->textCursor();

    // Inicializar el diálogo de fuente con la fuente actual del cursor
    QFontDialog fontDialog(cursor.charFormat().font(), this);

    // Mostrar el diálogo de fuente
    if (fontDialog.exec() == QDialog::Accepted)
    {
        // Obtener la fuente seleccionada del diálogo
        QFont fuenteSeleccionada = fontDialog.selectedFont();

        // // Verificar si hay texto seleccionado
        // if (cursor.hasSelection())
        // {
        //     // Modificar el formato del texto seleccionado
        //     QTextCharFormat format;
        //     format.setFont(fuenteSeleccionada);
        //     cursor.mergeCharFormat(format);
        //     std::cout << "hay texto seleccionado" << std::endl;
        // }
        // else
        //{
            // // Modificar el formato del texto completo
            // contenidoNota->selectAll();
            // QTextCharFormat format;
            // format.setFont(fuenteSeleccionada);
            // cursor.mergeCharFormat(format);
            // cursor.clearSelection();

            QTextCharFormat format = cursor.charFormat();
            format.setFont(fuenteSeleccionada);
            cursor.mergeCharFormat(format);
            std::cout << "no hay texto seleccionado" << std::endl;
        //}

        // Aplicar el cursor actualizado
        contenidoNota->setTextCursor(cursor);

        // Devolver el foco a contenidoNota
        contenidoNota->setFocus();
        // mostramos la accion
        mostrarEtiquetaAccion("Se cambio la fuente de la nota a " + fuenteSeleccionada.family());
    }
}

void Ventana::aumentarTamFuente()
{
    // Verificar si hay un ítem seleccionado en listaNotas
    if (!listaNotas->currentItem())
    {
        // No hay nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccionada");
        return;
    }

    // Obtener el cursor de texto actual
    QTextCursor cursor = contenidoNota->textCursor();

    // Obtener el formato de caracteres actual
    QTextCharFormat formato = cursor.charFormat();

    // Aumentar el tamaño de la fuente en 1
    formato.setFontPointSize(formato.fontPointSize() + 1);

    // Aplicar el nuevo formato al cursor
    cursor.setCharFormat(formato);

    // Aplicar el cursor actualizado
    contenidoNota->setTextCursor(cursor);

    // Devolver el foco a contenidoNota
    contenidoNota->setFocus();

    // Mostrar la acción
    mostrarEtiquetaAccion("Tamaño de la fuente: " + QString::number(formato.fontPointSize()));
}

void Ventana::disminuirTamFuente()
{
    // Verificar si hay un ítem seleccionado en listaNotas
    if (!listaNotas->currentItem())
    {
        // No hay nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccionada");
        return;
    }

    // Obtener el cursor de texto actual
    QTextCursor cursor = contenidoNota->textCursor();

    // Obtener el formato de caracteres actual
    QTextCharFormat formato = cursor.charFormat();

    // verificamos si el tamaño de la fuente es menor a 4
    if (formato.fontPointSize() <= 4)
    {
        // mostramos la accion
        mostrarEtiquetaAccion("El tamaño de la fuente no puede ser menor a 4");
        return;
    }

    // Disminuir el tamaño de la fuente en 1
    formato.setFontPointSize(formato.fontPointSize() - 1);

    // Aplicar el nuevo formato al cursor
    cursor.setCharFormat(formato);

    // Aplicar el cursor actualizado
    contenidoNota->setTextCursor(cursor);

    // Devolver el foco a contenidoNota
    contenidoNota->setFocus();

    // Mostrar la acción
    mostrarEtiquetaAccion("Tamaño de la fuente: " + QString::number(formato.fontPointSize()));
}

void Ventana::cambiarColor()
{
    // verificamos si tenemos un item de la lista de notas seleccionado
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccioanda");
        return;
    }
    QColorDialog colorDialog;
    // [Configuración de estilo para QColorDialog...]

    // Guardar la posición actual del cursor
    //int cursorPos = contenidoNota->textCursor().position();

    if (colorDialog.exec() == QDialog::Accepted)
    {
        QColor colorSeleccionado = colorDialog.selectedColor();
        QTextCursor cursor = contenidoNota->textCursor();

        // // verificamos si tenemos texto seleccionado lo que implicaria que queremos modificar el texto seleccioado
        // if (cursor.hasSelection())
        // {
        //     // si tenemos texto seleccionado modificamos el texto seleccionado
        //     QTextCharFormat format = cursor.charFormat();
        //     format.setForeground(colorSeleccionado);
        //     cursor.mergeCharFormat(format);
        // } else {
        //     // si no tenemos texto seleccionado modificamos el texto completo
        //     //contenidoNota->setTextColor(colorSeleccionado);

        //     // si no tenemos texto seleccionado modificamos el color del texto actual (cursor)
            QTextCharFormat format = cursor.charFormat();
            format.setForeground(colorSeleccionado);
            cursor.mergeCharFormat(format);
        //}

        contenidoNota->setTextCursor(cursor); // Aplicar el cursor actualizado
        contenidoNota->setFocus(); // Devolver el foco a contenidoNota
        mostrarEtiquetaAccion("Se cambio el color de la nota a " + colorSeleccionado.name());
    }
}

void Ventana::cambiarColorFondo()
{
    if (listaNotas->currentItem() == nullptr)
    {
        // No hay nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccioanda");

        return;
    }

    QColorDialog colorDialog;
    // [Configuración de estilo para QColorDialog...]

    // Obtener el cursor de texto actual
    QTextCursor cursor = contenidoNota->textCursor();

    // Obtener el inicio y el fin de la selección
    //int inicioSeleccion = cursor.selectionStart();
    //int finSeleccion = cursor.selectionEnd();

    if (colorDialog.exec() == QDialog::Accepted)
    {
        QColor colorSeleccionado = colorDialog.selectedColor();

        // Configurar el formato del texto seleccionado
        QTextCharFormat format;
        format.setBackground(colorSeleccionado);

        // Aplicar el formato al texto seleccionado
        //cursor.setPosition(inicioSeleccion);
        //cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor, finSeleccion - inicioSeleccion);
        cursor.mergeCharFormat(format);

        // Aplicar el cursor actualizado
        contenidoNota->setTextCursor(cursor);

        // Devolver el foco a contenidoNota
        contenidoNota->setFocus();
        //mostrarEtiquetaAccion("Se cambio el color de fondo de la nota");
        mostrarEtiquetaAccion("Se cambio el color de fondo de la nota a " + colorSeleccionado.name());
    }
}

void Ventana::ocultarEtiquetaAccion()
{
    etiquetaAccion->hide();
    //redimensionarImagenes();

}

void Ventana::mostrarEtiquetaAccion(const QString &accion)
{
    etiquetaAccion->setText(accion);
    etiquetaAccion->show();
    //QTimer::singleShot(3000, this, SLOT(ocultarEtiquetaAccion()));
    // iniciamos el temporizador
    temporizadorAccion->start(3000);

}

void Ventana::ocultarEtiquetaAccionConfiguracion()
{
    etiquetaAccionConfiguracion->hide();
    //redimensionarImagenes();

}

void Ventana::mostrarEtiquetaAccionConfiguracion(const QString &accion)
{
    etiquetaAccionConfiguracion->setText(accion);
    etiquetaAccionConfiguracion->show();
    //QTimer::singleShot(3000, this, SLOT(ocultarEtiquetaAccionConfiguracion()));
    // iniciamos el temporizador
    temporizadorAccionConfiguracion->start(3000);
}

Ventana::~Ventana()
{
    // guardamos la nota que tenemos abierta en caso de tener una nota seleccionada
    if (listaNotas->currentItem() != nullptr)
    {
        guardarNota();
    }

}


void Ventana::resizeEvent(QResizeEvent *event) {
    // guardamos la posicion del cursor de la nota
    //QTextCursor cursor = contenidoNota->textCursor();
    // Llamamos al resizeEvent de la clase base
    QWidget::resizeEvent(event);

    // mostramos el valor de puedoRedimensionarImagenes
    //std::cout << puedoRedimensionarImagenes << std::endl;
    // verificamos si podemos redimensionar las imagenes
    if (puedoRedimensionarImagenes)
    {
        // Redimensionamos las imagenes de la nota actual
        puedoRedimensionarImagenes = false;
        QTimer::singleShot(200, this, SLOT(cambiarEstadoPuedoRedimensionarImagenes()));
        redimensionarImagenes();
    }
    // volvemos a colocar el cursor en la nota
    //contenidoNota->setTextCursor(cursor);



}

void Ventana::cambiarEstadoPuedoRedimensionarImagenes()
{
    // mostramos que estamos cambiando el estado de puedoRedimensionarImagenes
    //std::cout << "cambiando estado de puedoRedimensionarImagenes" << std::endl;
    puedoRedimensionarImagenes = true;
}

void Ventana::redimensionarImagenes()
{
    // extraemos el cursor de la nota
    QTextCursor cursor = contenidoNota->textCursor();
    // Verificamos si hay un ítem seleccionado en listaNotas
    if (!listaNotas->currentItem())
    {
        // No hay nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccionada");
        return;
    }

    // Extraemos el contenido del QTextEdit
    QString contenido = contenidoNota->toHtml();

    // mostramos la posicion del cursor
    //std::cout << cursor.position() << std::endl;

    // guardamos la posicion del cursor
    int posicionCursor = cursor.position();
    // mostramos el contenido de posicionCursor
    //std::cout << posicionCursor << std::endl;

    // Modificamos el ancho y alto de las imágenes
    contenido = redimensionarAnchoAltoImagenes(contenido);

    // Actualizamos el contenido del QTextEdit
    contenidoNota->setHtml(contenido);
    // llamamos al sonido
    //sonidoBoton->play();


    // colocamos el cursor en la posicion extraida
    cursor.setPosition(posicionCursor);
    contenidoNota->setTextCursor(cursor);


}


QString Ventana::redimensionarAnchoAltoImagenes(const QString &html)
{
    // Utilizamos una expresión regular para buscar todas las etiquetas de imagen
    QRegularExpression regex("<img[^>]*>");

    // Índice utilizado para iterar sobre las coincidencias de la expresión regular
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(html);

    // Copiamos el contenido HTML para modificarlo
    QString contenido = html;

    // Iteramos sobre todas las coincidencias
    while (matchIterator.hasNext())
    {
        // Obtener la siguiente coincidencia
        QRegularExpressionMatch match = matchIterator.next();
        QString imgTag = match.captured(0);

        // Reemplazar el ancho en la etiqueta de imagen por el de contenidoNota
        QString ancho = "width=\"";
        if (contenidoNota->size().width() >= 1050)
        {
            ancho += QString::number(999);
            ancho += "\"";
        }
        else
        {
            ancho += QString::number(contenidoNota->size().width() - 50);
            ancho += "\"";
        }

        imgTag.replace(QRegularExpression("width=\"[^\"]*\""), ancho);

        // Reemplazar la etiqueta original con la modificada en el contenido HTML
        contenido.replace(match.capturedStart(), match.capturedLength(), imgTag);
    }

    return contenido;
}

void Ventana::actualizarConfiguracion()
{
    // guardamos la nota que tenemos abierta en caso de tener una nota seleccionada
    if (listaNotas->currentItem() != nullptr)
    {
        guardarNota();
    }
    // deseleccionamos la nota actual
    listaNotas->setCurrentItem(nullptr);
    // borramos el contenido del editor de texto
    contenidoNota->clear();
    // borramos el string notaActual
    nombreNotaActual = "";



    // primero verificamos si existe la carpeta de configuracion
    ManejoFicheros fichero;
    if (!fichero.existeCarpeta(*nombreCarpetaConfiguracion))
    {
        // si no existe la creamos
        fichero.verificacionInicial(*nombreCarpetaConfiguracion);
        std::cout << "creando carpeta configuracion" << std::endl;

        // -- BLOQUE DE OBTENCION DE RUTA DE LA CARPETA DE NOTAS -----------------------------------------------------------------------------------------------------------------
        // generamos un dialogo para pedir la ubicacion de la carpeta de notas
        QString nombreCarpeta = QFileDialog::getExistingDirectory(this, tr("Por favor seleccione en que ruta le gustaria tener su boveda"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        std::string config;
        // verificamos si se ingreso un nombre
        if (!nombreCarpeta.isEmpty())
        {
            // creamos el archivo de configuracion
            config = "rutaCarpetaBoveda: \"" + nombreCarpeta.toStdString();
            config += "\"\n";
            //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
        } else {
            // creamos el archivo de configuracion
            //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", "./notas/");
            config = "rutaCarpetaBoveda: \"./\"\n";
        }
        fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);

    } // en caso de existir
    else
    {
        // actualizamos la lista de notas
        actualizarListaNotas();

        // luego leemos el archivo de configuracion
        std::string configuracion = fichero.leerFichero(*nombreCarpetaConfiguracion + "configuracion.tak");
        // procesamos el archivo generando un string con el contenido de la ruta de la boveda y otro con el nombre de la boveda
        // -- BLOQUE DE OBTENCION DE LA RUTA DE LA CARPETA DE NOTAS --
        // luego obtenemos el nombre de la carpeta de notas
        rutaCarpetaNotas = fichero.extraerString(configuracion, "rutaCarpetaBoveda: \"");
        // tomamos el contenido de configuración hasta el salto de linea
        rutaCarpetaNotas = rutaCarpetaNotas.substr(0, rutaCarpetaNotas.find("\""));
        //std::cout << "rutaCarpetaNotas: " << rutaCarpetaNotas << std::endl;

        // -- BLOQUE DE OBTENCION DEL NOMBRE DE LA CARPETA DE NOTAS --
        // Obtenemos el nombre de la carpeta de notas
        nombreCarpetaNotas = fichero.extraerString(configuracion, rutaCarpetaNotas + "\"\nnombreCarpetaBoveda: \"");
        nombreCarpetaNotas = nombreCarpetaNotas.substr(0, nombreCarpetaNotas.find("\""));
        //std::cout << "nombreCarpeta: " << nombreCarpetaNotas << std::endl;

        // asignamos texto al label configuracion
        //configuracion = "Configuración";

        // colocamos las rutas en los botones
        botonSeleccionarRutaBoveda->setText(QString::fromStdString(rutaCarpetaNotas));
        botonSeleccionarNombreBoveda->setText(QString::fromStdString(nombreCarpetaNotas));

        // colocamos el estado de las notas ocultas
        if (!mostrarNotasOcultas)
            botonMostrarNotasOcultas->setText("Mostrar notas ocultas");
        else
            botonMostrarNotasOcultas->setText("Ocultar notas ocultas");

        if (!mostrarFechasNotas)
            botonMostrarFechas->setText("Mostrar fechas de las notas");
        else
            botonMostrarFechas->setText("Ocultar fechas de las notas");

        // mostramos el frame de configuracion
        mostrarConfiguracion();

        // mostramos una etiqueta de accion indicando que acabamos de ingresar a la configuracion
        mostrarEtiquetaAccionConfiguracion("Acabas de ingresar a la configuración");



    }
}

// --Metodo para imprimir la nota--
void Ventana::imprimir()
{
    // verificamos si tenemos una nota seleccionada
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccionada");
        return;
    }
    // guardamos la nota que tenemos abierta en caso de tener una nota seleccionada
    guardarNota();
    // extraemos el nombre de la nota
    QString nombreNota = listaNotas->currentItem()->text();
    // extraemos el contenido de la nota
    QString contenido = contenidoNota->toPlainText();

    // Creamos un documento de texto
    QTextDocument document;
    // Le asignamos el contenido de la nota
    document.setPlainText(contenido);
    // Obtenemos un cursor del documento
    QTextCursor cursor(&document);
    QTextCharFormat formato;
    // establecemos un fondo negro para todo el documento
    formato.setBackground(Qt::black);
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(formato);


    // // Obtener la ruta de destino del archivo PDF
    // QString rutaArchivoPDF = QFileDialog::getSaveFileName(this, "Guardar como PDF", "", "Archivos PDF (*.pdf)");

    // if (!rutaArchivoPDF.isEmpty()) {
    //     // Configurar la impresora para generar un archivo PDF
    //     QPrinter printer(QPrinter::PrinterResolution);
    //     printer.setOutputFormat(QPrinter::PdfFormat);
    //     printer.setPaperSize(QPrinter::A4);
    //     printer.setOutputFileName(rutaArchivoPDF);

    //     // Imprimir el documento en el archivo PDF
    //     document.print(&printer);
    // }
    // Configurar la impresora para permitir la selección del usuario
    QPrintDialog printDialog;
    if (printDialog.exec() == QDialog::Accepted) {
        // Obtener la impresora seleccionada
        QPrinter* printer = printDialog.printer();

        // Imprimir el documento en la impresora seleccionada
        document.print(printer);
    }
}



// --SLOTS DE LA CONFIGURACION--
void Ventana::seleccionarRutaBoveda()
{
    // generamos un objeto de tipo ManejoFicheros
    ManejoFicheros fichero;
    // creamos un booleano que simbolice la existencia de la carpeta por lo que es necesario respaldar el nombre de la boveda
    bool existeCarpeta = true;
    // vamos a verificar y modificar archivos por lo que es necesario usar un try catch
    try {
        // verificamos que exista la carpeta de configuracion
        if (!fichero.existeCarpeta(*nombreCarpetaConfiguracion))
        {
            // si no existe la creamos
            fichero.verificacionInicial(*nombreCarpetaConfiguracion);
            std::cout << "creando carpeta configuracion" << std::endl;
            existeCarpeta = false; // ya que no existia la carpeta de configuracion no existe la carpeta de la boveda

        }
        // -- BLOQUE DE OBTENCION DE RUTA DE LA CARPETA DE NOTAS -----------------------------------------------------------------------------------------------------------------
        // generamos un dialogo para pedir la ubicacion de la carpeta de notas
        QString nombreCarpeta = QFileDialog::getExistingDirectory(this, tr("Por favor seleccione en que ruta le gustaria tener su boveda"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        std::string config;
        // verificamos si se ingreso un nombre
        if (!nombreCarpeta.isEmpty())
        {
            // creamos el archivo de configuracion
            config = "rutaCarpetaBoveda: \"" + nombreCarpeta.toStdString();
            config += "\"\n";
            //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
        } else {
            // creamos el archivo de configuracion
            //fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", "./notas/");
            config = "rutaCarpetaBoveda: \"./\"\n";
            return;
        }

        // en caso de que exista la carpeta de configuracion extraemos el nombre de la boveda
        // verificamos la existencia del archivo de configuracion
        if(!fichero.existeFichero(*nombreCarpetaConfiguracion + "configuracion.tak" ))
            existeCarpeta = false; // decir que no existe la carpeta de configuracion es lo mismo que decir que no existe el archivo de configuracion que implica que no existe la carpeta de la boveda

        if (existeCarpeta)
        {
            // extraemos el contenido del archivo de configuracion
            std::string configuracion = fichero.leerFichero(*nombreCarpetaConfiguracion + "configuracion.tak");
            // obtenemos el nombre de la boveda
            std::string nombreBoveda = fichero.extraerString(configuracion, "rutaCarpetaBoveda: \"");
            // tomamos el contenido de configuración hasta el salto de linea
            nombreBoveda = nombreBoveda.substr(0, nombreBoveda.find("/"));
            // extraemos el nombre de la carpeta de notas
            nombreBoveda = fichero.extraerString(configuracion, rutaCarpetaNotas + "\"\nnombreCarpetaBoveda: \"");
            // tomamos el contenido de configuración hasta el salto de linea
            nombreBoveda = nombreBoveda.substr(0, nombreBoveda.find("\""));
            // quitamos los / del nombre de la boveda
            nombreBoveda = nombreBoveda.substr(1, nombreBoveda.size() - 2);
            // mostramos la opcion de copiar las notas a la nueva carpeta
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Copia de notas", "¿Deseas copiar las notas a la nueva carpeta?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // copiamos las notas a la nueva carpeta
                fichero.copiarFicheroNotas(rutaCarpetaNotas + "/" + nombreBoveda , nombreCarpeta.toStdString() + "/" + nombreBoveda);
            } else {
                // no copiamos las notas a la nueva carpeta
            }



            //std::cout << "nombreBoveda: " << nombreBoveda << std::endl;
            // luego creamos el archivo de configuracion
            config += "nombreCarpetaBoveda: \"/" + nombreBoveda + "/\"\n";
        } else {
            // le asignamos un nombre por defecto a la boveda
            config += "nombreCarpetaBoveda: \"/notas/\"\n";

        }



        // luego creamos el archivo de configuracion
        fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
        // actualizamos la configuracion
        verificacionInicial(true); // indicamos que es una iteracion interna
        // actualizamos las etiquetas y botones de la configuracion
        actualizarConfiguracion();
        // mostramos una etiqueta de accion indicando que acabamos de actualizar la ruta de la boveda
        mostrarEtiquetaAccionConfiguracion("Acabas de actualizar la ruta de la boveda");
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
        // acaba de suceder un error por lo que ideal realizar una verificacion inicial
        verificacionInicial( true); // indicamos que es una iteracion interna
        // actualizamos las etiquetas y botones de la configuracion
        actualizarConfiguracion();
        // mostramos una etiqueta de accion indicando que acaba de pasar un error
        mostrarEtiquetaAccionConfiguracion("ERROR, NO PODEMOS ASEGURAR LA INTEGRIDAD DE LOS DATOS DE LA BOVEDA, CODIGO DE ERROR: 101010");
    }
}


void Ventana::seleccionarNombreBoveda()
{
    // generamos un objeto de tipo ManejoFicheros
    ManejoFicheros fichero;
    // creamos un booleano que simbolice la existencia de la carpeta por lo que es necesario respaldar el nombre de la boveda
    //bool existeCarpeta = true;

    // vamos a verificar y modificar archivos por lo que es necesario usar un try catch
    try {
        // verificamos que exista la carpeta de configuracion
        if (!fichero.existeCarpeta(*nombreCarpetaConfiguracion))
        {
            // si no existe la creamos
            fichero.verificacionInicial(*nombreCarpetaConfiguracion);
            std::cout << "creando carpeta configuracion" << std::endl;
            //existeCarpeta = false; // ya que no existia la carpeta de configuracion no existe la carpeta de la boveda

        }
        // -- BLOQUE DE OBTENCION DE NOMBRE DE LA CARPETA DE NOTAS -----------------------------------------------------------------------------------------------------------------
        // generamos un dialogo para pedir el nombre de la carpeta de notas
        bool ok = false;
        QString boveda;
        // ciclo que se sera ejecutado hasta que se ingrese un nombre valido
        while(!ok)
        {
            boveda = QInputDialog::getText(this, "Configuracion", "Nombre de la carpeta de notas:", QLineEdit::Normal, "", &ok);
            // si no se ingreso un nombre retornamos
            if (!ok)
                return;
            // verificamos si se ingreso un nombre
            // vamos a crear un un fichero por lo que el nombre no debe contener caracteres especiales
            if (boveda.contains(QRegularExpression("[\\/:*?\"<>|]") ))
            {
                // mostramos que no se puede crear una nota con ese nombre
                //mostrarEtiquetaAccion("No se puede crear una nota con ese nombre");
                // mostramos un dialogo de error
                QMessageBox::critical(this, "Error", "No se puede crear una nota con ese nombre");
                ok = false;
            }
        }

        if (ok && !boveda.isEmpty())
        {
            // creamos el archivo de configuracion
            std::string config = "rutaCarpetaBoveda: \"" + rutaCarpetaNotas;
            config += "\"\n";
            config += "nombreCarpetaBoveda: \"/" + boveda.toStdString() + "/\"\n";
            fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);
        } else {
            // creamos el archivo de configuracion
            std::string config = "rutaCarpetaBoveda: \"" + rutaCarpetaNotas;
            config += "\"\n";
            config = "nombreCarpetaBoveda: \"notas/\"\n";
            fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", config);

        }
        // mostramos la opcion de copiar las notas a la nueva boveda
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Copia de notas", "¿Deseas copiar las notas a la nueva carpeta?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // copiamos las notas a la nueva carpeta
            fichero.copiarFicheroNotas(rutaCarpetaNotas + nombreCarpetaNotas , rutaCarpetaNotas + "/" + boveda.toStdString());
            std::cout << "origen" << rutaCarpetaNotas + nombreCarpetaNotas << std::endl;
            std::cout << "destino" << rutaCarpetaNotas + "/" + boveda.toStdString() << std::endl;

        } else {
            // no copiamos las notas a la nueva carpeta
        }


        // actualizamos la configuracion
        verificacionInicial(true); // indicamos que es una iteracion interna
        // actualizamos las etiquetas y botones de la configuracion
        actualizarConfiguracion();
        // mostramos una etiqueta de accion indicando que acabamos de actualizar la ruta de la boveda
        mostrarEtiquetaAccionConfiguracion("Acabas de actualizar el nombre de la boveda");
    } catch (const std::exception &e)
    {
        // mostramos el error en una ventana
        QMessageBox::critical(this, "Error", e.what());
        // acaba de suceder un error por lo que ideal realizar una verificacion inicial
        verificacionInicial(true); // indicamos que es una iteracion interna
        // actualizamos las etiquetas y botones de la configuracion
        actualizarConfiguracion();
        // mostramos una etiqueta de accion indicando que acaba de pasar un error
        mostrarEtiquetaAccionConfiguracion("ERROR, NO PODEMOS ASEGURAR LA INTEGRIDAD DE LOS DATOS DE LA BOVEDA, CODIGO DE ERROR: 101011");
    }

}


void Ventana::mostrarNotasOcultass()
{
    mostrarNotasOcultas = !mostrarNotasOcultas;
    // mostramos una etiqueta de accion indicando que acabamos de actualizar el estado de las notas ocultas
    if (!mostrarNotasOcultas)
        mostrarEtiquetaAccionConfiguracion("Acabas de ocultar las notas ocultas");
    else
        mostrarEtiquetaAccionConfiguracion("Acabas de mostrar las notas ocultas");
    // actualizamos la configuracion
    verificacionInicial(true); // indicamos que es una iteracion interna
    // actualizamos las etiquetas y botones de la configuracion
    actualizarConfiguracion();

}


void Ventana::mostrarFechas()
{
    mostrarFechasNotas = !mostrarFechasNotas;
    // mostramos una etiqueta de accion indicando que acabamos de actualizar el estado de las notas ocultas
    if (!mostrarFechasNotas)
    {
        // moficaos el texto del boton
        //botonMostrarFechas->setText("Mostrar fechas");
        mostrarEtiquetaAccionConfiguracion("Acabas de ocultar las fechas");
        // ocultamos las fechas
        // // ocultamos la fecha de creacion de la nota
        // etiquetaFechaCreacion->hide();
        // ocultamos la fecha de modificacion de la nota
        etiquetaFechaModificacion->hide();
    }
    else
    {
        // moficaos el texto del boton
        //botonMostrarFechas->setText("Ocultar fechas");
        mostrarEtiquetaAccionConfiguracion("Acabas de mostrar las fechas");
        // mostramos las fechas
        // // mostramos la fecha de creacion de la nota
        // etiquetaFechaCreacion->show();
        // mostramos la fecha de modificacion de la nota
        etiquetaFechaModificacion->show();
    }

    // procedemos a modificar el archivo de configuracion
    // generamos un objeto de tipo ManejoFicheros
    ManejoFicheros fichero;
    // verificamos que exista la carpeta de configuracion
    if (!fichero.existeCarpeta(*nombreCarpetaConfiguracion))
    {
        // si no existe llamamos a verificacionInicial
        verificacionInicial(true); // indicamos que es una iteracion interna
    }
    // luego leemos el archivo de configuracion
    std::string configuracion = fichero.leerFichero(*nombreCarpetaConfiguracion + "configuracion.tak");
    std::string valor{mostrarFechasNotas ? "true" : "false"};
    // buscamos la posicion de la palabra mostrarFechasNotas
    int posicion = configuracion.find("mostrarFechasNotas: ");
    // asignamos configuracion hasta la posicion de mostrarFechasNotas a configuracion
    configuracion = configuracion.substr(0, posicion);
    // agregamos el nuevo valor de mostrarFechasNotas
    configuracion += "mostrarFechasNotas: \"" + valor + "\"\n";
    // guardamos en el archivo de configuracion
    fichero.escribirFichero(*nombreCarpetaConfiguracion + "configuracion.tak", configuracion);



    // actualizamos la configuracion
    verificacionInicial(true); // indicamos que es una iteracion interna
    // actualizamos las etiquetas y botones de la configuracion
    actualizarConfiguracion();

}

// --Metodos para aumentar y disminuir el zoom del QTextEdit--
void Ventana::aumentarZoom()
{
    // aumentamos el zoom del QTextEdit
    contenidoNota->zoomIn();

    // mostramos una etiqueta de accion indicando que acabamos de aumentar el zoom
    mostrarEtiquetaAccionConfiguracion("Acabas de aumentar el zoom");
}

void Ventana::disminuirZoom()
{
    // disminuimos el zoom del QTextEdit
    contenidoNota->zoomOut();
    // mostramos una etiqueta de accion indicando que acabamos de disminuir el zoom
    mostrarEtiquetaAccionConfiguracion("Acabas de disminuir el zoom");
}

// -- METODOS PARA SELECCIONAR LETRAS A PARTIR DE LA POSICION DEL CURSOR --
void Ventana::seleccionarLetraIzquierda()
{
    // verificamos si tenemos un item de la lista de notas seleccionado
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccioanda");
        return;
    }
    // extraemos el cursor de la nota
    QTextCursor cursor = contenidoNota->textCursor();
    // verificamos si la posicion del cursor es mayor a 0
    if (cursor.position() > 0)
    {
        // movemos el cursor a la izquierda
        //cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        // seleccionamos la letra
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);

        // colocamos el cursor en la posicion extraida
        contenidoNota->setTextCursor(cursor);
    }
}

void Ventana::seleccionarLetraDerecha()
{
    // verificamos si tenemos un item de la lista de notas seleccionado
    if (listaNotas->currentItem() == nullptr)
    {
        // no hay una nota seleccionada
        mostrarEtiquetaAccion("No hay una nota seleccioanda");
        return;
    }
    // extraemos el cursor de la nota
    QTextCursor cursor = contenidoNota->textCursor();
    // verificamos si la posicion del cursor es menor al tamaño del texto
    if (cursor.position() < contenidoNota->toPlainText().size())
    {
        // seleccionamos la letra
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
        // colocamos el cursor en la posicion extraida
        contenidoNota->setTextCursor(cursor);

    }
}
