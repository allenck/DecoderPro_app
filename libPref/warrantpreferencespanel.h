#ifndef WARRANTPREFERENCESPANEL_H
#define WARRANTPREFERENCESPANEL_H
#include "preferencespanel.h"
#include <QPair>
#include "abstracttablemodel.h"
#include "actionlistener.h"
#include "libpref_global.h"

class QSpinBox;
class FlowLayout;
class QRadioButton;
class QButtonGroup;
class ActionListener;
class ScaleData;
class AppearanceTableModel;
class JTable;
class SpeedNameTableModel;
class QComboBox;
class JTextField;
class WarrantPreferences;
class LIBPREFSHARED_EXPORT WarrantPreferencesPanel : public QWidget, public PreferencesPanel
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
 Q_INVOKABLE explicit WarrantPreferencesPanel(QWidget *parent = 0);
 ~WarrantPreferencesPanel() {}
 WarrantPreferencesPanel(const WarrantPreferencesPanel&) : QWidget() {}
 /*public*/ QString getPreferencesItem();
 /*public*/ QString getPreferencesItemText();
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey();
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant() ;
 /*public*/ void savePreferences();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired();
 /*public*/ bool isPreferencesValid();
 /*public*/ QString getPreferencesTooltip();

 /*public*/ QString className();
 QSize sizeHint();
 QSize minimumSizeHint();
 /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
 /*public*/ void itemStateChanged(/*ItemEvent e*/int);
 void on_rampIncre_leaveField();
 // void on_applyB_clicked();
private:
 static int STRUT_SIZE;// = 10;

 ///*private*/ WarrantPreferences* _preferences;
 /*private*/ bool _isDirty;// = false;

 /*private*/ QComboBox* _layoutScales;
 /*private*/ QSpinBox*  _searchDepth;
 /*private*/ QSpinBox*  _timeIncre;
 /*private*/ JTextField*  _rampIncre;
 /*private*/ JTextField*  _throttleScale;
 /*private*/ int _interpretation;// = SignalSpeedMap::PERCENT_NORMAL;
 /*private*/ QList<QPair<QString, float> > _speedNameMap;
 /*private*/ SpeedNameTableModel* _speedNameModel;
 /*private*/ JTable*  _speedNameTable;
 /*private*/ QList<QPair<QString, QString>* > _appearanceMap;
 /*private*/ AppearanceTableModel* _appearanceModel;
 /*private*/ JTable*  _appearanceTable;
 /*private*/ QList<QPair<QString, int>* > _stepIncrementMap;
 /*private*/ void initGUI();
// /*private*/ void setGUI();
 /*private*/ QWidget* layoutScalePanel();
 /*private*/ ScaleData* makeCustomItem(float scale);
 /*private*/ QWidget* searchDepthPanel(bool vertical);
 /*private*/ QWidget* throttleScalePanel(bool vertical);
 /*private*/ QWidget* speedNamesPanel();
 /*private*/ QWidget* appearancePanel() ;
 static /*private*/ QWidget* tablePanel(JTable* table, QString toolTip, ActionListener* insertAction, ActionListener* removeAction) ;
 /*private*/ void insertSpeedNameRow();
 /*private*/ QWidget* interpretationPanel() ;
 /*private*/ void makeButton(FlowLayout* panelLayout, QButtonGroup* group, QString name, QString tooltip, int interp);
 /*private*/ QWidget* timeIncrementPanel(bool vertical, QSpinBox *_timeIncre) ;
 /*private*/ QWidget* throttleIncrementPanel(bool vertical, JTextField *_rampincre);
 /*private*/ void setValues();
 // /*private*/ QWidget* applyPanel() ;
 /*private*/ void deleteSpeedNameRow();

public slots:

 friend class ButtonActionListener;
 friend class InsertActionListener;
 friend class DeleteActionListener;
 friend class SpeedNameTableModel;
 friend class AppearanceTableModel;
 friend class StepIncrementTableModel;
};
Q_DECLARE_METATYPE(WarrantPreferencesPanel)

class ScaleData : public QObject
{
    float scale;
    QString scaleName;
public:
    ScaleData(QString scaleName, float scale);
    /*public*/ virtual QString toString();
    friend class WarrantPreferencesPanel;
    friend class CustomDialog;
};

class CustomDialog : public ScaleData
{
 Q_OBJECT
public:
 CustomDialog(QString scaleName, float scale) ;
    /*public*/ QString toString() ;
};
/************************* SpeedName Table ******************************/
class SpeedNameTableModel : public  AbstractTableModel
{
 Q_OBJECT
//    /*private*/ static final long serialVersionUID = 7088050123933847145L;
 WarrantPreferencesPanel* panel;
public:
    /*public*/ SpeedNameTableModel(WarrantPreferencesPanel* panel);
 /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

/************************* appearance Table ******************************/
class AppearanceTableModel : public AbstractTableModel
{
 Q_OBJECT
//    /*private*/ static final long serialVersionUID = 7088050123933847144L;
 WarrantPreferencesPanel* panel;
public:
    /*public*/ AppearanceTableModel(WarrantPreferencesPanel* panel);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col) ;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

class InsertActionListener : public ActionListener
{
 Q_OBJECT
 WarrantPreferencesPanel* panel;
public:
 InsertActionListener(WarrantPreferencesPanel* panel);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
class DeleteActionListener : public ActionListener
{
 Q_OBJECT
 WarrantPreferencesPanel* panel;
public:
 DeleteActionListener(WarrantPreferencesPanel* panel);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
class ButtonActionListener : public ActionListener
{
 Q_OBJECT
 int value;
 QRadioButton* but;
 WarrantPreferencesPanel* panel;
 public:
 ButtonActionListener* init(QRadioButton* b, int num, WarrantPreferencesPanel* panel);
public slots:
 /*public*/ void actionPerformed(JActionEvent* /*e*/) ;
};

/************************* Throttle Step Increment Table ******************************/
class StepIncrementTableModel : public AbstractTableModel
{
 Q_OBJECT
//    /*private*/ static final long serialVersionUID = 7088050123933847143L;
 WarrantPreferencesPanel* panel;
public:
    /*public*/ StepIncrementTableModel( WarrantPreferencesPanel* panel);
 /*public*/ int columnCount (const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};
#endif // WARRANTPREFERENCESPANEL_H
