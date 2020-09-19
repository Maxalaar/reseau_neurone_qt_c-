#ifndef FONCTION_H
#define FONCTION_H

#include <QVector>
#include <QtMath>

#import "neurone.h"

double fonction_combinaison_somme(double biais, QVector<Neurone*> tab_neurone_entree, QVector<double*> tab_poid_synapse_entree);

double fonction_activation_ReLU6(double combinaison);

double fonction_activation_ReLU(double combinaison);
double derivee_fonction_activation_ReLU(double combinaison);

double fonction_activation_Leaky_ReLU(double combinaison);
double derivee_fonction_activation_Leaky_ReLU(double combinaison);

double fonction_activation_sigmoide(double combinaison);
double derivee_fonction_activation_sigmoide(double combinaison);

#endif // FONCTION_H
