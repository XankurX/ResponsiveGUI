#ifndef RENDERIMAGEEVENT_H
#define RENDERIMAGEEVENT_H

#include "MFEvent.h"
#include <QString>

class RenderImageEvent : public MF::MFEvent
{
public:
  RenderImageEvent(std::string const & inRecepient, QString const & inImagePath)
    :
      MF::MFEvent(inRecepient)
      , mImagePath(inImagePath)
  {
  }
  QString const & GetImagePath(){return mImagePath;}
private:
  QString mImagePath;
};

#endif // RENDERIMAGEEVENT_H
