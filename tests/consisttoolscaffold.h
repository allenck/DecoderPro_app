#ifndef CONSISTTOOLSCAFFOLD_H
#define CONSISTTOOLSCAFFOLD_H

#include "jframeoperator.h"

class ConsistToolScaffold : public JFrameOperator
{
 Q_OBJECT
 public:
  explicit ConsistToolScaffold(QObject *parent = nullptr);
  /*public*/ void pushAdvancedConsistButton();
  /*public*/ void pushCommandStationConsistButton();
  /*public*/ void setConsistAddressValue(QString value);
  /*public*/ void pushAddButton();
  /*public*/ void pushResetButton();
  /*public*/ void setLocoAddressValue(QString value);
  /*public*/ void pushDeleteButton();
  /*public*/ void pushDeleteWithDismiss();
  /*public*/ void pushThrottleButton();
  /*public*/ void pushReverseButton();
  /*public*/ void pushRestoreButton();
  /*public*/ void startRosterScan();
  void requestClose();

 signals:

 public slots:
  friend class JButtonOperatorO1;
};

class JButtonOperatorO1 : public JButtonOperator
{
  Q_OBJECT
public:
  JButtonOperatorO1(QObject* parent, QString text) : JButtonOperator(parent, text) {}
  //@Override
  /*public*/ bool checkComponent(QWidget* comp) override ;
  //@Override
  /*public*/ QString getDescription() {
      return "tooltip for delete button";
  }
 friend class ConsistToolScaffold;
};

class DeleteWithDismiss : public QObject
{
 Q_OBJECT
 qint64 start;
public:
 DeleteWithDismiss();
public slots:
 void process();
signals:
 void finished();
};
#endif // CONSISTTOOLSCAFFOLD_H
