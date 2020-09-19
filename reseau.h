#ifndef RESEAU_H
#define RESEAU_H

#include <QVector>
#include <QDebug>

//#include "fenetre_affichage_entrainement.h"
#import "neurone.h"
#import "thread_activation_neurone.h"

class Reseau
{
public:
    static void entrainement_reseau_neurone(Reseau*, QVector<QVector<double> > tab_valeur_entree, QVector<QVector<double> > tab_valeur_sortie_cible, int nombre_repetition_max);

    Reseau(QVector<int> tableau_forme, double (*fonction_combinaison)(double, QVector<Neurone*>, QVector<double*>), double (*fonction_activation)(double), double (*derivee_fonction_activation)(double), double borne_sup, double borne_inf);

    void set_nom(QString);
    QString get_nom();
    QVector<QVector<Neurone*> > get_tableau_neurone();
    QVector<double> activation(QVector<double> valeur_entree);
    double retropropagation(QVector<double> valeur_entree, QVector<double> valeur_sortie_cible);

//    //C'est pour le test
//    Fenetre_affichage_entrainement* fenetre_affichage_entrainement;

private:
    double (*fonction_combinaison)(double, QVector<Neurone*>, QVector<double*>);
    double (*fonction_activation)(double);
    double (*derivee_fonction_activation)(double);

    QVector<QVector<Neurone*> > tableau_neurone;
    QString nom;
    double taux_apprentissage;
};

#endif // RESEAU_H
