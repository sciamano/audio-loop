#pragma once

#include "track.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
public:
  MainWindow(QWidget* parent = nullptr);

private slots:
  void playFile();
  void playExample();

private:
  void setupMenu();

  Track* track;
};
