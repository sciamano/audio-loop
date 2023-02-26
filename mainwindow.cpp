#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  track = new Track(this);

  setupMenu();
}

void MainWindow::setupMenu()
{
  auto* fileMenu = menuBar()->addMenu("File");

  auto* playFileAction = fileMenu->addAction(tr("Play"));
  connect(playFileAction, &QAction::triggered, this, &MainWindow::playFile);

  auto* pauseAction = fileMenu->addAction(tr("Pause"));
  connect(pauseAction, &QAction::triggered, track, &Track::pausePlay);

  auto* continueAction = fileMenu->addAction(tr("Continue"));
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
