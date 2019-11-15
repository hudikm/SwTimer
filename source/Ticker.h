/*
 * Ticker.h
 *
 *  Created on: Nov 13, 2019
 *      Author: martin
 */

#ifndef TICKER_H_
#define TICKER_H_

//#include <SwTimer.h>
#include <TickerBase.h>

template<unsigned N = 0, SwTimer* const ...Args>
class Ticker: public TickerBase {
private:
	static const int size = sizeof...(Args);
	static SwTimer* const swTimers[sizeof...(Args)];
	static SwTimer* swTimersRunTime[N];

public:

	void checkExpiration() {
		for (int i = 0; i < size; i++) {
			swTimers[i]->hasExpired(true);
		}

		for (SwTimer* pt : swTimersRunTime) {
			if (pt != nullptr) {
				pt->hasExpired(true);
			}
		}
	}

private:
	virtual bool attach_timer(SwTimer* swtimer) override {
		for (unsigned i = 0; i < N; i++) {
			if (swTimersRunTime[i] == nullptr) {
				swTimersRunTime[i] = swtimer;
				return true;
			}
		}
		return false;
	}

	virtual bool detach_timer(SwTimer* swtimer) override {
		for (unsigned i = 0; i < N; i++) {
			if (swTimersRunTime[i] == swtimer) {
				swTimersRunTime[i] = nullptr;
				return true;
			}
		}
		return false;
	}
};

template<unsigned N, SwTimer* const ...Args>
SwTimer* const Ticker<N, Args...>::swTimers[sizeof...(Args)] = { Args... };

template<unsigned N, SwTimer* const ...Args>
SwTimer* Ticker<N, Args...>::swTimersRunTime[N] = { };

#endif /* TICKER_H_ */
