#ifndef POWERBUTTONACTION_H
#define POWERBUTTONACTION_H
#include "abstractaction.h"

class PowerButtonAction : public AbstractAction
{
 Q_OBJECT
public:
 PowerButtonAction(QObject* parent = nullptr);
 /*public*/ PowerButtonAction(QString title, QObject* parent);
 ~PowerButtonAction() {}
 PowerButtonAction(const PowerButtonAction&) : AbstractAction() {}

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* ev);
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
 void checkManager();
 void updateLabel();

};
Q_DECLARE_METATYPE(PowerButtonAction)
#endif // POWERBUTTONACTION_H
