#ifndef BLOCKTABLEACTION_H
#define BLOCKTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "libtables_global.h"

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
 /*public*/ void addToFrame(BeanTableFrame* f);
/*public*/ void setMenuBar(BeanTableFrame* f);
 /*public*/ void dispose();
 Q_INVOKABLE /*public*/ QString getClassDescription();
 Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
signals:

public slots:
 void on_deletePaths();
 void inchBoxChanged();
 void centimeterBoxChanged();
 void on_defaultSpeeds();
 void okPressed(ActionEvent* e = 0);
 void cancelPressed(ActionEvent* e = 0);


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
 JmriJFrame* addFrame;// = NULL;
 JTextField* sysName;// = new JTextField(5);
 JTextField* userName;// = new JTextField(5);
 QLabel* sysNameLabel;// = new JLabel(tr("LabelSystemName"));
 QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));

 QComboBox* cur;// = new QComboBox*(curveOptions);
 JTextField* lengthField;// = new JTextField(7);
 JTextField* blockSpeed;// = new JTextField(7);
 QCheckBox* checkPerm;// = new QCheckBox(tr("BlockPermColName"));

 JTextField* numberToAdd;// = new JTextField(10);
 QCheckBox* range;// = new JCheckBox(tr("LabelNumberToAdd"));
 QCheckBox* _autoSystemName ;//= new JCheckBox(tr("LabelAutoSysName"));
 UserPreferencesManager* pref;

 QComboBox* speeds;// = new QComboBox*();
 QWidget* additionalAddOption();
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
 /*protected*/ void addPressed(ActionEvent* /*e*/);
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

 /*public*/ QString getValue(QString name) const;
 /*public*/ Manager* getManager();
 /*public*/ NamedBean* getBySystemName(QString name) const;
 /*public*/ NamedBean* getByUserName(QString name);
 /*public*/ void clickOn(NamedBean* t);
 //Permissive and speed columns are temp disabled
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ void configValueColumn(JTable* table);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ void configureTable(JTable* table);
 /*public*/ QPushButton* configureButton();
 /*synchronized*/ /*public*/ void dispose();
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
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
 /*protected*/ QString getBeanType();
  protected slots:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);

};
class BTActionListener : public ActionListener
{
 Q_OBJECT
 BlockTableAction* blockTableAction;
public:
 BTActionListener(BlockTableAction* blockTableAction);
public slots:
 void actionPerformed(ActionEvent* = 0);
};
class BTCancelListener : public ActionListener
{
 Q_OBJECT
 BlockTableAction* blockTableAction;
public:
 BTCancelListener(BlockTableAction* blockTableAction);
public slots:
 void actionPerformed(ActionEvent* = 0);
};

#endif // BLOCKTABLEACTION_H
