#ifndef ROUTEEDITFRAME_H
#define ROUTEEDITFRAME_H
#include "abstractrouteaddeditframe.h"

class RouteEditFrame : public AbstractRouteAddEditFrame
{
 public:
  /*public*/ RouteEditFrame(QString systemName, QWidget* parent = nullptr);
  /*public*/ RouteEditFrame(QString name, QString systemName, QWidget* parent = nullptr);
  /*public*/ RouteEditFrame(QString name, bool saveSize, bool savePosition, QString systemName, QWidget* parent = nullptr);
  /*public*/ void initComponents() override;


 private:
  /*private*/ /*final*/ QString systemName;
  /*private*/ void exportButtonPressed(/*ActionEvent e*/);
  /*private*/ void cancelPressed(/*ActionEvent e*/);
  /*private*/ void deletePressed(/*ActionEvent e*/);

 protected:
  /*protected*/ JPanel* getButtonPanel() override;

};

#endif // ROUTEEDITFRAME_H
