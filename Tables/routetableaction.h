#ifndef ROUTETABLEACTION_H
#define ROUTETABLEACTION_H
#include "abstracttableaction.h"

class RouteTableAction : AbstractTableAction
{
  Q_OBJECT
 public:
  Q_INVOKABLE /*public*/ RouteTableAction(QString s, QObject* parent);
  Q_INVOKABLE /*public*/ RouteTableAction(QObject* parent=nullptr);
  ~RouteTableAction() {}
  RouteTableAction(const RouteTableAction&) : AbstractTableAction() {}
  /*public*/ void setMessagePreferencesDetails() override;
  /*public*/ QString getClassDescription() override;

 private:

 protected:
  /*protected*/ void createModel() override;
  /*protected*/ void setTitle() override;
  /*protected*/ QString helpTarget() override;
  /*protected*/ void addPressed(/*ActionEvent e*/) override;
  /*protected*/ QString getClassName() override;

};
Q_DECLARE_METATYPE(RouteTableAction )
#endif // ROUTETABLEACTION_H
