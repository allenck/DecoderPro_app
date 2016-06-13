#ifndef CARSTABLEFRAME_H
#define CARSTABLEFRAME_H

#include "operationsframe.h"
#include <QList>
#include "appslib_global.h"


class QButtonGroup;
class QLabel;
class CarsTableModel;
class CarManager;
class JTextField;
class QRadioButton;
class QPushButton;
namespace Operations
{
class RollingStock;
 class CarEditFrame;
 class CarsTableModel;
 class CarManager;
 class APPSLIBSHARED_EXPORT CarsTableFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ CarsTableFrame(bool showAllCars, QString locationName, QString trackName, QWidget* parent= 0);
  /*public*/ QList<RollingStock*>* getSortByList();
  /*public*/ void radioButtonActionPerformed(QWidget* ae);

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  CarsTableModel* carsTableModel;
  JTable* carsTable;
  bool showAllCars;
  QString locationName;
  QString trackName;
  CarManager* carManager;// = CarManager.instance();

  // labels
  QLabel* numCars;// = new JLabel();
  QLabel* textCars;// = new JLabel(Bundle.getMessage("cars"));
  QLabel* textSep1;// = new JLabel("      ");

  // radio buttons
  QRadioButton* sortByNumber;//= new JRadioButton(Bundle.getMessage("Number"));
  QRadioButton* sortByRoad;//= new JRadioButton(Bundle.getMessage("Road"));
  QRadioButton* sortByType;//= new JRadioButton(Bundle.getMessage("Type"));
  QRadioButton* sortByColor;//= new JRadioButton(Bundle.getMessage("Color"));
  QRadioButton* sortByLoad;//= new JRadioButton(Bundle.getMessage("Load"));
  QRadioButton* sortByKernel;//= new JRadioButton(Bundle.getMessage("Kernel"));
  QRadioButton* sortByLocation;//= new JRadioButton(Bundle.getMessage("Location"));
  QRadioButton* sortByDestination;//= new JRadioButton(Bundle.getMessage("Destination"));
  QRadioButton* sortByFinalDestination;//= new JRadioButton(Bundle.getMessage("FD"));
  QRadioButton* sortByRwe;//= new JRadioButton(Bundle.getMessage("RWE"));
  QRadioButton* sortByTrain;//= new JRadioButton(Bundle.getMessage("Train"));
  QRadioButton* sortByMoves;//= new JRadioButton(Bundle.getMessage("Moves"));
  QRadioButton* sortByBuilt;//= new JRadioButton(Bundle.getMessage("Built"));
  QRadioButton* sortByOwner;//= new JRadioButton(Bundle.getMessage("Owner"));
  QRadioButton* sortByValue;//= new JRadioButton(Setup.getValueLabel());
  QRadioButton* sortByRfid;//= new JRadioButton(Setup.getRfidLabel());
  QRadioButton* sortByWait;//= new JRadioButton(Bundle.getMessage("Wait"));
  QRadioButton* sortByPickup;//= new JRadioButton(Bundle.getMessage("Pickup"));
  QRadioButton* sortByLast;//= new JRadioButton(Bundle.getMessage("Last"));
  QButtonGroup* group;//= new ButtonGroup();

  // major buttons
  QPushButton* addButton;//= new JButton(Bundle.getMessage("Add"));
  QPushButton* findButton;//= new JButton(Bundle.getMessage("Find"));
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  JTextField* findCarTextBox;// = new JTextField(6);
  /*private*/ void updateNumCars();
  CarEditFrame* f;// = null;
  Logger* log;

 };
}
#endif // CARSTABLEFRAME_H
