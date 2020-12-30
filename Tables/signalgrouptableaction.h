#ifndef SIGNALGROUPTABLEACTION_H
#define SIGNALGROUPTABLEACTION_H

#include <QObject>
#include "../LayoutEditor/beantabledatamodel.h"
#include "abstracttablemodel.h"
#include "abstracttableaction.h"
#include "libtables_global.h"

class QSignalMapper;
class QSignalMapper;
class WindowMaker;
class JActionEvent;
class QButtonGroup;
class QRadioButton;
class QLabel;
class JmriBeanComboBox;
class ATSignalMastAppearanceModel;
class QScrollArea;
class SignalGroupSignalHeadModel;
class JTextField;
class JmriJFrame;
class QComboBox;
class SGBeanTableDataModel;
class SignalGroup;
class SignalHead;
class PropertyChangeEvent;
class LIBTABLESSHARED_EXPORT SignalGroupTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SignalGroupTableAction(QObject *parent = 0);
    Q_INVOKABLE /*public*/ SignalGroupTableAction(QString s, QObject *parent = 0);
    ~SignalGroupTableAction() {}
    SignalGroupTableAction(const SignalGroupTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    Q_INVOKABLE /*public*/ QString getClassDescription();
    int signalStateFromBox(QComboBox* box);
    void setSignalStateBox(int mode, QComboBox* box);
    SGBeanTableDataModel* model();
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void on_allButton_clicked(ActionEvent* e = 0);
    void editPressed(ActionEvent* e = 0);
    void updatePressed(ActionEvent* e, bool newSignalGroup, bool close);
    /*public*/ void on_includedButton_clicked(ActionEvent* e = 0);
    void deletePressed(ActionEvent* e = 0);
    void on_updateButton_clicked();
    void On_mainSignal_currentIndexChanged();
    void signalEditPressed(int row);

private:
    void common();
    QString name;
    void setEnabled(bool b);
    bool bEnabled;
    /*private*/ bool showAll;// = true;   // false indicates show only included Turnouts

    /*private*/ static int ROW_HEIGHT;

    /*private*/ static QStringList COLUMN_NAMES;// = {tr("System Name"),
//                                            tr("User Name"),
//                                            tr("Include"),
//                                            tr("Set State")};
    /*private*/ static QStringList COLUMN_SIG_NAMES;// = {tr("System Name"),
//                                            tr("User Name"),
//                                            tr("Include"),
//                                            tr("On State"), tr("Off State"), tr("Edit")};

    /*private*/ static QVector<QString> signalStates;// =  QStringList() {tr("StateSignalHeadDark"), tr("StateSignalHeadRed"), tr("StateSignalHeadYellow"), tr("StateSignalHeadGreen"), tr("StateSignalHeadLunar")};
/*private*/ static QVector<int> signalStatesValues;// =  QList<int>() {SignalHead::DARK, SignalHead::RED, SignalHead::YELLOW, SignalHead::GREEN, SignalHead::LUNAR};

    Logger* log;
    JTextField* _systemName;// = new JTextField(10);
    JTextField* _userName;// = new JTextField(22);

    JmriJFrame* addFrame;// = NULL;

    SignalGroupSignalHeadModel* _signalGroupSignalModel;
    QScrollArea* _SignalGroupSignalScrollPane;

    ATSignalMastAppearanceModel* _AppearanceModel;
    QScrollArea* _SignalAppearanceScrollPane;

    //JTextField mainSignal = new JTextField(30);
    JmriBeanComboBox* mainSignal;

    QButtonGroup* selGroup;// = NULL;
    QRadioButton* allButton;// = NULL;
    QRadioButton* includedButton;// = NULL;

    QLabel* nameLabel;// = new QLabel("SignalGroup System Name:");
    QLabel* userLabel;// = new QLabel("SignalGroup User Name:");
    QLabel* fixedSystemName;// = new QLabel("xxxxxxxxxxx");

    QPushButton* deleteButton;// = new QPushButton("Delete SignalGroup");
    QPushButton* updateButton;// = new QPushButton("Done");

    QWidget*  p2xs;// = NULL;   // SignalHead list table
    QWidget*  p2xsi;// = NULL;   // SignalHead list table
    QWidget*  p3xsi;// = NULL;

    SignalGroup* curSignalGroup;// = NULL;
    bool SignalGroupDirty;// = false;  // true to fire reminder to save work
    bool editMode;// = false;

    /*private*/ /*static*/ class SignalGroupSignal
    {

        //String _sysName=NULL;
        //String _userName=NULL;
     SignalHead* _signal;// = NULL;
     bool _included;
    public:
        SignalGroupSignal(QString sysName, QString userName);
        SignalHead* getBean();
        QString getSysName();
        QString getUserName();
        bool isIncluded();
        void setIncluded(bool include);
        QString getOnState();
        QString getOffState();
        int getOnStateInt();
        int getOffStateInt();
        void setSetOnState(QString state);
        void setSetOffState(QString state);
        /*public*/ void setOnState(int state);
        /*public*/ void setOffState(int state);
    private:
        int _onState;// = 0x00;
        int _offState;// = 0x00;
    };

    /*private*/ /*static*/ class SignalMastAspect
    {
    public:
        SignalMastAspect(QString aspect);
        void setIncluded(bool include);
        bool isIncluded();
        void setAspect(QString app);
        QString getAspect();
    private:
        bool _include;
        QString _aspect;

    };
    /*private*/ QList <SignalGroupSignal*> _signalList;        // array of all Sensorsy
    /*private*/ QList <SignalGroupSignal*> _includedSignalList;

    /*private*/ QList <SignalMastAspect*> _mastAppearancesList;        // array of all Sensorsy
    /*private*/ QList <SignalMastAspect*> _includedMastAspectsList;
 //SGBeanTableDataModel* m;
 void setColumnToHoldButton(JTable* table, int column, QPushButton* sample);
 void initializeIncludedList();
 bool checkNewNamesOK();
 void setMastAspectInformation(SignalGroup* g);
 void setValidSignalAspects();
 bool checkValidSignalMast();
 SignalGroup* checkNamesOK();
 void finishUpdate();
 JmriJFrame* signalEditFrame;// = NULL;
 int setSignalInformation(SignalGroup* g);

private slots:

protected:
    /*protected*/ void createModel();
    /*protected*/ QString getClassName();
 /*protected*/ void setTitle() ;
 /*protected*/ QString helpTarget();
 /*protected*/ /*BeanTableFrame*/ JmriJFrame* f;
protected slots:
 /*protected*/ void addPressed(ActionEvent* e = 0);

 friend class SGBeanTableDataModel;
 friend class ATSignalMastAppearanceModel;
 friend class SignalGroupSignalHeadModel;
 friend class SignalGroupOutputModel;
 friend class SignalGroupsWidget;
};
Q_DECLARE_METATYPE(SignalGroupTableAction)

class SGBeanTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
 SignalGroupTableAction* act;
public:
 enum COLUMNS
 {
  COMMENTCOL = 2+1,
  DELETECOL = 3+1,
  ENABLECOL = 4+1,
  SETCOL = 5+1
 };
 SGBeanTableDataModel(SignalGroupTableAction* act);
 /*public*/ int columnCount(const QModelIndex &parent) const;

 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ void configureTable(JTable* table);
 void doDelete(NamedBean* bean);
 /*public*/ Manager* getManager();
 /*public*/ NamedBean* getBySystemName(QString name) const;
 /*public*/ NamedBean* getByUserName(QString name);
 /*public*/ int getDisplayDeleteMsg();
 /*public*/ void setDisplayDeleteMsg(int boo);
 /*public*/ void clickOn(NamedBean* t);
 /*public*/ QString getValue(QString s) const;
 /*public*/ QPushButton* configureButton();

private:
protected:
 /*protected*/ void configDeleteColumn(JTable* table);
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
 /*protected*/ QString getBeanType();
 /*protected*/ QString getMasterClassName();
 friend class WindowMaker;
};

/*public*/ class ATSignalMastAppearanceModel : public AbstractTableModel //implements PropertyChangeListener
{
    Q_OBJECT
    SignalGroupTableAction* act;
public:
    ATSignalMastAppearanceModel(SignalGroupTableAction* act);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ void dispose();
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    enum COLUMNS
    {
     APPEAR_COLUMN = 0,
     INCLUDE_COLUMN = 1
    };
    /*public*/ void setSetToState(QString x);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

};
/**
 * Base table model for selecting outputs
 */
/*public*/ /*abstract*/ class SignalGroupOutputModel : public AbstractTableModel //implements PropertyChangeListener
{
    Q_OBJECT
    SignalGroupTableAction *act;
public:
    enum COLUMNS
    {
      SNAME_COLUMN = 0,
      UNAME_COLUMN = 1,
      INCLUDE_COLUMN = 2,
      STATE_COLUMN = 3
    };

    SignalGroupOutputModel(SignalGroupTableAction *act);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    friend class SignalGroupSignalHeadModel;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

};

class SignalGroupSignalHeadModel : public SignalGroupOutputModel
{
    Q_OBJECT
public:
    SignalGroupSignalHeadModel(SignalGroupTableAction *act) ;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    enum COLUMNS
    {
     STATE_ON_COLUMN = 3,
     STATE_OFF_COLUMN = 4,
     EDIT_COLUMN = 5
    };
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ void setSetToState(QString x);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

    /*public*/ QString getDisplayName(int r);
    /*public*/ SignalHead* getBean(int r);
    /*public*/ void dispose();
    QSignalMapper* editMapper;
//public slots:
//    void on_editMapper_triggered(int);

};

#endif // SIGNALGROUPTABLEACTION_H
