#include "thread_activation_neurone.h"

Thread_activation_neurone::Thread_activation_neurone(Neurone* neurone)
{
    this->neurone = neurone;
}

void Thread_activation_neurone::run()
{
    neurone->activation();
}
