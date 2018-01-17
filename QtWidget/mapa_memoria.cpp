#include "mapa_memoria.h"

Mapa_Memoria::Mapa_Memoria()
{
    this->irriga = false;
}

void Mapa_Memoria::set_irrga(bool value)
{
    this->irriga = value;
}

bool Mapa_Memoria::get_irriga()
{
    return this->irriga;
}
