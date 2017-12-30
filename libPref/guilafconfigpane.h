#ifndef GUILAFCONFIGPANE_H
#define GUILAFCONFIGPANE_H
#include "preferencespanel.h"
#include <QMap>
#include "libpref_global.h"

class ActionListener;
class QCheckBox;
class QButtonGroup;
class QComboBox;
class QLocale;
class LIBPREFSHARED_EXPORT GuiLafConfigPane : public PreferencesPanel
{
    Q_OBJECT
public:
    explicit GuiLafConfigPane(QWidget *parent = 0);
    ~GuiLafConfigPane() {}
    GuiLafConfigPane(const GuiLafConfigPane&) : PreferencesPanel() {}
    /*public*/ QWidget* doLocale();
    /*public*/ void setLocale(QString loc);
    virtual
    /*public*/ QLocale* getLocale() ;
    static int fontSize;// = 0;
    /*public*/ static void setFontSize(int size);
    /*public*/ static int getFontSize();
    /*static*/ QComboBox* fontSizeComboBox;// = new JComboBox<>(fontSizes);
    //static ActionListener* listener;
    /*public*/ void doFontSize(QWidget* panel);
    /*public*/ QString getClassName() ;
    virtual
    /*public*/ QString getPreferencesItem();
    virtual
    /*public*/ QString getPreferencesItemText();
    virtual
    /*public*/ QString getTabbedPreferencesTitle();
    virtual
    /*public*/ QString getLabelKey() ;
    virtual
    /*public*/ QWidget* getPreferencesComponent();
    virtual
    /*public*/ bool isPersistant();
    virtual
    /*public*/ QString getPreferencesTooltip();
    virtual
    /*public*/ void savePreferences();
    virtual
    /*public*/ bool isDirty();
    virtual
    /*public*/ bool isRestartRequired();
signals:

public slots:
    void On_fontSizeConboBox_currentIndexChanged(QString);
private:
    /*private*/ /*final*/ QComboBox* localeBox;// = new JComboBox<>(new String[]{
//    Locale.getDefault().getDisplayName(),
//        "(Please Wait)"});
    /*private*/ /*final*/ QMap<QString, QLocale*> locale;// = new HashMap<>();
    /*private*/ /*final*/ QButtonGroup* LAFGroup;// = new ButtonGroup();
    /*public*/ QCheckBox* mouseEvent;
    /*private*/ bool dirty;// = false;
    void doClickSelection(QWidget* panel);
    void doLAF(QWidget* panel);
    /*private*/ int getDefaultFontSize();
    /*private*/ static /*final*/ QStringList fontSizes;
 friend class GuiLafConfigPaneXml;
};

#endif // GUILAFCONFIGPANE_H
