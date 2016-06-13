#include "guilafconfigpane.h"
#include <QComboBox>
#include <QCheckBox>
#include <QLocale>
#include <QBoxLayout>
#include <QMap>
#include <QButtonGroup>
#include "flowlayout.h"
#include <QLabel>
#include "QRadioButton"

//GuiLafConfigPane::GuiLafConfigPane(QWidget *parent) :
//    PreferencesPanel(parent)
//{
//}
/**
 * Provide GUI to configure Swing GUI LAF defaults
 * <P>
 * Provides GUI configuration for SWING LAF by displaying radio buttons for each
 * LAF implementation available. This information is then persisted separately
 * (e.g. by {@link jmri.configurexml.GuiLafConfigPaneXml})
 * <P>
 * Locale default language and country is also considered a GUI (and perhaps
 * LAF) configuration item.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2010
 * @version	$Revision: 28420 $
 * @since 2.9.5 (Previously in jmri package)
 */
// /*public*/ class GuiLafConfigPane extends QWidget* implements PreferencesPanel {

    //private static final long serialVersionUID = -3846942336860819413L;
    //static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle");


/*public*/ GuiLafConfigPane::GuiLafConfigPane(QWidget *parent)
    : PreferencesPanel(parent)
{
 setObjectName("GuiLafConfigPane");
 localeBox = new QComboBox();
 fontSizeComboBox = new QComboBox(/*fontSizes*/);
 fontSizeComboBox->addItems(fontSizes);
//    Locale.getDefault().getDisplayName(),
//    "(Please Wait)"});
 locale =  QMap<QString, QLocale*>();
 LAFGroup = new QButtonGroup();
 dirty = false;
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));
 QWidget* p;
 doLAF(p = new QWidget());
 thisLayout->addWidget(p);
 doFontSize(p = new QWidget());
 thisLayout->addWidget(p);
 doClickSelection(p = new QWidget());
 thisLayout->addWidget(p);
}

void GuiLafConfigPane::doClickSelection(QWidget* panel)
{
 FlowLayout* panelLayout;
 panel->setLayout(panelLayout =new FlowLayout());
    mouseEvent = new QCheckBox("Use non-standard release event for mouse click?");
//    mouseEvent->setChecked(SwingSettings.getNonStandardMouseEvent());
 panelLayout->addWidget(mouseEvent);
}

void GuiLafConfigPane::doLAF(QWidget* panel)
{
 // find L&F definitions
 FlowLayout* panelLayout;
 panel->setLayout(panelLayout =new FlowLayout());
#if 0
    UIManager.LookAndFeelInfo[] plafs = UIManager.getInstalledLookAndFeels();
    HashMap<String, String> installedLAFs = new HashMap<>(plafs.length);
    for (UIManager.LookAndFeelInfo plaf : plafs) {
        installedLAFs.put(plaf.getName(), plaf.getClassName());
    }
    // make the radio buttons
    for (String name : installedLAFs.keySet()) {
        JRadioButton jmi = new JRadioButton(name);
        panelLayout->addWidget(jmi);
        LAFGroup.add(jmi);
        jmi.setActionCommand(name);
        jmi.addActionListener((ActionEvent e) -> {
            this.dirty = true;
        });
        if (installedLAFs.get(name).equals(UIManager.getLookAndFeel().getClass().getName())) {
            jmi.setSelected(true);
        }
    }
#else
 QRadioButton* jmi = new QRadioButton("Metal");
 jmi->setChecked(true);
 panelLayout->addWidget(jmi);
 LAFGroup->addButton(jmi);
#endif
}

/**
 * Create and return a QWidget* for configuring default local.
 * <P>
 * Most of the action is handled in a separate thread, which replaces the
 * contents of a JComboBox when the list of Locales is available.
 *
 * @return the panel
 */
/*public*/ QWidget* GuiLafConfigPane::doLocale()
{
    QWidget* panel = new QWidget();
    // add JComboBoxen for language and country
    FlowLayout* panelLayout;
    panel->setLayout(panelLayout =new FlowLayout());
    panelLayout->addWidget(localeBox);
#if 0
    // create object to find locales in new Thread
    Runnable r = () -> {
        Locale[] locales = Locale.getAvailableLocales();
        String[] localeNames = new String[locales.length];
        for (int i = 0; i < locales.length; i++) {
            locale.put(locales[i].getDisplayName(), locales[i]);
            localeNames[i] = locales[i].getDisplayName();
        }
        Arrays.sort(localeNames);
        Runnable update = () -> {
            localeBox.setModel(new DefaultComboBoxModel<>(localeNames));
            //localeBox.setModel(new javax.swing.DefaultComboBoxModel(locale.keySet().toArray()));
            localeBox.setSelectedItem(Locale.getDefault().getDisplayName());
        };
        SwingUtilities.invokeLater(update);
    };
    new Thread(r).start();
#endif
 QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
 foreach (QLocale l, allLocales)
 {
    localeBox->addItem(l.name());
 }
 localeBox->setCurrentIndex(localeBox->findText(QLocale::system().name()));
 return panel;
}

