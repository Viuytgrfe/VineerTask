#pragma once


class Task {
public:
    int _priority;
    int priority_counter;
    int delay;
    int tmr;
    void (*_func)(Task*);
    Task(int priority, void (*func)(Task*)) {
        _priority = priority;
        _func = func;
        delay = 0;
        tmr = 0;
        priority_counter = 0;
    }
    bool execute() {
        if(delay <= 0) {
            priority_counter += _priority;
            if(priority_counter >= 100) {
                priority_counter %= 100;
                _func(this);
            }
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
