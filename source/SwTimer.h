/*
 * SwTimer.h
 *
 *  Created on: Nov 13, 2019
 *      Author: martin
 */

#ifndef SWTIMER_H_
#define SWTIMER_H_

#include "stdint.h"
using f_GlTIME = uint64_t (*) (void); // Definovanie typu funkcie int fun_name(void);

class SwTimer
{
public:
    /*! Constructor */
    SwTimer(f_GlTIME func) :GlTimeFn(func) {}; //Konstruktor
    bool isExpired();
    void startTimer(uint64_t delayMs);
    void restartTimer();

private:
    f_GlTIME GlTimeFn;  //Odkaz na funciu ktora vracia globalny cas
    uint64_t endTime; //Pomocna premnena
    uint64_t _delayMs; //Perioda casovaca
};


#endif /* SWTIMER_H_ */
