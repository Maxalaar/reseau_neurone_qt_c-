#include "neurone.h"

Neurone::Neurone(double (*fonction_combinaison)(double, QVector<Neurone*>, QVector<double*>), double (*fonction_activation)(double), double (*derivee_fonction_activation)(double))
{
    this->fonction_combinaison = fonction_combinaison;
    this->fonction_activation = fonction_activation;
    this->derivee_fonction_activation = derivee_fonction_activation;
    this->biais = 0;    //Un nan serait mieux
}

void Neurone::set_valeur_activation(double valeur_activation)
{
    this->valeur_activation = valeur_activation;
}

double Neurone::get_valeur_activation()
{
    return valeur_activation;
}

QVector<Neurone*>* Neurone::set_tab_neurone_sortie()
{
    return &tab_neurone_sortie;
}

QVector<Neurone*>* Neurone::set_tab_neurone_entree()
{
    return &tab_neurone_entree;
}

void Neurone::set_valeur_erreur(double valeur_erreur)
{
    this->valeur_erreur = valeur_erreur;
}

double Neurone::get_valeur_erreur()
{
    return valeur_erreur;
}

QVector<double *>* Neurone::get_tab_poid_synapse_entree()
{
    return &tab_poid_synapse_entree;
}

void Neurone::activation()
{
    //On applique la fonction de combinaisont
    somme_entree = fonction_combinaison(biais, tab_neurone_entree, tab_poid_synapse_entree);

    //On applique la fonction d'activation
    valeur_activation = fonction_activation(somme_entree);
}

void Neurone::correction(double taux_apprentissage)
{
    //Pour la couche de sortie
    if(tab_neurone_sortie.size() == 0)
    {
        //On corrige le poid du biais
        biais = biais + taux_apprentissage * valeur_erreur * derivee_fonction_activation(somme_entree); //Je ne suis pas sur !

        //On corrige tous les poid qui pointe vers ce neurone
        for(int i = 0; i < tab_neurone_entree.size(); i++)
        {
            *tab_poid_synapse_entree[i] = *tab_poid_synapse_entree[i] + taux_apprentissage * tab_neurone_entree[i]->valeur_activation * valeur_erreur * derivee_fonction_activation(somme_entree);
        }
    }
    //Pour les autres couches
    else
    {
        //On fait la somme des valeurs d'erreur de la couche suivante
        double somme_erreur_prov = 0;

        for(int i = 0; i < tab_neurone_sortie.size(); i++)
        {
            somme_erreur_prov += *tab_poid_synapse_sortie[i] * tab_neurone_sortie[i]->get_valeur_erreur();
        }

        //On calcule l'erreur de ce neurone
        valeur_erreur = derivee_fonction_activation(somme_entree) * somme_erreur_prov;

        //On corrige le poid du biais
        biais = biais + taux_apprentissage * valeur_erreur; //Je ne suis pas sur !

        //On corrige tous les poid qui pointe vers ce neurone
        for(int i = 0; i < tab_neurone_entree.size(); i++)
        {
            *tab_poid_synapse_entree[i] = *tab_poid_synapse_entree[i] + taux_apprentissage * tab_neurone_entree[i]->valeur_activation * valeur_erreur;
        }


    }
}

void Neurone::ajouter_neurone_entee(Neurone* neurone_entree, double poid_lien)
{
    //On ajoute les deux neurone à leur tableau respectif (entrée ou sortie)
    tab_neurone_entree.push_back(neurone_entree);
    neurone_entree->set_tab_neurone_sortie()->push_back(this);

    //On fait un poiteur sur un double pour pas qu'il ne soit détruie en sortant de la fonction
    double* p_poid_lien;
    p_poid_lien = new double(poid_lien);

    //On ajoute le poid à leur tableau respectif (poid entrée ou poid sortie)
    tab_poid_synapse_entree.push_back(p_poid_lien);
    neurone_entree->tab_poid_synapse_sortie.push_back(p_poid_lien);
}

void Neurone::setBiais(double value)
{
    biais = value;
}

QVector<Neurone *> Neurone::get_tab_neurone_entree() const
{
    return tab_neurone_entree;
}
