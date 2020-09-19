#include <QApplication>
#include <QPushButton>
#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QtOpenGL>

#import "neurone.h"
#import "reseau.h"
#import "fenetre_affichage_reseau.h"
#import "fenetre_affichage_entrainement.h"
#import "menu_principal.h"
#import "fonction_calcul.h"

//double fonction_combinaison_somme(double biais, QVector<Neurone*> tab_neurone_entree, QVector<double*> tab_poid_synapse_entree)
//{
//    double combinaison = 0;

//    combinaison += biais;

//    for(int i = 0; i < tab_neurone_entree.size(); i++)
//    {
//        combinaison += tab_neurone_entree[i]->get_valeur_activation()*(*tab_poid_synapse_entree[i]);
//    }

//    return combinaison;
//}

//double derivee_fonction_activation_ReLU6(double combinaison)
//{
//    double derivee;

//    if(combinaison < 0){
//        derivee = 0;
//    } else if(combinaison > 6){
//        derivee = 0;
//    } else {
//        derivee = 1;
//    }

//    return derivee;
//}

//double fonction_activation_ReLU(double combinaison)
//{
//    double activation;

//    if(combinaison < 0){
//        activation = 0;
//    } else {
//        activation = combinaison;
//    }

//    return (double)activation;
//}

//double derivee_fonction_activation_ReLU(double combinaison)
//{
//    double derivee;

//    if(combinaison < 0){
//        derivee = 0;
//    } else {
//        derivee = 1;
//    }

//    return derivee;
//}

//double fonction_activation_Leaky_ReLU(double combinaison)
//{
//    double activation;

//    if(combinaison < 0){
//        activation = combinaison*0.1;
//    } else {
//        activation = combinaison;
//    }

//    return (double)activation;
//}

//double derivee_fonction_activation_Leaky_ReLU(double combinaison)
//{
//    double derivee;

//    if(combinaison < 0){
//        derivee = 0.1;
//    } else {
//        derivee = 1;
//    }

//    return derivee;
//}

//double fonction_activation_sigmoide(double combinaison)
//{
//    return 1/(1+qExp(-combinaison));
//}

//double derivee_fonction_activation_sigmoide(double combinaison)
//{
//    return fonction_activation_sigmoide(combinaison)*(1-fonction_activation_sigmoide(combinaison));
//}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);

    //C'est pour le test
//    fenetre_affichage_entrainement = new Fenetre_affichage_entrainement();
//    fenetre_affichage_entrainement->show();

    Menu_principal* menu_principal = new Menu_principal();
    menu_principal->show();

    //Création du reseau de neurone

    QVector<int> tableau_forme;
    tableau_forme.push_back(2);
//    tableau_forme.push_back(8);
//    tableau_forme.push_back(4);
//    tableau_forme.push_back(4);
    tableau_forme.push_back(20);
    tableau_forme.push_back(10);
    tableau_forme.push_back(20);
//    tableau_forme.push_back(10);
//    tableau_forme.push_back(13);
    tableau_forme.push_back(1);

//    Reseau *reseau_test = new Reseau(tableau_forme, *fonction_combinaison_somme, *fonction_activation_Leaky_ReLU, *derivee_fonction_activation_Leaky_ReLU, 1, -1);
//    Fenetre_affichage_reseau fenetre_reseau(reseau_test);
//    fenetre_reseau.show();

//    //Création des valeur d'entrainement
//    QVector<QVector<double> > tab_valeur_entree;
//    QVector<QVector<double> > tab_valeur_sortie_cible;

//    //cas1
//    QVector<double> valeur_entre1;
//    valeur_entre1.push_back(0);
//    valeur_entre1.push_back(0);

//    QVector<double> valeur_sortie1;
//    valeur_sortie1.push_back(0);

//    tab_valeur_entree.push_back(valeur_entre1);
//    tab_valeur_sortie_cible.push_back(valeur_sortie1);

//    //cas2
//    QVector<double> valeur_entre2;
//    valeur_entre2.push_back(1);
//    valeur_entre2.push_back(0);

//    QVector<double> valeur_sortie2;
//    valeur_sortie2.push_back(1);

//    tab_valeur_entree.push_back(valeur_entre2);
//    tab_valeur_sortie_cible.push_back(valeur_sortie2);

//    //cas3
//    QVector<double> valeur_entre3;
//    valeur_entre3.push_back(0);
//    valeur_entre3.push_back(1);

//    QVector<double> valeur_sortie3;
//    valeur_sortie3.push_back(1);

//    tab_valeur_entree.push_back(valeur_entre3);
//    tab_valeur_sortie_cible.push_back(valeur_sortie3);

//    //cas4
//    QVector<double> valeur_entre4;
//    valeur_entre4.push_back(1);
//    valeur_entre4.push_back(1);

//    QVector<double> valeur_sortie4;
//    valeur_sortie4.push_back(0);


//    tab_valeur_entree.push_back(valeur_entre4);
//    tab_valeur_sortie_cible.push_back(valeur_sortie4);

//    //Application
//    QVector<double> resultat;

////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);
////    reseau->retropropagation(valeur_entre, valeur_sortie);

////    Reseau::entrainement_reseau_neurone(reseau, tab_valeur_entree, tab_valeur_sortie_cible, 50000);

////    for(int i = 0; i < 5000; i++)
////    {
////       QVector<double> valeur_entre_A;
////        valeur_entre_A.push_back(1);
////      valeur_entre_A.push_back(1);

////      QVector<double> valeur_sortie_A;
////       valeur_sortie_A.push_back(0.5);

////      reseau->retropropagation(valeur_entre_A, valeur_sortie_A);

////        reseau->retropropagation(valeur_entre1, valeur_sortie1);
////        reseau->retropropagation(valeur_entre2, valeur_sortie2);
////        reseau->retropropagation(valeur_entre3, valeur_sortie3);
////        reseau->retropropagation(valeur_entre4, valeur_sortie4);
////    }


//    //Affichage
////    Fenetre_affichage_reseau fenetre_reseau(reseau);
////    fenetre_reseau.show();

////    for(int i = 0; i < 10; i++){
////        i = 0;
////    }


////    resultat = reseau->activation(valeur_entre1);

////    for(int i = 0; i < resultat.size(); i++)
////    {
////        qDebug() << resultat[i];
////    }

////    resultat = reseau->activation(valeur_entre2);

////    for(int i = 0; i < resultat.size(); i++)
////    {
////        qDebug() << resultat[i];
////    }

////    resultat = reseau->activation(valeur_entre4);

////    for(int i = 0; i < resultat.size(); i++)
////    {
////        qDebug() << resultat[i];
////    }

////    resultat = reseau->activation(valeur_entre3);

////    for(int i = 0; i < resultat.size(); i++)
////    {
////        qDebug() << resultat[i];
////    }


    return app.exec();
}
