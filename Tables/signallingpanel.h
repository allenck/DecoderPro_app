#ifndef SIGNALLINGPANEL_H
#define SIGNALLINGPANEL_H

#include <QWidget>
#include "logger.h"
#include <QLabel>
#include "jcheckbox.h"
#include <QPushButton>
#include <QScrollArea>
#include <QRadioButton>
#include <QButtonGroup>
#include "abstracttablemodel.h"
#include <QItemDelegate>
#include "libtables_global.h"
#include "tabledelegates.h"
#include "jframe.h"
#include "jmripanel.h"
#include "namedbeancombobox.h"

class SignalMastLogic;
class SignalMast;
class NamedBeanHandleManager;
class JmriBeanComboBox;
class SignalMastLogic;
class SignalMastManager;
class BlockModel;
class AutoBlockModel;
class ManualBlockList;
class AutoBlockList;
class TurnoutModel;
class AutoTurnoutModel;
class ManualTurnoutList;
class SensorModel;
class AutoTurnoutList;
class SignalMastModel;
class AutoMastModel;
class ManualSignalMastList;
class AutoSignalMastList;
class ManualSensorList;
class Block;
class PropertyChangeEvent;
class LIBTABLESSHARED_EXPORT SignallingPanel : public JmriPanel
{
    Q_OBJECT
  public:


public:
    //explicit SignallingPanel(QWidget *parent = 0);
    /*public*/ SignallingPanel(JFrame *frame, QWidget* parent = 0);
    /*public*/ SignallingPanel(SignalMast* source, SignalMast* dest, JFrame* frame, QWidget* parent = 0);
    /*public*/ void dispose();

signals:

public slots:
    void on_destMastBox_currentSelectionChanged(int);
    void on_allButton_toggled(bool);
    void on_useLayoutEditor_toggled(bool);
    void on_includedButton_toggled(bool);
    void updatePressed(/*ActionEvent e*/);
    void applyPressed(/*ActionEvent e*/);
    void cancelPressed(/*ActionEvent e*/);

private:
    Logger* log;
    NamedBeanComboBox* sourceMastBox;
    NamedBeanComboBox* destMastBox;
    QLabel* fixedSourceMastLabel;// = new QLabel();
    QLabel* fixedDestMastLabel;// = new QLabel();
    QLabel* sourceMastLabel;// = new JLabel(tr("Source Mast"));
    QLabel* destMastLabel;// = new JLabel(tr("Dest Mast"));
    QPushButton* updateButton;// = new JButton(tr("Update Logic"));
    JCheckBox* useLayoutEditor;// = new JCheckBox(tr("UseLayoutEditorPaths"));
    JCheckBox* useLayoutEditorTurnout;// = new JCheckBox(tr("UseTurnoutDetails"));
    JCheckBox* useLayoutEditorBlock;// = new JCheckBox(tr("UseBlockDetails"));
    JCheckBox* allowAutoMastGeneration;// = new JCheckBox(tr("AllowAutomaticSignalMast"));
    JCheckBox* lockTurnouts;// = new JCheckBox(tr("LockTurnouts"));
//    /*private*/ static /*final*/ JButton* sizer;// = new JButton("Sizer");  // NOI18N


    SignalMast* sourceMast;
    SignalMast* destMast;
    /*private*/ SignalMastLogic* sml = nullptr;

    NamedBeanHandleManager* nbhm;// = InstanceManager.getDefault("NamedBeanHandleManager");

    JFrame* jFrame;
    void init();
    void common(SignalMast* source, SignalMast* dest, JFrame* frame);
    /*private*/ bool destOK = true; // false indicates destMast and sourceMast are identical
    int blockModeFromBox(JComboBox/*<String>*/* box);
    void setBlockModeBox(int mode, JComboBox/*<String>*/* box);

