#ifndef SYSTEMCONSOLECONFIGPANEL_H
#define SYSTEMCONSOLECONFIGPANEL_H
#include "preferencespanel.h"
#include "appslib_global.h"

class QComboBox;
class JToggleButton;
class APPSLIBSHARED_EXPORT SystemConsoleConfigPanel : public QWidget,  public PreferencesPanel, public InstanceManagerAutoDefault
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)

public:
 Q_INVOKABLE explicit SystemConsoleConfigPanel(QWidget* parent = 0);
 ~SystemConsoleConfigPanel() {}
 SystemConsoleConfigPanel(const SystemConsoleConfigPanel&) :QWidget() {}
 /*public*/  QString getPreferencesItem() override;
 /*public*/  QString getPreferencesItemText() override;
 /*public*/  QString getTabbedPreferencesTitle() override;
 /*public*/  QString getLabelKey() override;
 /*public*/  QWidget* getPreferencesComponent() override;
 /*public*/  bool isPersistant() override;
 /*public*/  QString getPreferencesTooltip() override;
 /*public*/  void savePreferences() override;
 /*public*/  bool isDirty() override;
 /*public*/  bool isRestartRequired() override;
 /*public*/  bool isPreferencesValid() override;
 /*punlic*/ QString className() override;

 /*public*/ QObject* ppself()  override{return (QObject*)this;}

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
