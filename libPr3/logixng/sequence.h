#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"
#include "femaledigitalexpressionsocket.h"

class FemaleDigitalActionSocket;
class ActionEntry;
class ExpressionEntry;
class FemaleDigitalExpressionSocket;
class Sequence : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  Sequence(QString sys, QString user, QObject * parent = nullptr);
  enum SEQ {
  EXPRESSION_START = 0,
  EXPRESSION_STOP = 1,
  EXPRESSION_RESET = 2,
  NUM_STATIC_EXPRESSIONS = 3
  };
  Sequence(QString sys, QString user,
              QList<QMap<QString, QString>>* expressionSystemNames,
              QList<QMap<QString, QString>>* actionSystemNames, QObject* parent = nullptr);
  /*public*/  QString getNewActionSocketName();
  /*public*/  QString getNewExpressionSocketName();
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/;
  /*public*/  Category getCategory() override;
  /*public*/  void execute() /*throws JmriException*/ override;
  /*public*/  bool getStartImmediately();
  /*public*/  void setStartImmediately(bool startImmediately);
  /*public*/  bool getRunContinuously();
  /*public*/  void setRunContinuously(bool runContinuously);
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalExpressionSocket* getStartExpressionSocket();
  /*public*/  QString getStartExpressionSocketSystemName();
  /*public*/  void setStartExpressionSocketSystemName(QString systemName) ;
  /*public*/  FemaleDigitalExpressionSocket* getStopExpressionSocket();
  /*public*/  QString getStopExpressionSocketSystemName();
  /*public*/  void setStopExpressionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalExpressionSocket* getResetExpressionSocket();
  /*public*/  QString getResetExpressionSocketSystemName();
  /*public*/  void setResetExpressionSocketSystemName(QString systemName);
  /*public*/  int getNumExpressions();
  /*public*/  FemaleDigitalExpressionSocket* getExpressionSocket(int socket);
  /*public*/  QString getExpressionSocketSystemName(int socket);
  /*public*/  void setExpressionSocketSystemName(int socket, QString systemName);
  /*public*/  int getNumActions();
  /*public*/  FemaleDigitalActionSocket* getActionSocket(int socket);
  /*public*/  QString getActionSocketSystemName(int socket);
  /*public*/  void setActionSocketSystemName(int socket, QString systemName);
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

 private:
  static Logger* log;
  /*private*/ QString _startExpressionSocketSystemName;
  /*private*/ QString _stopExpressionSocketSystemName;
  /*private*/ QString _resetExpressionSocketSystemName;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _startExpressionSocket;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _stopExpressionSocket;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _resetExpressionSocket;
  /*private*/ int _currentStep = -1;
  /*private*/ bool _isRunning = false;
  /*private*/ bool _startImmediately = false;
  /*private*/ bool _runContinuously = false;
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ void setExpressionSystemNames(QList<QMap<QString, QString>>* systemNames);
  /*private*/ void setActionSystemNames(QList<QMap<QString, QString> > *systemNames);
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

  /*private*/ /*static*/ class ExpressionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalExpressionSocket* _socket;

      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket) {
          this->_socket = socket;
      }
    friend class Sequence;

  };

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
    friend class Sequence;
  };
  /*private*/ /*final*/ QList<ExpressionEntry> _expressionEntries = QList<Sequence::ExpressionEntry>();
  /*private*/ /*final*/ QList<ActionEntry> _actionEntries = QList<ActionEntry>();
  friend class ActionEntry;
  friend class ExpressionEntry;
};

#endif // SEQUENCE_H
