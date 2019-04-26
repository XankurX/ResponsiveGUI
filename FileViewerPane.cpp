#include "FileViewerPane.h"

#include <QVBoxLayout>
#include <QDir>
#include <QStringList>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QSizePolicy>

namespace
{
  void UpdateList(QListWidget* ioList, QString const & inPath)
  {
    ioList->clear();
    QDir dir(inPath);
    QStringList filters;
    filters << "*.jpeg" << "*.png" << "*.jpg";
    dir.setNameFilters(filters);

    auto fileNames = dir.entryList();
    QStandardItemModel model;
    for(auto const & fileName: fileNames)
    {
      ioList->addItem(new QListWidgetItem(fileName));
    }
  }
}


FileViewerPane::FileViewerPane(QWidget *parent)
  :
    QWidget(parent)
  , mLocationButton(new QPushButton("Browse..."))
  , mLocationLabel(new QLabel(""))
  , mFileList(new QListWidget(this))
  , mCurrentDir("")
{
  setFixedWidth(300);
  setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

  QVBoxLayout* mLayout = new QVBoxLayout(this);

  mLayout->addWidget(mLocationLabel);
  mLayout->addWidget(mLocationButton);
  mLayout->addWidget(mFileList);

  ::UpdateList(mFileList, mCurrentDir);
  mLocationLabel->setText(mCurrentDir);
  setLayout(mLayout);

  mFileList->setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(mFileList,&QListWidget::itemSelectionChanged,this,&FileViewerPane::DoOnFileSelectionChanged);
  connect(mLocationButton,&QPushButton::clicked,this,&FileViewerPane::DoOnLocationButtonClicked);
  DoOnLocationButtonClicked();
}

void FileViewerPane::DoOnLocationButtonClicked()
{
  auto dir = QFileDialog::getExistingDirectory(this, "Pick Directory of Images", mCurrentDir, QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
  if(dir.isEmpty())
    return;
  mCurrentDir = dir;
  mLocationLabel->setText(mCurrentDir);
  ::UpdateList(mFileList, mCurrentDir);
  OnFileLoadedCountChanged("");
}

void FileViewerPane::DoOnFileSelectionChanged()
{
  auto const & currentSelection = mFileList->selectedItems();
  std::vector<QString> selectedFileNames;
  for(auto const & item: currentSelection)
  {
    selectedFileNames.push_back(item->text());
  }
  OnFilesSelectionChanged(mCurrentDir, selectedFileNames);
}

