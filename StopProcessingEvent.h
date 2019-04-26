#pragma once

#include "MFEvent.h"

class StopProcessingEvent : public MF::MFEvent
{
public:
  StopProcessingEvent(std::string const & inRecepient)
  :
    MF::MFEvent(inRecepient)
    {
    }
};