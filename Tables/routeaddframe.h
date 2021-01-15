#ifndef ROUTEADDFRAME_H
#define ROUTEADDFRAME_H
#include "abstractrouteaddeditframe.h"

class RouteAddFrame : public AbstractRouteAddEditFrame
{
  Q_OBJECT
 public:
  /*public*/ RouteAddFrame(QWidget* parent = nullptr);
  /*public*/ RouteAddFrame(QString name, QWidget* parent = nullptr);
  /*public*/ RouteAddFrame(QString name, bool saveSize, bool savePosition, QWidget* parent = nullptr);

 private:
  /*private*/ void cancelAddPressed(/*ActionEvent e*/);
  /*private*/ void cancelAdd();
  /*private*/ void createPressed(/*ActionEvent e*/);
  /*private*/ bool checkNewNamesOK();

 protected:
  /*protected*/ JPanel* getButtonPanel() override;

  friend class RouteOutputModel;
};

#endif // ROUTEADDFRAME_H
