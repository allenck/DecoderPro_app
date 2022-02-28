#ifndef STRINGMANY_H
#define STRINGMANY_H
#include "abstractstringaction.h"
#include "femalesocketlistener.h"
#include "femalestringactionsocket.h"


class ActionEntry;
class StringMany : public AbstractStringAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  StringMany(QString sys, QString user, QObject* parent = nullptr);
  /*public*/  StringMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject* parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ override;
  /*public*/  QString getActionSystemName(int index);
  /*public*/  void setup() override;
  /*public*/  Category* getCategory()override;
  /*public*/  void setValue(QString value) /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ /*static*/ class ActionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleStringActionSocket* _socket;

      /*private*/ ActionEntry(FemaleStringActionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ActionEntry(FemaleStringActionSocket* socket) {
          this->_socket = socket;
      }
   friend class StringMany;
  };
  /*private*/ void setActionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ /*final*/ QList<ActionEntry*> _actionEntries = QList<ActionEntry*>();
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);
  /*private*/ void checkFreeSocket();
  /*private*/ void setNumSockets(int num) ;

};

#endif // STRINGMANY_H
