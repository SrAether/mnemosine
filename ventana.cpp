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

    // ruta de carpeta
    nombreCarpeta = "./notas/";

    // etiqueta de nombre
    std::string nombre = "Mnemosine";

    // etiqueta de accion
    std::string accion = "Se acaba de abrir una nota";


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

    // fijamos el tamaño de los botones (iconos de los mismos)
    tamBoton = 50;

    // luego creamos los botones del menu

    // boton ocultar
    botonOcultar = new QPushButton{frameMenu};
    botonOcultar->setGeometry(0, 0, tamBoton, tamBoton);
    botonOcultar->setFont(*fuente);
    botonOcultar->setIcon(QIcon{*iconoOcultar});
    botonOcultar->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonOcultar->setMaximumSize(tamBoton, tamBoton);
    botonOcultar->setToolTip("Boton para ocultar la lista de notas /n Ctrl + O");

    // boton mostrar
    botonMostrar = new QPushButton{frameContenido};
    botonMostrar->setGeometry(5, 10, tamBoton, tamBoton);
    botonMostrar->setFont(*fuente);
    botonMostrar->setIcon(QIcon{*iconoMostrar});
    botonMostrar->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonMostrar->setMaximumSize(tamBoton, tamBoton);
    botonMostrar->setToolTip("Boton para mostrar la lista de notas /n Ctrl + M");
    botonMostrar->hide();


    // boton nueva nota
    botonNuevaNota = new QPushButton{frameMenu};
    botonNuevaNota->setGeometry(0, 50, tamBoton, tamBoton);
    botonNuevaNota->setFont(*fuente);
    botonNuevaNota->setIcon(QIcon{*iconoNuevaNota});
    botonNuevaNota->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonNuevaNota->setMaximumSize(tamBoton, tamBoton);
    botonNuevaNota->setToolTip("Boton para crear una nueva nota /n Ctrl + N");

    // boton guardar nota
    botonGuardarNota = new QPushButton{frameMenu};
    botonGuardarNota->setGeometry(0, 100, tamBoton, tamBoton);
    botonGuardarNota->setFont(*fuente);
    botonGuardarNota->setIcon(QIcon{*iconoGuardarNota});
    botonGuardarNota->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonGuardarNota->setMaximumSize(tamBoton, tamBoton);
    botonGuardarNota->setToolTip("Boton para guardar la nota /n Ctrl + S");

    // boton guardar nota 2
    botonGuardarNota2 = new QPushButton{frameContenido};
    botonGuardarNota2->setGeometry(0, 100, tamBoton, tamBoton);
    botonGuardarNota2->setFont(*fuente);
    botonGuardarNota2->setIcon(QIcon{*iconoGuardarNota});
    botonGuardarNota2->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonGuardarNota2->setMaximumSize(tamBoton, tamBoton);
    botonGuardarNota2->setToolTip("Boton para guardar la nota /n Ctrl + S");
    botonGuardarNota2->hide();

    // boton eliminar nota
    botonEliminarNota = new QPushButton{frameMenu};
    botonEliminarNota->setGeometry(0, 150, tamBoton , tamBoton);
    botonEliminarNota->setFont(*fuente);
    botonEliminarNota->setIcon(QIcon{*iconoEliminarNota});
    botonEliminarNota->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonEliminarNota->setMaximumSize(tamBoton, tamBoton);
    botonEliminarNota->setToolTip("Boton para eliminar la nota /n Ctrl + E");

    // boton eliminar nota 2
    botonEliminarNota2 = new QPushButton{frameContenido};
    botonEliminarNota2->setGeometry(0, 150, tamBoton, tamBoton);
    botonEliminarNota2->setFont(*fuente);
    botonEliminarNota2->setIcon(QIcon{*iconoEliminarNota});
    botonEliminarNota2->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonEliminarNota2->setMaximumSize(tamBoton, tamBoton);
    botonEliminarNota2->setToolTip("Boton para eliminar la nota /n Ctrl + E");
    botonEliminarNota2->hide();

    // boton para agregar imagen
    botonAgregarImagen = new QPushButton{frameMenu};
    botonAgregarImagen->setGeometry(0, 200, tamBoton, tamBoton);
    botonAgregarImagen->setFont(*fuente);
    botonAgregarImagen->setIcon(QIcon{*iconoAgregarImagen});
    botonAgregarImagen->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonAgregarImagen->setMaximumSize(tamBoton, tamBoton);
    botonAgregarImagen->setToolTip("Boton para agregar una imagen /n Ctrl + I");

    // boton para agregar imagen 2
    botonAgregarImagen2 = new QPushButton{frameContenido};
    botonAgregarImagen2->setGeometry(0, 200, tamBoton, tamBoton);
    botonAgregarImagen2->setFont(*fuente);
    botonAgregarImagen2->setIcon(QIcon{*iconoAgregarImagen});
    botonAgregarImagen2->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonAgregarImagen2->setMaximumSize(tamBoton, tamBoton);
    botonAgregarImagen2->setToolTip("Boton para agregar una imagen /n Ctrl + I");
    botonAgregarImagen2->hide();

    // boton para cambiar tipo de texto
    botonCambiarFuente = new QPushButton{frameContenido};
    botonCambiarFuente->setGeometry(0, 250, tamBoton, tamBoton);
    botonCambiarFuente->setFont(*fuente);
    botonCambiarFuente->setIcon(QIcon{*iconoCambiarFuente});
    botonCambiarFuente->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonCambiarFuente->setMaximumSize(tamBoton, tamBoton);
    botonCambiarFuente->setToolTip("Boton para cambiar el tipo de texto /n Ctrl + F");
    botonCambiarFuente->hide();

    // boton para cambiar color de texto
    botonCambiarColor = new QPushButton{frameContenido};
    botonCambiarColor->setGeometry(0, 300, tamBoton, tamBoton);
    botonCambiarColor->setFont(*fuente);
    botonCambiarColor->setIcon(QIcon{*iconoCambiarColor});
    botonCambiarColor->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonCambiarColor->setMaximumSize(tamBoton, tamBoton);
    botonCambiarColor->setToolTip("Boton para cambiar el color de texto /n Ctrl + G");
    botonCambiarColor->hide();

    // boton para cambiar color de fondo
    botonCambiarColorFondo = new QPushButton{frameContenido};
    botonCambiarColorFondo->setGeometry(0, 350, tamBoton, tamBoton);
    botonCambiarColorFondo->setFont(*fuente);
    botonCambiarColorFondo->setIcon(QIcon{*iconoCambiarColorFondo});
    botonCambiarColorFondo->setIconSize(QSize{tamBoton - 5, tamBoton - 5});
    botonCambiarColorFondo->setMaximumSize(tamBoton, tamBoton);
    botonCambiarColorFondo->setToolTip("Boton para cambiar el color de fondo /n Ctrl + H");
    botonCambiarColorFondo->hide();


    // luego creamos la etiqueta del nombre de la nota
    etiquetaNombre = new QLabel{QString::fromStdString(nombre), frameContenido};
    etiquetaNombre->setFont(*fuente);
    etiquetaNombre->hide();

    // luego creamos la etiqueta de accion de la nota
    etiquetaAccion = new QLabel{QString::fromStdString(accion), frameContenido};
    etiquetaAccion->setFont(*fuente);
    etiquetaAccion->hide();

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
    contentLayout2->addWidget(botonMostrar);
    contentLayout2->addWidget(botonGuardarNota2);
    contentLayout2->addWidget(botonEliminarNota2);
    contentLayout2->addWidget(botonAgregarImagen2);
    contentLayout2->addWidget(botonCambiarFuente);
    contentLayout2->addWidget(botonCambiarColor);
    contentLayout2->addWidget(botonCambiarColorFondo);
    contentLayout2->addWidget(etiquetaNombre);
    contentLayout2->addWidget(etiquetaAccion);
    contentLayout2->addStretch(1);
    //contentLayout->setMargin(0);
    contentLayout->addLayout(contentLayout2);
    contentLayout->addWidget(contenidoNota);

    // Layout principal de la ventana
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(frameMenu);
    mainLayout->addWidget(frameContenido); // El contenido se expande



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
    // actualizamos la lista de notas
    verificacionInicial();
    actualizarListaNotas();








}

