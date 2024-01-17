#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QTextEdit>
#include <QFrame>
#include <QPushButton>
#include <QListWidget>
#include <QBoxLayout>
#include <QLabel>
// para sonido del boton
#include <QtMultimedia/QMediaPlayer>
/*
El objetivo de la clase es crear la ventana principal de mi app de notas.
como tal tendra un frame que contiene el menu, y otro frame que contiene el contenido
El frame del menu se puede reducir, mostrando solo el icono para volverlo a agrandar,
dentro de este frame en la parte inferior se mostrara una lista de notas a las cuales
se podra acceder dando click sobre ellas
El frame contenido mostrara el contenido de la nota de haber alguna seleccionada
*/

class Ventana : public QWidget
{
    Q_OBJECT
private:
    // aqui van los widgets
    // agregamos una fuente
    QFont *fuente;
    // agregamos el nombre de la carpeta donde se guardaran las notas
    std::string nombreCarpeta;
    // mostrar notas ocultas
    bool mostrarNotasOcultas;
    // mostrar fechas
    bool mostrarFechasNotas;



    // STRING DE CONFIGURACION
    // agregamos la ruta de la boveda
    std::string configuracion;
    // string que se usa en la funcion que muestra por unos segundos un mensaje en la interfaz grafica de configuracion, es parte de la construccion del label de accion
    std::string accionConfiguracion;

    // STRINGS QUE MUESTRAN LA FECHA DE CREACION DE LA NOTA Y FECHA DE MODIFICACION
    std::string fechaCreacion;
    std::string fechaModificacion;

    // agregamos el nombre de la carpeta de configuracion
    std::string* nombreCarpetaConfiguracion;
    // string que contiene la ruta de la carpeta de notas, se usa en el area de configuracion (interfaz grafica)
    std::string rutaCarpetaNotas;
    // string que contiene el nombre de la carpeta de notas, se usa en el area de configuracion (interfaz grafica)
    std::string nombreCarpetaNotas;

    // primero un frame que contendra toda la ventana
    QFrame *frame;
    // luego un frame que contendra el menu
    QFrame *frameMenu;
    // creamos un frame que contenga las opciones de configuracion
    QFrame *frameConfiguracion;
    // luego creamos un layout para el menu
    QHBoxLayout *layoutMenu;
    // luego un frame que contendra el contenido
    QFrame *frameContenido;
    // luego los botones del menu
    QPushButton *botonOcultar;
    QPushButton *botonMostrar;
    QPushButton *botonNuevaNota;
    QPushButton *botonGuardarNota;
    QPushButton *botonGuardarNota2;
    QPushButton *botonEliminarNota;
    QPushButton *botonEliminarNota2;
    QPushButton *botonAgregarImagen;
    QPushButton *botonAgregarImagen2;
    QPushButton *botonCambiarFuente;
    QPushButton *botonCambiarColor;
    QPushButton *botonCambiarColorFondo;
    QPushButton *botonConfiguracion;


    // --BOTON DE CONFIGURACION--
    QPushButton *botonSeleccionarRutaBoveda;
    QPushButton *botonSeleccionarNombreBoveda;
    QPushButton *botonOcultarConfiguracion;
    QPushButton *botonMostrarNotasOcultas;
    QPushButton *botonMostrarFechas;

    // --ETIQUETAS --
    // --ETIQUETAS DE CONTENIDO--
    // luego la etiqueta del nombre de la nota
    QLabel *etiquetaNombre;
    // creamos una etiqueta que nombra a alguna accion realizada
    QLabel *etiquetaAccion;
    QLabel *etiquetaFechaCreacion; // etiqueta que muestra la fecha de creacion de la nota
    QLabel *etiquetaFechaModificacion; // etiqueta que muestra la fecha de modificacion de la nota


    // --ETIQUETAS DE CONFIGURACION--
    // etiqueta para mostrar la ruta de la carpeta de notas
    QLabel *etiquetaAccionConfiguracion;
    // etiqueta para mostrar el nombre de la carpeta de notas
    QLabel *etiquetaConfiguracion;




    // luego la lista de notas
    QListWidget *listaNotas;
    // luego el contenido de la nota
    QTextEdit *contenidoNota;
    // luego las imagenes de los botones
    QPixmap *iconoOcultar;
    QPixmap *iconoMostrar;
    QPixmap *iconoNuevaNota;
    QPixmap *iconoGuardarNota;
    QPixmap *iconoEliminarNota;
    QPixmap *iconoAgregarImagen;
    QPixmap *iconoCambiarFuente;
    QPixmap *iconoCambiarColor;
    QPixmap *iconoCambiarColorFondo;
    QPixmap *iconoConfiguracion;
    // --ICONOS DE CONFIGURACION--
    QPixmap *iconoSeleccionarRutaBoveda;
    QPixmap *iconoSeleccionarNombreBoveda;
    QPixmap *iconoMostrarNotasOcultas;

    // tamaño de los botones
    int tamBoton;
    // sonido del boton
    QMediaPlayer *sonidoBoton;



    // metodo para actualizar la lista de notas
    void actualizarListaNotas();
    void verificacionInicial(bool iteracion = false);
    // metodo para insertar imagenes

    // metodo para usar comandos de teclado
    void keyPressEvent(QKeyEvent *event) override;

    // QString para el nombre de la nota seleccionada actualmente
    QString nombreNotaActual;
    // QString con la accion realizada
    QString accionRealizada;


    // metodo para mostrar la etiqueta con un mensaje dado
    void mostrarEtiquetaAccion(const QString& mensaje);

    // metodo para mostrar la etiqueta de accion de configuracion
    void mostrarEtiquetaAccionConfiguracion(const QString& mensaje);

    // metodo para redimensionar imagenes dentro de QTextEdit
    void redimensionarImagenes();
    QString redimensionarAnchoAltoImagenes(const QString &html);
    // booleano que me indica si puedo o no redimencionar una imagen
    bool puedoRedimensionarImagenes;



public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();
private slots:
    // aqui van los slots
    void ocultarMenu();
    void mostrarMenu();
    void ocultarConfiguracion();
    void mostrarConfiguracion();
    //void ocultarContenido();
   // void mostrarContenido();
    void nuevaNota();
    void guardarNota();
    void eliminarNota();
    void seleccionarNota();
    void insertarImagen();
    void cambiarFuente();
    void cambiarColor();
    void cambiarColorFondo();
    void ocultarEtiquetaAccion();
    void ocultarEtiquetaAccionConfiguracion();
    void cambiarEstadoPuedoRedimensionarImagenes();
    // --SLOTS DE CONFIGURACION--
    void seleccionarRutaBoveda();
    void seleccionarNombreBoveda();
    void mostrarNotasOcultass();
    void mostrarFechas();

    // metodo para actualizar la ruta de la carpeta de notas
    void actualizarConfiguracion();



signals:


protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // VENTANA_H