    //QScrollArea* _manualBlockScrollPane;
    JTable* manualBlockTable=nullptr;
    //QScrollArea* _autoBlockScrollPane;
    JTable* manualSensorTable = nullptr;
    //QScrollArea* _manualTurnoutScrollPane;
    JTable* manualTurnoutTable = nullptr;
    //QScrollArea* _manualSignalMastScrollPane;
    JTable* manualSignalMastTable= nullptr;
    //QScrollArea* _autoSignalMastScrollPane;
    JTable* autoSignalMastTable = nullptr;
    //QScrollArea* _autoTurnoutScrollPane;
    JTable* autoTurnoutTable = nullptr;
    //QScrollArea* _manualSensorScrollPane;
    JTable* autoBlockTable = nullptr;

    QWidget* p2xc;// = NULL;
    QWidget* p2xt;// = NULL;
    QWidget* p2xs;// = NULL;
    QWidget* p2xm;// = NULL;

    BlockModel* _blockModel;
    AutoBlockModel* _autoBlockModel;
    QList<ManualBlockList*> _manualBlockList;
    QList<AutoBlockList*>* _automaticBlockList;// = new ArrayList<AutoBlockList>();

    TurnoutModel* _turnoutModel;
    AutoTurnoutModel* _autoTurnoutModel;
    QList<ManualTurnoutList*> _manualTurnoutList;
    QList<AutoTurnoutList*>* _automaticTurnoutList;// = new ArrayList<AutoTurnoutList>();

    SensorModel* _sensorModel;
    QList<ManualSensorList*> _manualSensorList;

    SignalMastModel* _signalMastModel;
    AutoMastModel* _autoSignalMastModel;
    QList<ManualSignalMastList*> _manualSignalMastList;
    QList<AutoSignalMastList*>* _automaticSignalMastList;// = new ArrayList<AutoSignalMastList>();
    QWidget* p2xb;// = new QWidget();
    QButtonGroup* selGroup;// = NULL;
    QRadioButton* allButton;// = NULL;
    QRadioButton* includedButton;// = NULL;

    /*private*/ bool showAll;// = true;   // false indicates show only included items
    /*private*/ static QStringList blockInputModes;// =  QStringList() << tr("UnOccupied")<< tr("Occupied");
    /*private*/ static QList<int> blockInputModeValues;// =  Qlist<int>() << Block::UNOCCUPIED <<  Block<<OCCUPIED;
    QWidget* p2xa;// = new QWidget();
    QWidget* buildBlocksPanel();
    QWidget* p2xsm;// = new QWidget();
    QWidget* buildTurnoutPanel();
    QWidget* buildSensorPanel();
    void initializeIncludedList();
    QWidget* buildSignalMastPanel();

    /*private*/ static QString SET_TO_ACTIVE;// = tr("SensorActive");
    /*private*/ static QString SET_TO_INACTIVE;// = tr("SensorInactive");
    /*private*/ static QString SET_TO_CLOSED;// = jmri.InstanceManager.turnoutManagerInstance().getClosedText();
    /*private*/ static QString SET_TO_THROWN;// = jmri.InstanceManager.turnoutManagerInstance().getThrownText();

    /*private*/ static QString SET_TO_UNOCCUPIED;// = tr("UnOccupied");
    /*private*/ static QString SET_TO_OCCUPIED;// = tr("Occupied");
    /*private*/ static QString SET_TO_ANY;// = tr("AnyState");

    /*private*/ static int ROW_HEIGHT;
    //    private ArrayList <AutoBlockList> _autoBlockList;
    /*private*/ QList <ManualBlockList*> _includedManualBlockList;
    /*private*/ QList <ManualTurnoutList*> _includedManualTurnoutList;
    /*private*/ QList <ManualSensorList*> _includedManualSensorList;
    /*private*/ QList <ManualSignalMastList*> _includedManualSignalMastList;

    void editDetails();
    void setAssociatedSection(SignalMast* destMast);

