#ifndef LOCATIONSTABLEFRAME_H
#define LOCATIONSTABLEFRAME_H

#include "operationsframe.h"
#include "appslib_global.h"

class QRadioButton;
class QLabel;
class JTable;
class QScrollArea;
class QGroupBox;
namespace Operations
{
 class LocationsTableModel;
 class APPSLIBSHARED_EXPORT LocationsTableFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  LocationsTableFrame(QWidget* parent = 0);

  public slots:
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);

  /*public*/ void dispose();
  /*public*/ QString getClassName();

 private:
  LocationsTableModel* locationsModel;// = new LocationsTableModel();
  JTable* locationsTable;// = new javax.swing.JTable(locationsModel);
  //QScrollArea locationsPane;

  // labels
  QLabel* textSort;// = new JLabel(Bundle.getMessage("SortBy"));
  QLabel* textSep;// = new JLabel("          ");

  // radio buttons
  QRadioButton* sortByName;// = new javax.swing.JRadioButton(Bundle.getMessage("Name"));
  QRadioButton* sortById;// = new javax.swing.JRadioButton(Bundle.getMessage("Id"));

  // major buttons
  JButton* addButton;// = new JButton(Bundle.getMessage("Add"));
//	JButton printTableButton = new JButton("Print Table");
  Logger* log;
 };
}
#endif // LOCATIONSTABLEFRAME_H
