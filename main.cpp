#include "MainWindow.h"
#include <QApplication>

#include <thread>
#include "ViewerPaneController.h"

int main(int argc, char *argv[])
{
  std::thread uiThread
  (
    [&]
    {
      QApplication a(argc, argv);
      MainWindow w;
      w.show();
      return a.exec();
    }
  );
  // Controller constructed on the main thread:
  // It quits its own loop upon the closure of GUI.
  // Run the application with more than 1 argument to switch to superfast mode.
  ViewerPaneController viewerPanController(argc>1);
  viewerPanController.StartProcessing();

  uiThread.join();
  return 0;
}
