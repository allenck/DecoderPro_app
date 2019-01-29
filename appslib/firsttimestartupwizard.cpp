#include "firsttimestartupwizard.h"
#include "loggerfactory.h"
#include "jmrixconfigpane.h"
#include "jmrijframe.h"
#include "apps3.h"
#include <QLabel>
#include <QComboBox>
#include <QBoxLayout>
#include "fileutil.h"
#include "imageicon.h"
#include "flowlayout.h"
#include "jtextfield.h"
#include "rosterconfigmanager.h"
#include "instancemanager.h"
#include "system.h"
#include "jtextarea.h"
#include <QApplication>
#include <QFrame>
#include <QPushButton>
#include "configuremanager.h"
#include "abstractconnectionconfig.h"
#include <QComboBox>
#include "joptionpane.h"
#include "profilemanager.h"
#include "guilafpreferencesmanager.h"

// /*public*/ class FirstTimeStartUpWizard {


/*public*/ FirstTimeStartUpWizard::FirstTimeStartUpWizard(JmriJFrame* parent, Apps3* app) : QObject(parent)
{
 connectionConfigPane = JmrixConfigPane::createNewPanel();
 header = new QLabel();
 wizPage = QList<WizardPage*>();
 entryPanel = new QWidget();
 entryPanelLayout = new QVBoxLayout(entryPanel);
 helpPanel = new QWidget();
 minHelpFieldDim = QSize(160, 20);
 maxHelpFieldDim = QSize(160, 300);
 owner = new JTextField(20);
 currentScreen = 0;
 mainWizardPanel = new QWidget();

    this->parent = parent;
    this->app = app;
 QVBoxLayout* mainWizardPanelLayout;
    mainWizardPanel->setLayout(mainWizardPanelLayout = new QVBoxLayout()); //new BorderLayout());
    mainWizardPanelLayout->addWidget(createTopBanner(), 0, Qt::AlignTop);//BorderLayout.NORTH);

    mainWizardPanelLayout->addWidget(createHelpPanel(), 0, Qt::AlignLeft);//BorderLayout.WEST);

    mainWizardPanelLayout->addWidget(createEntryPanel(), 0, Qt::AlignCenter); // BorderLayout.CENTER);

    mainWizardPanelLayout->addWidget(createButtonPanel(),0, Qt::AlignBottom);// BorderLayout.SOUTH);
}


QWidget* FirstTimeStartUpWizard::createTopBanner() {
    QWidget* top = new QWidget();
    QHBoxLayout* topLayout = new QHBoxLayout(top);
    header->setText("Welcome to JMRI StartUp Wizard");
    topLayout->addWidget(header);

    return top;
}

QWidget* FirstTimeStartUpWizard::createHelpPanel() {
    //splashIm = Toolkit.getDefaultToolkit().getImage(FileUtil::findURL("resources/logo.gif", FileUtil::Location::INSTALLED));
    splashIm = QImage(FileUtil::findURL("resources/logo.gif", FileUtil::Location::INSTALLED).toString());
    ImageIcon* img = new ImageIcon(splashIm, "JMRI splash screen");
    int imageWidth = img->getIconWidth();
    minHelpFieldDim = QSize(imageWidth, 20);
    maxHelpFieldDim = QSize((imageWidth + 20), 350);
    helpPanel->resize(maxHelpFieldDim);
    helpPanel->setMaximumSize(maxHelpFieldDim);
    QVBoxLayout* helpPanelLayout;
    helpPanel->setLayout(helpPanelLayout =
            new QVBoxLayout(helpPanel)); //, BoxLayout.Y_AXIS));

    QLabel* l = new QLabel(/*img*/);
    l->setPixmap(QPixmap::fromImage(splashIm));
    //l.setAlignmentX(Component.CENTER_ALIGNMENT);
    //l->setOpaque(false);
    helpPanelLayout->addWidget(l,0,Qt::AlignCenter);
    return helpPanel;
}


void FirstTimeStartUpWizard::createScreens() {
    firstWelcome();
    setDefaultOwner();
    setConnection();
    finishAndConnect();
}

/*public*/ void FirstTimeStartUpWizard::dispose() {
    QCursor normalCursor = QCursor(Qt::ArrowCursor);//Cursor(Cursor.DEFAULT_CURSOR);
    parent->setCursor(normalCursor);
    app->createAndDisplayFrame();
    parent->setVisible(false);
    parent->dispose();
}


