#include "track.h"

#include <QTest>

class TestLoopBuffer : public QObject
{
  Q_OBJECT
private slots:
  void bufferSizeTest();
};

void TestLoopBuffer::bufferSizeTest()
{
  auto* buffer = new LoopBuffer(this);
  QVERIFY(buffer != nullptr);
  QCOMPARE(buffer->size(), std::numeric_limits<qint64>::max());
}

QTEST_MAIN(TestLoopBuffer)
#include "mytest.moc"
