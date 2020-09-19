#ifndef THREAD_ENTRAINEMENT_RESEAU_H
#define THREAD_ENTRAINEMENT_RESEAU_H

#include <QThread>

#import "reseau.h"
#import "fenetre_affichage_entrainement.h"
#import "fenetre_affichage_reseau.h"

class Thread_entrainement_reseau : public QThread
{
    Q_OBJECT

public:
    Thread_entrainement_reseau(Reseau* reseau, QVector<QVector<double> > tab_valeur_entree, QVector<QVector<double> > tab_valeur_sortie_cible, double erreur_batch_tolere, int taille_batch, int nombre_repetition_max, Fenetre_affichage_entrainement* fenetre_affichage_entrainement, Fenetre_affichage_reseau* fenetre_reseau);
    void run();

private:
    Reseau* reseau;
    QVector<QVector<double> > tab_valeur_entree;
    QVector<QVector<double> > tab_valeur_sortie_cible;
    double erreur_batch_tolere;
    int taille_batch;
    int nombre_repetition_max;
    Fenetre_affichage_entrainement* fenetre_affichage_entrainement;
    Fenetre_affichage_reseau* fenetre_reseau;

signals:
    void nouveau_retropropagation(int value);
    void set_text_label_erreur_batch(QString);
    void set_text_label_erreur_actuel(QString);
};

#endif // THREAD_ENTRAINEMENT_RESEAU_H
