#ifndef DEFAULTFEMALEGENERICEXPRESSIONSOCKET_H
#define DEFAULTFEMALEGENERICEXPRESSIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femalegenericexpressionsocket.h"
#include "defaultfemaleanalogexpressionsocket.h"

class DefaultFemaleAnalogExpressionSocket;
class FemaleStringExpressionSocket;
class FemaleDigitalExpressionSocket;
class FemaleAnalogExpressionSocket;
class DefaultFemaleGenericExpressionSocket : public AbstractFemaleSocket, public FemaleGenericExpressionSocket, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleGenericExpressionSocket)
 public:
  DefaultFemaleGenericExpressionSocket(SocketType socketType,
                                       Base* parent,
                                       FemaleSocketListener* listener,
                                       QString name,
                                       QObject* parentObject = nullptr);
  /*public*/  FemaleSocket* getCurrentActiveSocket();
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  void setSocketType(SocketType socketType);
  /*public*/  SocketType getSocketType()override;
  /*public*/  void setDoI18N(bool do_i18n);
  /*public*/  bool getDoI18N();
  /*public*/  QVariant evaluateGeneric() /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QHash<Category *, QList<QString> > getConnectableClasses()override;
  /*public*/  void _connect(MaleSocket* socket) /*throws SocketAlreadyConnectedException*/override;
  /*public*/  void _disconnect()override;
  /*public*/  MaleSocket* getConnectedSocket() override;
  /*public*/  bool isConnected()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  void disposeMe()override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.implementation.DefaultFemaleGenericExpressionSocket";}

  QObject* self() override{return (QObject*)this;}
  QObject* bself() override{return (QObject*)this;}

 private:
  /*private*/ SocketType _socketType;             // The type of the socket the user has selected
  /*private*/ SocketType _currentSocketType;      // The current type of the socket.
  /*private*/ FemaleSocket* _currentActiveSocket;  // The socket that is currently in use, if any. Null otherwise.
  /*private*/ /*final*/ FemaleAnalogExpressionSocket* _analogSocket;// = new DefaultFemaleAnalogExpressionSocket(this, this, "A");
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _digitalSocket;// = new DefaultFemaleDigitalExpressionSocket(this, this, "D");
  /*private*/ /*final*/ FemaleStringExpressionSocket* _stringSocket;// = new DefaultFemaleStringExpressionSocket(this, this, "S");
  /*private*/ bool _do_i18n;
  /*private*/ void addClassesToMap(
    QHash<Category*, QList</*Class<? extends Base>*/QString> > destinationClasses,
    QHash<Category*, QList</*Class<? extends Base>*/QString> > sourceClasses);

};

#endif // DEFAULTFEMALEGENERICEXPRESSIONSOCKET_H