    friend class ManualBlockList;
    friend class BlockModel;
    friend class AutoTableModel;
    friend class AutoBlockModel;
friend class SignalMastElement;
friend class ManualTurnoutList;
friend class TurnoutModel;
friend class AutoTurnoutModel;
friend class ManualSensorList;
friend class SensorModel;
friend class AutoMastModel;
friend class SignalMastModel;
friend class SignalMastComboBoxDelegate;
friend class SPTableModel;
};

/*private*/ /*abstract*/ class SignalMastElement : public QObject
{
 Q_OBJECT
public:
    SignalMastElement(SignallingPanel* signallingPanel);
    SignalMastElement(QString sysName, QString userName, SignallingPanel* signallingPanel);
    QString getSysName() ;
    QString getUserName();
    QString getDisplayName();
    bool isIncluded();
    void setIncluded(bool include);
    virtual  /*abstract*/ QString getSetToState() = 0;
    virtual /*abstract*/ void setSetToState(QString state) = 0;
    int getState() ;
    void setState(int state);
public:
    QString _sysName;
    QString _userName;
    bool _included;
    int _setToState;
private:
    SignallingPanel* signallingPanel;
    friend class ManualBlockList;
    friend class ManualTurnoutList;
    friend class ManualSensorList;
};

/*private*/ class ManualBlockList : public SignalMastElement
{
 Q_OBJECT
public:
    ManualBlockList(Block* block, SignallingPanel* signallingPanel);
    QString getSysName() ;
     QString getUserName() ;
     bool getPermissiveWorking();
     QString getBlockSpeed();
     virtual QString getSetToState();
     virtual void setSetToState(QString state);
private:
    Block* block;

};

/*private*/ class AutoBlockList : public ManualBlockList
{
    Q_OBJECT
 public:
    AutoBlockList(Block* block, SignallingPanel* self);
    void setSetToState(QString state);
};

/*abstract*/ class SPTableModel : public  AbstractTableModel,  public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
    SPTableModel(SignallingPanel* signallingPanel);
    //QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    int columnCount(const QModelIndex &parent) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ void dispose();
    QObject* self() override {return (QObject*)this;}
    enum COLUMNS
    {
        SNAME_COLUMN = 0,
        UNAME_COLUMN = 1,
        INCLUDE_COLUMN = 2,
        STATE_COLUMN = 3,
        SPEED_COLUMN = 4,
        PERMISSIVE_COLUMN = 5

    };
    void fireTableDataChanged()override;
public slots:
    /*public*/ virtual void propertyChange(PropertyChangeEvent* e) override;

private:
    SignallingPanel* signallingPanel;
    friend class BlockModel;
    friend class TurnoutModel;
    friend class SensorModel;
    friend class SignalMastModel;
};

class BlockModel : public  SPTableModel
{
    Q_OBJECT
public:
     BlockModel(SignallingPanel* signallingPanel);
     int rowCount(const QModelIndex &parent) const override;
     int columnCount(const QModelIndex &parent) const override;
     QVariant data(const QModelIndex &index, int role) const override;
     bool setData(const QModelIndex &index, const QVariant &value, int role) override;
     /*public*/ QString getColumnClass(int c) const override;
     /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
//     virtual Qt::ItemFlags flags(const QModelIndex &index) const;
public slots:
     void propertyChange(PropertyChangeEvent *e)override;
 private:
};

/*abstract*/ class AutoTableModel : public AbstractTableModel // implements PropertyChangeListener
{
    Q_OBJECT
 public:
    AutoTableModel(SignallingPanel* signallingPanel);
    /*public*/ void smlValid();
//        /*public*/ Class<?> getColumnClass(int c);
    /*public*/ void dispose();
    virtual /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    enum COLUMNS
    {
    SNAME_COLUMN = 0,
    UNAME_COLUMN = 1,
    STATE_COLUMN = 2
    };
    void fireTableDataChanged();
public slots:
    void propertyChange(PropertyChangeEvent*);

 private:
    SignallingPanel* signallingPanel;
    friend class AutoBlockModel;
    friend class AutoTurnoutModel;
    friend class AutoMastModel;
};

