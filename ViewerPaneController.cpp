#include "ViewerPaneController.h"
#include "MFQueueManager.h"
#include "MFQueue.hpp"

#include "CloseWindowEvent.h"
#include "RenderImageEvent.h"
#include "RenderImageDone.h"

#include <QImage>

#include <thread>
#include <functional>

ViewerPaneController::ViewerPaneController(bool useMultipleWorkers)
:
  mLoopFlag(true)
  , mName("ViewerPaneController")
  , mDataReady(false)
  , mUseMultipleWorkers(useMultipleWorkers)
  , mWorkers()
{
  MF::MFQueueManager::GetInstance().GetQueue("Controller").Register(this);
}

ViewerPaneController::~ViewerPaneController()
{
    for(auto & worker:mWorkers)
    {
        worker.join();
    }
}

void ViewerPaneController::Notify()
{
  mDataReady.store(true);
}

void ViewerPaneController::ProcessQueueEvents()
{
    if (MF::MFQueueManager::GetInstance().GetQueue("Controller").GetSize() != 0)
    {
        auto eventEntity = MF::MFQueueManager::GetInstance().GetQueue("Controller").remove();
        auto* event = eventEntity.second;
        if (event)
        {
            // process the event type:
            if (RenderImageEvent* renderEvent = dynamic_cast<RenderImageEvent*>(event))
            {
                QImage* image = new QImage(renderEvent->GetImagePath());
                MF::MFQueueManager::GetInstance().GetQueue("GUI").addToQueue(this, new RenderImageDone("ImagePane", renderEvent->GetImagePath(), image));
            }
            else if (CloseWindowEvent* closeEvent = dynamic_cast<CloseWindowEvent*>(event))
            {
                mLoopFlag.store(false);
            }
            delete event;
        }
    }
}

void ViewerPaneController::StartProcessing()
{
    unsigned int threadCount = std::thread::hardware_concurrency();
    if (mUseMultipleWorkers)
    {
        for (unsigned int i = 0; i < threadCount; ++i)
        {
            mWorkers.push_back
            (
                std::thread
                (
                    [this]
                    {
                        while (mLoopFlag.load())
                        {
                            if (mDataReady.load())
                                ProcessQueueEvents();
                            std::this_thread::sleep_for(std::chrono::milliseconds(5));
                        }
                    }
                )
            );
        }
    }
    else
    {
        while (mLoopFlag.load())
            ProcessQueueEvents();
    }
}
