#ifndef PERFORMSCRIPTPANEL_H
#define PERFORMSCRIPTPANEL_H
#include "preferencespanel.h"
#include "libpref_global.h"

class QVBoxLayout;
class JActionEvent;
class QLabel;
class PerformScriptModel;
class QPushButton;
class JFileChooser;
class LIBPREFSHARED_EXPORT PerformScriptPanel : public QWidget, public PreferencesPanel
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
 explicit PerformScriptPanel(QWidget *parent = 0);
 ~PerformScriptPanel() {}
 PerformScriptPanel(const PerformScriptPanel&) : QWidget() {}
 /*public*/ QString getPreferencesItem();
 /*public*/ QString getPreferencesItemText() ;
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey();
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant() ;
 /*public*/ QString getPreferencesTooltip();
 /*public*/ void savePreferences();
 /*public*/ bool isDirty() ;
 /*public*/ bool isRestartRequired();
 /*public*/virtual bool isPreferencesValid();
 /*public*/ QString className();
 /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
private:
 /*private*/ bool dirty;// = false;
 QWidget* _self;  // used for synchronization

 JFileChooser* fc;// = XmlFile::userFileChooser("Python script files", "py");
 QVBoxLayout* thisLayout;

protected slots:
 /*protected*/ void addItem();
 friend class PSPItem;
};
/*public*/ class PSPItem :  public QWidget //implements ActionListener
{
 Q_OBJECT
 /**
  *
  */
 //private static final long serialVersionUID = 773446142833490795L;
 QPushButton* removeButton;// = new JButton(rb.getString("ButtonScriptRemove"));
public:
 PSPItem(QWidget* parent); // parent must be provided!
 PSPItem(PerformScriptModel* m, QWidget* parent); // parent must be provided!
 /*public*/ PerformScriptModel* getModel();
private:
 PerformScriptModel* model;// = new PerformScriptModel();
 QLabel* selected;

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) ;
 friend class PerformScriptPanel;
};

Q_DECLARE_METATYPE(PerformScriptPanel)
#endif // PERFORMSCRIPTPANEL_H
