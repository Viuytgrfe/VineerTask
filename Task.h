#pragma once

#define ASYNC 1
#define TIMER 2
#define LATER 3

class Task {
public:
    int _priority;
    int delay;
    int tmr;
    void (*_func)(Task*);
    Task(int priority, void (*func)(Task*)) {
        _priority = priority;
        _func = func;
        delay = 0;
        tmr = 0;
    }
    bool execute() {
        if(delay <= 0) {
            _func(this);
            return true;
        }
        else {
            delay -= (millis() - tmr);
            tmr = millis();
        }
        return false;
    }

    void ms_delay(int d) {
        delay = d;
        tmr = millis();
    }
};
