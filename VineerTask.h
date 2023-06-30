#pragma once

#include "Task.h"
#include "Arduino.h"
#include <queue>

class VineerTask {
public:
    VineerTask() {}
    void tick() {
        int start = millis();
        for(int i = 0; i < tasks.size(); i++) {
            int tmp = millis();
            if(tasks[i].execute()) {
                loadTime += (millis() - tmp);
            }
        }
        if(millis() - tmp >= 1009) {
            lastLoad = float(loadTime) / float(millis() - tmp);
            tmp = millis();
            loadTime = 0;
        }
    }

    void add(Task task) {
        sum_priority += task._priority;
        if(sum_priority > 100) {
            Serial.println("Failed to initialize task! priority percent is incorrect!");
            return;
        }
        for(int i = 0; i < tasks.size(); i++) {
            if(tasks[i]._priority < task._priority) {
                tasks.insert(tasks.begin() + i, task);
                return;
            }
        }
        tasks.push_back(task);
    }

    int getMaxSum() {
        return sum_priority;
    }

    float getLoad() {
        return lastLoad*100;
    }
private:
    std::vector<Task> tasks;
    int sum_priority = 0;
    int loadTime = 0;
    int tmp = millis();
    float lastLoad = 0.00;
};


