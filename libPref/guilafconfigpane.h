#ifndef GUILAFCONFIGPANE_H
#define GUILAFCONFIGPANE_H
#include "preferencespanel.h"
#include <QMap>
#include "libpref_global.h"

class JSpinner;
class JPanel;
class ActionListener;
class JCheckBox;
class QButtonGroup;
class JComboBox;
class QLocale;
class LIBPREFSHARED_EXPORT GuiLafConfigPane : public QWidget, public PreferencesPanel
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel)

public:
    /*public*/ static /*final*/ int MAX_TOOLTIP_TIME;// = 3600;
    /*public*/ static /*final*/ int MIN_TOOLTIP_TIME;// = 1;
    /*public*/ static /*final*/ int MIN_DISPLAYED_FONT_SIZE;// = MIN_FONT_SIZE;
    /*public*/ static /*final*/ int MAX_DISPLAYED_FONT_SIZE;// = 20;
    Q_INVOKABLE explicit GuiLafConfigPane(QWidget *parent = 0);
    ~GuiLafConfigPane() {}
    GuiLafConfigPane(const GuiLafConfigPane&) : QWidget() {}
    /*public*/ QWidget* doLocale();
    /*public*/ void setLocale(QString loc);
    virtual
    /*public*/ QLocale* getLocale() ;
    static int fontSize;// = 0;
    /*public*/ static void setFontSize(int size);
    /*public*/ static int getFontSize();
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

    /*public*/ QString className();
    void doGraphicState(JPanel* panel);
    void doTabbedOblockEditor(JPanel* panel);
    void doEditorUseOldLocSize(JPanel* panel);
    /*public*/ void doToolTipDismissDelay(JPanel* panel);
    /*public*/ QObject* self() {return (QObject*)this;}
    /*public*/ JCheckBox* graphicStateDisplay;
    /*public*/ JCheckBox* tabbedOblockEditor;
    /*public*/ JCheckBox* editorUseOldLocSizeDisplay;
    /*private*/ bool dirty;// = false;

signals:

public slots:
    void On_fontSizeConboBox_currentIndexChanged(QString);
    void on_toolTipDismissDelaySpinner(int);
    void on_graphicStateDisplay_clicked(bool b);
    void on_editorUseOldLocSizeDisplay_clicked(bool);

private:
    /*private*/ /*final*/ JComboBox* localeBox;// = new JComboBox<>(new String[]{
//    Locale.getDefault().getDisplayName(),
//        "(Please Wait)"});
    /*private*/ /*final*/ QMap<QString, QLocale*> locale;// = new HashMap<>();
    /*private*/ /*final*/ QButtonGroup* LAFGroup;// = new ButtonGroup();
    /*public*/ JCheckBox* mouseEvent;
    /*private*/ JComboBox/*<Integer>*/* fontSizeComboBox;
    void doClickSelection(QWidget* panel);
    void doLAF(QWidget* panel);
    /*private*/ int getDefaultFontSize();
//    /*private*/ static /*final*/ QStringList fontSizes;
    /*private*/ JSpinner* toolTipDismissDelaySpinner;

 friend class GuiLafConfigPaneXml;
};

#endif // GUILAFCONFIGPANE_H
