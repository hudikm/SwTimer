/*
 * SwTimer.h
 *
 *  Created on: Nov 13, 2019
 *      Author: martin
 */

#ifndef SWTIMER_H_
#define SWTIMER_H_

#include "stdint.h"
#include "Ticker.h"

class SwTimer {
public:
	using f_GlTIME = uint64_t (*) (void); // Definovanie typu funkcie int fun_name(void);
	using f_callback = void (*) (SwTimer&); // Definovanie typu callback funkcie
	SwTimer(f_GlTIME func, bool auto_reload = false) :
			auto_reload(auto_reload), GlTimeFn(func) {
	}
	;/*! Constructor */
	~SwTimer() {
		if (attachedTicker != nullptr) {
			attachedTicker->detach_timer(this);
		}
	}
	bool hasExpired(bool callCallback = false);
	void startTimer(uint64_t delayMs);
	void restartTimer();

	bool isAutoReload() const;
	void setAutoReload(bool autoReload);
	uint64_t getDelayMs() const;
	void setDelayMs(uint64_t delayMs);
	void setCallbackFn(f_callback callbackFn);

	void attach_to_ticker(TickerBase& ticker) {
		attachedTicker = &ticker;
		ticker.attach_timer(this);
	}
	void detach_from_ticker() {
		if (attachedTicker != nullptr)
			attachedTicker->detach_timer(this);
		attachedTicker = nullptr;
	}

private:
	TickerBase* attachedTicker = nullptr;
	bool _hasExpired();
	bool auto_reload;
	bool fired_flag = false;
	f_GlTIME GlTimeFn;  //Odkaz na funciu ktora vracia globalny cas
	f_callback callback_fn; // Callback funkcia
	uint64_t endTime = UINT64_MAX; //Pomocna premnena
	uint64_t _delayMs; //Perioda casovaca
};

#endif /* SWTIMER_H_ */
