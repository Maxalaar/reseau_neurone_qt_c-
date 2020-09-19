#include "fonction_calcul.h"

double fonction_combinaison_somme(double biais, QVector<Neurone*> tab_neurone_entree, QVector<double*> tab_poid_synapse_entree)
{
    double combinaison = 0;

    combinaison += biais;

    for(int i = 0; i < tab_neurone_entree.size(); i++)
    {
        combinaison += tab_neurone_entree[i]->get_valeur_activation()*(*tab_poid_synapse_entree[i]);
    }

    return combinaison;
}

double fonction_activation_ReLU6(double combinaison)
{
    double activation;

    if(combinaison < 0){
        activation = 0;
    } else if(combinaison > 6){
        activation = 6;
    } else {
        activation = combinaison;
    }

    return activation;
}

double fonction_activation_ReLU(double combinaison)
{
    double activation;

    if(combinaison < 0){
        activation = 0;
    } else {
        activation = combinaison;
    }

    return (double)activation;
}

double derivee_fonction_activation_ReLU(double combinaison)
{
    double derivee;

    if(combinaison < 0){
        derivee = 0;
    } else {
        derivee = 1;
    }

    return derivee;
}

double fonction_activation_Leaky_ReLU(double combinaison)
{
    double activation;

    if(combinaison < 0){
        activation = combinaison*0.1;
    } else {
        activation = combinaison;
    }

    return (double)activation;
}

double derivee_fonction_activation_Leaky_ReLU(double combinaison)
{
    double derivee;

    if(combinaison < 0){
        derivee = 0.1;
    } else {
        derivee = 1;
    }

    return derivee;
}

double fonction_activation_sigmoide(double combinaison)
{
    return 1/(1+qExp(-combinaison));
}

double derivee_fonction_activation_sigmoide(double combinaison)
{
    return fonction_activation_sigmoide(combinaison)*(1-fonction_activation_sigmoide(combinaison));
}
