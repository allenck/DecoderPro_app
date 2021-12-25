#ifndef TRANSITTABLEACTION_H
#define TRANSITTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "windowlistener.h"

class Block;
class QRadioButton;
class SpecialActionTableModel;
class QComboBox;
class UserPreferencesManager;
class TransitSectionAction;
class Section;
class SectionTableModel;
class Transit;
class QLabel;
class JTextField;
class SectionManager;
class TransitManager;
class TransitTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE TransitTableAction(QObject* parent = 0);
    ~TransitTableAction() {}
    Q_INVOKABLE /*public*/ TransitTableAction(QString actionName, QObject* parent);
    TransitTableAction(const TransitTableAction* that) : AbstractTableAction(that->text(), that->parent()) {}
    Q_INVOKABLE /*public*/ QString getClassDescription();

private:
   void common();
   void editPressed(QString sName);
   void duplicatePressed(QString sName);

   // instance variables
   /*private*/ bool editMode = false;
   /*private*/ bool duplicateMode = false;
   /*private*/ TransitManager* transitManager = nullptr;
   /*private*/ SectionManager* sectionManager;// = InstanceManager::sectionManagerInstance();
   /*private*/ Transit* curTransit = nullptr;
   /*private*/ SectionTableModel* sectionTableModel = nullptr;
   /*private*/ QList<Section*>* sectionList;// = new QList<>();
   /*private*/ QVector<int>* direction;// = new int[150];
   /*private*/ QVector<int>* sequence;// = new int[150];
   /*private*/ QVector<QList<TransitSectionAction*>*> action;// = new QList[150];
   /*private*/ QVector<bool>* alternate;// = new boolean[150];
   /*private*/ QVector<bool> safe = QVector<bool>(150);
   /*private*/ QVector<QString> sensorList;
   /*private*/ /*final*/ QVector<QString> sensorStopAllocation = QVector<QString>(150);
   /*private*/ int maxSections;// = 150;  // must be equal to the dimension of the above arrays
   /*private*/ QList<Section*>* primarySectionBoxList;// = new QList<>();
   /*private*/ QVector<int>* priSectionDirection;// = new int[150];
   /*private*/ QList<Section*>* alternateSectionBoxList;// = new QList<>();
   /*private*/ QVector<int>* altSectionDirection;// = new int[150];
   /*private*/ QList<Section*>* insertAtBeginningBoxList;// = new QList<>();
   /*private*/ QVector<int>* insertAtBeginningDirection;// = new int[150];
   /*private*/ Section* curSection;// = NULL;
   /*private*/ int curSectionDirection;// = 0;
   /*private*/ Section* prevSection;// = NULL;
   /*private*/ int prevSectionDirection;// = 0;
   /*private*/ int curSequenceNum;// = 0;

   // add/create variables
   JmriJFrame* addFrame;// = NULL;
   JTextField* sysName;// = new JTextField(5);
   QLabel* sysNameFixed;// = new JLabel("");
   JTextField* userName;// = new JTextField(17);
   QLabel* sysNameLabel;// = new JLabel(tr("LabelSystemName"));
   QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
   QPushButton* create = nullptr;
   QPushButton* update = nullptr;
   QPushButton* deleteSections;// = NULL;
   QComboBox* primarySectionBox;// = new JComboBox<>();
   QPushButton* addNextSection;// = NULL;
   QPushButton* removeLastSection;// = NULL;
   QPushButton* removeFirstSection;// = NULL;
   QPushButton* insertAtBeginning;// = NULL;
   QComboBox* insertAtBeginningBox;// = new JComboBox<>();
   QLabel* seqNumLabel;// = new JLabel(tr("LabelSeqNum"));
   JTextField* seqNum;// = new JTextField(5);
   QPushButton* replacePrimaryForSequence;// = NULL;
   QPushButton* deleteAlternateForSequence = NULL;
   QPushButton* addAlternateForSequence;// = NULL;
   QComboBox* alternateSectionBox;// = new JComboBox<>();
   QPushButton* addAlternateSection;// = NULL;
   QCheckBox* _autoSystemName;// = new JCheckBox(tr("LabelAutoSysName"));
   UserPreferencesManager* pref;
   QString systemNameAuto;// = this.getClass().getName() + ".AutoSystemName";

   // variables for view actions window
   /*private*/ int activeRow;// = 0;
   /*private*/ SpecialActionTableModel* actionTableModel;// = NULL;
   /*private*/ JmriJFrame* actionTableFrame;// = NULL;
   /*private*/ QLabel* fixedSectionLabel;// = new JLabel("X");

   // variables for add/edit action window
   /*private*/ bool editActionMode;// = false;
   /*private*/ JmriJFrame* addEditActionFrame;// = NULL;
   /*private*/ TransitSectionAction* curTSA;// = NULL;
   /*private*/ QComboBox* whenBox;// = new QComboBox();
   /*private*/ JTextField* whenDataField;// = new JTextField(7);
   /*private*/ JTextField* whenStringField;// = new JTextField(17);
   /*private*/ QComboBox* whatBox;// = new QComboBox();
   /*private*/ JTextField* whatData1Field;// = new JTextField(7);
   /*private*/ JTextField* whatData2Field;// = new JTextField(7);
   /*private*/ JTextField* whatStringField;// = new JTextField(17);
   /*private*/ QPushButton* updateActionButton;// = NULL;
   /*private*/ QPushButton* createActionButton;// = NULL;
   /*private*/ QPushButton* cancelAddEditActionButton;// = NULL;
   /*private*/ QComboBox* blockBox;// = new QComboBox();
   /*private*/ QList<Block*> blockList;// = new ArrayList<>();
   /*private*/ QRadioButton* onButton;// = new JRadioButton(tr("On"));
   /*private*/ QRadioButton* offButton;// = new JRadioButton(tr("Off"));
   /*private*/ QLabel* doneSensorLabel;// = new JLabel(tr("DoneSensorLabel"));
   /*private*/ JTextField* doneSensorField;// = new JTextField(17);

   // temporary action variables
   /*private*/ int tWhen;// = 0;
   /*private*/ int tWhenData;// = 0;
   /*private*/ QString tWhenString;// = "";
   /*private*/ int tWhat;// = 0;
   /*private*/ int tWhatData1;// = 0;
   /*private*/ int tWhatData2;// = 0;
   /*private*/ QString tWhatString;// = "";


   void addEditPressed();
   /*private*/ void initializeEditInformation();
   /*private*/ void initializeSectionCombos();
   /*private*/ bool forwardConnected(Section* s1, Section* s2, int restrictedDirection);
   /*private*/ bool reverseConnected(Section* s1, Section* s2, int restrictedDirection);
   /*private*/ bool notIncludedWithSeq(Section* s, int seq);
   /*private*/ void addEditActionsPressed(int r);
   /*private*/ QString getSectionNameByRow(int r);
   bool inSectionList(Section* s, QList<Section*> sList);
   int getSeqNum();
   Logger* log;
   /*private*/ QString getWhenText(int r);
   /*private*/ QString getWhatText(int r);
   /*private*/ void editAction(int r);
   /*private*/ void deleteAction(int r);
   /*private*/ void addEditActionWindow();
   /*private*/ bool checkTransitInformation();
   /*private*/ bool setTransitInformation();
   /*private*/ void setWhen(int code);
   /*private*/ void setWhat(int code);
   /*private*/ void initializeWhenBox();
   /*private*/ QString getWhenMenuText(int i);
   /*private*/ void initializeWhatBox();
   /*private*/ QString getWhatMenuText(int i);
   /*private*/ void initializeBlockBox();
   /*private*/ void setBlockBox();
   /*private*/ bool readWhatData2(QString err, int min, int max);
   /*private*/ bool validateWhenData();
   /*private*/ bool validateSensor(QString sName, bool when);
   /*private*/ bool validateWhatData();
   /*private*/ bool readWhatData1(QString err, int min, int max);


