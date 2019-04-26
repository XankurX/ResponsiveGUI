#include "MFEvent.h"

MF::MFEvent::MFEvent(std::string const & inRecepient)
:
  mRecepient(inRecepient)
{

}

std::string const & MF::MFEvent::GetRecepientName()
{
  return mRecepient;
}