/*public*/ void GuiLafConfigPane::setLocale(QString loc) {
    localeBox->setCurrentIndex(localeBox->findText(loc));
}

/**
 * Get the currently configured Locale or Locale.getDefault if no
 * configuration has been done.
 *
 * @return the in-use Locale
 */
//@Override
/*public*/ QLocale* GuiLafConfigPane::getLocale()
{
 QLocale* desired = new QLocale(localeBox->currentText());
    return (desired != NULL) ? desired : new QLocale(QLocale::system());
}

/*static*/ int GuiLafConfigPane::fontSize = 0;

/*public*/ /*static*/ void GuiLafConfigPane::setFontSize(int size) {
    fontSize = size < 9 ? 9 : size > 18 ? 18 : size;
    //fontSizeComboBox.setSelectedItem(fontSize);
}

/*public*/ /*static*/ int GuiLafConfigPane::getFontSize() {
    return fontSize;
}

/*private*/ int GuiLafConfigPane::getDefaultFontSize()
{
 if (getFontSize() == 0)
 {
#if 0
        java.util.Enumeration<Object> keys = UIManager.getDefaults().keys();
        while (keys.hasMoreElements()) {
            Object key = keys.nextElement();
            Object value = UIManager.get(key);

            if (value instanceof javax.swing.plaf.FontUIResource && key.toString().equals("List.font")) {
                Font f = UIManager.getFont(key);
                log.debug("Key:" + key.toString() + " Font: " + f.getName() + " size: " + f.getSize());
                return f.getSize();
            }
        }
#endif
        return 11;	// couldn't find the default return a reasonable font size
    }
    return getFontSize();
}

/*private*/ /*static*/ /*final*/ QStringList GuiLafConfigPane::fontSizes = QStringList() <<                                                                       "9" <<                                                                                 "10" <<                                                                                 "11" <<                                                                                                                                                        "12" <<                                                                                                                                                      "13" <<                                                                                                                                                        "14" <<                                                                                                                                                        "15" <<                                                                                                                                                        "16" <<                                                                                                                                                        "17" <<                                                                                                                                                        "18";

// /*static*/ QComboBox* GuiLafConfigPane::fontSizeComboBox = new QComboBox(/*fontSizes*/);
//GuiLafConfigPane::fontSizeComboBox->addItems(GuiLafConfigPane::fontSizes);
// /*static*/ ActionListener* GuiLafConfigPane::listener = NULL;

/*public*/ void GuiLafConfigPane::doFontSize(QWidget* panel)
{
    FlowLayout* panelLayout;
    panel->setLayout(panelLayout =new FlowLayout());

 QLabel* fontSizeLabel = new QLabel(tr("Select font size"));
    //fontSizeComboBox.removeActionListener(listener);
    fontSizeComboBox->setCurrentIndex(fontSizeComboBox->findText(QString::number(getDefaultFontSize())));
    QLabel* fontSizeUoM = new QLabel(tr("points"));

    panelLayout->addWidget(fontSizeLabel);
    panelLayout->addWidget(fontSizeComboBox);
    panelLayout->addWidget(fontSizeUoM);

//    fontSizeComboBox.addActionListener(listener = (ActionEvent e) -> {
//        setFontSize((Integer) fontSizeComboBox.getSelectedItem());
//        this.dirty = true;
//    });
    connect(fontSizeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_fontSizeConboBox_currentIndexChanged(QString)));
}
void GuiLafConfigPane::On_fontSizeConboBox_currentIndexChanged(QString txt)
{
 setFontSize(txt.toInt());
 this->dirty = true;
}

/*public*/ QString GuiLafConfigPane::getClassName()
{
 if(LAFGroup->checkedButton()== NULL)
  return "Metal";
 return LAFGroup->checkedButton()->text();
}

//@Override
/*public*/ QString GuiLafConfigPane::getPreferencesItem() {
    return "DISPLAY"; // NOI18N
}

//@Override
/*public*/ QString GuiLafConfigPane::getPreferencesItemText() {
    return tr("Display"); // NOI18N
}

//@Override
/*public*/ QString GuiLafConfigPane::getTabbedPreferencesTitle() {
    return tr("GUI"); // NOI18N
}

//@Override
/*public*/ QString GuiLafConfigPane::getLabelKey() {
    return tr("Select your preferred appearance for buttons, menus, etc."); // NOI18N
}

//@Override
/*public*/ QWidget* GuiLafConfigPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool GuiLafConfigPane::isPersistant() {
    return true;
}

//@Override
/*public*/ QString GuiLafConfigPane::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void GuiLafConfigPane::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool GuiLafConfigPane::isDirty() {
    return (this->dirty
//            || SwingSettings.getNonStandardMouseEvent() != mouseEvent.isSelected()
//            || !QLocale::system()==(this->locale.get(this.localeBox.getSelectedItem().toString()))
            );
}

//@Override
/*public*/ bool GuiLafConfigPane::isRestartRequired() {
    return this->isDirty(); // all changes require a restart
}
