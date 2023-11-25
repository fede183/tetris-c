#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef RANDOM_H
#define RANDOM_H
unsigned int random_number_generator(unsigned int min, unsigned int max) {
  srand(time(0));

  return (rand() % (max - 1)) + min;
}
#endif //RANDOM_H