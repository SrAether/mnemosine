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
    // primero un frame que contendra toda la ventana
    QFrame *frame;
    // luego un frame que contendra el menu
    QFrame *frameMenu;
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
    // luego la etiqueta del nombre de la nota
    QLabel *etiquetaNombre;
    // creamos una etiqueta que nombra a alguna accion realizada
    QLabel *etiquetaAccion;
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
    // tamaño de los botones
    int tamBoton;
    // sonido del boton QSound *sonidoBoton;




    // metodo para actualizar la lista de notas
    void actualizarListaNotas();
    void verificacionInicial();
    // metodo para insertar imagenes

    // metodo para usar comandos de teclado
    void keyPressEvent(QKeyEvent *event) override;

    // QString para el nombre de la nota seleccionada actualmente
    QString nombreNotaActual;
    // QString con la accion realizada
    QString accionRealizada;


    // metodo para mostrar la etiqueta con un mensaje dado
    void mostrarEtiquetaAccion(const QString& mensaje);

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
    void nuevaNota();
    void guardarNota();
    void eliminarNota();
    void seleccionarNota();
    void insertarImagen();
    void cambiarFuente();
    void cambiarColor();
    void cambiarColorFondo();
    void ocultarEtiquetaAccion();
    void cambiarEstadoPuedoRedimensionarImagenes();


signals:

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // VENTANA_H
