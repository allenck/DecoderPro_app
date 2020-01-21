#ifndef ROUTESTABLEFRAME_H
#define ROUTESTABLEFRAME_H
#include "operationsframe.h"

class QLabel;
namespace Operations
{
 class RoutesTableModel;
 class RoutesTableFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  RoutesTableFrame(QWidget* parent = 0);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  RoutesTableModel* routesModel;// = new RoutesTableModel();

  // labels
  QLabel* textSort;// = new JLabel(Bundle.getMessage("SortBy"));
  QLabel* textSep;// = new javax.swing.JLabel("          ");

  // radio buttons
  QRadioButton* sortByName;// = new JRadioButton(Bundle.getMessage("Name"));
  QRadioButton* sortById;// = new JRadioButton(Bundle.getMessage("Id"));

  // major buttons
  QPushButton* addButton;// = new JButton(Bundle.getMessage("Add"));
  Logger* log;
 };
}
#endif // ROUTESTABLEFRAME_H
