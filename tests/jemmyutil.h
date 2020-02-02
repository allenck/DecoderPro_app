#ifndef JEMMYUTIL_H
#define JEMMYUTIL_H

#include <QObject>

class JmriJFrame;
class JemmyUtil : public QObject
{
 Q_OBJECT
public:
 static /*public*/ void pressDialogButton(JmriJFrame* f, QString buttonName);
 static /*public*/ void pressDialogButton(QString title, QString text);

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
#endif // JEMMYUTIL_H