private slots:
   /*private*/ void deleteAllSections(ActionEvent* =0);
   void addNextSectionPressed(ActionEvent* e = 0);
   void removeLastSectionPressed(ActionEvent* e = 0);
   void insertAtBeginningPressed(ActionEvent* e = 0);
   void removeFirstSectionPressed(ActionEvent* /*e*/= 0);
   void replacePrimaryForSeqPressed(ActionEvent* /*e*/ =0);
   void deleteAlternateForSeqPressed(ActionEvent* /*e*/= 0);
   void addAlternateForSeqPressed(ActionEvent* /*e*/= 0);
   void addAlternateSectionPressed(ActionEvent* /*e*/ = 0);
   void createPressed(ActionEvent* /*e*/ = 0);
   void cancelPressed(ActionEvent* /*e*/ = 0);
   void updatePressed(ActionEvent* /*e*/ = 0);
   /*private*/ void doneWithActionsPressed(ActionEvent* /*e*/= 0);
   /*private*/ void newActionPressed(ActionEvent* /*e*/= 0);
   /*private*/ void createActionPressed(ActionEvent* /*e*/ = 0);
   /*private*/ void updateActionPressed(ActionEvent* /*e*/ = 0);
   /*private*/ void cancelAddEditActionPressed(ActionEvent* /*e*/ = 0);
   /*private*/ void autoSystemName();


