#ifndef JSONSERVERACTION_H
#define JSONSERVERACTION_H
#include "abstractaction.h"

class JsonServerAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ JsonServerAction(QString s, QObject* parent);
 /*public*/ JsonServerAction(QObject* parent);
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0) ;
};

#endif // JSONSERVERACTION_H
