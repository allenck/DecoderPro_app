#ifndef BEANSELECTCREATEPANEL_H
#define BEANSELECTCREATEPANEL_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include "jtextfield.h"
#include "managercombobox.h"
#include "exceptions.h"
#include "libtables_global.h"

class UserPreferencesManager;
class Manager;
class NamedBean;
class NamedBeanComboBox;
class LIBTABLESSHARED_EXPORT BeanSelectCreatePanel : public QWidget
{
    Q_OBJECT
public:
    //explicit BeanSelectCreatePanel(QWidget *parent = 0);
    /*public*/ BeanSelectCreatePanel(Manager* manager, NamedBean* defaultSelect, QWidget *parent = 0);
    /*public*/ void setEnabled(bool enabled);
    /*public*/ void refresh();
    /*public*/ QString getDisplayName();
    /*public*/ NamedBean* getNamedBean() throw (JmriException);
    /*public*/ void setReference(QString ref);
    /*public*/ void setDefaultNamedBean(NamedBean* nBean);
    /*public*/ void dispose();

signals:

public slots:
    void update();

private:
    Manager* _manager;
    NamedBean* _defaultSelect;
    QString _reference;// = NULL;
    QRadioButton* existingItem;// = new QRadioButton();
    QRadioButton* newItem;
    QButtonGroup* selectcreate;// = new QButtonGroup();

    NamedBeanComboBox* existingCombo;
    JTextField* hardwareAddress =  new JTextField(8);
    ManagerComboBox* prefixBox = new ManagerComboBox();
    UserPreferencesManager* p;
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    /*private*/ NamedBean* createBean() throw (JmriException);

};

#endif // BEANSELECTCREATEPANEL_H
