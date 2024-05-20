/*******************************************************************************
* File:     startApp.c
* Purpose:  ice cream teller, basic sequence
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

    int      j;
    char     string[8];
    sem_t    *coin, *coffee, *ready;

    sem_unlink(COIN_SEMAPHOR);
    sem_unlink(COFFEE_SEMAPHOR);
    sem_unlink(READY_SEMAPHOR);

    coin   = sem_open(COIN_SEMAPHOR,   O_CREAT, 0700, 0);
    coffee = sem_open(COFFEE_SEMAPHOR, O_CREAT, 0700, 0);
    ready  = sem_open(READY_SEMAPHOR,  O_CREAT, 0700, 1);

    for (j = 1; j <= CUSTOMERS; j++) {
        if (fork() == 0) {
            sprintf(string, "%d", j);
            execl("./customer.e", "customer.e", string, NULL);
            perror("execl failed");
            exit(1);
        }
    }

    if (fork() == 0) {
        execl("./coffeeTeller.e", "coffeeTeller.e", NULL);
        perror("execl failed");
        exit(1);
    }

    for (j = 0; j <= CUSTOMERS + 1; j++) {
        wait(NULL);
    }

    sem_close(coin);
    sem_close(coffee);
    sem_close(ready);
    sem_unlink(COIN_SEMAPHOR);
    sem_unlink(COFFEE_SEMAPHOR);
    sem_unlink(READY_SEMAPHOR);

    return 0;
}

//******************************************************************************