protected:
   /*protected*/ void setTitle()override;
   /*protected*/ QString helpTarget()override;
   /*protected*/ void createModel()override;
   /*protected*/ QString getClassName()override;

protected slots:
   /*protected*/ void addPressed(JActionEvent* e=0)override;
   void On_whenBox_currentIndexChanged();
   void On_whatBox_currentIndexChanged();

friend class SectionTableModel;
friend class TransitTableDataModel;
friend class SpecialActionTableModel;
friend class ATWindowListener;
friend class AEFWindowListener;
};
Q_DECLARE_METATYPE(TransitTableAction)

class TransitTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
    TransitTableAction* act;
public:
    enum COLUMNS
    {
     EDITCOL = NUMCOLUMN,
     DUPLICATECOL = EDITCOL + 1
    };
    TransitTableDataModel(TransitTableAction* act);

    /*public*/ QString getValue(QString name) const;
    /*public*/ AbstractManager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name);
    /*public*/ void clickOn(NamedBean* t) ;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ void configValueColumn(JTable* table);
    /*public*/ QPushButton* configureButton() ;

private:
    Logger* log;

protected:
    /*protected*/ QString getMasterClassName();
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) ;
    /*protected*/ QString getBeanType() ;
};


/**
 * Table model for Sections in Create/Edit Transit window
 */
/*public*/ class SectionTableModel : public AbstractTableModel, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
 TransitTableAction* act;
public:
 enum COLUMNS
 {
  SEQUENCE_COLUMN = 0,
  SECTIONNAME_COLUMN = 1,
  ACTION_COLUMN = 2,
  SEC_DIRECTION_COLUMN = 3,
  ALTERNATE_COLUMN = 4
 };

    /*public*/ SectionTableModel(TransitTableAction* act);
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 QObject* self() override {return (QObject*)this;}

 public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

};

/**
 * Table model for Actions in Special Actions window
 */
/*public*/ class SpecialActionTableModel : public  AbstractTableModel, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
    TransitTableAction* act;
public:
    SpecialActionTableModel(TransitTableAction* act);
    enum COLUMNS
    {
     WHEN_COLUMN = 0,
     WHAT_COLUMN = 1,
     EDIT_COLUMN = 2,
     REMOVE_COLUMN = 3
    };

    /*public*/ SpecialActionTableModel();
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QObject* self() override {return (QObject*)this;}

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

};

class ATWindowListener : public WindowListener
{
  Q_OBJECT
    TransitTableAction* act;
public:
    ATWindowListener(TransitTableAction* act);
    /*public*/ void windowClosing(QCloseEvent* );

};

class AEFWindowListener : public WindowListener
{
 Q_OBJECT
  TransitTableAction* act;
public:
  AEFWindowListener(TransitTableAction* act);
  void windowClosing(QCloseEvent *e);
};

#endif // TRANSITTABLEACTION_H
