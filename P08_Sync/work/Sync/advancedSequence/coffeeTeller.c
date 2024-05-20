/*******************************************************************************
* File:     coffeTeller.c
* Purpose:  simple sequence with semaphores
* Course:   bsy
* Author:   M. Thaler, 2011
* Revision: 5/2012, 7/2013
* Version:  v.fs20
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include "commonDefs.h"

//******************************************************************************

int main(void) {

    int      i;
    sem_t    *coin, *coffee, *ready;

    // set up a semaphore
    coin   = sem_open(COIN_SEMAPHOR,   0);
    coffee = sem_open(COFFEE_SEMAPHOR, 0);
    ready  = sem_open(READY_SEMAPHOR,  0);

    // start teller machine
    printf("\nCoffee teller machine starting\n\n");

    for (i = 0; i < ITERS; i++) {
        printf("teller (%d): waiting for coins\n", i);
        for (int j = 0; j < NUM_COIN; j++) {
            sem_wait(coin);  // Wait for each coin
        }
        printf("       (%d): got coins, dispense coffee\n", i);
        sem_post(coffee);  // Signal that coffee is dispensed
    }
    return 0;
}

//******************************************************************************
