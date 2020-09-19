#ifndef FENETRE_AFFICHAGE_RESEAU_GL_H
#define FENETRE_AFFICHAGE_RESEAU_GL_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>

#include "reseau.h"

class Fenetre_affichage_reseau : public QOpenGLWindow
{
    Q_OBJECT

public:
    Fenetre_affichage_reseau(Reseau* reseau, QWidget *parent = nullptr);
    ~Fenetre_affichage_reseau();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *keyEvent);

private:
    void afficher_neurone(Neurone* neurone, float r, int num_segments, int height, int width, double absolue_max_activation_synapse);
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;
    double zoomScale;
    double translationX;
    double translationY;
    Reseau* reseau;
    double largeur_absolue_max_poid;
};

#endif // FENETRE_AFFICHAGE_RESEAU_GL_H
