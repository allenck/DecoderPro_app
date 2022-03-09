#ifndef DIGITALBOOLEANMANY_H
#define DIGITALBOOLEANMANY_H

#include "abstractdigitalbooleanaction.h"
#include "femalesocketlistener.h"

class ActionEntry;
class FemaleDigitalBooleanActionSocket;
class DigitalBooleanMany : public AbstractDigitalBooleanAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit DigitalBooleanMany(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  DigitalBooleanMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/override;
  /*public*/  QString getActionSystemName(int index) ;
  /*public*/  void setup()override;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ /*static*/ class ActionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalBooleanActionSocket* _socket;

      /*private*/ ActionEntry(FemaleDigitalBooleanActionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ActionEntry(FemaleDigitalBooleanActionSocket* socket) {
          this->_socket = socket;
      }
      friend class DigitalBooleanMany;
  };
  /*private*/ /*final*/ QList<ActionEntry*> _actionEntries = QList<ActionEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ void setActionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ void setNumSockets(int num);
  /*private*/ void checkFreeSocket();
  /*private*/ void insertNewSocket(int index) ;
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // DIGITALBOOLEANMANY_H
