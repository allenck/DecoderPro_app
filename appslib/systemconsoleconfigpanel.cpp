#include "systemconsoleconfigpanel.h"
#include "systemconsole.h"
#include "instancemanager.h"
#include "jtogglebutton.h"
#include "controlpanel.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QLabel>
#include <QComboBox>
#include "rosterentry.h"
#include <QFontDatabase>

//SystemConsoleConfigPanel::SystemConsoleConfigPanel(QObject *parent) :
//  PreferencesPanel(parent)
//{
//}
/**
 *
 */
///*private*/ static final long serialVersionUID = 2050602237831555417L;

///*private*/ static final ResourceBundle rbc = ResourceBundle.getBundle("apps.AppsConfigBundle");
/*private*/ /*static final*/ QList<int> SystemConsoleConfigPanel::fontSizes  = QList<int>() << 6 <<
    8 <<
    9 <<
    10 <<
    11 <<
    12 <<
    13 <<
    14 <<
    16 <<
    18 <<
    20 <<
    24;

/*private*/ /*static final*/ QList<int>  SystemConsoleConfigPanel::wrapStyles = QList<int>() <<
    SystemConsole::WRAP_STYLE_NONE <<
    SystemConsole::WRAP_STYLE_LINE <<
    SystemConsole::WRAP_STYLE_WORD;

/*private*/ /*static final*/ QStringList SystemConsoleConfigPanel::wrapStyleNames = QStringList() <<
    tr("No text wrapping") <<
    tr("Wrap text at end of line")<<
    tr("Wrap text at end of last word");

///*private*/ /*static*/ /*final*/ JToggleButton* SystemConsoleConfigPanel::fontStyleBold = new JToggleButton("B");

///*private*/ /*static*/ /*final*/ JToggleButton* SystemConsoleConfigPanel::fontStyleItalic = new JToggleButton("I");

///*private*/ /*static*/ /*final*/ QComboBox SystemConsoleConfigPanel::schemes = new QComboBox;//<ControlPanel::Scheme*>(SystemConsole::getInstance()->getSchemes());

///*private*/ /*static*/ /*final*/ QComboBox* SystemConsoleConfigPanel::fontFamily = new QComboBox(); //FontComboUtil.getFontCombo(FontComboUtil.MONOSPACED, 14);

///*private*/ static /*final*/ QComboBox* SystemConsoleConfigPanel::fontSize = new QComboBox<int>(fontSizes);


