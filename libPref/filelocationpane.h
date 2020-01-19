#ifndef FILELOCATIONPANE_H
#define FILELOCATIONPANE_H
#include "preferencespanel.h"
#include "libpref_global.h"
#include "abstractaction.h"

class JFileChooser;
class JTextField;
class LIBPREFSHARED_EXPORT FileLocationPane : public QWidget, public PreferencesPanel
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel)

public:
    Q_INVOKABLE explicit FileLocationPane(QWidget *parent = 0);
    ~FileLocationPane() {}
    FileLocationPane(const FileLocationPane&);
    virtual
    /*public*/ QString getPreferencesItem();
    virtual
    /*public*/ QString getPreferencesItemText() ;
    virtual
    /*public*/ QString getTabbedPreferencesTitle();
    virtual
    /*public*/ QString getLabelKey();
    virtual
    /*public*/ QWidget* getPreferencesComponent();
    virtual
    /*public*/ bool isPersistant();
    virtual
    /*public*/ QString getPreferencesTooltip() ;
    virtual
    /*public*/ void savePreferences();
    virtual
    /*public*/ bool isDirty();
    virtual
    /*public*/ bool isRestartRequired();

    /*public*/ QString className();
    /*public*/ QObject* self() {return (QObject*)this;}

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
