#ifndef TRAINSTABLEFRAME_H
#define TRAINSTABLEFRAME_H

#include "operationsframe.h"
#include "appslib_global.h"
#include "propertychangelistener.h"

class QLabel;
class JButton;
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
 class APPSLIBSHARED_EXPORT TrainsTableFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  TrainsTableFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString MOVE;//= Bundle.getMessage("Move");
  /*public*/ static /*final*/ QString TERMINATE;//= Bundle.getMessage("Terminate");
  /*public*/ static /*final*/ QString RESET;//= Bundle.getMessage("Reset");
  /*public*/ static /*final*/ QString CONDUCTOR;//= Bundle.getMessage("Conductor");
  /*public*/ QList<Train*> getSortByList();
  /*public*/ void dispose() override;
  /*public*/ QString getClassName() override;
  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void checkBoxActionPerformed(QWidget* ae) override;
  /*public*/ void radioButtonActionPerformed(QWidget* ae) override;


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
  JButton* addButton;//= new JButton(tr("Add"));
  JButton* buildButton;//= new JButton(tr("Build"));
  JButton* printButton;//= new JButton(tr("Print"));
  JButton* openFileButton;//= new JButton(tr("OpenFile"));
  JButton* runFileButton;//= new JButton(tr("RunFile"));
  JButton* switchListsButton;//= new JButton(tr("SwitchLists"));
  JButton* terminateButton;//= new JButton(tr("Terminate"));
  JButton* saveButton;//= new JButton(tr("SaveBuilds"));

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
