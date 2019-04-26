#include "MFQueueManager.h"
#include "MFQueue.hpp"

#include "CloseWindowEvent.h"
#include "RenderImageEvent.h"
#include "RenderImageDone.h"
#include "StopProcessingEvent.h"
#include "ViewerPane.h"

#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QVBoxLayout>

#include <chrono>
#include <QDebug>

class ImagePage : public QWidget
{
public:
  ImagePage(QWidget* inParent, QImage* image)
  :
    QWidget(inParent)
  , mScrollArea(new QScrollArea())
  , mImageLabel(new QLabel(this))
  {

    mScrollArea = new QScrollArea;
    mScrollArea->setBackgroundRole(QPalette::Dark);

    mImageLabel = new QLabel();
    mImageLabel->setSizePolicy(QSizePolicy::Expanding,
                                        QSizePolicy::Expanding);
    mImageLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mLayout = new QVBoxLayout(this);
    mLayout->addWidget(mScrollArea);

    mImageLabel->setPixmap(QPixmap::fromImage(*image));
    mScrollArea->setWidget(mImageLabel);
    setLayout(mLayout);
  }
private:
  QScrollArea* mScrollArea;
  QLabel* mImageLabel;
};

ViewerPane::ViewerPane(QWidget * inParent)
:
  QTabWidget(inParent)
  , MF::MFListener()
  , mName("ImagePane")
  , mTabPages()
{
  MF::MFQueueManager::GetInstance().GetQueue("GUI").Register(this);
  connect
  (
    this
    , &ViewerPane::ProcessEventQueueMessages
    , this
    , &ViewerPane::RefreshPane
    , Qt::QueuedConnection
  );
}

void ViewerPane::Notify()
{
  ProcessEventQueueMessages();
}

void ViewerPane::RenderFiles(QString const & directory, std::vector<QString> const & fileNames)
{
  mProcess.store(false);

  MF::MFQueueManager::GetInstance().GetQueue("GUI").Clear();

  for(auto item: mTabPages)
    delete item.second;

  for(int index=0;index<count();++index)
    tabCloseRequested(index);

  mTabPages.clear();

  mProcess.store(true);
  for(auto const & fileName : fileNames)
  {
    MF::MFQueueManager::GetInstance().GetQueue("Controller").addToQueue(this, new RenderImageEvent("ViewerPaneController",directory+QDir::separator()+fileName));
  }
}

void ViewerPane::RefreshPane()
{
  while(MF::MFQueueManager::GetInstance().GetQueue("GUI").GetSize() != 0)
  {
      if (mProcess.load())
      {
          auto eventEntity = MF::MFQueueManager::GetInstance().GetQueue("GUI").remove();
          auto * event = eventEntity.second;
          if (event)
          {
              if (RenderImageDone* renderEventDone = dynamic_cast<RenderImageDone*>(event))
              {
                  QString const & name = renderEventDone->GetImageName();
                  if (mTabPages.find(name) == mTabPages.end())
                  {
                      QImage* image = renderEventDone->GetImage();
                      ImagePage* tabPage = new ImagePage(this, image);
                      addTab(tabPage, name);
                      mTabPages[name] = tabPage;
                      OnFileLoadedCountChanged(QString("Loaded Image Count : ") + QString::number(mTabPages.size()));
                  }
              }
              delete event;
          }
      }
  }
}

void ViewerPane::CloseRequestTriggered()
{
  MF::MFQueueManager::GetInstance().GetQueue("Controller").addToQueue(this, new CloseWindowEvent("ViewerPaneController"));
  mProcess.store(false);
}