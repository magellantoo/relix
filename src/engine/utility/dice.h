#ifndef __DICE_H__
#define __DICE_H__

// Engine
#include "constants.h"

typedef struct Dice {
    // [count]d[sides]+[flat]
    char label[LABEL_SHORT];

    int count;
    int sides;
    int flat;
} Dice;

Dice parseDice(const char *label);

int rollDice(const Dice dice);

#endif
