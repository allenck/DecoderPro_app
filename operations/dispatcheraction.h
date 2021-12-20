#ifndef DISPATCHERACTION_H
#define DISPATCHERACTION_H
#include "abstractaction.h"

class DispatcherFrame;
class DispatcherAction : public AbstractAction
{
  Q_OBJECT
public:
 DispatcherAction(QObject* parent = 0);
 ~DispatcherAction() {}
 DispatcherAction(const DispatcherAction&) : AbstractAction() {}
 DispatcherAction(QString s, QObject* parent);

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 DispatcherFrame* f;// = null;

};
Q_DECLARE_METATYPE(DispatcherAction)
#endif // DISPATCHERACTION_H
