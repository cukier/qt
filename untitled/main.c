#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define NR_SETORES  6

typedef struct pivo
{
    uint8_t iteracao;
    uint16_t nrSetores;
    float angulo[NR_SETORES];
    float anguloOperacao;
} pivo_t;

void init_pivo(pivo_t *pivo)
{
    uint16_t cont;

    pivo->iteracao = 0;
    pivo->nrSetores = NR_SETORES;
    pivo->anguloOperacao = 360.0;

    for(cont = 0; cont < NR_SETORES; ++cont)
    {
        pivo->angulo[cont] =  pivo->anguloOperacao / pivo->nrSetores;
    }
}

void recalcular_angulos(pivo_t *pivo)
{
    uint16_t cont;

    for (cont = 0; cont < NR_SETORES; ++cont)
    {
        if (cont < pivo->nrSetores)
        {
            pivo->angulo[cont] = pivo->anguloOperacao / pivo->nrSetores;
        }
        else
        {
            pivo->angulo[cont] = 0;
        }
    }
}

void set_nrSetores(pivo_t *pivo, uint16_t nr_setores)
{
    if (nr_setores <= 0 || nr_setores > NR_SETORES)
    {
        return;
    }

    pivo->nrSetores = nr_setores;
    recalcular_angulos(pivo);
    printf("Numero de setores %u\n\r", nr_setores);
}

void mostra_pivo(pivo_t *pivo)
{
    uint16_t cont;

    printf("\n\rPivo %u\n\r", ++pivo->iteracao);
    printf("Nr setores      : %u\n\r", pivo->nrSetores);
    printf("Angulo Operacao : %3.2f\n\r", pivo->anguloOperacao);

    for (cont = 0; cont < NR_SETORES; ++cont) {
        printf(" Angulo %u       : %3.2f\n\r", cont + 1, pivo->angulo[cont]);
    }

    printf("\n\r");
}

float soma_pivo(float *angulos)
{
    uint16_t cont;
    float ret;

    ret = 0;

    for (cont = 0; cont < NR_SETORES; ++cont)
    {
        ret += angulos[cont];
    }

    return ret;
}

void set_angulo(pivo_t *pivo, float angulo, uint16_t setor)
{
    float diff, take;
    float angAux[NR_SETORES];
    uint16_t cont;

    if (setor <= 0 || setor > NR_SETORES || angulo == 0 || pivo == NULL)
        return;

    --setor;

    for(cont = 0; cont < NR_SETORES; ++cont)
    {
        if (cont != setor)
        {
            angAux[cont] = pivo->angulo[cont];
        }
        else
        {
            angAux[cont] = angulo;
        }
    }

    cont = pivo->nrSetores - 1;
    take = 0;

    do
    {
        diff = pivo->anguloOperacao - soma_pivo(angAux);

        if (cont == setor && cont != 0)
            --cont;

        take = angAux[cont] + diff;

        if (take <= 0)
        {
            angAux[cont] = 1;
            --cont;

            if (cont > NR_SETORES)
                return;
        }
        else
        {
            angAux[cont] = take;
        }
    } while (soma_pivo(angAux) != pivo->anguloOperacao);

    for (cont = 0; cont < NR_SETORES; ++cont)
        pivo->angulo[cont] = angAux[cont];

    printf("Angulo do setor %u setado para %3.2f\n\r", setor + 1, angulo);
}

void set_anguloOperacao(pivo_t *pivo, float angulo)
{

    if (angulo <= 0 || angulo > pivo->anguloOperacao)
        return;

    pivo->anguloOperacao = angulo;
    recalcular_angulos(pivo);
    printf("Angulo de operacao setado para %3.2f\n\r", angulo);
}

int main()
{
    pivo_t *pivo;

    pivo = (pivo_t *) malloc(sizeof(pivo_t));

    init_pivo(pivo);
    mostra_pivo(pivo);
    set_anguloOperacao(pivo, 300);
    mostra_pivo(pivo);
    set_nrSetores(pivo, 1);
    mostra_pivo(pivo);
    set_nrSetores(pivo, 6);
    mostra_pivo(pivo);
    set_angulo(pivo, 200, 1);
    mostra_pivo(pivo);
    free(pivo);

    return 0;
}