QWidget* FirstTimeStartUpWizard::createEntryPanel() {
    createScreens();
    for (int i = 0; i < wizPage.size(); i++) {
        entryPanelLayout->addWidget(wizPage.at(i)->getPanel());
        helpPanel->layout()->addWidget(wizPage.at(i)->getHelpDetails());
    }
    wizPage.at(0)->getPanel()->setVisible(true);
    wizPage.at(0)->getHelpDetails()->setVisible(true);
    //header->setFont(header->getFont().deriveFont(14f));
    QFont f = header->font();
    f.setPointSize(14);
    header->setFont(f);
    return entryPanel;
}

void FirstTimeStartUpWizard::setDefaultOwner() {
    QWidget* p = new QWidget();
    QVBoxLayout* pLayout;
    p->setLayout(pLayout =new QVBoxLayout());//(p, BoxLayout.Y_AXIS));
    pLayout->addWidget(formatText("Select your language<br>"));
    initalLocale = QLocale();//Locale.getDefault();
    pLayout->addWidget(doLocale());

    pLayout->addWidget(formatText("<br>Enter in the default owner for all your loco roster entries<p>If you are part of group or club, where different people will be accessing Decoder Pro, then you can leave this blank</p>"));
    QWidget* p2 = new QWidget();
    FlowLayout* p2Layout;
    p2->setLayout(p2Layout=new FlowLayout());
    p2Layout->addWidget(new QLabel(/*rb.getString("LabelDefaultOwner")*/"Default Owner"));

    owner->setText(static_cast<RosterConfigManager*>(InstanceManager::getDefault("RosterConfigManager"))->getDefaultOwner());
    if (owner->text()==("")) {
        owner->setText(System::getProperty("user.name"));
    }
    p2Layout->addWidget(owner);
    pLayout->addWidget(p2);

    wizPage.append(new WizardPage(p, new QWidget(), "Set the Default Language and Owner"));
}

void FirstTimeStartUpWizard::setConnection() {

    QWidget* h = new QWidget();
    QVBoxLayout* hLayout;
    h->setLayout(hLayout=new QVBoxLayout());//(h, BoxLayout.Y_AXIS));
    h->setMaximumSize(maxHelpFieldDim);

    JTextArea* text = new JTextArea("First select the manufacturer of your DCC system\n\nFollowed by the type of connection being used.\n\nFinally select the serial port or enter in the IP address of the device");
    text->setEditable(false);
    text->setLineWrap(true);
    text->setWrapStyleWord(true);
    text->setOpaque(false);
    text->setMinimumSize(minHelpFieldDim);
    text->setMaximumSize(maxHelpFieldDim);
    hLayout->addWidget(text);

    wizPage.append(new WizardPage(this->connectionConfigPane, h, "Select your DCC Connection"));
}

void FirstTimeStartUpWizard::firstWelcome() {
    QWidget* p = new QWidget();
    QVBoxLayout* p2Layout;
    p->setLayout(p2Layout = new QVBoxLayout());//(p, BoxLayout.Y_AXIS));
    p2Layout->addWidget(formatText("Welcome to JMRI's " + QApplication::applicationDisplayName() + "<p><br>This little wizard will help to guide you through setting up " + QApplication::applicationDisplayName() + " for the first time"));

    wizPage.append(new WizardPage(p, new QWidget(), "Welcome to JMRI StartUp Wizard"));
}


void FirstTimeStartUpWizard::finishAndConnect() {
    QWidget* p = new QWidget();
    QVBoxLayout* pLayout;
    p->setLayout(pLayout = new QVBoxLayout());//(p, BoxLayout.Y_AXIS));
    pLayout->addWidget(formatText("Configuration is now all complete, press finish below to connect to your system and start using " + QApplication::applicationDisplayName() + "\n\nIf at any time you need to change your settings, you can find the preference setting under the Edit Menu"));
    wizPage.append(new WizardPage(p, new QWidget(), "Finish and Connect"));
}


