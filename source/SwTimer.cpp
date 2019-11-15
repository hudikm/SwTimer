/*
 * SwTimer.cpp
 *
 *  Created on: Nov 13, 2019
 *      Author: martin
 */

#include "SwTimer.h"

bool SwTimer::hasExpired(bool call_Callback) {
	bool ret = _hasExpired();
	if (ret && call_Callback && callback_fn != nullptr && !fired_flag) {
		fired_flag = true;
		callback_fn(*this);
		return ret;
	}
	return ret;
}

bool SwTimer::_hasExpired() {
	bool ret = GlTimeFn() >= (endTime);

	if (ret && auto_reload) {
		fired_flag = false;
		endTime += _delayMs;
		(void) _hasExpired();
	}

	return ret;
}

void SwTimer::startTimer(uint64_t delayMs) {
	_delayMs = delayMs;
	endTime = GlTimeFn() + delayMs;
	fired_flag = false;
}

void SwTimer::restartTimer() {
	startTimer(_delayMs);
	fired_flag = false;
}

bool SwTimer::isAutoReload() const {
	return auto_reload;
}

void SwTimer::setAutoReload(bool autoReload) {
	auto_reload = autoReload;
}

uint64_t SwTimer::getDelayMs() const {
	return _delayMs;
}

void SwTimer::setDelayMs(uint64_t delayMs) {
	_delayMs = delayMs;
}

void SwTimer::setCallbackFn(f_callback callbackFn) {
	callback_fn = callbackFn;
}
