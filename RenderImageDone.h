#ifndef RENDERIMAGEDONE_H
#define RENDERIMAGEDONE_H

#include "MFEvent.h"
#include <QImage>
#include <QString>

class RenderImageDone : public MF::MFEvent
{
public:
  RenderImageDone
  (
      std::string const & inRecepient,
      QString const & inImageName,
      QImage* inImage
  )
  :
      MF::MFEvent(inRecepient)
      , mImageName(inImageName)
      , mImage(inImage)
  {
  }
  ~RenderImageDone()
  {
      delete mImage;
  }
  QImage* GetImage(){return mImage;}
  QString const & GetImageName(){return mImageName;}
private:
  QString mImageName;
  QImage* mImage;
};

#endif // RENDERIMAGEDONE_H
