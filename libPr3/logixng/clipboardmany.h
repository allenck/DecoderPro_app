#ifndef CLIPBOARDMANY_H
#define CLIPBOARDMANY_H

#include "abstractbase.h"
#include "femalesocketlistener.h"
#include "femaleanysocket.h"

class ItemData;
class ItemEntry;
class Logger;
class ClipboardMany : public AbstractBase, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
public:
  QObject* self() override {return (QObject*)this;}
 private:
  /*private*/ /*static*/ class ItemEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ QString _itemManagerClass;
      /*private*/ /*final*/ FemaleAnySocket* _socket;

      /*private*/ ItemEntry(FemaleAnySocket* socket, QString itemManagerClass, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _itemManagerClass = itemManagerClass;
          _socket = socket;
      }

      /*private*/ ItemEntry(FemaleAnySocket* socket) {
          this->_socket = socket;
      }
   friend class ClipboardMany;
  };

  /*public*/ /*static*/ class ItemData {
   public:
      /*public*/ /*final*/ QString _systemName;
      /*public*/ /*final*/ QString _className;
      /*public*/ /*final*/ QString _socketName;

      /*public*/ ItemData(QString socketName, QString systemName, QString className) {
          _systemName = systemName;
          _className = className;
          _socketName = socketName;
      }
  };

 public:
  /*public*/ ClipboardMany(QString sys, QString user, QObject *parent = nullptr)
          ;
  /*public*/ ClipboardMany(QString sys, QString user, QList<ItemData*> itemSystemNames, QObject *parent = nullptr)
          /*throw (BadUserNameException, BadSystemNameException)*/;
  /*public*/ QString getItemSystemName(int index);
  /*public*/ void setup()override;
  /*public*/ Category* getCategory()override;

  /*public*/ FemaleSocket* getChild(int index) /*throw (IllegalArgumentException, UnsupportedOperationException)*/ override;
  /*public*/ int getChildCount()override;
  /*public*/ void ensureFreeSocketAtTop();
  /*public*/ void connected(FemaleSocket* socket)override;
  /*public*/ void disconnected(FemaleSocket* socket)override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale) override;
  /*public*/ void setState(int s) /*throw (JmriException)*/override;
  /*public*/ int getState()override;
  /*public*/ QString getBeanType()override;
  /*public*/ Base* getParent() const override;
  /*public*/ void setParent(Base* parent)override;
  /*public*/ Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) throw  (JmriException)override;
  /*public*/ Base* deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/override;
  /*public*/ void registerListenersForThisClass() override;
  /*public*/ void unregisterListenersForThisClass()override;
  /*public*/ void disposeMe()override;

 private:
  static Logger* log;
  /*private*/ Base* _parent;
  /*private*/ /*final*/ QList<ItemEntry*> _itemEntries = QList<ItemEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ void setItemSystemNames(QList<ItemData*> systemNamesAndClasses);
  /*private*/ QString getNewSocketName();
};

#endif // CLIPBOARDMANY_H
