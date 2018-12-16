#include <stdio.h>


#include "tutorial.h"
#include "../data.h"
#include "movement.h"

extern void processTutorial(Data* data, float Vchange) {
    int tutorialValue = data->lobby->tutorial;
    if(tutorialValue != 0) {
        switch(tutorialValue) {
            case 1: {
                // First part of the tutorial
                if(getTime_Timer(data->lobby->timerMessage) > 12) {
                    stop_Timer(data->lobby->timerMessage);
                    data->lobby->tutorial = 2;
                }
                automaticAskMovement(data, Vchange, 200, 384);
                break;
            }
            case 2: {
                // Second part of the tutorial
                if (automaticAskMovement(data, Vchange, 1015, 384) == 1) {
                    data->lobby->tutorial = 3;
                    copyStats(data->Isaac->stats->current, data->Isaac->stats->basic);
                    start_Timer(data->lobby->timerMessage);
                }
                break;
            }
            case 3: {
                // Third part of the tutorial
                if(getTime_Timer(data->lobby->timerMessage) > 12) {
                    stop_Timer(data->lobby->timerMessage);
                    data->lobby->tutorial = 0;
                }
            }

        }
    }
}