void Ventana::ocultarMenu()
{
    // guardamos la posicion del cursor de la nota
    //QTextCursor cursor = contenidoNota->textCursor();
    // guardamos la posicion del scroll
    // scroll = contenidoNota->verticalScrollBar();
    // guardamos el formato del texto
    //QTextCharFormat formato = contenidoNota->currentCharFormat();
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
    etiquetaNombre->show();

    // cambiamos el nombre de la nota
    if (listaNotas->currentItem() != nullptr)
    {
        etiquetaNombre->setText(listaNotas->currentItem()->text());
    } else {
        etiquetaNombre->setText(const_cast<char*>("Mnemosine"));
    }
    redimensionarImagenes();

    // volvemos a colocar el cursor en la nota
    //contenidoNota->setTextCursor(cursor);
    // volvemos a colocar el formato
   // contenidoNota->setCurrentCharFormat(formato);

    // regresamos el foco a la nota
    contenidoNota->setFocus();


}

void Ventana::mostrarMenu()
{
    // guardamos la posicion del cursor de la nota
    //QTextCursor cursor = contenidoNota->textCursor();
    // extraemos la posicion del cursor
    //int posicionCursor = contenidoNota->textCursor().position();

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
    // redimensionamos las imagenes despues de 200 milisegundos
    //QTimer::singleShot(200, this, SLOT(redimensionarImagenes()));
    redimensionarImagenes();
    //std::cout << "Imagen redimensionada \n";


    // volvemos a colocar el cursor en la nota
    //contenidoNota->setTextCursor(cursor);

    // regresamos el foco a la nota
    contenidoNota->setFocus();



    // luego colocamos la posicion del cursor
    //contenidoNota->textCursor().setPosition(posicionCursor);
}

