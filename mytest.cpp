#include "track.h"

#include <QTest>

class TestLoopBuffer : public QObject
{
  Q_OBJECT
private slots:
  void initTestCase();
  void bufferSizeTest();
};

void TestLoopBuffer::initTestCase()
{
    const QTemporaryDir tmp_dir;
    const QDir base_dir(tmp_dir.path());
    QString file_name("./");

    QFile file(":/media/sound_0100.wav");
    file_name.append(QFileInfo(file).fileName());
    file_name = QDir::cleanPath(base_dir.absoluteFilePath(file_name));
    QVERIFY(file.copy(file_name));
}

void TestLoopBuffer::bufferSizeTest()
{
  auto* buffer = new LoopBuffer(this);
  QVERIFY(buffer != nullptr);
  QCOMPARE(buffer->size(), std::numeric_limits<qint64>::max());
}

QTEST_MAIN(TestLoopBuffer)
#include "mytest.moc"
