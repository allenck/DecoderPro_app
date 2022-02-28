#ifndef DIGITALMANY_H
#define DIGITALMANY_H

#include "abstractdigitalaction.h"
#include "femaledigitalactionsocket.h"
#include "femalesocketlistener.h"


class DigitalMany : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
  /*private*/ /*static*/ class ActionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalActionSocket* _socket;

      /*private*/ ActionEntry(FemaleDigitalActionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ActionEntry(FemaleDigitalActionSocket* socket) {
          this->_socket = socket;
      }
      friend class DigitalMany;
  };

 public:
  explicit DigitalMany(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  DigitalMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject* parent);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/;
  /*public*/  QString getActionSystemName(int index);
  /*public*/  void setup()override;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute() override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale);
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;

  /*private*/ /*final*/ QList<ActionEntry*> _actionEntries = QList<ActionEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ void setActionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ void setNumSockets(int num);
  /*private*/ void checkFreeSocket();
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // DIGITALMANY_H
