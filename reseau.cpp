#include "reseau.h"

void Reseau::entrainement_reseau_neurone(Reseau* reseau, QVector<QVector<double> > tab_valeur_entree, QVector<QVector<double> > tab_valeur_sortie_cible, int nombre_repetition_max)
{
    //On verifie que le tableau des valeurs entrée a la même taille que le tabableau de sortie
    if(tab_valeur_entree.size() == tab_valeur_sortie_cible.size())
    {
        //Pour le nombre de repetition on fait une retropropagation sur une configuration aléatoire
        for(int i = 0; i < nombre_repetition_max; i++){
            int nombre_aleatoire = (rand() *1.0000)/((int)RAND_MAX )*tab_valeur_entree.size();
            reseau->retropropagation(tab_valeur_entree[nombre_aleatoire], tab_valeur_sortie_cible[nombre_aleatoire]);
        }
    }
    else
    {
        qDebug() << "L'entrainement du reseau : " << reseau->get_nom() << " n'est pas possible car les dimentions des valeur_entree et les valeur_sortie_cible ne coresponde pas.";
    }
}

Reseau::Reseau(QVector<int> tableau_forme, double (*fonction_combinaison)(double, QVector<Neurone*>, QVector<double*>), double (*fonction_activation)(double), double (*derivee_fonction_activation)(double), double borne_sup, double borne_inf)
{
    //On definit les atributs du reseau
    nom = "reseau sans nom";
    taux_apprentissage = 0.01;

    this->fonction_combinaison = fonction_combinaison;
    this->fonction_activation = fonction_activation;
    this->derivee_fonction_activation = derivee_fonction_activation;

    //Pour chaque couche du reseau
    for(int i = 0; i < tableau_forme.size(); i++)
    {
        QVector<Neurone*> tableau_couche;

        //Pour chanque neurone dans la couche
        for(int j = 0; j < tableau_forme[i]; j++)
        {
            Neurone* neurone_prov = new Neurone(*fonction_combinaison, *fonction_activation, derivee_fonction_activation);

            if(i > 0)
            {
                double biais = (rand() *1.0000)/((double)RAND_MAX )*(borne_sup - borne_inf) + borne_inf;
                neurone_prov->setBiais(biais);

                for(int k = 0; k < tableau_neurone[i-1].size(); k++){
                    double poids = (rand() *1.0000)/((double)RAND_MAX )*(borne_sup - borne_inf) + borne_inf;
                    neurone_prov->ajouter_neurone_entee(tableau_neurone[i-1][k], poids);
                }
            }
            tableau_couche.push_back(neurone_prov);
        }

        tableau_neurone.push_back(tableau_couche);
    }
}

void Reseau::set_nom(QString nom)
{
    this->nom = nom;
}

QString Reseau::get_nom()
{
    return nom;
}

QVector<QVector<Neurone*> > Reseau::get_tableau_neurone()
{
    return tableau_neurone;
}

QVector<double> Reseau::activation(QVector<double> valeur_entree)
{
    //On verifie que le tableau des valeurs entrée a la même taille que la couche d'entrée du reseau
    if(valeur_entree.size() == tableau_neurone[0].size())
    {
        //On injecte les valeur d'entrée dans la couche d'entrée
        for(int i = 0; i < valeur_entree.size(); i++){
            tableau_neurone[0][i]->set_valeur_activation(valeur_entree[i]);
        }

        //On active chaque neurone du réseau couche par couche
        for(int i = 1; i < tableau_neurone.size(); i++){

            QVector<Thread_activation_neurone*> tableau_thread_activation;

//            for(int j = 0; j < tableau_neurone[i].size(); j++){
//                Thread_activation_neurone* activation_neurone = new Thread_activation_neurone(tableau_neurone[i][j]);
//                activation_neurone->start();
//                tableau_thread_activation.push_back(activation_neurone);
//            }

//            for(int j = 0; j < tableau_neurone[i].size(); j++){
//                  tableau_thread_activation[j]->wait();
//            }

            for(int j = 0; j < tableau_neurone[i].size(); j++){
                tableau_neurone[i][j]->activation();
            }
        }

        //On récupère les valeur de la couche de sortie
        QVector<double> resultat;
        for(int i = 0; i < tableau_neurone[tableau_neurone.size()-1].size(); i++){
            resultat.push_back(tableau_neurone[tableau_neurone.size()-1][i]->get_valeur_activation());
        }

        return resultat;
    }
    else
    {
        qDebug() << "L'activation du reseau : " << nom << " n'est pas possible car les dimentions de la premier couche et les valeurs d'entrees ne coresponde pas.";
    }
}

double Reseau::retropropagation(QVector<double> valeur_entree, QVector<double> valeur_sortie_cible)
{
    if(valeur_sortie_cible.size() == tableau_neurone[tableau_neurone.size()-1].size())
    {   
        //On active le reseau de neurone
        QVector<double> resultat;
        resultat = activation(valeur_entree);
        double erreur_sortie;

        //On calcule et on injecte la valeur d'erreur de chaque neurone de la couche de sortie
        for(int i = 0; i < tableau_neurone[tableau_neurone.size()-1].size(); i++)
        {
            erreur_sortie = valeur_sortie_cible[i] - tableau_neurone[tableau_neurone.size()-1][i]->get_valeur_activation();
            tableau_neurone[tableau_neurone.size()-1][i]->set_valeur_erreur(erreur_sortie);
        }

        //On applique la fonction correction a chaque neurone (sauf a la couche d'entrée)
        for(int i = tableau_neurone.size()-1; i > 0; i--){
            for(int j = 0; j < tableau_neurone[i].size(); j++){
                tableau_neurone[i][j]->correction(taux_apprentissage);
            }
        }
        return erreur_sortie;
    }
    else
    {
        qDebug() << "La retropropagation du reseau : " << nom << " n'est pas possible car les dimentions de la dernière couche et les valeurs de sorties ne coresponde pas.";
    }
}
