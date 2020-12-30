#ifndef OPERATIONSSETUPPANEL_H
#define OPERATIONSSETUPPANEL_H
#include "operationspreferencespanel.h"
#include "appslib_global.h"
#include "propertychangeevent.h"

class JActionEvent;
class JTextArea;
class JTextField;
class QCheckBox;
class QPushButton;
class QRadioButton;
class Logger;
class QComboBox;
class QLabel;
namespace Operations
{
 class RouteManager;
 class APPSLIBSHARED_EXPORT OperationsSetupPanel : public OperationsPreferencesPanel
 {
  Q_OBJECT
 public:
  explicit OperationsSetupPanel(QWidget *parent = 0);
  /*public*/ QString getTabbedPreferencesTitle();
  /*public*/ QString getPreferencesTooltip();
  /*public*/ void savePreferences();
  /*public*/ bool isDirty();

 private:
  /*private*/ void setDirectionCheckBox(int direction);
  /*private*/ void setScale();

 signals:

 public slots:
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  /**
   *
   */
  //private static final long serialVersionUID = 7662835134616666932L;
  //static Logger log = LoggerFactory.getLogger(OperationsSetupFrame.class.getName());
  Logger* log;

  // labels
  QLabel* textIconNorth; //=new QLabel(Bundle.getMessage("IconNorth"));
  QLabel* textIconSouth; //=new QLabel(Bundle.getMessage("IconSouth"));
  QLabel* textIconEast; //=new QLabel(Bundle.getMessage("IconEast"));
  QLabel* textIconWest; //=new QLabel(Bundle.getMessage("IconWest"));
  QLabel* textIconLocal; //=new QLabel(Bundle.getMessage("IconLocal"));
  QLabel* textIconTerminate; //=new QLabel(Bundle.getMessage("IconTerminate"));
  // QLabel* textComment; //=new QLabel(Bundle.getMessage("Comment"));

  // major buttons
  QPushButton* backupButton; //=new JButton(Bundle.getMessage("Backup"));
  QPushButton* restoreButton; //=new JButton(Bundle.getMessage("Restore"));
  QPushButton* saveButton; //=new JButton(Bundle.getMessage("Save"));

  // radio buttons
  QRadioButton* scaleZ; //=new JRadioButton("Z"); // NOI18N
  QRadioButton* scaleN; //=new JRadioButton("N"); // NOI18N
  QRadioButton* scaleTT; //=new JRadioButton("TT"); // NOI18N
  QRadioButton* scaleHOn3; //=new JRadioButton("HOn3"); // NOI18N
  QRadioButton* scaleOO; //=new JRadioButton("OO"); // NOI18N
  QRadioButton* scaleHO; //=new JRadioButton("HO"); // NOI18N
  QRadioButton* scaleSn3; //=new JRadioButton("Sn3"); // NOI18N
  QRadioButton* scaleS; //=new JRadioButton("S"); // NOI18N
  QRadioButton* scaleOn3; //=new JRadioButton("On3"); // NOI18N
  QRadioButton* scaleO; //=new JRadioButton("O"); // NOI18N
  QRadioButton* scaleG; //=new JRadioButton("G"); // NOI18N

  QRadioButton* typeDesc; //=new JRadioButton(Bundle.getMessage("Descriptive"));
  QRadioButton* typeAAR; //=new JRadioButton(Bundle.getMessage("AAR"));

  QRadioButton* feetUnit; //=new JRadioButton(Bundle.getMessage("Feet"));
  QRadioButton* meterUnit; //=new JRadioButton(Bundle.getMessage("Meter"));

  // check boxes
  QCheckBox* eastCheckBox; //=new JCheckBox(Bundle.getMessage("eastwest"));
  QCheckBox* northCheckBox; //=new JCheckBox(Bundle.getMessage("northsouth"));
  QCheckBox* mainMenuCheckBox; //=new JCheckBox(Bundle.getMessage("MainMenu"));
  QCheckBox* closeOnSaveCheckBox; //=new JCheckBox(Bundle.getMessage("CloseOnSave"));
  QCheckBox* autoSaveCheckBox; //=new JCheckBox(Bundle.getMessage("AutoSave"));
  QCheckBox* autoBackupCheckBox; //=new JCheckBox(Bundle.getMessage("AutoBackup"));
  QCheckBox* iconCheckBox; //=new JCheckBox(Bundle.getMessage("trainIcon"));
  QCheckBox* appendCheckBox; //=new JCheckBox(Bundle.getMessage("trainIconAppend"));
// QCheckBox* rfidCheckBox; //=new JCheckBox(Bundle.getMessage("EnableRfid"));

  // text field
  // JTextField* ownerTextField = new JTextField(10);
  JTextField* panelTextField; //=new JTextField(30);
  JTextField* railroadNameTextField; //=new JTextField(35);
  JTextField* maxLengthTextField; //=new JTextField(5);
  JTextField* maxEngineSizeTextField; //=new JTextField(3);
  JTextField* hptTextField; //=new JTextField(3);
  JTextField* switchTimeTextField; //=new JTextField(3);
  JTextField* travelTimeTextField; //=new JTextField(3);
  JTextField* yearTextField; //=new JTextField(4);

  // combo boxes
  QComboBox* northComboBox; //=new JComboBox<>();
  QComboBox* southComboBox; //=new JComboBox<>();
  QComboBox* eastComboBox; //=new JComboBox<>();
  QComboBox* westComboBox; //=new JComboBox<>();
  QComboBox* localComboBox; //=new JComboBox<>();
  QComboBox* terminateComboBox; //=new JComboBox<>();

  // text area
  JTextArea* commentTextArea; //=new JTextArea(2, 8
  /*private*/ void loadIconComboBox(QComboBox* comboBox);
  /*private*/ void setCarTypes();
  /*private*/ void setLengthUnit();
  /*private*/ void save();
  /*private*/ void checkRoutes();
  /*private*/ QWidget* getTopLevelAncestor();


 };
}
#endif // OPERATIONSSETUPPANEL_H
