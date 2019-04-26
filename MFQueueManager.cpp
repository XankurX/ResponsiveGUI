#include "MFQueueManager.h"
#include "MFQueue.hpp"
#include "MFEvent.h"
#include <algorithm>

MF::MFQueueManager& MF::MFQueueManager::GetInstance()
{
  static MFQueueManager sMFQueueManager;
  return sMFQueueManager;
}

MF::MFQueueManager::MFQueueManager()
:
  mQueues()
{
}

MF::MFQueue<MF::MFEvent>& MF::MFQueueManager::GetQueue(std::string const & inTag)
{
  if(mQueues.find(inTag) == mQueues.end())
  {
    mQueues[inTag] = new MF::MFQueue<MF::MFEvent>(inTag);
  }
  return *mQueues[inTag];
}
