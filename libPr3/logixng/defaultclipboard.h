#ifndef DEFAULTCLIPBOARD_H
#define DEFAULTCLIPBOARD_H
#include "abstractbase.h"
#include "clipboard.h"
#include "clipboardmany.h"

class DefaultFemaleAnySocket;
class DefaultClipboard : public AbstractBase, public Clipboard
{
  Q_OBJECT
  Q_INTERFACES(Clipboard)
 public:
  DefaultClipboard(QObject* parent = nullptr);
  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ ClipboardMany* _clipboardItems = new ClipboardMany("", nullptr);
  /*private*/ /*final*/ FemaleAnySocket* _femaleSocket = new DefaultFemaleAnySocket(this, new FemaleSocketListener(),"A");

};

class DefaultFemaleAnySocket : public QObject, public FemaleAnySocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleAnySocket)

 public:
  QObject* self() override {return (QObject*)this;}
  //@Override
  /*public*/ void connected(FemaleSocket* socket) {
      // Do nothing
  }

  //@Override
  /*public*/ void disconnected(FemaleSocket* socket) {
      // Do nothing
  }

};
#endif // DEFAULTCLIPBOARD_H
