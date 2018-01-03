#ifndef JSONSERVERACTION_H
#define JSONSERVERACTION_H
#include "abstractaction.h"

class JsonServerAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ JsonServerAction(QString s, QObject* parent);
 /*public*/ JsonServerAction(QObject* parent = 0);
 ~JsonServerAction() {}
 JsonServerAction(const JsonServerAction&) : AbstractAction() {}
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0) ;
};
Q_DECLARE_METATYPE(JsonServerAction)
#endif // JSONSERVERACTION_H