QWidget* FirstTimeStartUpWizard::createButtonPanel() {
    QFrame* buttonPanel = new QFrame();
    FlowLayout* buttonPanelLayout;
    buttonPanel->setLayout(buttonPanelLayout= new FlowLayout(/*FlowLayout::RIGHT*/));
    //buttonPanel.setBorder(new BevelBorder(BevelBorder.LOWERED));
    buttonPanel->setFrameShadow(QFrame::Sunken);
    /*final*/ /*QPushButton**/ previous = new QPushButton("< Back");
    /*final*/ /*QPushButton**/ next = new QPushButton("Next >");
    /*final*/ /*QPushButton**/ finish = new QPushButton("Finish");
    finish->setVisible(false);
    QPushButton* cancel = new QPushButton("Cancel");
//    cancel.addActionListener((java.awt.event.ActionEvent e) -> {
//        Locale.setDefault(initalLocale);
//        dispose();
//    });
 connect(cancel, SIGNAL(clicked(bool)), this, SLOT(onCancel()));

//    previous.addActionListener((java.awt.event.ActionEvent e) -> {
//        if (currentScreen < wizPage.size()) {
//            wizPage.value(currentScreen).getPanel().setVisible(false);
//            wizPage.value(currentScreen).getHelpDetails().setVisible(false);
//        }
//        finish.setVisible(false);

//        currentScreen = currentScreen - 1;
//        if (currentScreen != -1) {
//            wizPage.value(currentScreen).getPanel().setVisible(true);
//            wizPage.value(currentScreen).getHelpDetails().setVisible(true);
//            header.setText(wizPage.get(currentScreen).getHeaderText());
//            header.setFont(header.getFont().deriveFont(14f));

//            if (currentScreen == 0) {
//                previous.setEnabled(false);
//            }
//            next.setEnabled(true);
//            next.setVisible(true);
//        } else {
//            currentScreen = 0;
//            previous.setEnabled(false);
//        }
//    });
 connect(previous, SIGNAL(clicked(bool)), this, SLOT(onPrevious()));

//    next.addActionListener((java.awt.event.ActionEvent e) -> {
//        wizPage.value(currentScreen).getPanel().setVisible(false);
//        wizPage.value(currentScreen).getHelpDetails().setVisible(false);
//        currentScreen++;
//        if (currentScreen < wizPage.size()) {
//            wizPage.value(currentScreen).getPanel().setVisible(true);
//            wizPage.value(currentScreen).getHelpDetails().setVisible(true);
//            header.setText(wizPage.get(currentScreen).getHeaderText());
//            header.setFont(header.getFont().deriveFont(14f));
//            previous.setEnabled(true);
//            if (currentScreen == (wizPage.size() - 1)) {
//                next.setEnabled(false);
//                next.setVisible(false);
//                finish.setVisible(true);
//            }
//        }
//    });
 connect(next, SIGNAL(clicked(bool)), this, SLOT(onNext()));

//    finish.addActionListener((java.awt.event.ActionEvent e) -> {
//        Runnable r = new Connect();
//        Thread connectThread = new Thread(r);
//        connectThread.start();
//        connectThread.setName("Start-Up Wizard Connect");
//    });
    connect(finish, SIGNAL(clicked(bool)), this, SLOT(onFinish()));

    buttonPanelLayout->addWidget(previous);
    buttonPanelLayout->addWidget(next);
    buttonPanelLayout->addWidget(new QLabel("     ")); // filler
    buttonPanelLayout->addWidget(finish);
    buttonPanelLayout->addWidget(cancel);
    previous->setEnabled(false);

    return buttonPanel;
}

void FirstTimeStartUpWizard::onCancel()
{
 QLocale::setDefault(initalLocale);
 dispose();
}

void FirstTimeStartUpWizard::onPrevious()
{
 if (currentScreen < wizPage.size()) {
     wizPage.value(currentScreen)->getPanel()->setVisible(false);
     wizPage.value(currentScreen)->getHelpDetails()->setVisible(false);
 }
 finish->setVisible(false);

 currentScreen = currentScreen - 1;
 if (currentScreen != -1) {
     wizPage.value(currentScreen)->getPanel()->setVisible(true);
     wizPage.value(currentScreen)->getHelpDetails()->setVisible(true);
     header->setText(wizPage.value(currentScreen)->getHeaderText());
     //header.setFont(header.getFont().deriveFont(14f));
     QFont f = header->font();
     f.setPointSize(14);
     header->setFont(f);

     if (currentScreen == 0) {
         previous->setEnabled(false);
     }
     next->setEnabled(true);
     next->setVisible(true);
 } else {
     currentScreen = 0;
     previous->setEnabled(false);
 }

}

