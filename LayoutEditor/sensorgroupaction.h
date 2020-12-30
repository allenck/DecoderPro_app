#ifndef SENSORGROUPACTION_H
#define SENSORGROUPACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT SensorGroupAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit SensorGroupAction(QObject *parent);
 /*public*/ SensorGroupAction(QString s,QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;

private:
 void common();

};

#endif // SENSORGROUPACTION_H
