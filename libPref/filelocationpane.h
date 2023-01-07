#ifndef FILELOCATIONPANE_H
#define FILELOCATIONPANE_H
#include "preferencespanel.h"
#include "libpref_global.h"
#include "abstractaction.h"
#include "instancemanagerautodefault.h"

class JFileChooser;
class JTextField;
class LIBPREFSHARED_EXPORT FileLocationPane : public QWidget, public PreferencesPanel, public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)

public:
    Q_INVOKABLE explicit FileLocationPane(QWidget *parent = 0);
    ~FileLocationPane() {}
    FileLocationPane(const FileLocationPane&);
    /*public*/ QString getPreferencesItem() override;
    /*public*/ QString getPreferencesItemText() override;
    /*public*/ QString getTabbedPreferencesTitle() override;
    /*public*/ QString getLabelKey() override;
    /*public*/ QWidget* getPreferencesComponent() override;
    /*public*/ bool isPersistant() override;
    /*public*/ QString getPreferencesTooltip()  override;
    /*public*/ void savePreferences() override;
    /*public*/ bool isDirty() override;
    /*public*/ bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override;

    /*public*/ QString className() override;
    /*public*/ QObject* ppself()  override{return (QObject*)this;}

signals:

public slots:
    void On_fileSelected(QString file);
    /*private*/ void programLocationChange(QString loc);

private:
    /*private*/ bool restartRequired;// = false;
    /*private*/ /*final*/ JTextField* scriptLocation;// = new JTextField();
    /*private*/ /*final*/ JTextField* userLocation;// = new JTextField();
    /*private*/ /*final*/ JTextField* _programLocation;// = new JTextField();

    /*private*/ QWidget* prefLocation();
    /*private*/ void common();
    /*private*/ QWidget* scriptsLocation();
    /*final*/ JFileChooser* fcScript;
    /*private*/ QWidget* programLocation();

};

/*private*/ class OpenAction : public AbstractAction {
 Q_OBJECT
    JFileChooser* chooser;
    JTextField* field;
    FileLocationPane* pane;
public:
    OpenAction(JFileChooser* chooser, JTextField* field, FileLocationPane* pane);
public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
};

#endif // FILELOCATIONPANE_H
