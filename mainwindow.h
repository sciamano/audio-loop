#pragma once

#include "track.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
public:
  MainWindow(QWidget* parent = nullptr);

private slots:
  void playFile();

private:
  void setupMenu();

  Track* track;
};
