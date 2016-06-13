#ifndef VSDPREFERENCESACTION_H
#define VSDPREFERENCESACTION_H

#include "abstractaction.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT VSDPreferencesAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit VSDPreferencesAction(QObject *parent);
 /*public*/ VSDPreferencesAction(QString s,QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

};

#endif // VSDPREFERENCESACTION_H
