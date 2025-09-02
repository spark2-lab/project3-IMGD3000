#include "Points.h"
#include "EventStep.h"
#include "EventView.h"
#include "ViewObject.h"
#include <stdio.h>
#include <stdlib.h>
#include "LogManager.h"

#define FILE_NAME "high_score.txt"

int Points::getHighScore()
{
    FILE *file = fopen(FILE_NAME, "r");
    int high_score = 0;

    if (file == NULL)
    {
        return 0;
    }

    if (fscanf(file, "%d", &high_score) != 1)
    {
        high_score = 0;
    }
    fclose(file);
    return high_score;
}

void Points::setHighScore(int score)
{
    int high_score = getHighScore();

    LM.writeLog("Score %d vs %d", high_score, score);

    if (high_score >= score)
    {
        return;
    }

    LM.writeLog("Score2 %d vs %d", high_score, score);

    FILE *file = fopen(FILE_NAME, "w");
    fprintf(file, "%d", score);
    fclose(file);
}

int Points::eventHandler(const df::Event *p_e)
{

    // Parent handles event if score update.
    if (df::ViewObject::eventHandler(p_e))
    {
        return 1;
    }
    // If step, increment score every second (30 steps).
    if (p_e->getType() == df::STEP_EVENT)
    {
        if (dynamic_cast<const df::EventStep *>(p_e)
                    ->getStepCount() %
                30 ==
            0)
            setValue(getValue() + 1);
        return 1;
    }
    // If get here, have ignored this event.
    return 0;
}

Points::Points()
{
    setLocation(df::TOP_RIGHT);
    setType("PointsView");
    setViewString(POINTS_STRING);
    setColor(df::YELLOW);
    // Need to update score each second, so count "step" events.
    registerInterest(df::STEP_EVENT);
}
