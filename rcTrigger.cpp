/*
 rcTrigger.cpp - Library for RC signal detection (in microseconds) and actions triggering
 Created by TheDIYGuy999 June 2020
 Released into the public domain.
 V1.0
 */

#include "Arduino.h"
#include "rcTrigger.h"


// Member definition (code) ========================================================================
rcTrigger::rcTrigger(unsigned long duration) { // Constructor (called, when new ojects of that class are created)
    _duration = duration;
}

// Momentary function (true, if pressed) ************************************************************
bool rcTrigger::momentary(unsigned int pulsewidth, unsigned int target) {
    _momentaryPulsewidth = pulsewidth;
    _momentaryTarget = target;
    
    if (millis() - _momentaryPreviousMillis > 20) { // every 20ms
        _momentaryPreviousMillis = millis();
        if (_momentaryPulsewidth > 0) {
            if (_momentaryPulsewidth >= _momentaryTarget - 50 && _momentaryPulsewidth <= _momentaryTarget + 50) _momentaryState = true; // Range OK
            else _momentaryState = false;
        }
        _momentaryPulsewidthPrevious = _momentaryPulsewidth;
    }
    
    return _momentaryState;
}

// Toggle function (toggling true / false, if pressed shorter than "duration") ************************************************************
bool rcTrigger::toggle(unsigned int pulsewidth, unsigned int target) {
    _togglePulsewidth = pulsewidth;
    _toggleTarget = target;
    _toggleDuration = _duration;
    
    if (millis() - _togglePreviousMillis > 20) { // every 20ms
        _togglePreviousMillis = millis();
        if (_togglePulsewidth >= _toggleTarget - 50 && _togglePulsewidth <= _toggleTarget + 50 // Range OK
            && _togglePulsewidth >= _togglePulsewidthPrevious - 10 && _togglePulsewidth <= _togglePulsewidthPrevious + 10) _toggleTargetOk = true; // stable reading
        else _toggleTargetOk = false;
        
        _togglePulsewidthPrevious = _togglePulsewidth;
    }
    
    switch (_toggleStep) {
        case 0: //---- Step 0 (do nothing)
            _toggleStep = 1;
            break;
            
        case 1: //---- Step 1 (if reading is in target area)
            if (_toggleTargetOk) {
                _toggleStartTime = millis();
                _toggleStep = 2;
            }
            break;
            
        case 2: //---- Step 2 (if reading is not in target range anymore)
            if (!_toggleTargetOk) {
                if (millis() - _toggleStartTime < _toggleDuration) _toggleState = !_toggleState;
                _toggleStep = 0;
            }
            break;
    }
    
    return _toggleState;
}

// Toggle long function (toggling true / false, if pressed longer than "duration") ************************************************************
bool rcTrigger::toggleLong(unsigned int pulsewidth, unsigned int target) {
    _toggleLongPulsewidth = pulsewidth;
    _toggleLongTarget = target;
    _toggleLongDuration = _duration;
    
    if (millis() - _toggleLongPreviousMillis > 20) { // every 20ms
        _toggleLongPreviousMillis = millis();
        if (_toggleLongPulsewidth >= _toggleLongTarget - 50 && _toggleLongPulsewidth <= _toggleLongTarget + 50 // Range OK
            && _toggleLongPulsewidth >= _toggleLongPulsewidthPrevious - 10 && _toggleLongPulsewidth <= _toggleLongPulsewidthPrevious + 10) _toggleLongTargetOk = true; // stable reading
        else _toggleLongTargetOk = false;
        
        _toggleLongPulsewidthPrevious = _toggleLongPulsewidth;
    }
    
    switch (_toggleLongStep) {
        case 0: //---- Step 0 (do nothing)
            _toggleLongStep = 1;
            break;
            
        case 1: //---- Step 1 (if reading is in target area)
            if (_toggleLongTargetOk) {
                _toggleLongStartTime = millis();
                _toggleLongStep = 2;
            }
            break;
            
        case 2: //---- Step 2 (if reading is not in target range anymore)
            if (!_toggleLongTargetOk) {
                if (millis() - _toggleLongStartTime > _toggleLongDuration) _toggleLongState = !_toggleLongState;
                _toggleLongStep = 0;
            }
            break;
    }
    
    return _toggleLongState;
}

