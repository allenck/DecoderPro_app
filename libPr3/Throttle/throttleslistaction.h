#ifndef THROTTLESLISTACTION_H
#define THROTTLESLISTACTION_H

#include <QAction>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ThrottlesListAction : public QAction
{
 Q_OBJECT
public:
 explicit ThrottlesListAction(QObject *parent = 0);
 /*public*/ ThrottlesListAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};

#endif // THROTTLESLISTACTION_H
