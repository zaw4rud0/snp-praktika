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
    coin   = sem_open(COIN_SEMAPHOR, O_CREAT, 0700, 0);
    coffee = sem_open(COFFEE_SEMAPHOR, O_CREAT, 0700, 0);
    ready  = sem_open(READY_SEMAPHOR, O_CREAT, 0700, 1);  // Initially ready

    // start teller machine
    printf("\nCoffee teller machine starting\n\n");

    for (i = 0; i < ITERS; i++) {
        sem_wait(coin);  // Wait for coin
        printf("teller (%d): got coin, dispense coffee\n", i);
        sem_post(coffee);  // Coffee ready
    }
    sem_close(coin);
    sem_close(coffee);
    sem_close(ready);
    return 0;
}

//******************************************************************************
