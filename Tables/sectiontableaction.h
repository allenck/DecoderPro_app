#ifndef SECTIONTABLEACTION_H
#define SECTIONTABLEACTION_H

#include "abstracttableaction.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "abstracttablemodel.h"
#include "actionlistener.h"
#include "libtables_global.h"

class QMenu;
class JDialog;
//class ActionEvent;
class BeanTableFrame;
class QButtonGroup;
class QRadioButton;
class QComboBox;
class UserPreferencesManager;
class QLabel;
class JTextField;
class JmriJFrame;
class Sensor;
class EntryPoint;
class LayoutEditor;
class Section;
class BlockManager;
class EntryPointTableModel;
class BlockTableModel;
class Block;
class SectionManager;
class LIBTABLESSHARED_EXPORT SectionTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    explicit SectionTableAction(QObject *parent = 0);
    Q_INVOKABLE /*public*/ SectionTableAction(QString actionName, QObject *parent = 0);
    ~SectionTableAction() {}
    SectionTableAction(const SectionTableAction& that) : AbstractTableAction(that.text(), that.parent()){}
    Q_INVOKABLE /*public*/ QString getClassDescription();
    /*public*/ void setMenuBar(BeanTableFrame* f);
    /*public*/ QMenu* createToolsMenu();

signals:

public slots:
private:
    void setEnabled(bool);
    bool enabled;
    //BeanTableDataModel* m;

    // instance variables
    QList<Block*> blockList;// = new ArrayList<Block>();
    BlockTableModel* blockTableModel = nullptr;
    EntryPointTableModel* entryPointTableModel = nullptr;
    SectionManager* sectionManager = nullptr;
    BlockManager* blockManager;// = jmri.InstanceManager.blockManagerInstance();
    bool editMode;// = false;
    Section* curSection = nullptr;
    bool addCreateActive;// = true;
    QList<LayoutEditor*>* lePanelList = nullptr;
    LayoutEditor* curLayoutEditor = nullptr;
    QList<Block*> blockBoxList;// = new ArrayList<Block>();
    Block* beginBlock = nullptr;
    Block* endBlock = nullptr;
    Sensor* fSensor = nullptr;
    Sensor* rSensor = nullptr;
    Sensor* fStopSensor = nullptr;
    Sensor* rStopSensor = nullptr;
    QList<EntryPoint*> entryPointList;// = new ArrayList<EntryPoint>();
    bool manualEntryPoints;// = true;

    // add/create variables
    JmriJFrame* addFrame = nullptr;
    JTextField* sysName;// = new JTextField(5);
    QLabel* sysNameFixed;// = new JLabel("");
    JTextField* userName;// = new JTextField(17);
    QLabel* sysNameLabel;// = new JLabel(rb.getString("LabelSystemName"));
    QLabel* userNameLabel;// = new JLabel(rb.getString("LabelUserName"));
    QCheckBox* _autoSystemName;// = new JCheckBox(rb.getString("LabelAutoSysName"));
    UserPreferencesManager* pref;
    QPushButton* create = nullptr;
    QPushButton* update = nullptr;
    QComboBox* blockBox;// = new JComboBox();
    QPushButton* addBlock = nullptr;
    QPushButton* deleteBlocks = nullptr;
    QComboBox* layoutEditorBox;// = new JComboBox();
    JTextField* forwardSensorField;// = new JTextField(12);
    JTextField* reverseSensorField;// = new JTextField(12);
    JTextField* forwardStopSensorField;// = new JTextField(12);
    JTextField* reverseStopSensorField;// = new JTextField(12);
    QRadioButton* manually;// = new JRadioButton(tr("SetManually"),true);
    QRadioButton* automatic;// = new JRadioButton(tr("UseConnectivity"),false);
    QButtonGroup* entryPointOptions = nullptr;
    QString systemNameAuto;// = this.getClass().getName()+".AutoSystemName";
    BeanTableFrame* f;
    /*private*/ EntryPoint* getEntryPointInList(QList<EntryPoint*> list, Block* b, Block* pb, QString pbDir);
    /*private*/ QList<EntryPoint*> getBlockEntryPointsList(Block* b);
    void editPressed(QString sName);
    void addEditPressed();
    /*private*/ void initializeEditInformation();
    /*private*/ void clearForCreate();
    /*private*/ bool checkSectionInformation();
    /*private*/ bool setSectionInformation();
    /*private*/ bool initializeLayoutEditorCombo(QComboBox* box);
    /*private*/ void initializeBlockCombo();
    /*private*/ bool inSection(Block* b);
    /*private*/ bool connected(Block* b1, Block* b2);
    /*private*/ void initializeEntryPoints();
    JmriJFrame* frame = nullptr;

    LayoutEditor* panel = nullptr;
    /*private*/ bool initializeLayoutEditor(bool required);
    Logger* log;

