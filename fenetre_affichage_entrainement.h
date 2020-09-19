#ifndef FENETRE_AFFICHAGE_ENTRAINEMENT_H
#define FENETRE_AFFICHAGE_ENTRAINEMENT_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>


#include "reseau.h"
#include "fonction_calcul.h"
#include "fenetre_affichage_reseau.h"

class Fenetre_affichage_entrainement : public QWidget
{
    Q_OBJECT

public:
    Fenetre_affichage_entrainement(Reseau* reseau, QWidget *parent = 0);

    QProgressBar* getProgressBar() const;
    void setProgressBar(QProgressBar *value);

    QLabel *getLabel_erreur_batch() const;
    void setLabel_erreur_batch(QLabel *value);

    QLabel *getLabel_erreur_actuel() const;

private:
    Reseau* reseau;
    //    double erreur_batch_tolere;
    //    QPushButton *bouton_quitter;

    QProgressBar *progressBar;
    QVBoxLayout *layout_principal;
    QLabel* label_erreur_batch;
    QLabel* label_erreur_actuel;


public slots:
//    void changerLargeur(int largeur);
//    void changerHauteur(int hauteur);
//    void ouvrirDialogue();

signals:
//    void agrandissementMax();
};

#endif // FENETRE_AFFICHAGE_ENTRAINEMENT_H
