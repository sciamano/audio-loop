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

  {
    auto platform = new QLabel(QString("Platform: %1").arg(qApp->platformName()));
    layout->addWidget(platform, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto dirPath = new QLabel(QString("application dir: %1").arg(QCoreApplication::applicationDirPath()));
    layout->addWidget(dirPath, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto filePath = new QLabel(QString("application file: %1").arg(QCoreApplication::applicationFilePath()));
    layout->addWidget(filePath, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto logicalDPI = new QLabel(QString("Logical DPI: %1").arg(logicalDpiX()));
    layout->addWidget(logicalDPI, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto physicalDPI = new QLabel(QString("Physical DPI: %1").arg(physicalDpiX()));
    layout->addWidget(physicalDPI, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto pixelRatio = new QLabel(QString("Pixel Ratio: %1").arg(devicePixelRatioF()));
    layout->addWidget(pixelRatio, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto screenLogicalDPI = new QLabel(QString("Screen Logical DPI: %1").arg(screen()->logicalDotsPerInch()));
    layout->addWidget(screenLogicalDPI, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto screenPhysicalDPI = new QLabel(QString("Screen Physical DPI: %1").arg(screen()->physicalDotsPerInch()));
    layout->addWidget(screenPhysicalDPI, 0, Qt::AlignmentFlag::AlignLeft);
  }

  {
    auto screenPixelRatio = new QLabel(QString("Screen Pixel Ratio: %1").arg(screen()->devicePixelRatio()));
    layout->addWidget(screenPixelRatio, 0, Qt::AlignmentFlag::AlignLeft);
  }

  //  {
  //      auto control1 = new Control1(this);
  //      layout->addWidget(control1, 0, Qt::AlignmentFlag::AlignLeft);
  //  }

  //  {
  //      auto control2 = new Control1(this);
  //      layout->addWidget(control2, 0, Qt::AlignmentFlag::AlignLeft);
  //  }

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

  auto* playExampleAction = fileMenu->addAction(tr("Example"));
  connect(playExampleAction, &QAction::triggered, this, &MainWindow::playExample);
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