/*public*/  SystemConsoleConfigPanel::SystemConsoleConfigPanel(QWidget *parent) :
  QWidget(parent)
{
 setObjectName("SystemConsoleConfigPanel");
 setProperty("JavaPackageName", "apps.SystemConsoleConfigPanel");

 fontStyleBold = new JToggleButton("B");

 fontStyleItalic = new JToggleButton("I");

 QComboBox* schemes = new QComboBox();
 QList<SystemConsole::Scheme*>* schemeList = SystemConsole::getInstance()->getSchemes();
 foreach( SystemConsole::Scheme* scheme, *schemeList)
 {
  schemes->addItem(scheme->description, VPtr<SystemConsole::Scheme>::asQVariant(scheme));
 }

 fontSize = new QComboBox;
 foreach(int fontsize, fontSizes)
 {
  fontSize->addItem(QString::number(fontsize), fontsize);
 }

 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 //QWidget* p = new QWidget();
 FlowLayout* pLayout = new FlowLayout();
 pLayout->addWidget(new QLabel(tr("Console color scheme")));

 schemes->setCurrentIndex(SystemConsole::getInstance()->getScheme());
// schemes.addActionListener((ActionEvent e) -> {
//     SystemConsole.getInstance().setScheme(schemes.getSelectedIndex());
// });
 connect(schemes, SIGNAL(currentIndexChanged(int)), this, SLOT(On_Schemes(int)));
#if 0
 schemes.setRenderer((JList<? extends Scheme> list, Scheme scheme, int index, bool isSelected, bool hasFocus) -> {
        QWidget p1 = new QWidget();
        p1.setOpaque(index > -1);
        if (isSelected && index > -1) {
            p1.setBackground(list.getSelectionBackground());
            p1.setForeground(list.getSelectionForeground());
        } else {
            p1.setBackground(list.getBackground());
            p1.setForeground(list.getForeground());
        }
        JLabel l = new JLabel(" " + scheme.description + " ");
        l.setOpaque(true);
        l.setFont(new Font("Monospaced", SystemConsole.getInstance().getFontStyle(), 12));
        l.setForeground(scheme.foreground);
        l.setBackground(scheme.background);
        p1.add(l);
        // 'Oribble hack as CDE/Motif JComboBox doesn't seem to like
        // displaying QWidget objects in the JComboBox header
        if (UIManager.getLookAndFeel().getName().equals("CDE/Motif") && index == -1) {
            return l;
        }
        return p1;
    });
#endif
 pLayout->addWidget(schemes);
 thisLayout->addLayout(pLayout);

    //p = new QWidget(new FlowLayout());
 {
  FlowLayout* pLayout = new FlowLayout;

//  fontFamily.addActionListener((ActionEvent e) -> {
//        SystemConsole.getInstance().setFontFamily((String) fontFamily.getSelectedItem());
//        schemes.repaint();
//    });
  fontFamily = new QComboBox(); //FontComboUtil.getFontCombo(FontComboUtil.MONOSPACED, 14);
  QFontDatabase* fdb = new QFontDatabase();
  QStringList fAll = fdb->families();
  QStringList families;
  foreach (QString family, fAll)
  {
   if(fdb->isFixedPitch(family))
    families.append(family);
  }
  fontFamily->addItems(families);
  fontFamily->setCurrentIndex(fontFamily->findText(SystemConsole::getInstance()->getFontFamily()));

  connect(fontFamily, SIGNAL(currentIndexChanged(int)), this, SLOT(On_fontFamily(int)));

  QLabel* fontFamilyLabel = new QLabel(tr("Select font style"));
  //fontFamilyLabel->setLabelFor(fontFamily);

  pLayout->addWidget(fontFamilyLabel);
  pLayout->addWidget(fontFamily);

//  fontSize.addActionListener((ActionEvent e) -> {
//        SystemConsole.getInstance().setFontSize((Integer) fontSize.getSelectedItem());
//    });

  connect(fontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(On_fontSize(int)));
  fontSize->setToolTip(tr("Select font size"));
  fontSize->setCurrentIndex(fontSize->findText(QString::number(SystemConsole::getInstance()->getFontSize())));
  QLabel* fontSizeUoM = new QLabel(tr("points"));

  pLayout->addWidget(fontSize);
  pLayout->addWidget(fontSizeUoM);

  QFont f = fontStyleBold->font();
  f.setWeight(QFont::Bold);
  fontStyleBold->setFont(f);
//    fontStyleBold.addActionListener((ActionEvent e) -> {
//        doFontStyle();
//    });
  connect(fontStyleBold, SIGNAL(toggled(bool)), this, SLOT(doFontStyle()));
  fontStyleBold->setToolTip(tr("Bold"));
  fontStyleBold->setSelected((SystemConsole::getInstance()->getFontStyle() & SystemConsole::BOLD) == SystemConsole::BOLD);
  pLayout->addWidget(fontStyleBold);

  f= fontStyleItalic->font();
  f.setStyle(QFont::StyleItalic);
  fontStyleItalic->setFont(f);
  //fontStyleItalic.setFont(fontStyleItalic.getFont().deriveFont(Font.ITALIC));
//  fontStyleItalic.addActionListener((ActionEvent e) -> {
//        doFontStyle();
//    });
  connect(fontStyleItalic, SIGNAL(toggled(bool)), this, SLOT(doFontStyle()));
  fontStyleItalic->setChecked((SystemConsole::getInstance()->getFontStyle() & SystemConsole::ITALIC) == SystemConsole::ITALIC);
  fontStyleItalic->setToolTip(tr("Italic"));
  pLayout->addWidget(fontStyleItalic);

  thisLayout->addLayout(pLayout);
 }
 {
  //p = new QWidget(new FlowLayout());
  FlowLayout* pLayout = new FlowLayout;
  /*final*/ QComboBox* wrapStyle = new QComboBox;//(wrapStyleNames);
  wrapStyle->addItems(wrapStyleNames);
//    wrapStyle.addActionListener((ActionEvent e) -> {
//        SystemConsole.getInstance().setWrapStyle(wrapStyles[wrapStyle.getSelectedIndex()]);
//    });
  connect(wrapStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(On_wrapStyle(int)));
  wrapStyle->setCurrentIndex(SystemConsole::getInstance()->getWrapStyle());

  pLayout->addWidget(new QLabel(tr("Select text wrapping style")));
  pLayout->addWidget(wrapStyle);
  thisLayout->addLayout(pLayout);

//    p = new QWidget();
//    p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
  }

    thisLayout->addLayout(pLayout);

}
void SystemConsoleConfigPanel::On_Schemes(int i)
{
 SystemConsole::getInstance()->setScheme(i);
}
void SystemConsoleConfigPanel::On_fontFamily(int)
{
 SystemConsole::getInstance()->setFontFamily( fontFamily->currentText());
 //schemes.repaint();
}
void SystemConsoleConfigPanel::On_fontSize(int i)
{
 if(i >= 0)
 SystemConsole::getInstance()->setFontSize(fontSizes.at(i));
}
void SystemConsoleConfigPanel::On_wrapStyle(int i)
{
 SystemConsole::getInstance()->setWrapStyle(wrapStyles[i]);

}

