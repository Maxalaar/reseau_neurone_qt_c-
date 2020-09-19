#include "fenetre_affichage_entrainement.h"

Fenetre_affichage_entrainement::Fenetre_affichage_entrainement(Reseau* reseau, QWidget *parent) : QWidget(parent)
{
    this->reseau = reseau;

//    setFixedSize(400, 250);
    this->setWindowTitle("Entrainement du reseau : " + reseau->get_nom());
    layout_principal = new QVBoxLayout;

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setGeometry(10, 10, 150, 20);
    progressBar->setValue(50);

    label_erreur_batch = new QLabel;
    label_erreur_batch->setText("Cette zonne de text n'arive pas a communiquer avec le thread d'entrainement du reseau");

    label_erreur_actuel = new QLabel;
    label_erreur_actuel->setText("Cette zonne de text n'arive pas a communiquer avec le thread d'entrainement du reseau");

    layout_principal->addWidget(label_erreur_batch);
    layout_principal->addWidget(label_erreur_actuel);
    layout_principal->addWidget(progressBar);
    this->setLayout(layout_principal);

//    bouton_quitter = new QPushButton("Quitter", this);
//    bouton_quitter->setCursor(Qt::PointingHandCursor);
//    bouton_quitter->setToolTip("Pour mettre fin a la session d'entrainement");
//    bouton_quitter->move(180, 30);
//    QObject::connect(bouton_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    this->show();
}

QProgressBar *Fenetre_affichage_entrainement::getProgressBar() const
{
    return progressBar;
}

void Fenetre_affichage_entrainement::setProgressBar(QProgressBar *value)
{
    progressBar = value;
}

QLabel *Fenetre_affichage_entrainement::getLabel_erreur_batch() const
{
    return label_erreur_batch;
}

void Fenetre_affichage_entrainement::setLabel_erreur_batch(QLabel *value)
{
    label_erreur_batch = value;
}

QLabel *Fenetre_affichage_entrainement::getLabel_erreur_actuel() const
{
    return label_erreur_actuel;
}
