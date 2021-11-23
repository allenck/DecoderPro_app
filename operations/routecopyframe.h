#ifndef ROUTECOPYFRAME_H
#define ROUTECOPYFRAME_H

#include "operationsframe.h"

class JTextField;
class QLabel;
namespace Operations
{
 class RouteManager;
 class RouteCopyFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  RouteCopyFrame(QWidget* parent = 0);
  /*public*/ void setRouteName(QString routeName);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  Logger* log;
  RouteManager* routeManager;//= RouteManager.instance();

  // labels
  QLabel* textCopyRoute;//= new JLabel(Bundle.getMessage("CopyRoute"));
  QLabel* textRouteName;//= new JLabel(Bundle.getMessage("RouteName"));

  // text field
  JTextField* routeNameTextField;//= new JTextField(Control.max_len_string_route_name);

  // check boxes
  QCheckBox* invertCheckBox;//= new JCheckBox(Bundle.getMessage("Invert"));

  // major buttons
  JButton* copyButton;//= new JButton(Bundle.getMessage("Copy"));

  // combo boxes
  JComboBox* routeBox;//= RouteManager.instance().getComboBox();
  /*private*/ void reportRouteExists(QString s);
  /*private*/ void reportRouteDoesNotExist();
  /*private*/ bool checkName();


 };
}
#endif // ROUTECOPYFRAME_H
