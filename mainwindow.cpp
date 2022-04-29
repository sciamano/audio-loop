#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  track = new Track(this);

  setupMenu();
}

void MainWindow::setupMenu()
{
  QAction* playFileAction = menuBar()->addAction(tr("Play"));
  connect(playFileAction, &QAction::triggered, this, &MainWindow::playFile);

  QAction* pauseAction = menuBar()->addAction(tr("Pause"));
  connect(pauseAction, &QAction::triggered, track, &Track::pausePlay);

  QAction* continueAction = menuBar()->addAction(tr("Continue"));
  connect(continueAction, &QAction::triggered, track, &Track::continuePlay);
}

void MainWindow::playFile()
{
  QString fileName = QFileDialog::getOpenFileName(this);
  if (!fileName.isEmpty())
  {
    track->playFile(fileName);
  }
}
