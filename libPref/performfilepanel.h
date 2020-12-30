#ifndef PERFORMFILEPANEL_H
#define PERFORMFILEPANEL_H

#include "preferencespanel.h"
#include "libpref_global.h"

class QVBoxLayout;
class QLabel;
class JActionEvent;
class PerformFileModel;
class QPushButton;
class XmlFile;
class JFileChooser;
class LIBPREFSHARED_EXPORT PerformFilePanel : public QWidget, public PreferencesPanel
{
    Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
    Q_INVOKABLE explicit PerformFilePanel(QWidget *parent = 0);
    ~PerformFilePanel() {}
    PerformFilePanel(const PerformFilePanel&) : QWidget() {}
    /*public*/ QString getPreferencesItem() ;
    /*public*/ QString getPreferencesItemText();
    /*public*/ QString getTabbedPreferencesTitle();
    /*public*/ QString getLabelKey();
    /*public*/ QWidget* getPreferencesComponent() ;
    /*public*/ bool isPersistant();
    /*public*/ QString getPreferencesTooltip() ;
    /*public*/ void savePreferences();
    /*public*/ bool isDirty() ;
    /*public*/ bool isRestartRequired() ;

    /*public*/ QString className();
    /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
private:
    /*private*/ bool dirty;// = false;
    JFileChooser* fc;// = XmlFile::userFileChooser("XML files", "xml");
    QVBoxLayout* thisLayout;
protected slots:
    /*protected*/ void addItem();
 friend class PFItem;
};

/*public*/ class PFItem : public  QWidget //implements ActionListener {
{
    Q_OBJECT
/**
 *
 */
 //private static final long serialVersionUID = 9081562133732338951L;
 QPushButton* removeButton;// = new QPushButton(tr("Remove"));
 QLabel* selected;
 PerformFilePanel* self;
public:
 PerformFileModel* model;// = new PerformFileModel();

 PFItem(PerformFilePanel* self);
 PFItem(PerformFileModel* m, PerformFilePanel* self) ;
/*public*/ PerformFileModel* getModel();
public slots:
 /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0);
};
#endif // PERFORMFILEPANEL_H
