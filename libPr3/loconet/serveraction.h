#ifndef SERVERACTION_H
#define SERVERACTION_H

#include <QAction>

class ServerAction : public QAction
{
 Q_OBJECT
public:
 explicit ServerAction(QObject *parent = 0);
 /*public*/ ServerAction(QString s, QObject *parent);
 /*public*/ ServerAction();

signals:

public slots:
   /*public*/ void actionPerformed(ActionEvent* e = 0);

};

#endif // SERVERACTION_H
