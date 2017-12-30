#ifndef SENSORTABLEACTION_H
#define SENSORTABLEACTION_H

#include <QObject>
#include "actionlistener.h"
#include "abstracttableaction.h"
#include "libtables_global.h"

class ProxySensorManager;
class QTableView;
class PropertyChangeEvent;
class BeanTableFrame;
class BeanTableDataModel;
class JFrame;
//class ActionEvent;
class Manager;
class SensorManager;
class QLabel;
class QCheckBox;
class UserPreferencesManager;
class QComboBox;
class JmriJFrame;
class JTextField;
class LIBTABLESSHARED_EXPORT SensorTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    explicit SensorTableAction(QObject *parent = 0);
    /*public*/ SensorTableAction(QString actionName, QObject *parent);
    ~SensorTableAction() {}
    SensorTableAction(const SensorTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(Manager* man);
    /*public*/ void setMenuBar(JmriJFrame* f);
    /*public*/ void setEnabled(bool newValue);
    /*public*/ void addToFrame(BeanTableFrame* f);
    /*public*/ void setMessagePreferencesDetails();
    /*public*/ QString getClassDescription();
    static QString getName();
    /*public*/ void addToPanel(AbstractTableTabAction* f);

signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
//    void onDebounce();

private:
    JmriJFrame* addFrame;// = NULL;

    JTextField* sysName;// = new JTextField(40);
    JTextField* userName;// = new JTextField(40);
    QComboBox* prefixBox;// = new JComboBox();
    JTextField* numberToAdd;// = new JTextField(5);
    QCheckBox* range;// = new JCheckBox("Add a range");
    QLabel* sysNameLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    QString userNameError;// = this.getClass().getName()+".DuplicateUserName";
    UserPreferencesManager* p;
    void handleCreateException(QString sysName);
    BeanTableFrame* f;
    //BeanTableDataModel* m;
    QCheckBox* showDebounceBox;// = new JCheckBox(tr("SensorDebounceCheckBox"));
    bool enabled;


private slots:
    /*private*/ void canAddRange();
    void showDebounceChanged(bool);

protected:
    /*protected*/ SensorManager* senManager;// = jmri.InstanceManager.sensorManagerInstance();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ void setDefaultDebounce(JFrame* _who);
    /*protected*/ QString getClassName();
    /*protected*/ void setDefaultState(JFrame* _who);

protected slots:
    /*protected*/ void addPressed();
    void okPressed();
    void cancelPressed(ActionEvent* e = 0);


friend class STOkButtonActionListener;
friend class STCancelActionListener;
friend class STRangeActionListener;
friend class DebounceActionListener;
friend class SensorWidget;
friend class SensorTableWidget;
friend class DefaultStateActionListener;
};

class STOkButtonActionListener : public ActionListener
{
 Q_OBJECT
 SensorTableAction* act;
public:
 STOkButtonActionListener(SensorTableAction* act);
public slots:
 void actionPerformed();

};

class STCancelActionListener : public ActionListener
{
 Q_OBJECT
 SensorTableAction* act;
public:
 STCancelActionListener(SensorTableAction* act);
public slots:
 void actionPerformed();
};

class STRangeActionListener : public ActionListener
{
 Q_OBJECT
 SensorTableAction* act;
public:
 STRangeActionListener(SensorTableAction* act);
public slots:
 void actionPerformed();
};

class DebounceActionListener : public ActionListener
{
 Q_OBJECT
 JmriJFrame* finalF;
 SensorTableAction* act;
public:
 DebounceActionListener(JmriJFrame* finalF, SensorTableAction* act);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};

class DefaultStateActionListener : public ActionListener
{
 Q_OBJECT
 JmriJFrame* finalF;
 SensorTableAction* act;
public:
 DefaultStateActionListener(JmriJFrame* finalF, SensorTableAction* act);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};

#endif // SENSORTABLEACTION_H
