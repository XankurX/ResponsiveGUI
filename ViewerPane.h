#ifndef VIEWERPANE_H
#define VIEWERPANE_H

#include "MFListener.h"

#include <QString>
#include <QTabWidget>

#include <atomic>
#include <map>
#include <string>
#include <vector>

class ViewerPane : public QTabWidget , public MF::MFListener
{
 Q_OBJECT
public:
  ViewerPane(QWidget * inParent);
  void AddImage(QString const &,QImage const &);
  std::string const & GetName() const override {return mName;}
  void SetName(std::string const & inName) override{mName=inName;}
  virtual void Notify() override;

  void RenderFiles(QString const & directory, std::vector<QString> const & fileNames);
  void RefreshPane();
  void CloseRequestTriggered();

signals:
  void ProcessEventQueueMessages();
  void OnFileLoadedCountChanged(QString const &);

private:
  std::string mName;
  std::atomic<bool> mProcess;
  std::map<QString,QWidget*> mTabPages;
};

#endif // VIEWERPANE_H
