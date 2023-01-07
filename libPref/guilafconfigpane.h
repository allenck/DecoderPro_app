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
class LIBPREFSHARED_EXPORT GuiLafConfigPane : public QWidget, public PreferencesPanel, public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)

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

    /*public*/ QLocale* getLocale() ;
    static int fontSize;// = 0;
    /*public*/ static void setFontSize(int size);
    /*public*/ static int getFontSize();
    //static ActionListener* listener;
    /*public*/ void doFontSize(QWidget* panel);
    /*public*/ QString getClassName() ;

    /*public*/ QString getPreferencesItem() override;

    /*public*/ QString getPreferencesItemText() override;

    /*public*/ QString getTabbedPreferencesTitle() override;

    /*public*/ QString getLabelKey()  override;

    /*public*/ QWidget* getPreferencesComponent() override;

    /*public*/ bool isPersistant() override;

    /*public*/ QString getPreferencesTooltip() override;

    /*public*/ void savePreferences() override;

    /*public*/ bool isDirty() override;

    /*public*/ bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override;

    /*public*/ QString className();
    void doGraphicState(JPanel* panel);
    void doTabbedOblockEditor(JPanel* panel);
    void doEditorUseOldLocSize(JPanel* panel);
    /*public*/ void doToolTipDismissDelay(JPanel* panel);
    /*public*/ QObject* ppself() {return (QObject*)this;}
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
