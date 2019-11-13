/*
 * Ticker.h
 *
 *  Created on: Nov 13, 2019
 *      Author: martin
 */

#ifndef TICKER_H_
#define TICKER_H_
#include "SwTimer.h"

//using f_GlTIME = uint64_t (*) (void); // Definovanie typu funkcie int fun_name(void);
using f_Callback = void (*) (void);  // CallBack
template<unsigned N>
class Ticker {
public:
	static Ticker* tickers[N];
	/*! Constructor */
	Ticker(f_GlTIME func) :GlTimeFn(func) {}; //Konstruktor
    bool isExpired();
    void attach_ms(f_Callback, uint64_t ms);

private:
    f_GlTIME GlTimeFn;  //Odkaz na funciu ktora vracia globalny cas
    f_Callback CallBack;
    uint64_t endTime; //Pomocna premnena
    uint64_t _delayMs; //Perioda casovaca

};

#endif /* TICKER_H_ */
