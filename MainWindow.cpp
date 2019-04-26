#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mCentralWidget(new QSplitter(this))
  , mFileViewerPaner(new FileViewerPane(mCentralWidget))
  , mViewer(new ViewerPane(this))
{
    ui->setupUi(this);
    mCentralWidget->addWidget(mFileViewerPaner);
    mCentralWidget->addWidget(mViewer);

    setCentralWidget(mCentralWidget);

    connect(mFileViewerPaner, &FileViewerPane::OnFilesSelectionChanged, this, &MainWindow::DoOnFilesSelectionChanged);
    connect(mViewer, &ViewerPane::OnFileLoadedCountChanged, this, &MainWindow::UpdateStatusBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DoOnFilesSelectionChanged(QString const & directory, std::vector<QString> const & fileNames)
{
  mViewer->RenderFiles(directory,fileNames);
}

void MainWindow::UpdateStatusBar(QString const & inMsg)
{
  statusBar()->showMessage(inMsg);
}

void MainWindow::closeEvent(QCloseEvent *)
{
  mViewer->CloseRequestTriggered();
}
