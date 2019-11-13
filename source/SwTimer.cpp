/*
 * SwTimer.cpp
 *
 *  Created on: Nov 13, 2019
 *      Author: martin
 */

#include "SwTimer.h"

bool SwTimer::isExpired(){
    return  GlTimeFn() >= (endTime);
}

void SwTimer::startTimer(uint64_t delayMs){
    _delayMs=delayMs;
    endTime =  GlTimeFn() + delayMs;
}

void SwTimer::restartTimer(){
    startTimer(_delayMs);
}
