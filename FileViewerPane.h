#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QFileSystemModel>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include <vector>

class FileViewerPane : public QWidget
{
  Q_OBJECT
public:
  explicit FileViewerPane(QWidget *parent = nullptr);

signals:
  void OnFilesSelectionChanged
  (
      QString const & directory,
      std::vector<QString> const & fileNames
  );
  void OnFileLoadedCountChanged(QString const &);
public slots:
  void DoOnLocationButtonClicked();
  void DoOnFileSelectionChanged();
private:
  QPushButton* mLocationButton;
  QLabel* mLocationLabel;
  QListWidget* mFileList;

  QString mCurrentDir;
};

#endif // FILEVIEWER_H
