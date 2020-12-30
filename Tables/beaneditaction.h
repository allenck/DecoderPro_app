#ifndef BEANEDITACTION_H
#define BEANEDITACTION_H

#include "abstractaction.h"
#include "abstracttablemodel.h"
#include "actionlistener.h"
#include "libtables_global.h"
#include <QStatusBar>
#include <QLabel>

class KeyValueModel;
class NamedBeanHandleManager;
class JTextArea;
class BeanEditItem;
class Logger;
class QTabWidget;
class JmriJFrame;
class BeanPropertiesTableModel;
class BeanItemPanel;
class QScrollArea;
class JTextArea;
class JTextField;
class NamedBean;
class LIBTABLESSHARED_EXPORT BeanEditAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit BeanEditAction(QObject *parent = 0);
 /*public*/ BeanEditAction(QString s,QObject *parent);
 /*public*/ void setBean(NamedBean* bean);
 /*public*/ void setSelectedComponent(QWidget* c);
 /*public*/ void save();
 /*public*/ void renameBean(QString _newName);
 /*public*/ void removeName();

signals:
private:
 NamedBean* bean;
 Logger* log;

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0)override;
 void On_okBut_clicked();

private:
 void common();
 JTextField* userNameField;// = new JTextField(20);
 JTextArea* commentField;// = new JTextArea(3, 30);
 QScrollArea* commentFieldScroller;// = new JScrollPane(commentField);
 virtual BeanItemPanel* basicDetails();
 virtual BeanItemPanel* usageDetails();
 BeanPropertiesTableModel* propertiesModel;
 virtual BeanItemPanel* propertiesDetails();
 JmriJFrame* f;
 /*private*/ QTabWidget* detailsTab;// = new JTabbedPane();
 void formatTextAreaAsLabel(JTextArea* pane);
 static bool validateNumericalInput(QString text);
 NamedBeanHandleManager* nbMan;// = InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);
 QLabel* statusBarWidget;

protected:
 virtual /*protected*/ void initPanels();
 virtual /*protected*/ void initPanelsFirst() ;
 virtual /*protected*/ void initPanelsLast();
 virtual /*protected*/ void saveBasicItems(ActionEvent* e = 0);
 virtual /*protected*/ void resetBasicItems(ActionEvent* e = 0);
 virtual /*abstract*/ /*protected*/ QString helpTarget();
 /*protected*/QList<BeanItemPanel*> bei;// = new ArrayList<BeanItemPanel>(5);
 /*protected*/ QWidget* selectedTab;// = NULL;
protected slots:
 /*protected*/ void applyButtonAction(ActionEvent* e = 0);
 /*protected*/ void cancelButtonAction(ActionEvent* e = 0);
 /*protected*/ void addToPanel(QWidget* panel, QList<BeanEditItem*> items);
 virtual /*abstract*/ /*protected*/ QString getBeanType();
 virtual /*abstract*/ /*protected*/ NamedBean* getByUserName(QString name);

 friend class TurnoutEditAction;
 friend class FeedbackSaveItemListener;
 friend class FeedbackResetItemListener;
 friend class LockSaveItemListener;
 friend class LockResetItemListener;
 friend class SpeedSaveItemListener;
 friend class SpeedResetItemListener;
 friend class PropertiesSetSaveActionListener;
 friend class PropertiesSetResetActionListener;
 friend class BasicSetSaveActionListener;
 friend class BasicSetResetActionListener;
 friend class BlockEditAction;
 friend class SensorDebounceEditAction;
 friend class SetResetItemAction;
 friend class SetSaveItemAction;
 friend class OBlockEditAction;
 friend class OBTSaveItemAction1;
 friend class OBTResetItemAction1;
 friend class OBTResetItemAction1a;
 friend class OBTSaveItemAction2;
 friend class OBTResetItemAction2;
 friend class OBTSaveItemAction3;
 friend class OBTResetItemAction3;
};
/*private*/ /*static*/ class LIBTABLESSHARED_EXPORT BeanPropertiesTableModel : public  AbstractTableModel
{
 Q_OBJECT
    /**
     *
     */
    //private static final long serialVersionUID = -7466799526127205872L;
 /*private*/ /*static*/ class KeyValueModel
 {
  public:
     /*public*/ KeyValueModel(QVariant k, QVariant v) ;
     /*public*/ QVariant key, value;
 };
    QVector<KeyValueModel*> attributes;
    QStringList titles;
    bool _wasModified;
    /*private*/ bool keyExist(QVariant k) ;


  public:
    /*public*/ BeanPropertiesTableModel() ;

    /*public*/ void setModel(NamedBean* nb);
    /*public*/ void updateModel(NamedBean* nb);
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ bool wasModified() ;
};
class LIBTABLESSHARED_EXPORT BasicSetSaveActionListener : public AbstractAction
{
 Q_OBJECT
 BeanEditAction* act;
public:
 BasicSetSaveActionListener(BeanEditAction* act);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
class LIBTABLESSHARED_EXPORT BasicSetResetActionListener : public AbstractAction
{
 Q_OBJECT
 BeanEditAction* act;
public:
 BasicSetResetActionListener(BeanEditAction* act);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
class LIBTABLESSHARED_EXPORT PropertiesSetSaveActionListener : public AbstractAction
{
 Q_OBJECT
 BeanEditAction* act;
public:
 PropertiesSetSaveActionListener(BeanEditAction* act);
public slots:
 void actionPerformed(JActionEvent *e = 0) /*override*/;
};
class LIBTABLESSHARED_EXPORT PropertiesSetResetActionListener : public AbstractAction
{
 Q_OBJECT
 BeanEditAction* act;
public:
 PropertiesSetResetActionListener(BeanEditAction* act);
public slots:
 void actionPerformed(JActionEvent *e = 0) /*override*/;
};

#endif // BEANEDITACTION_H
