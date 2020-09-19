#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include "fonction_calcul.h"
#include "fenetre_affichage_entrainement.h"
#include "fenetre_affichage_reseau.h"
#include "reseau.h"
#include "thread_entrainement_reseau.h"


class Menu_principal : public QWidget
{
    Q_OBJECT

public:
    Menu_principal();

private:
        QPushButton *bouton_entrainement;
        QHBoxLayout *layout_principal;

public slots:
        void entrainement();
};

#endif // MENU_PRINCIPAL_H
