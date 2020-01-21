#ifndef TRAINSTABLEFRAME_H
#define TRAINSTABLEFRAME_H

#include "operationsframe.h"
#include "appslib_global.h"

class QLabel;
class QPushButton;
class QRadioButton;
class QSortFilterProxyModel;
namespace Operations
{
 class Train;
 class TrainSwitchListEditFrame;
 class CarManagerXml;
 class EngineManagerXml;
 class TrainManagerXml;
 class TrainManager;
 class LocationManager;
 class TrainsTableModel;
 class APPSLIBSHARED_EXPORT TrainsTableFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainsTableFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString MOVE;//= Bundle.getMessage("Move");
  /*public*/ static /*final*/ QString TERMINATE;//= Bundle.getMessage("Terminate");
  /*public*/ static /*final*/ QString RESET;//= Bundle.getMessage("Reset");
  /*public*/ static /*final*/ QString CONDUCTOR;//= Bundle.getMessage("Conductor");
  /*public*/ QList<Train*> getSortByList();
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);


 private:
  CarManagerXml* carManagerXml;//= CarManagerXml.instance(); // load cars
  EngineManagerXml* engineManagerXml;//= EngineManagerXml.instance(); // load engines
  TrainManager* trainManager;//= TrainManager.instance();
  TrainManagerXml* trainManagerXml;//= TrainManagerXml.instance();
  LocationManager* locationManager;//= LocationManager.instance();

  TrainsTableModel* trainsModel;
  QSortFilterProxyModel* sorter;
  JTable* trainsTable;
  //QScrollArea* trainsPane;

  // labels
  QLabel* numTrains;//= new JLabel();
  QLabel* textTrains;//= new JLabel(tr("Trains").toLowerCase());
  QLabel* textSep1;//= new JLabel("      ");

  // radio buttons
  QRadioButton* showTime;//= new JRadioButton(tr("Time"));
  QRadioButton* showId;//= new JRadioButton(tr("Id"));

  QRadioButton* moveRB;//= new JRadioButton(MOVE);
  QRadioButton* terminateRB;//= new JRadioButton(TERMINATE);
  QRadioButton* resetRB;//= new JRadioButton(RESET);
  QRadioButton* conductorRB;//= new JRadioButton(CONDUCTOR);

  // major buttons
  QPushButton* addButton;//= new JButton(tr("Add"));
  QPushButton* buildButton;//= new JButton(tr("Build"));
  QPushButton* printButton;//= new JButton(tr("Print"));
  QPushButton* openFileButton;//= new JButton(tr("OpenFile"));
  QPushButton* runFileButton;//= new JButton(tr("RunFile"));
  QPushButton* switchListsButton;//= new JButton(tr("SwitchLists"));
  QPushButton* terminateButton;//= new JButton(tr("Terminate"));
  QPushButton* saveButton;//= new JButton(tr("SaveBuilds"));

  // check boxes
  QCheckBox* buildMsgBox;//= new JCheckBox(tr("BuildMessages"));
  QCheckBox* buildReportBox;//= new JCheckBox(tr("BuildReport"));
  QCheckBox* printPreviewBox;//= new JCheckBox(tr("Preview"));
  QCheckBox* openFileBox;//= new JCheckBox(tr("OpenFile"));
  QCheckBox* runFileBox;//= new JCheckBox(tr("RunFile"));
  QCheckBox* showAllBox;//= new JCheckBox(tr("ShowAllTrains"));
  /*private*/ void updateTitle();
  /*private*/ void updateRunAndOpenButtons();
  /*private*/ /*synchronized*/ void addPropertyChangeLocations();
  /*private*/ /*synchronized*/ void removePropertyChangeLocations();
  TrainSwitchListEditFrame* tslef;
  int _status;// = TableSorter.ASCENDING;
  Logger* log;
  /*private*/ void updateSwitchListButton();
  /*private*/ void setPrintButtonText();
  /*private*/ void setTrainActionButton();

 protected:
  /*protected*/ QString getSortBy();
  /*protected*/ void handleModified();
  /*protected*/ void storeValues();

 friend class PrintTrainsAction;
 };
}
#endif // TRAINSTABLEFRAME_H
