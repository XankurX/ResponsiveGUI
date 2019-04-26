#ifndef MFEVENT_H
#define MFEVENT_H

#include <string>

namespace MF
{
  class MFEvent
  {
  public:
    MFEvent(std::string const & inRecepient);
    std::string const & GetRecepientName();
    virtual ~MFEvent(){}
  private:
    std::string mRecepient;

  };
}

#endif // MFEVENT_H
