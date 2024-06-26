/*******************************************************************************
* File:     customer.c
* Purpose:  simple sequence with semaphores
* Course:   bsy
* Author:   M. Thaler, 2011
* Revision: 5/2012, 7/2013
* Version:  v.fs20
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include "commonDefs.h"

//******************************************************************************

int main(int argc, char *argv[]) {

    int      i, myID;
    sem_t    *myTurn, *coin, *coffee, *ready;

    if (argc > 1)
        myID = atoi(argv[1]);
    else
        myID = 0;

    // set up a semaphore
    coin   = sem_open(COIN_SEMAPHOR,   0);
    coffee = sem_open(COFFEE_SEMAPHOR, 0);
    ready  = sem_open(READY_SEMAPHOR,  0);

    // start customer
    printf("Customer starting (%d)\n", myID);

    for (i = 0; i < ITERS; i++) {
        for (int j = 0; j < NUM_COIN; j++) {
            sem_post(coin);  // Insert each coin
        }
        printf("\t\t\t\tcustomer(%d) put coins %d\n", myID, i);
        sem_wait(coffee); // Wait for coffee
        printf("\t\t\t\tcustomer(%d) got coffee %d\n", myID, i);
        drinkingCoffee(myID);
    }
    return 0;
}

//******************************************************************************
