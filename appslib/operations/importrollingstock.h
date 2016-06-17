#ifndef IMPORTROLLINGSTOCK_H
#define IMPORTROLLINGSTOCK_H
#include <QObject>

class QTextStream;
class QLabel;
class JmriJFrame;
class File;
namespace Operations
{
 class ImportRollingStock : public QObject
 {
  Q_OBJECT
 public:
  explicit ImportRollingStock(QObject *parent = 0);

 signals:

 public slots:
 protected:
  /*protected*/ static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  /*protected*/ QLabel* lineNumber;// = new JLabel();
  /*protected*/ QLabel* importLine;// = new JLabel();

  /*protected*/ JmriJFrame* fstatus;
  /*protected*/ File* getFile();
  /*protected*/ QTextStream* getBufferedReader(File* file);
  /*protected*/ void createStatusFrame(QString title);
  /*protected*/ QStringList parseCommaLine(QString line, int arraySize);

 };
}
#endif // IMPORTROLLINGSTOCK_H
