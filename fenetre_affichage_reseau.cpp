#include "fenetre_affichage_reseau.h"

Fenetre_affichage_reseau::Fenetre_affichage_reseau(Reseau* reseau, QWidget *parent)
{
    //Je ne sais pas tros a quoi tous ça sert
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);

    setFormat(format);
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    openGLFunctions = context->functions();

    //On definit les paramétres d'affichage
    zoomScale = 1;
    translationX = 0;
    translationY = 0;
    largeur_absolue_max_poid = 6.5;

    this->reseau = reseau;
    this->setTitle("Reseau : " + reseau->get_nom());
    this->resize(640, 480);
}

Fenetre_affichage_reseau::~Fenetre_affichage_reseau()
{

}

void Fenetre_affichage_reseau::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta();
    if (numDegrees.y() < 0)  zoomScale = zoomScale/1.1;
    if (numDegrees.y() > 0)  zoomScale = zoomScale*1.1;

    update();
}

void Fenetre_affichage_reseau::keyPressEvent(QKeyEvent *keyEvent)
{
    double translation = 0.1/zoomScale;

    switch(keyEvent->key())
    {
        //Les fleches du clavier
        case Qt::Key_Up:
           translationY += -translation;
           update();
        break;
        case Qt::Key_Down:
           translationY += +translation;
           update();
        break;
        case Qt::Key_Right:
           translationX += -translation;
           update();
        break;
        case Qt::Key_Left:
           translationX += +translation;
           update();
        break;

        //Les touches z, q, s, d
        case Qt::Key_Z:
           translationY += -translation;
           update();
        break;
        case Qt::Key_S:
           translationY += +translation;
           update();
        break;
        case Qt::Key_D:
           translationX += -translation;
           update();
        break;
        case Qt::Key_Q:
           translationX += +translation;
           update();
        break;
    }
}

void Fenetre_affichage_reseau::afficher_neurone(Neurone* neurone, float r, int num_segments, int height, int width, double absolue_max_activation_synapse)
{
    float centre_x = neurone->position_x;
    float centre_y = neurone->position_y;

    double activation_neurone = neurone->get_valeur_activation()/absolue_max_activation_synapse;

    //On fait la bordure en noir
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON);
    glColor4f(0, 0, 0, 1);

    for(int ii = 0; ii < num_segments; ii++)
    {
     float theta = 2.0f * 3.1415926f * float(ii)/float(num_segments);

     float x = r * cosf(theta) * (float)((float)height/(float)width);
     float y = r * sinf(theta);

     glVertex2f(x + centre_x, y + centre_y);

    }
    glEnd();

    //On definie la taille de la bordure
    r = r - r * 0.1;

    //On fait le coeur en blanc
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON);
    glColor4f(1, 1, 1, 1);

    for(int ii = 0; ii < num_segments; ii++)
    {
     float theta = 2.0f * 3.1415926f * float(ii)/float(num_segments);

     float x = r * cosf(theta) * (float)((float)height/(float)width);
     float y = r * sinf(theta);

     glVertex2f(x + centre_x, y + centre_y);

    }
    glEnd();

    //On change la couleur en fonction de l'activation du neurone
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON);
    if(neurone->get_valeur_activation() < 0)
    {
        glColor4f(0, 0, 1, neurone->get_valeur_activation()/absolue_max_activation_synapse);
    }
    else
    {
        glColor4f(1, 0, 0, neurone->get_valeur_activation()/absolue_max_activation_synapse);
    }

    for(int ii = 0; ii < num_segments; ii++)
    {
     float theta = 2.0f * 3.1415926f * float(ii)/float(num_segments);

     float x = r * cosf(theta) * (float)((float)height/(float)width);
     float y = r * sinf(theta);

     glVertex2f(x + centre_x, y + centre_y);

    }
    glEnd();
}

void Fenetre_affichage_reseau::initializeGL()
{

}

void Fenetre_affichage_reseau::resizeGL(int w, int h)
{

}

