#ifndef JEMMYUTIL_H
#define JEMMYUTIL_H

#include <QObject>
#include "jframeoperator.h"

class JmriJFrame;
class JemmyUtil : public QObject
{
 Q_OBJECT
public:
 static /*public*/ void pressDialogButton(JmriJFrame* f, QString buttonName);
 static /*public*/ void pressDialogButton(QString title, QString text);
 /*public*/ static QThread* createModalDialogOperatorThread(QString dialogTitle, QString buttonText);

signals:

public slots:

 private:
 explicit JemmyUtil(QObject *parent = nullptr);

};

class JemmyWait : public QObject
{
 Q_OBJECT
 QString dialogTitle;
 QString buttonName;
 int counter = 0;
public:
 JemmyWait(QString dialogTitle, QString buttonName);

public slots:
 void process();

signals:
 void finished();

};
class JUModalDialogOperator : public QObject
{
 Q_OBJECT
 QString dialogTitle;
 QString buttonText;
 JDialogOperator* jdo;
 JButtonOperator* jbo;
public:
 JUModalDialogOperator(QString dialogTitle, QString buttonText)
 {
  this->dialogTitle = dialogTitle;
  this->buttonText = buttonText;
 }
public slots:
 void process()
 {
  jdo = new JDialogOperator(dialogTitle);
  jbo = new JButtonOperator(jdo, buttonText);
  jbo->pushNoBlock();
  emit finished();
 }
signals:
 void finished();
};
#endif // JEMMYUTIL_H
