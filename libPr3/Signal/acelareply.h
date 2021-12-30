#ifndef ACELAREPLY_H
#define ACELAREPLY_H

#include <abstractmrreply.h>
#include <QWidget>

class AcelaReply : public AbstractMRReply
{
  Q_OBJECT
 public:
  explicit AcelaReply(QObject *parent = nullptr);
  AcelaReply(QString s, QObject* parent);
  /*public*/  AcelaReply(AcelaReply* l, QObject* parent);

 private:

 protected:
  /*protected*/ int skipPrefix(int index);

};

#endif // ACELAREPLY_H
