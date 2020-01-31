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

#endif // JEMMYUTIL_H
