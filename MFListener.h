#ifndef MFLISTENER_H
#define MFLISTENER_H

#include <MFEvent.h>
namespace MF
{
  class MFListener
  {
  public:
    MFListener();
    virtual std::string const & GetName() const=0;
    virtual void SetName(std::string const & inName)=0;
    virtual void Notify(){}
    virtual ~MFListener(){}
  };
}
#endif // MFLISTENER_H
