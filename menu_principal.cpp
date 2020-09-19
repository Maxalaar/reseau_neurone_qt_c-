#include "menu_principal.h"

Menu_principal::Menu_principal()
{
    resize(325, 300);
    this->setWindowTitle("Menu Principale Reseau Neurone");
    layout_principal = new QHBoxLayout;

    bouton_entrainement = new QPushButton("Entrainement", this);
    QObject::connect(bouton_entrainement, SIGNAL(clicked()), this, SLOT(entrainement()));

    layout_principal->addWidget(bouton_entrainement);
    this->setLayout(layout_principal);
}

void Menu_principal::entrainement()
{

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

    Reseau* reseau = new Reseau(tableau_forme, *fonction_combinaison_somme, *fonction_activation_Leaky_ReLU, *derivee_fonction_activation_Leaky_ReLU, 1, -1);

        Fenetre_affichage_entrainement *fenetre_affichage_entrainement = new Fenetre_affichage_entrainement(reseau);

    //Création des valeur d'entrainement
    QVector<QVector<double> > tab_valeur_entree;
    QVector<QVector<double> > tab_valeur_sortie_cible;

    //cas1
    QVector<double> valeur_entre1;
    valeur_entre1.push_back(0);
    valeur_entre1.push_back(0);

    QVector<double> valeur_sortie1;
    valeur_sortie1.push_back(0);

    tab_valeur_entree.push_back(valeur_entre1);
    tab_valeur_sortie_cible.push_back(valeur_sortie1);

    //cas2
    QVector<double> valeur_entre2;
    valeur_entre2.push_back(1);
    valeur_entre2.push_back(0);

    QVector<double> valeur_sortie2;
    valeur_sortie2.push_back(1);

    tab_valeur_entree.push_back(valeur_entre2);
    tab_valeur_sortie_cible.push_back(valeur_sortie2);

    //cas3
    QVector<double> valeur_entre3;
    valeur_entre3.push_back(0);
    valeur_entre3.push_back(1);

    QVector<double> valeur_sortie3;
    valeur_sortie3.push_back(1);

    tab_valeur_entree.push_back(valeur_entre3);
    tab_valeur_sortie_cible.push_back(valeur_sortie3);

    //cas4
    QVector<double> valeur_entre4;
    valeur_entre4.push_back(1);
    valeur_entre4.push_back(1);

    QVector<double> valeur_sortie4;
    valeur_sortie4.push_back(0);


    tab_valeur_entree.push_back(valeur_entre4);
    tab_valeur_sortie_cible.push_back(valeur_sortie4);

    //Application
    //On affiche la fenetre pour l'interface graphique

//    fenetre_affichage_entrainement->show();

    Fenetre_affichage_reseau* fenetre_reseau = new Fenetre_affichage_reseau(reseau);

//    QVector<double> resultat;
    Thread_entrainement_reseau* thread_entrainement = new Thread_entrainement_reseau(reseau, tab_valeur_entree, tab_valeur_sortie_cible, 0.000, 1000, 100000, fenetre_affichage_entrainement, fenetre_reseau);
    thread_entrainement->start();

//    while(thread_entrainement->isRunning() == true){

//    }

//    Reseau::entrainement_reseau_neurone(reseau, tab_valeur_entree, tab_valeur_sortie_cible, 50000);


    //Affichage

//    fenetre_reseau->show();
}
