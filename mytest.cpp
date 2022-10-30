#include "track.h"

#include <QSignalSpy>
#include <QTest>

class TestTrack : public QObject
{
  Q_OBJECT
private slots:
  void initTestCase();
  void bufferSizeTest();
  void trackPlayPauseTest();

private:
  const QTemporaryDir tmp_dir{};
  const QDir base_dir{tmp_dir.path()};
  QString file_name{"./"};
};

void TestTrack::initTestCase()
{
    QFile file(":/tone.wav");
    file_name.append(QFileInfo(file).fileName());
    file_name = QDir::cleanPath(base_dir.absoluteFilePath(file_name));
    QVERIFY(file.copy(file_name));
}

void TestTrack::bufferSizeTest()
{
  auto* buffer = new LoopBuffer(this);
  QVERIFY(buffer != nullptr);
  QCOMPARE(buffer->size(), std::numeric_limits<qint64>::max());
}

void TestTrack::trackPlayPauseTest()
{

  auto track = new Track(this);
  qDebug() << file_name;

  QSignalSpy track_decoded(track, &Track::decoded);
  track->playFile(file_name);
  QVERIFY(track_decoded.wait());
  QVERIFY(track->audio->state() != QAudio::ActiveState);

  track->pausePlay();
  QVERIFY(track->audio->state() == QAudio::SuspendedState);

  track->continuePlay();
  QVERIFY(track->audio->state() == QAudio::ActiveState);
}

QTEST_MAIN(TestTrack)
#include "mytest.moc"
