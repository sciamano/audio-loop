#include "mainwindow.h"

#include <QtWidgets>

class Control1 : public QCheckBox
{
public:
  explicit Control1(QWidget* parent = nullptr) :
      QCheckBox(parent)
  {
    QString style("QCheckBox::indicator:unchecked  { image: url(:/control1.svg); }");
    setStyleSheet(style);
  }
};

class Control2 : public QCheckBox
{
public:
  explicit Control2(QWidget* parent = nullptr) :
      QCheckBox(parent)
  {
    QString style("QCheckBox::indicator:unchecked  { image: url(:/control2.svg); }");
    setStyleSheet(style);
  }
};

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
  track = new Track(this);

  setupMenu();

  auto widget = new QWidget(this);
  auto layout = new QVBoxLayout(widget);
  auto control1 = new Control1(this);
  layout->addWidget(control1, 0, Qt::AlignmentFlag::AlignLeft);
  auto control2 = new Control1(this);
  layout->addWidget(control2, 0, Qt::AlignmentFlag::AlignLeft);
  setCentralWidget(widget);
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
