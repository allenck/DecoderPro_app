#ifndef BLOCKTABLEACTION_H
#define BLOCKTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "libtables_global.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "jtextfield.h"
#include "windowadapter.h"

class BufferedImage;
class Block;
class UserPreferencesManager;
class QComboBox;
class QLabel;
class JTextField;
class QCheckBox;
class DecimalFormat;
class LIBTABLESSHARED_EXPORT BlockTableAction : public AbstractTableAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit BlockTableAction(QObject *parent = NULL);
 ~BlockTableAction() {}
 BlockTableAction(const BlockTableAction& other) : AbstractTableAction(other.text(), other.parent()) {}
 Q_INVOKABLE/*public*/ BlockTableAction(QString actionName, QObject *parent);
 /*public*/ void addToFrame(BeanTableFrame* f) override;
/*public*/ void setMenuBar(BeanTableFrame* f) override;
 /*public*/ void dispose();
 Q_INVOKABLE /*public*/ QString getClassDescription() override;
 Q_INVOKABLE /*public*/ void setMessagePreferencesDetails() override;
signals:

public slots:
 void on_deletePaths();
 void inchBoxChanged();
 void centimeterBoxChanged();
 void on_defaultSpeeds();
 void okPressed(JActionEvent* e = 0);
 void cancelPressed(JActionEvent *e = 0);


private:
 void common();
 /*private*/ QString noneText;// = tr("BlockNone");
 /*private*/ QString gradualText;// = tr("BlockGradual");
 /*private*/ QString tightText;// = tr("BlockTight");
 /*private*/ QString severeText;// = tr("BlockSevere");
 /*private*/ QStringList curveOptions;// = {noneText, gradualText, tightText, severeText};
 /*private*/ QVector<QString> speedList;// = new java.util.Vector<String>();
 /*private*/ QStringList sensorList;
 /*private*/ DecimalFormat* twoDigit;// = new DecimalFormat("0.00");
 QString defaultBlockSpeedText;
 QCheckBox* inchBox;// = new JCheckBox(tr("LengthInches"));
 QCheckBox* centimeterBox;// = new JCheckBox(tr("LengthCentimeters"));
 /*private*/ void updateSensorList();
 /*private*/ void updateSpeedList();
 JmriJFrame* addFrame = NULL;
 JTextField* sysName = new JTextField(20);
 JTextField* userName = new JTextField(20);
 JLabel* sysNameLabel = new JLabel(tr("SystemName"));
 JLabel* userNameLabel = new JLabel(tr("UserName"));


 QComboBox* cur;// = new QComboBox*(curveOptions);
 JTextField* lengthField = new JTextField(7);
 JTextField* blockSpeed = new JTextField(7);
 QCheckBox* checkPerm = new QCheckBox(tr("Permissive"));

 SpinnerNumberModel* numberToAddSpinnerNumberModel = new SpinnerNumberModel(1, 1, 100, 1); // maximum 100 items
 JSpinner* numberToAddSpinner = new JSpinner(numberToAddSpinnerNumberModel);
 JCheckBox* addRangeCheckBox = new JCheckBox(tr("Add a sequential range"));
 JCheckBox* _autoSystemNameCheckBox = new JCheckBox(tr("Automatically generate System Name"));
 JLabel* statusBar = new JLabel(tr("Enter a System Name and (optional) User Name."), JLabel::LEADING);
 UserPreferencesManager* pref;

 QComboBox* speeds = new QComboBox();
 QString systemNameAuto;// = this.getClass().getName() + ".AutoSystemName";
 bool validateNumericalInput(QString text);
 Logger* log;
 void handleCreateException(QString sysName);
 void deletePaths(JmriJFrame* f);
 JmriJFrame* finalF;

 // for icon state col
 bool _graphicState = false; // updated from prefs

protected:
 /*protected*/ void createModel();
 /*protected*/ void setTitle();
 /*protected*/ void setDefaultSpeeds(JFrame* _who);
 /*protected*/ QString helpTarget();

