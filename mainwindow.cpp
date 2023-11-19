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

  auto widget = new QWidget(this);
  auto layout = new QVBoxLayout(widget);

  QPushButton* load_button = new QPushButton("Load and play", this);
  layout->addWidget(load_button, 0, Qt::AlignmentFlag::AlignLeft);
  connect(load_button, &QPushButton::clicked, this, &MainWindow::playFile);

  QPushButton* pause_button = new QPushButton("Pause", this);
  layout->addWidget(pause_button, 0, Qt::AlignmentFlag::AlignLeft);
  connect(pause_button, &QPushButton::clicked, track, &Track::pausePlay);

  QPushButton* continue_button = new QPushButton("Continue", this);
  layout->addWidget(continue_button, 0, Qt::AlignmentFlag::AlignLeft);
  connect(continue_button, &QPushButton::clicked, track, &Track::continuePlay);

  auto platform = new QLabel(QString("Platform: %1").arg(qApp->platformName()));
  layout->addWidget(platform, 0, Qt::AlignmentFlag::AlignLeft);

  setCentralWidget(widget);
}

void MainWindow::playFile()
{
  QString fileName = QFileDialog::getOpenFileName(this);
  if (!fileName.isEmpty())
  {
    track->playFile(fileName);
  }
}

void MainWindow::playExample()
{
  QString fileName = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../Data/tone.wav");
  fileName = QDir::cleanPath(fileName);
  qDebug() << fileName;
  track->playFile(fileName);
}
