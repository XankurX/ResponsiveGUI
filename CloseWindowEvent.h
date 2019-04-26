#ifndef CLOSEWINDOWEVENT_H
#define CLOSEWINDOWEVENT_H

#include "MFEvent.h"

class CloseWindowEvent : public MF::MFEvent
{
public:
  CloseWindowEvent(std::string const & inRecepient)
  :
    MF::MFEvent(inRecepient)
    {
    }
};

#endif // CLOSEWINDOWEVENT_H