/*private*/ /*static*/ void SystemConsoleConfigPanel::doFontStyle() {
    SystemConsole::getInstance()->setFontStyle(
            (fontStyleBold->isChecked() ? SystemConsole::BOLD : SystemConsole::PLAIN)
            | (fontStyleItalic->isChecked() ? SystemConsole::ITALIC : SystemConsole::PLAIN));
//    schemes.repaint();
}

//@Override
/*public*/  QString SystemConsoleConfigPanel::getPreferencesItem() {
    return "DISPLAY"; // NOI18N
}

//@Override
/*public*/  QString SystemConsoleConfigPanel::getPreferencesItemText() {
    return tr("MenuDisplay"); // NOI18N
}

//@Override
/*public*/  QString SystemConsoleConfigPanel::getTabbedPreferencesTitle() {
    return tr("Console"); // NOI18N
}

//@Override
/*public*/  QString SystemConsoleConfigPanel::getLabelKey() {
    return tr("Select your preferred appearance for the JMRI System Console"); // NOI18N
}

//@Override
/*public*/  QWidget* SystemConsoleConfigPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/  bool SystemConsoleConfigPanel::isPersistant() {
    return true;
}

//@Override
/*public*/  QString SystemConsoleConfigPanel::getPreferencesTooltip() {
 return "";
}

//@Override
/*public*/  void SystemConsoleConfigPanel::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/  bool SystemConsoleConfigPanel::isDirty() {
    // console preferences take effect immediately, but are not saved
    // immediately, so we can't tell without rereading the preferences.xml,
    // but it's to expensive to read that file to determine if it matches
    // the in memory preferences for this console, so simply return false
    return false;
}

//@Override
/*public*/  bool SystemConsoleConfigPanel::isRestartRequired() {
    // since changes are applied immediately, this is not required
    return false;
}

//@Override
/*public*/  bool SystemConsoleConfigPanel::isPreferencesValid() {
    return true; // no validity checking performed
}
