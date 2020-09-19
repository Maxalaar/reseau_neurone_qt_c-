#ifndef THREAD_ACTIVATION_NEURONE_H
#define THREAD_ACTIVATION_NEURONE_H

#include <QThread>

#import "neurone.h"

class Thread_activation_neurone : public QThread
{
    Q_OBJECT

public:
    Thread_activation_neurone(Neurone* neurone);
    void run();

private:
    Neurone* neurone;
};

#endif // THREAD_ACTIVATION_NEURONE_H