void FirstTimeStartUpWizard::onNext()
{
 wizPage.value(currentScreen)->getPanel()->setVisible(false);
 wizPage.value(currentScreen)->getHelpDetails()->setVisible(false);
 currentScreen++;
 if (currentScreen < wizPage.size()) {
     wizPage.value(currentScreen)->getPanel()->setVisible(true);
     wizPage.value(currentScreen)->getHelpDetails()->setVisible(true);
     header->setText(wizPage.value(currentScreen)->getHeaderText());
//     header.setFont(header.getFont().deriveFont(14f));
     QFont f = header->font();
     f.setPointSize(14);
     header->setFont(f);

     previous->setEnabled(true);
     if (currentScreen == (wizPage.size() - 1)) {
         next->setEnabled(false);
         next->setVisible(false);
         finish->setVisible(true);
     }
 }

}

void FirstTimeStartUpWizard::onFinish()
{
 //Runnable r = new Connect();
 Connect* _connect = new Connect(this);
 QThread* connectThread = new QThread();
 connect(connectThread, SIGNAL(started()), _connect, SLOT(process()));
 connect(_connect, SIGNAL(finished()), connectThread, SLOT(quit()));
 connectThread->start();
 connectThread->setObjectName("Start-Up Wizard Connect");
}

//The connection process is placed into its own thread so that it doens't hog the swingthread while waiting for the connections to open.
///*protected*/ class Connect implements Runnable {

