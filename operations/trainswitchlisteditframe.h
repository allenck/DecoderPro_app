#ifndef TRAINSWITCHLISTEDITFRAME_H
#define TRAINSWITCHLISTEDITFRAME_H

#include "operationsframe.h"
#include "propertychangelistener.h"
class JActionEvent;
class QGroupBox;
namespace Operations
{
 class Location;
 class TrainSwitchListCommentFrame;
 class LocationManager;
 class TrainSwitchListEditFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  TrainSwitchListEditFrame(QWidget* parent = 0);
  /*public*/ void initComponents() override;
  /*public*/ void dispose() override;
  /*public*/ QString getClassName() override;

  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void checkBoxActionPerformed(QWidget* ae) override;
  /*public*/ void locationCheckBoxActionPerformed(QWidget*);
  /*public*/ void commentButtonActionPerformed(JActionEvent* ae = 0);

 private:
  QScrollArea* switchPane;

  // load managers
  LocationManager* locationManager;// = LocationManager.instance();
  QList<QCheckBox*> locationCheckBoxes;// = new ArrayList<JCheckBox>();
  QList<JComboBox*> locationComboBoxes;// = new ArrayList<JComboBox<String>>();
  QWidget* locationPanelCheckBoxes;// = new JPanel();

  // checkboxes
  QCheckBox* switchListRealTimeCheckBox;// = new JCheckBox(Bundle.getMessage("SwitchListRealTime"));
  QCheckBox* switchListAllTrainsCheckBox;// = new JCheckBox(Bundle.getMessage("SwitchListAllTrains"));

  // major buttons
  QPushButton* clearButton;// = new JButton(Bundle.getMessage("Clear"));
  QPushButton* setButton;// = new JButton(Bundle.getMessage("Select"));
  QPushButton* printButton;// = new JButton(Bundle.getMessage("PrintSwitchLists"));
  QPushButton* previewButton;// = new JButton(Bundle.getMessage("PreviewSwitchLists"));
  QPushButton* changeButton;// = new JButton(Bundle.getMessage("PrintChanges"));
  QPushButton* runButton;// = new JButton(Bundle.getMessage("RunFile"));
  QPushButton* runChangeButton;// = new JButton(Bundle.getMessage("RunFileChanges"));
  QPushButton* csvGenerateButton;// = new JButton(Bundle.getMessage("CsvGenerate"));
  QPushButton* csvChangeButton;// = new JButton(Bundle.getMessage("CsvChanges"));
  QPushButton* updateButton;// = new JButton(Bundle.getMessage("Update"));
  QPushButton* resetButton;// = new JButton(Bundle.getMessage("ResetSwitchLists"));
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  JComboBox* switchListPageComboBox;// = Setup.getSwitchListPageFormatComboBox();

  // panels
  JPanel* customPanel;
  /*private*/ void reset();
  /*private*/ void save();
  Logger* log;
  /*private*/ void buildSwitchList(bool isPreview, bool isChanged, bool isCsv, bool isUpdate);
  /*private*/ void selectCheckboxes(bool enable);
  /*private*/ void updateLocationCheckboxes();
  /*private*/ void runCustomSwitchLists(bool isChanged);
  /*private*/ void enableSaveButton(bool enable);
  /*private*/ void enableChangeButtons();
  /*private*/ void addLocationCheckBoxAction(QCheckBox* b);
  QSignalMapper* locationCheckBoxMapper;
  /*private*/ void addCommentButtonAction(QPushButton* b);

 private slots:
  /*private*/ void changeLocationCheckboxes(PropertyChangeEvent* e);

 protected slots:
  /*protected*/ void comboBoxActionPerformed(QWidget* ae);

 };

 /*private static */class TrainSwitchListCommentFrame : public OperationsFrame
 {
  Q_OBJECT
  /**
   *
   */
  //private static final long serialVersionUID = 4880037349897207594L;
  // text area
  HtmlTextEdit* commentTextArea;// = new JTextArea(10, 90);
  //QScrollArea* commentScroller;// = new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//             JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  QSize minScrollerDim;// = new Dimension(1200, 500);
  QPushButton* saveButton;// = new QPushButton(tr("Save"));

  Location* _location;
  Logger* log;
  /*private*/ TrainSwitchListCommentFrame(Location* location);
  /*private*/ void initComponents(Location* location);
 public:
  /*public*/ QString getClassName();

  // Buttons
 public slots:

  /*public*/ void buttonActionPerformed(QWidget* ae);
  friend class TrainSwitchListEditFrame;
 };

}
#endif // TRAINSWITCHLISTEDITFRAME_H
