#include <stdio.h>


#include "tutorial.h"
#include "../data.h"
#include "movement.h"

extern void processTutorial(Data* data, int Vchange) {
    int tutorialValue = data->lobby->tutorial;
    if(tutorialValue != 0) {
        switch(tutorialValue) {
            case 1:
                if(automaticAskMovement(data, Vchange, 1100, 384) == 1) {
                    data->lobby->tutorial = 0;
                }
                break;
        }
    }
}