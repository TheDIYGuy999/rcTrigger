/*
 rcTrigger.h - Library for RC signal detection (in microseconds) and actions triggering
 Created by TheDIYGuy999 June 2020
 Released into the public domain.
 V1.0
 */

#ifndef rcTrigger_h
#define rcTrigger_h

#include "Arduino.h"

// Class definition (header) ========================================================================
class rcTrigger {
  public:
    rcTrigger(unsigned long duration);
    
    bool momentary(unsigned int pulsewidth, unsigned int target);
    
    bool toggle(unsigned int pulsewidth, unsigned int target);
    
    bool toggleLong(unsigned int pulsewidth, unsigned int target);
    
  private:
    unsigned long _duration;
    
    // Momentary function
    unsigned int _momentaryPulsewidth;
    unsigned int _momentaryPulsewidthPrevious;
    unsigned int _momentaryTarget;
    unsigned long _momentaryPreviousMillis = 0;
    bool _momentaryState;
    
    // Toggle function
    unsigned int _togglePulsewidth;
    unsigned int _togglePulsewidthPrevious;
    unsigned int _toggleTarget;
    unsigned long _togglePreviousMillis = 0;
    unsigned long _toggleDuration;
    unsigned long _toggleStartTime;
    byte _toggleStep = 0;
    bool _toggleTargetOk;
    bool _toggleState;
    
    // Toggle long function
    unsigned int _toggleLongPulsewidth;
    unsigned int _toggleLongPulsewidthPrevious;
    unsigned int _toggleLongTarget;
    unsigned long _toggleLongPreviousMillis = 0;
    unsigned long _toggleLongDuration;
    unsigned long _toggleLongStartTime;
    byte _toggleLongStep = 0;
    bool _toggleLongTargetOk;
    bool _toggleLongState;
    
};

#endif
