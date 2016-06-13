#ifndef SYSTEMCONSOLECONFIGPANEL_H
#define SYSTEMCONSOLECONFIGPANEL_H
#include "preferencespanel.h"
#include "appslib_global.h"

class QComboBox;
class JToggleButton;
class APPSLIBSHARED_EXPORT SystemConsoleConfigPanel : public PreferencesPanel
{
 Q_OBJECT
public:
 explicit SystemConsoleConfigPanel(QWidget* parent = 0);
 ~SystemConsoleConfigPanel() {}
 SystemConsoleConfigPanel(const SystemConsoleConfigPanel&) :PreferencesPanel() {}
 /*public*/  QString getPreferencesItem();
 /*public*/  QString getPreferencesItemText();
 /*public*/  QString getTabbedPreferencesTitle();
 /*public*/  QString getLabelKey();
 /*public*/  QWidget* getPreferencesComponent();
 /*public*/  bool isPersistant();
 /*public*/  QString getPreferencesTooltip();
 /*public*/  void savePreferences();
 /*public*/  bool isDirty();
 /*public*/  bool isRestartRequired();
 /*public*/  bool isPreferencesValid();

signals:

public slots:
 void On_Schemes(int);
 void On_fontFamily(int);
 void On_fontSize(int);
 void On_wrapStyle(int);

private:
 /*private*/ static /*final*/ QList<int> fontSizes; //[] = {
//     8,
//     9,
//     10,
//     11,
//     12,
//     13,
//     14,
//     16,
//     18,
//     20,
//     24};

 /*private*/ static /*final*/ QList<int> wrapStyles; //[] = {
//     SystemConsole.WRAP_STYLE_NONE,
//     SystemConsole.WRAP_STYLE_LINE,
//     SystemConsole.WRAP_STYLE_WORD};

 /*private*/ static /*final*/ QStringList wrapStyleNames;//[] = {
//     rbc.getString("ConsoleWrapStyleNone"),
//     rbc.getString("ConsoleWrapStyleLine"),
//     rbc.getString("ConsoleWrapStyleWord")};

 /*private*/ /*static*/ /*final*/ JToggleButton* fontStyleBold;// = new JToggleButton("B");

 /*private*/ /*static*/ /*final*/ JToggleButton* fontStyleItalic;// = new JToggleButton("I");

 /*private*/ /*static*/ /*final*/ QComboBox* schemes;// = new JComboBox<>(SystemConsole.getInstance().getSchemes());

 /*private*/ /*static*/ /*final*/ QComboBox* fontFamily;// = FontComboUtil.getFontCombo(FontComboUtil.MONOSPACED, 14);

 /*private*/ /*static*/ /*final*/ QComboBox* fontSize;// = new JComboBox<>(fontSizes);

 private slots:
 /*private*/ /*static*/ void doFontStyle();

};
Q_DECLARE_METATYPE(SystemConsoleConfigPanel)
#endif // SYSTEMCONSOLECONFIGPANEL_H
