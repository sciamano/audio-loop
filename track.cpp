#include "track.h"

#include <QAudioDevice>
#include <QAudioFormat>
#include <QLocale>
#include <QMediaDevices>
#include <QUrl>

LoopBuffer::LoopBuffer(QObject* parent) : QBuffer(parent)
{
}

void LoopBuffer::prepareRead()
{
  loopLength = data().size();
  qDebug() << "loopLength" << QLocale().formattedDataSize(loopLength);

  QByteArray copy(data());
  buffer().append(copy);
  src = data().constData();
}

qint64 LoopBuffer::size() const
{
  return std::numeric_limits<qint64>::max();
}

qint64 LoopBuffer::readData(char* dest, qint64 len)
{
  len = std::min<qint64>(len, data().size() - offset);
  memcpy(dest, src + offset, len);
  offset += len;

  if (offset >= loopLength) { offset -= loopLength; }

  total += len;
  return len;
}

qint64 LoopBuffer::current() const
{
  return total;
}

Track::Track(QObject* parent) : QObject(parent)
{
  format.setChannelCount(2);
  format.setSampleRate(48000);
  format.setSampleFormat(QAudioFormat::Int16);

  QAudioDevice info(QMediaDevices::defaultAudioOutput());
  if (!info.isFormatSupported(format))
  {
    format = info.preferredFormat();
    qWarning() << "Raw audio format not supported by backend, replacing by preferredFormat" << format;
  }
  qDebug() << "format" << format;

  decoder = new QAudioDecoder(this);
  decoder->setAudioFormat(format);
  connect(decoder, &QAudioDecoder::bufferReady, this, &Track::copyFromBuffer);
  connect(decoder, &QAudioDecoder::finished, this, &Track::decodingFinished);

  loopBuffer = new LoopBuffer(this);

  audio = new QAudioSink(info, format);
}

void Track::playFile(const QString& fileName)
{
  qDebug() << "filename:" << fileName;

  audio->stop();
  loopBuffer->close();
  loopBuffer->buffer().clear();

  decoder->setSource(QUrl::fromLocalFile(fileName));
  decoder->start();
}

void Track::copyFromBuffer()
{
  QAudioBuffer audioBuffer = decoder->read();
  loopBuffer->buffer().append(audioBuffer.constData<char>(), audioBuffer.byteCount());
}

void Track::decodingFinished()
{
  loopBuffer->prepareRead();
  qDebug() << "decodingFinished" << QLocale().formattedDataSize(loopBuffer->data().size());

  qDebug() << "start playing" << QLocale().formattedDataSize(loopBuffer->size());
  loopBuffer->open(QIODevice::ReadOnly);
  audio->start(loopBuffer);
}

void Track::pausePlay()
{
  if (audio->state() == QAudio::ActiveState)
  {
    qDebug() << "pause playing" << QLocale().formattedDataSize(loopBuffer->current());
    audio->suspend();
  }
}

void Track::continuePlay()
{
  if (audio->state() == QAudio::SuspendedState)
  {
    qDebug() << "continue playing";
    audio->resume();
  }
}