void Fenetre_affichage_reseau::paintGL()
{
    //On colore le fond en blanc
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //On definie le zoom et les translations
    glLoadIdentity();
    glScaled(zoomScale, zoomScale, zoomScale);
    glTranslatef(translationX, translationY, 0);

    //On copie le tableau_neurone du réseau associer
    QVector<QVector<Neurone*> > tableau_neurone = reseau->get_tableau_neurone();

    //On cherche le nombre max de nerone sur une couche
    int max_neurone_couche = 0;

    for(int i = 0; i < tableau_neurone.size(); i++)
    {
        if(max_neurone_couche < tableau_neurone[i].size()){
            max_neurone_couche = tableau_neurone[i].size();
        }
    }

    //On cherche la valeur valeur absolue max d'un poid d'un synapse
    double absolue_max_activation_synapse = 0;

    for(int i = 0; i < tableau_neurone.size(); i++)
    {
        for(int j = 0; j < tableau_neurone[i].size(); j++)
        {
            for(int k = 0; k < tableau_neurone[i][j]->get_tab_poid_synapse_entree()->size(); k++)
            {
                if(absolue_max_activation_synapse < qFabs(*(tableau_neurone[i][j]->get_tab_poid_synapse_entree()[0][k]) * tableau_neurone[i][j]->get_tab_neurone_entree()[k]->get_valeur_activation())){
                    absolue_max_activation_synapse = qFabs(*(tableau_neurone[i][j]->get_tab_poid_synapse_entree()[0][k]) * tableau_neurone[i][j]->get_tab_neurone_entree()[k]->get_valeur_activation());
                }
            }
        }
    }

    //On cherche la valeur absolue max d'activation d'un neurone
    double absolue_max_activation_neurone = 0;

    for(int i = 0; i < tableau_neurone.size(); i++)
    {
        for(int j = 0; j < tableau_neurone[i].size(); j++)
        {
            for(int k = 0; k < tableau_neurone[i][j]->get_tab_poid_synapse_entree()->size(); k++)
            {
                if(absolue_max_activation_neurone < qFabs(tableau_neurone[i][j]->get_valeur_activation())){
                    absolue_max_activation_neurone = qFabs(tableau_neurone[i][j]->get_valeur_activation());
                }
            }
        }
    }

    //On définit les valeurs de l'affichage
    double decalage_esthetique = 0.5/(double)max_neurone_couche;
    double diametre_neurone = (double)(((double)2-decalage_esthetique*(double)(max_neurone_couche-1))/(double)max_neurone_couche);

    //On dessine chaque lien/synapse du réseau
    for(int i = 0; i < tableau_neurone.size(); i++)
    {
        for(int j = 0; j < tableau_neurone[i].size(); j++)
        {
            //On clacule les coordonnées
            double positionX = i*((double)(2-diametre_neurone*((float)((float)height()/(float)width())))/(tableau_neurone.size()-1))-1+(diametre_neurone/2*((float)((float)height()/(float)width())));
            double positionY = j*((double)2/tableau_neurone[i].size()) + ((double)1/tableau_neurone[i].size()) - 1;

            //stock les coordonnées dans le neurone associer
            tableau_neurone[i][j]->position_x = positionX;
            tableau_neurone[i][j]->position_y = positionY;

            //On affiche tous les synapse qui rentre dans le neurone
            for(int k = 0; k < tableau_neurone[i][j]->set_tab_neurone_entree()->size(); k++)
            {
                //On récupère les coordonnées du neurone d'entrée
                double x_neurone_entree = tableau_neurone[i][j]->set_tab_neurone_entree()[0][k]->position_x;
                double y_neurone_entree = tableau_neurone[i][j]->set_tab_neurone_entree()[0][k]->position_y;

                //On calcule la largeur de l'affichage du lien en fonction du absolue_max_poid
                double largeur_lien = largeur_absolue_max_poid*(qFabs(*(tableau_neurone[i][j]->get_tab_poid_synapse_entree()[0][k]) * tableau_neurone[i][j]->get_tab_neurone_entree()[k]->get_valeur_activation() / absolue_max_activation_synapse));

                //On affiche le lien si la largeur est superieur ou égale a 1
                if(largeur_lien >= 1){
                    glLineWidth(largeur_lien);
                    glBegin(GL_LINES);

                    //On choisie la couleur en fonction de si le lien est négatife ou positif
                    if(*(tableau_neurone[i][j]->get_tab_poid_synapse_entree()[0][k]) < 0)
                    {
                        glColor3f(0.25, 0.25, 1);
                    }
                    else
                    {
                        glColor3f(1, 0.25, 0.25);
                    }

                    glVertex2f(positionX, positionY);
                    glVertex2f(x_neurone_entree, y_neurone_entree);
                    glEnd();
                }
            }
        }
    }

//    //On dessine chaque neurone du reseau
    for(int i = 0; i < tableau_neurone.size(); i++)
    {
        for(int j = 0; j < tableau_neurone[i].size(); j++)
        {
            //On affiche le neurone
            afficher_neurone(tableau_neurone[i][j], diametre_neurone/2, 100, height(), width(), absolue_max_activation_synapse);
        }
    }

    glEnd();

    glFlush();
}

void Fenetre_affichage_reseau::resizeEvent(QResizeEvent *event)
{

}

void Fenetre_affichage_reseau::paintEvent(QPaintEvent *event)
{
    paintGL();
}