void Ventana::nuevaNota()
{
    // primero pedimos el nombre de la nota
    bool ok;
    QString nombreNota = QInputDialog::getText(this, "Nueva Nota", "Nombre de la nota:", QLineEdit::Normal, "", &ok);
    if (ok && !nombreNota.isEmpty())
    {
        // creamos una carpeta con el nombre de la nota dentro de esta guardaremos la nota y los archivos relacionados a la misma
        ManejoFicheros fichero;
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

void Ventana::actualizarListaNotas()
{
    // primero limpiamos la lista
    listaNotas->clear();
    // luego la actualizamos
    ManejoFicheros fichero;
    std::vector<std::string> notas = fichero.extraerFicheros(nombreCarpeta);
    // for (const std::string &nota : notas)
    // {
    //     listaNotas->addItem(QString::fromStdString(nota));
    // }
    // recorremos el arreglo de notas en orden decendente
    for (int i = notas.size() - 1; i >= 0; i--)
    {
        listaNotas->addItem(QString::fromStdString(notas[i]));
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

    // Primero obtenemos el nombre de la nota seleccionada
    QString nombreNota = listaNotas->currentItem()->text();

    // Luego obtenemos el contenido de la nota en formato HTML
    QString contenido = contenidoNota->toHtml();

    // Luego guardamos la nota
    ManejoFicheros fichero;
    //fichero.escribirFichero(nombreCarpeta + nombreNota.toStdString(), contenido.toStdString());
    fichero.escribirFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak", contenido.toStdString());
    mostrarEtiquetaAccion("Nota guardada");
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
        respuesta = QMessageBox::question(this, "Eliminar Nota", "¿Esta seguro de eliminar la nota \"" + nombreNota + "\"?", QMessageBox::Yes | QMessageBox::No);
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
    // primero obtenemos el nombre de la nota seleccionada
    QString nombreNota = listaNotas->currentItem()->text();

    // vamos a verificar si hubo cambios en la nota actual para guardarlos, si los hubo
    // primero verificamos que la nota actual no este vacia
    if (contenidoNota->toHtml() != "")
    {
        // verificamos si no es la primera entrada ya que en esta nombreNotaActual esta vacia
        if (nombreNotaActual != "")
        {
            // verificamos si se modifico la nota actual
            ManejoFicheros fichero;
            if (!fichero.compararStringConFichero(contenidoNota->toHtml().toStdString(), (nombreCarpeta + nombreNotaActual.toStdString() + "/" + nombreNotaActual.toStdString() + ".tak")))
            {
                // mostramos en consola que deberiamos guardar la nota
                std::cout << "deberiamos guardar la nota" << std::endl;
                // luego guardamos la nota
                fichero.escribirFichero(nombreCarpeta + nombreNotaActual.toStdString() + "/" + nombreNotaActual.toStdString() + ".tak", contenidoNota->toHtml().toStdString());
            }
        }
    }


    // Actualizamos el nombre de la nota actual
    nombreNotaActual = nombreNota;
    // mostramos el nombre en consola
    std::cout << nombreNota.toStdString() << std::endl;
    // luego obtenemos el contenido de la nota
    ManejoFicheros fichero;
    //std::string contenido = fichero.leerFichero(nombreCarpeta + nombreNota.toStdString() /*+ ".txt"*/);
    std::string contenido = fichero.leerFichero(nombreCarpeta + nombreNota.toStdString() + "/" + nombreNota.toStdString() + ".tak");
    // luego mostramos el contenido de la nota
    //contenidoNota->setText(QString::fromStdString(contenido));
    contenidoNota->setHtml(QString::fromStdString(contenido));
    // luego mostramos la accion
    mostrarEtiquetaAccion("Nota seleccionada");
    // redimensionamos las imagenes de la nota
    redimensionarImagenes();
}

void Ventana::verificacionInicial()
{
    // verificamos si existe la carpeta notas
    ManejoFicheros fichero;
    if (!fichero.existeCarpeta(nombreCarpeta))
    {
        // si no existe la creamos
        fichero.verificacionInicial(nombreCarpeta);
        std::cout << "creando carpeta contenedor" << std::endl;
        // y creamos una nota que explica los comandos basicos
        // primero creamos la carpeta de la nota
        fichero.verificacionInicial(nombreCarpeta + "comandosBasicos");
        // luego creamos la nota
        //fichero.escribirFichero(nombreCarpeta + "comandosBasicos/comandosBasicos.tak" , "Comandos Basicos: \n\nCtrl + S: Guardar nota\nCtrl + N: Crear nueva nota\nCtrl + E: Eliminar nota\nCtrl + I: Insertar imagen\nCtrl + Q: Salir de la aplicacion\nCtrl + O: Ocultar menu\nCtrl + M: Mostrar menu\nCtrl + A: Seleccionar todo\nCtrl + Z: Deshacer");
        fichero.escribirFichero(nombreCarpeta + "comandosBasicos/comandosBasicos.tak" , "<h1>Comandos Basicos:</h1><br><br><h2>Ctrl + S: Guardar nota</h2><br><h2>Ctrl + N: Crear nueva nota</h2><br><h2>Ctrl + E: Eliminar nota</h2><br><h2>Ctrl + I: Insertar imagen</h2><br><h2>Ctrl + Q: Salir de la aplicacion</h2><br><h2>Ctrl + O: Ocultar menu</h2><br><h2>Ctrl + M: Mostrar menu</h2><br><h2>Ctrl + A: Seleccionar todo</h2><br><h2>Ctrl + B: Negritas</h2><br><h2>Ctrl + Z: Deshacer</h2>");

    } else {
        std::cout << "Se encontro un contenedor" << std::endl;
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



        // // Insertar la imagen usando un formato de imagen HTML
        // QString htmlImage = QString("<img src='%1'/>").arg((nombreCarpeta + nombreNota.toStdString() + "/" + rutaImagen.split("/").last().toStdString()).c_str());
        // contenidoNota->textCursor().insertHtml(htmlImage);

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
    } else {
        event->ignore(); // Ignora el evento
    }


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
    QTimer::singleShot(3000, this, SLOT(ocultarEtiquetaAccion()));
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
    std::cout << cursor.position() << std::endl;

    // guardamos la posicion del cursor
    int posicionCursor = cursor.position();
    // mostramos el contenido de posicionCursor
    std::cout << posicionCursor << std::endl;

    // Modificamos el ancho y alto de las imágenes
    contenido = redimensionarAnchoAltoImagenes(contenido);

    // Actualizamos el contenido del QTextEdit
    contenidoNota->setHtml(contenido);


    // colocamos el cursor en la posicion extraida
    cursor.setPosition(posicionCursor);
    contenidoNota->setTextCursor(cursor);

    // volvemos a colocar el cursor en la nota
    //contenidoNota->setTextCursor(cursor);

    // // Mostramos el mensaje de acción
    // if (mensaje)
    //     mostrarEtiquetaAccion("Imágenes redimensionadas");
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