class AutoBlockModel : public AutoTableModel
{
    Q_OBJECT
 public:
    AutoBlockModel(SignallingPanel* self);
    enum COLUMNS
    {
     SPEED_COLUMN = 3,
     PERMISSIVE_COLUMN = 4
    };
    /*public*/ int columnCount(const QModelIndex &parent) const;
    virtual /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ QString getColumnClass(int c);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) ;
    void fireTableDataChanged();
private:
};

class TurnoutModel : public SPTableModel
{
 Q_OBJECT
public:
    TurnoutModel(SignallingPanel* self);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
public slots:
     void propertyChange(PropertyChangeEvent *e);
};
/*private*/ class ManualTurnoutList : public SignalMastElement
{
 Q_OBJECT
public:
    ManualTurnoutList (QString sysName, QString userName, SignallingPanel* self);
    QString getSetToState() ;
    void setSetToState(QString state);

};

/*private*/ class AutoTurnoutList : public ManualTurnoutList
{
 Q_OBJECT
 public:
    AutoTurnoutList(QString sysName, QString userName, SignallingPanel* self);
    void setSetToState(QString state);

};

/*private*/ class ManualSensorList : public SignalMastElement
{
 Q_OBJECT
 public:
    ManualSensorList (QString sysName, QString userName, SignallingPanel* self);
    QString getSetToState();
    void setSetToState(QString state);

};

/*private*/ class ManualSignalMastList : public SignalMastElement
{
    Q_OBJECT
public:
    ManualSignalMastList (SignalMast* s, SignallingPanel* self);
    SignalMast* getMast();
    QString getSysName();
    QString getUserName();
    QString getSetToState();
    void setSetToState(QString state);

private:
    QString _setToAspect;// = "";

    SignalMast* mast;
    friend class AutoSignalMastList;
};

/*private*/ class AutoSignalMastList : public ManualSignalMastList
{
    Q_OBJECT
public:
    AutoSignalMastList(SignalMast* s, SignallingPanel* self);
    void setSetToState(QString state);
    void setState(QString state);
};

class AutoTurnoutModel : public AutoTableModel
{
 Q_OBJECT
public:
    AutoTurnoutModel(SignallingPanel* self);
    int rowCount(const QModelIndex &parent) const;
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    QVariant data(const QModelIndex &index, int role) const;
};

class AutoMastModel : public AutoTableModel
{
  Q_OBJECT
 public:
    AutoMastModel(SignallingPanel* self);
    int rowCount(const QModelIndex &parent) const;
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    QVariant data(const QModelIndex &index, int role) const;

};

class SensorModel : public SPTableModel
{
    Q_OBJECT
   public:
    SensorModel(SignallingPanel* self);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
public slots:
     void propertyChange(PropertyChangeEvent *e);
private:
    Logger* log;
};

class SignalMastModel : public SPTableModel
{
    Q_OBJECT
   public:
    SignalMastModel(SignallingPanel* self);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QString getValue(QString name);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void fireTableRowsUpdated(int, int);
public slots:
     void propertyChange(PropertyChangeEvent *e);

};
#if 0
class SPComboBoxDelegate : public QItemDelegate
{
Q_OBJECT
public:
  SPComboBoxDelegate(QStringList items, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  QStringList items;

};
#endif
class SignalMastComboBoxDelegate : public JComboBoxEditor
{
Q_OBJECT
public:
  SignalMastComboBoxDelegate(SignallingPanel* panel, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//  void setEditorData(QWidget *editor, const QModelIndex &index) const;
//  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  QStringList* items;
  SignallingPanel* panel;
};
#endif // SIGNALLINGPANEL_H