private slots:
    void OnManually_Clicked();
    void OnAutomatic_Clicked();

    /*private*/ void autoSystemName();
    void createPressed();
    void cancelPressed();
    void updatePressed();
    void deleteBlocksPressed();
    void addBlockPressed();
    /*private*/ void layoutEditorSelectionChanged();
    /*private*/ void deleteSectionPressed(QString sName);
    /*private*/ void OnValidate();
    /*private*/ void OnSetDirSensors();
    /*private*/ void OnRemoveDirSensors();


protected:
    /*protected*/ void createModel();
    /*protected*/ QString getClassName();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
protected slots:
    /*protected*/ void addPressed();

friend class SectionWidget;
friend class SectionTableDataModel;
friend class EntryPointTableModel;
friend class BlockTableModel;
};
Q_DECLARE_METATYPE(SectionTableAction)

class SectionTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    SectionTableAction* act;
    Logger* log;
public:
    enum COLUMNS
    {
     BEGINBLOCKCOL = NUMCOLUMN,
     ENDBLOCKCOL = BEGINBLOCKCOL+1,
     EDITCOL = ENDBLOCKCOL+1
    };
    SectionTableDataModel(SectionTableAction* act);

    /*public*/ QString getValue(QString name) const;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name);
    /*public*/ void clickOn(NamedBean* t);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ void configValueColumn(JTable* table);
    /*public*/ void configureTable(JTable *table);
protected:
    QString getBeanType();
    /*protected*/ void createModel();
    /*protected*/ QString getMasterClassName();

protected slots:
    bool matchPropertyName(PropertyChangeEvent* e) ;


};

/**
 * Table model for Blocks in Create/Edit Section window
 */
/*public*/ class BlockTableModel : public  AbstractTableModel //implements
//        java.beans.PropertyChangeListener
{
 Q_OBJECT
 SectionTableAction* act;
public:
 enum COLUMNS
 {
   SNAME_COLUMN = 0,
   UNAME_COLUMN = 1
 };

    /*public*/ BlockTableModel(SectionTableAction* act) ;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};
/**
 * Table model for Entry Points in Create/Edit Section window
 */
/*public*/ class EntryPointTableModel : public  AbstractTableModel
{
 Q_OBJECT
 SectionTableAction* act;
public:
    enum COLUMNS
    {
     BLOCK_COLUMN = 0,
     TO_BLOCK_COLUMN = 1,	// GT - 12-Oct-2009
     DIRECTION_COLUMN = 2	// GT - 12-Oct-2009
    };
    /*public*/ EntryPointTableModel(SectionTableAction* act);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QString getColumnClass(int c);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};
class YesButtonActionListener : public ActionListener
{
 Q_OBJECT
 Section* s;
 JDialog* dlg;
public:
 YesButtonActionListener(JDialog* dlg, Section* s);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
class NoButtonActionListener : public ActionListener
{
 Q_OBJECT
 JDialog* dlg;
public:
 NoButtonActionListener(JDialog* dlg);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
#endif // SECTIONTABLEACTION_H