protected slots:
 /*protected*/ void addPressed(JActionEvent * /*e*/);
 /*protected*/ QString getClassName();

friend class BlockTableDataModel;
};
Q_DECLARE_METATYPE(BlockTableAction)

class BlockTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
 BlockTableAction* blockTableAction;
public:
 //BlockTableDataModel(BlockTableAction*);
 BlockTableDataModel(QCheckBox* inchBox, BlockTableAction* blockTableAction);
 /**
  *
  */
 enum COLUMNS
 {
  EDITCOL = NUMCOLUMN,
  DIRECTIONCOL = EDITCOL + 1,
  LENGTHCOL = DIRECTIONCOL + 1,
  CURVECOL = LENGTHCOL + 1,
  STATECOL = CURVECOL + 1,
  SENSORCOL = STATECOL + 1,
  REPORTERCOL = SENSORCOL + 1,
  CURRENTREPCOL = REPORTERCOL + 1,
  PERMISCOL = CURRENTREPCOL + 1,
  SPEEDCOL = PERMISCOL + 1\
 };

 /*public*/ QString getValue(QString name) const override;
 /*public*/ Manager* getManager() override;
 /*public*/ NamedBean* getBySystemName(QString name) const override;
 /*public*/ NamedBean* getByUserName(QString name)  override;
 /*public*/ void clickOn(NamedBean* t) override;
 //Permissive and speed columns are temp disabled
 /*public*/ int columnCount(const QModelIndex &parent) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 /*public*/ int getPreferredWidth(int col) override;
 /*public*/ void configValueColumn(JTable* table) override;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const  override;
 /*public*/ void configureTable(JTable* table) override;
 /*public*/ QPushButton* configureButton() override;
 /*synchronized*/ /*public*/ void dispose();
 /*public*/ QString getColumnClass(int col);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
 Logger* log;
 void editButton(Block* b);
 QCheckBox* inchBox;
 /*private*/ DecimalFormat* twoDigit;// = new DecimalFormat("0.00");
 void common();
 QStringList speedList;
 QMap<int, QString> curveOptions;

  protected:
  /*protected*/ QString getMasterClassName() ;
 /*protected*/ QString rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
 /*protected*/ char beanTypeChar;// = 'S'; // for Sensor
 /*protected*/ QString onIconPath;// = rootPath + beanTypeChar + "-on-s.png";
 /*protected*/ QString offIconPath;// = rootPath + beanTypeChar + "-off-s.png";
 /*protected*/ BufferedImage* onImage;
 /*protected*/ BufferedImage* offImage;
 /*protected*/ QPixmap onIcon;
 /*protected*/ QPixmap offIcon;
 /*protected*/ int iconHeight = -1;
 /*protected*/ void loadIcons();

 /*protected*/ QString getBeanType() override;
 /*protected*/ void configStateColumn(JTable* table);

  protected slots:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
};

class BTActionListener : public ActionListener
{
 Q_OBJECT
 BlockTableAction* blockTableAction;
public:
 BTActionListener(BlockTableAction* blockTableAction);
public slots:
 void actionPerformed(JActionEvent* = 0) override;
};
class BTCancelListener : public ActionListener
{
 Q_OBJECT
 BlockTableAction* blockTableAction;
public:
 BTCancelListener(BlockTableAction* blockTableAction);
public slots:
 void actionPerformed(JActionEvent* = 0) override;
};

class ABWindowListener : public WindowAdapter
{
  Q_OBJECT
  BlockTableAction* blockTableAction;
 public:
  ABWindowListener(BlockTableAction* blockTableAction) {this->blockTableAction = blockTableAction;}
  void windowClosed(QCloseEvent *e)
  {
   blockTableAction->cancelPressed();
  }
  void windowClosing(QCloseEvent*){}
};
#endif // BLOCKTABLEACTION_H
