#ifndef NEURONE_H
#define NEURONE_H

#include <QVector>
#include <QRect>
#include <QDebug>

class Neurone
{
public:
    Neurone(double (*fonction_combinaison)(double, QVector<Neurone*>, QVector<double*>), double (*fonction_activation)(double), double (*derivee_fonction_activation)(double));

    void set_valeur_activation(double valeur_activation);
    double get_valeur_activation();
    QVector<Neurone*>* set_tab_neurone_sortie();
    QVector<Neurone*>* set_tab_neurone_entree();
    void set_valeur_erreur(double valeur_erreur);
    double get_valeur_erreur();
    QVector<double*>* get_tab_poid_synapse_entree();
    QVector<Neurone *> get_tab_neurone_entree() const;

    void activation();
    void correction(double taux_apprentissage);
    void ajouter_neurone_entee(Neurone* neurone_entree, double poid_lien);
    QRect apparence_neurone;
    double position_x;
    double position_y;

    void setBiais(double value);

private:
    QVector<Neurone*> tab_neurone_entree;
    QVector<double*> tab_poid_synapse_entree;

    QVector<Neurone*> tab_neurone_sortie;
    QVector<double*> tab_poid_synapse_sortie;

    double (*fonction_combinaison)(double, QVector<Neurone*>, QVector<double*>);
    double (*fonction_activation)(double);
    double (*derivee_fonction_activation)(double);

    double somme_entree;
    double valeur_activation;
    double valeur_erreur;
    double biais;
};

#endif // NEURONE_H
