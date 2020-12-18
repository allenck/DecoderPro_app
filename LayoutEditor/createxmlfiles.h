#ifndef CREATEXMLFILES_H
#define CREATEXMLFILES_H

#include <QObject>

class PrintWriter;
class CreateXMLFiles : public QObject
{
  Q_OBJECT
 public:
  explicit CreateXMLFiles(QObject *parent = nullptr);
  /*public*/ static void generateProlog(PrintWriter* printWriter);
  /*public*/ static void generateEpilogue(PrintWriter* printWriter);

 signals:

 public slots:
};

#endif // CREATEXMLFILES_H
