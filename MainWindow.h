#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "FileViewerPane.h"
#include "ViewerPane.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
  void DoOnFilesSelectionChanged(QString const & directory, std::vector<QString> const & fileNames);
  void UpdateStatusBar(QString const &);
protected:
  void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
    QSplitter* mCentralWidget;
    FileViewerPane* mFileViewerPaner;
    ViewerPane* mViewer;
};

#endif // MAINWINDOW_H
