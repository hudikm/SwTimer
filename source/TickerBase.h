/*
 * TickerBase.h
 *
 *  Created on: Nov 14, 2019
 *      Author: martin
 */

#ifndef TICKERBASE_H_
#define TICKERBASE_H_
class SwTimer;
//template <typename T>
class TickerBase{
friend SwTimer;
private:
	virtual bool attach_timer(SwTimer* swtimer)= 0;
	virtual bool detach_timer(SwTimer* swtimer) = 0;

};

#endif /* TICKERBASE_H_ */