//    @Override
Connect::Connect(FirstTimeStartUpWizard* wizard) { this->wizard = wizard;}
/*public*/ void Connect::process()
{
        QCursor hourglassCursor = QCursor(Qt::WaitCursor);
        wizard->parent->setCursor(hourglassCursor);
        ConnectionConfig* connect = (ConnectionConfig*)wizard->connectionConfigPane->getCurrentObject();
        ConfigureManager* cm = static_cast<ConfigureManager*>(InstanceManager::getNullableDefault("ConfigureManager"));
        if (cm != nullptr) {
            cm->registerPref(connect);
        }
        if ( qobject_cast<AbstractConnectionConfig*>(connect)) {
            ((AbstractConnectionConfig*) connect)->updateAdapter();
            PortAdapter* adp = connect->getAdapter();
            try {
                adp->_connect();
                adp->configure();
            } catch (Exception ex) {
                wizard->log->error(ex.getLocalizedMessage(), ex);
                QCursor normalCursor = QCursor(Qt::ArrowCursor);//new Cursor(Cursor.DEFAULT_CURSOR);
               wizard-> parent->setCursor(normalCursor);
                JOptionPane::showMessageDialog(nullptr,
                        "An error occurred while trying to connect to " + connect->getConnectionName() + ", press the back button and check the connection details",
                        "Error Opening Connection",
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
        }
        Profile* project = ProfileManager::getDefault()->getActiveProfile();
        static_cast<RosterConfigManager*>(InstanceManager::getDefault("RosterConfigManager"))->setDefaultOwner(wizard->owner->text());
        static_cast<GuiLafPreferencesManager*>(InstanceManager::getDefault("GuiLafPreferencesManager"))->setLocale(QLocale());
        static_cast<RosterConfigManager*>(InstanceManager::getDefault("RosterConfigManager"))->savePreferences(project);
        static_cast<GuiLafPreferencesManager*>(InstanceManager::getDefault("GuiLafPreferencesManager"))->savePreferences(project);
        wizard->connectionConfigPane->savePreferences();
        static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->storePrefs();
        emit finished();
        wizard->dispose();

    }
//};

/*public*/ QWidget* FirstTimeStartUpWizard::doLocale() {
    QWidget* panel = new QWidget();
    FlowLayout* panelLayout;
    // add JComboBoxen for language and country
    panel->setLayout(panelLayout = new FlowLayout());
    localeBox = new QComboBox();
    {
        localeBox->addItem(QLocale::system().nativeLanguageName());
        localeBox->addItem("(Please Wait)");
    }//);
    panelLayout->addWidget(localeBox);

#if 0
    // create object to find locales in new Thread
    Runnable r = () -> {
        Locale[] locales = java.util.Locale.getAvailableLocales();
        localeNames = new String[locales.length];
        locale = new HashMap<>();
        for (int i = 0; i < locales.length; i++) {
            locale.put(locales[i].getDisplayName(), locales[i]);
            localeNames[i] = locales[i].getDisplayName();
        }
        java.util.Arrays.sort(localeNames);
        Runnable update = () -> {
            localeBox.setModel(new javax.swing.DefaultComboBoxModel<>(localeNames));
            localeBox.setSelectedItem(Locale.getDefault().getDisplayName());
        };
        javax.swing.SwingUtilities.invokeLater(update);
    };
    new Thread(r).start();
#endif

FindLocales* findLocales = new FindLocales(this);
QThread* ft = new QThread();
connect(ft, SIGNAL(started()), findLocales, SLOT(process()));
connect(findLocales, SIGNAL(finished()), ft, SLOT(quit()));
connect(findLocales, SIGNAL(update(QMap<QString,QLocale>)), this, SLOT(update(QMap<QString,QLocale>)));
ft->start();


//    localeBox.addActionListener((ActionEvent a) -> {
//        if (localeBox == null || locale == null) {
//            return;
//        }
//        String desired = (String) localeBox.getSelectedItem();
//        Locale.setDefault(locale.get(desired));
//    });
connect(localeBox,SIGNAL(currentIndexChanged(QString)), this, SLOT(onLocaleBox()));

    return panel;
}

void FirstTimeStartUpWizard::update(QMap<QString,QLocale> l)
{
 localeBox->clear();
 QMapIterator<QString,QLocale> iter(l);
 while(iter.hasNext())
 {
  iter.next();
  localeBox->addItem(iter.value().nativeLanguageName(), iter.value());
 }
 localeBox->setCurrentIndex(localeBox->findText(QLocale::system().nativeLanguageName()));
}

FindLocales::FindLocales(FirstTimeStartUpWizard *wizard) { this->wizard = wizard;}
void FindLocales::process()
{

 QList<QLocale> locales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);//java.util.Locale.getAvailableLocales();
 localeNames = QVector<QString>();
 locale = QMap<QString,QLocale>();
 for (int i = 0; i < locales.length(); i++)
 {
  if(!locale.contains(locales[i].languageToString(locales.at(i).language())))
  {
     locale.insert(locales[i].languageToString(locales.at(i).language()), locales[i]);
     localeNames.append(locales[i].languageToString(locales.at(i).language()));
  }
 }
 //java.util.Arrays.sort(localeNames);
// Runnable update = () -> {
//     localeBox.setModel(new javax.swing.DefaultComboBoxModel<>(localeNames));
//     localeBox.setSelectedItem(Locale.getDefault().getDisplayName());
// };
// javax.swing.SwingUtilities.invokeLater(update);
 emit update(locale);
 emit finished();

}

void FirstTimeStartUpWizard::onLocaleBox()
{
 if (localeBox == nullptr || locale.isEmpty()) {
     return;
 }
 QString desired = localeBox->currentText();
 QLocale::setDefault(localeBox->currentData().toLocale());

}


QLabel* FirstTimeStartUpWizard::formatText(QString text) {
    QLabel* label = new QLabel();
    label->setText("<html><body width='450'>" + text + "</html>");
    return label;
}


/*public*/ QWidget* FirstTimeStartUpWizard::getPanel() {
    return mainWizardPanel;
}

//static class WizardPage {

 /*static*/ QSize WizardPage::defaultInfoSize = QSize(500, 300);
//    JComponent panel;
//    QWidget* helpDetails = new JPanel();
//    QString headerText = "";

    WizardPage::WizardPage(QWidget* mainPanel, QWidget* helpDetails, QString headerText) : QObject()
    {

        this->panel = mainPanel;

        if (helpDetails != nullptr) {
            this->helpDetails = helpDetails;
            this->helpDetails->setLayout(
                    new QVBoxLayout()); //(this.helpDetails, BoxLayout.Y_AXIS));
        }
        if (this->panel != nullptr) {
            this->panel->resize(defaultInfoSize);
            this->panel->setVisible(false);
        }
        this->helpDetails->setVisible(false);
        this->headerText = headerText;
    }

    QWidget* WizardPage::getPanel() {
        return panel;
    }

    QWidget* WizardPage::getHelpDetails() {
        return helpDetails;
    }

    QString WizardPage::getHeaderText() {
        return headerText;
    }

//};

/*private*/ /*final*/ /*static*/ Logger* FirstTimeStartUpWizard::log = LoggerFactory::getLogger("FirstTimeStartUpWizard");
