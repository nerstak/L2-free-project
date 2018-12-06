#include <stdio.h>


#include "tutorial.h"
#include "../data.h"
#include "movement.h"

extern void processTutorial(Data* data, float Vchange) {
    int tutorialValue = data->lobby->tutorial;
    if(tutorialValue != 0) {
        switch(tutorialValue) {
            case 1: {
                if(getTime_Timer(data->lobby->timerMessage) > 12) {
                    stop_Timer(data->lobby->timerMessage);
                    data->lobby->tutorial = 2;
                }
                automaticAskMovement(data, Vchange, 50, 384);
                break;
            }
            case 2: {
                if (automaticAskMovement(data, Vchange, 1100, 384) == 1) {
                    data->lobby->tutorial = 0;
                }
                break;
            }
        }
    }
}