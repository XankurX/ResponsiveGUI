#ifndef MFQUEUEMANAGER_H
#define MFQUEUEMANAGER_H

#include <string>
#include <vector>

#include <MFEvent.h>
#include <MFQueue.hpp>

#include <map>

namespace MF
{
  class MFQueueManager
  {
  public:
    static MFQueueManager& GetInstance();
    MFQueue<MFEvent>& GetQueue(std::string const & inTag);
  private:
    MFQueueManager();
    std::map<std::string, MFQueue<MFEvent>*> mQueues;
  };
}

#endif // MFQUEUEMANAGER_H
