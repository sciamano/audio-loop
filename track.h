#pragma once

#include <QAudioDecoder>
#include <QAudioSink>
#include <QBuffer>

class LoopBuffer : public QBuffer
{
public:
  LoopBuffer(QObject* parent = nullptr);
  void   prepareRead();
  qint64 size() const override;
  qint64 readData(char* dest, qint64 len) override;
  qint64 current() const;

private:
  const char* src{nullptr};
  size_t      loopLength{0};
  size_t      offset{0};
  qint64      total{0};
};

class Track : public QObject
{
  Q_OBJECT

public:
  explicit Track(QObject* parent = nullptr);

  void playFile(const QString& fileName_);

public slots:
  void pausePlay();
  void continuePlay();

private slots:
  void copyFromBuffer();
  void decodingFinished();

private:
  QAudioFormat   format{};
  QAudioDecoder* decoder;
  LoopBuffer*    loopBuffer;
  QAudioSink*    audio;
};
