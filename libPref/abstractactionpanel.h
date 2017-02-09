#ifndef ABSTRACTACTIONPANEL_H
#define ABSTRACTACTIONPANEL_H

#include "preferencespanel.h"
#include "logger.h"
#include <QObjectList>
#include "libpref_global.h"

class PropertyChangeEvent;
class QVBoxLayout;
class ActionEvent;
class QComboBox;
class QPushButton;
class AbstractActionModel;
class LIBPREFSHARED_EXPORT AbstractActionPanel : public PreferencesPanel
{
    Q_OBJECT
public:
    //explicit AbstractActionPanel(QWidget *parent = 0);
    /*public*/ AbstractActionPanel(QString addButtonKey, QString removeButtonKey, QWidget *parent = 0);
    virtual
    /*public*/ QString getPreferencesItem();
    virtual
    /*public*/ QString getPreferencesItemText() ;
    virtual
    /*public*/ QWidget* getPreferencesComponent();
    virtual
    /*public*/ bool isPersistant();
    virtual
    /*public*/ QString getPreferencesTooltip();
    virtual
    /*public*/ void savePreferences() ;
    virtual
    /*public*/ bool isDirty() ;
    virtual
    /*public*/ bool isRestartRequired();
    /*public*/ QWidget* getTopLevelAncestor();

signals:

public slots:
    void propertyChange(PropertyChangeEvent* );

private:
    QWidget* self;  // used for synchronization
    QString removeButtonKey;
    virtual /*abstract*/ AbstractActionModel* getNewModel();
    Logger* log;
    /* virtual*/ /*abstract*/ QObjectList rememberedObjects() {return QObjectList();}
    QVBoxLayout* thisLayout;
    QString addButtonKey;

protected:
    /*protected*/ bool dirty;// = false;
protected slots:
    /*protected*/ void addItem();
    /*protected*/ void init();

 friend class Item;
 friend class PerformActionPanel;
};

/*public*/ class LIBPREFSHARED_EXPORT Item : public  QWidget //implements ActionListener
{
 Q_OBJECT
    //private static final long serialVersionUID = -2499516926618516181L;
 QPushButton* removeButton;// = new JButton(tr(removeButtonKey));
 QString removeButtonKey;
 AbstractActionPanel* panel;
public:
    Item(QString removeButtonKey, AbstractActionPanel* panel);
    Item(AbstractActionModel* m, AbstractActionPanel* panel);
    void updateCombo();
    /*public*/ AbstractActionModel* updatedModel();
public slots:
    virtual
    /*public*/ void actionPerformed(ActionEvent* e = 0);
    void On_selections_currentIndexChanged(int);
private:
    void common(AbstractActionPanel* parent);
    Logger* log;
    AbstractActionModel* model;// = NULL;
    QComboBox* selections;

};
#endif // ABSTRACTACTIONPANEL_H
