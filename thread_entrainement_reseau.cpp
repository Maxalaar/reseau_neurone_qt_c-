#include "thread_entrainement_reseau.h"

Thread_entrainement_reseau::Thread_entrainement_reseau(Reseau* reseau, QVector<QVector<double> > tab_valeur_entree, QVector<QVector<double> > tab_valeur_sortie_cible, double erreur_batch_tolere, int taille_batch, int nombre_repetition_max, Fenetre_affichage_entrainement* fenetre_affichage_entrainement, Fenetre_affichage_reseau* fenetre_reseau)
{
    this->reseau = reseau;
    this->tab_valeur_entree = tab_valeur_entree;
    this->tab_valeur_sortie_cible = tab_valeur_sortie_cible;
    this->erreur_batch_tolere = erreur_batch_tolere;
    this->nombre_repetition_max = nombre_repetition_max;
    this->taille_batch = taille_batch;
    this->fenetre_affichage_entrainement = fenetre_affichage_entrainement;
    this->fenetre_reseau = fenetre_reseau;
}

void Thread_entrainement_reseau::run()
{
    QObject::connect(this, SIGNAL(nouveau_retropropagation(int)), fenetre_affichage_entrainement->getProgressBar(), SLOT(setValue(int)));
    QObject::connect(this, SIGNAL(set_text_label_erreur_batch(QString)), fenetre_affichage_entrainement->getLabel_erreur_batch(), SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(set_text_label_erreur_actuel(QString)), fenetre_affichage_entrainement->getLabel_erreur_actuel(), SLOT(setText(QString)));

    emit set_text_label_erreur_batch("L'erreur du batch toléré est : " + QString::number(erreur_batch_tolere));

    //On verifie que le tableau des valeurs entrée a la même taille que le tabableau de sortie
    if(tab_valeur_entree.size() == tab_valeur_sortie_cible.size())
    {
//        Fenetre_affichage_reseau* fenetre_affichage_reseau = new Fenetre_affichage_reseau(reseau);
        double erreur_ativation = 0;

        //Pour le nombre de repetition on fait une retropropagation sur une configuration aléatoire
        for(int i = 0; i < nombre_repetition_max; i++){

            emit nouveau_retropropagation((int)((double)i * 100 /((double) nombre_repetition_max)));
//            fenetre_affichage_entrainement->getProgressBar()->setValue(i);

//            fenetre_affichage_entrainement->getProgressBar()->setValue(8);
//            QThread::msleep(0);

            int nombre_aleatoire = (rand() *1.0000)/((int)RAND_MAX )*tab_valeur_entree.size();
            erreur_ativation += pow(reseau->retropropagation(tab_valeur_entree[nombre_aleatoire], tab_valeur_sortie_cible[nombre_aleatoire]), 2);

            if(i % taille_batch == 0 && i != 0){
                erreur_ativation = erreur_ativation/2;
                erreur_ativation = erreur_ativation/taille_batch;
                emit set_text_label_erreur_actuel("L'erreur actuelle est du batch : " + QString::number(erreur_ativation));
                if(erreur_ativation <= erreur_batch_tolere){
                    i = nombre_repetition_max + 1;
                }
                erreur_ativation = 0;
//                QThread::msleep(3000);
            }
        }
        fenetre_affichage_entrainement->close();
//        fenetre_affichage_reseau->show();
        fenetre_reseau->show();
    }
    else
    {
        qDebug() << "L'entrainement du reseau : " << reseau->get_nom() << " n'est pas possible car les dimentions des valeur_entree et les valeur_sortie_cible ne coresponde pas.";
    }
}
