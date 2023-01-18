#include "jmriconfigurationmanager.h"
#include "profilemanager.h"
#include "configxmlmanager.h"
#include "profile.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "file.h"
#include "preferencesmanager.h"
#include "serviceloader.h"
#include "jlist.h"
#include <QMessageBox>
#include <QApplication>
#include <QLayout>
#include <QLabel>
#include "configxmlmanager.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "appsbase.h"
#include "editconnectionpreferencesdialog.h"
#include "joptionpane.h"
#include "tabbedpreferencesaction.h"
#include "vptr.h"
#include "loggerfactory.h"
#include "preferencespanel.h"
#include "storexmluseraction.h"
#include "jfilechooser.h"
#include <QVector>
#include "vptr.h"
#include "transferactionlistener.h"
#include "jlisttablemodel.h"
#include "system.h"
#include <QClipboard>
#include "hasconnectionbutunabletoconnectexception.h"
#include "abstractpreferencesmanager.h"
#include "jmripreferencesactionfactory.h"
#include "atomic"
#include "guilafpreferencesmanager.h"
#include "systemconsolepreferencesmanager.h"
#include "class.h"

//JmriConfigurationManager::JmriConfigurationManager()
//{

//}
/**
 *
 * @author Randall Wood
 */
// /*public*/ class JmriConfigurationManager implements ConfigureManager {

/*private*/ /*final*/ /*static*/ Logger* JmriConfigurationManager::log = LoggerFactory::getLogger("JmriConfigurationManager");

//@SuppressWarnings("unchecked") // For types in InstanceManager.store()
/*public*/ JmriConfigurationManager::JmriConfigurationManager(QObject* parent) : QObject(parent)
{
 setObjectName("JmriConfigurationManager");
 legacy = new ConfigXmlManager();

 //ServiceLoader<PreferencesManager> sl = ServiceLoader.load(PreferencesManager.class);
#if 0
    ServiceLoader<PreferencesManager>* sl = ServiceLoader<PreferencesManager>::load("PreferencesManager");

    for (PreferencesManager pp : sl) {
        InstanceManager.store(pp, PreferencesManager.class);
        for (Class provided : pp.getProvides()) { // use raw class so next line can compile
            InstanceManager.store(provided.cast(pp), provided);
        }
    }
#else
 QList<QString> lst = QList<QString>()
  << "StartupActionsManager" << "GuiLafPreferencesManager" << "SystemConsolePreferencesManager"
     << "FileLocationsPreferences" << "ManagerDefaultSelector" << "WarrantPreferences" << "RosterConfigManager"
     << "ProgrammerConfigManager" << "ConnectionConfigManager" << "JmriJTablePersistenceManager";

 foreach (QString name, lst)
 {
  PreferencesManager* pp;
  if(name != "ManagerDefaultSelector")
   pp = (PreferencesManager*)InstanceManager::getNullableDefault(name);
  else
   pp = (PreferencesManager*)Class::forName(name)->newInstance();
//  QList<PreferencesManager*> l = pp->getProvides();
//  foreach (PreferencesManager* provided, *pp->getProvides())
//  {
//   InstanceManager::store(provided, name);
//  }
  if(pp == NULL)
  {
     continue;
  }
  InstanceManager::store((QObject*)pp->self(), "PreferencesManager");
  QSet<QString> provides;
  QObject* pobj;
  if(QString(pp->self()->metaObject()->className()) == "GuiLafPreferencesManager")
  {
   provides = qobject_cast<GuiLafPreferencesManager*>(pp->self())->getProvides();
   pobj = qobject_cast<GuiLafPreferencesManager*>(pp->self());
  }
  else
   if(QString(pp->self()->metaObject()->className()) == "SystemConsolePreferencesManager")
   {
    provides = qobject_cast<SystemConsolePreferencesManager*>(pp->self())->getProvides();
    pobj = qobject_cast<SystemConsolePreferencesManager*>(pp->self());
   }
  else
   {
   provides = qobject_cast<AbstractPreferencesManager*>(pp->self())->getProvides();
   pobj = qobject_cast<AbstractPreferencesManager*>(pp->self());
   }
  foreach(QString provided, provides)
   InstanceManager::store(pobj, provided);
 }
#endif
 Profile* profile = ProfileManager::getDefault()->getActiveProfile();
 if (profile != nullptr) {
     this->legacy->setPrefsLocation(new File(profile->getPath(), Profile::CONFIG_FILENAME));
 }

//    if (!GraphicsEnvironment.isHeadless()) {
        ConfigXmlManager::setErrorHandler(new DialogErrorHandler());
//    }

}

//@Override
/*public*/ void JmriConfigurationManager::registerPref(QObject* o) {
    //if ((o instanceof PreferencesManager)) {
 if(qobject_cast<PreferencesPanel*>(o))
 {
  this->legacy->registerPref(o);
  return;
 }
 if(qobject_cast<PreferencesManager*>(o) != NULL)
 {
  InstanceManager::store(/*(PreferencesManager*)*/ o, "PreferencesManager");
 }
 this->legacy->registerPref(o);
}

//@Override
/*public*/ void JmriConfigurationManager::removePrefItems() {
    this->legacy->removePrefItems();
}

//@Override
/*public*/ void JmriConfigurationManager::registerConfig(QObject* o) {
    this->legacy->registerConfig(o);
}

//@Override
/*public*/ void JmriConfigurationManager::registerConfig(QObject* o, int x) {
    this->legacy->registerConfig(o, x);
}

//@Override
/*public*/ void JmriConfigurationManager::registerTool(QObject* o) {
    this->legacy->registerTool(o);
}

//@Override
/*public*/ void JmriConfigurationManager::registerUser(QObject* o) {
    this->legacy->registerUser(o);
}

//@Override
/*public*/ void JmriConfigurationManager::registerUserPrefs(QObject* o) {
    this->legacy->registerUserPrefs(o);
}

//@Override
/*public*/ void JmriConfigurationManager::deregister(QObject* o) {
    this->legacy->deregister(o);
}

//@Override
/*public*/ QObject* JmriConfigurationManager::findInstance(QString c, int index) {
    return this->legacy->findInstance(c, index);
}

//@Override
/*public*/ QList<QObject*> JmriConfigurationManager::getInstanceList(QString c) {
    return this->legacy->getInstanceList(c);
}

//@Override
/*public*/ bool JmriConfigurationManager::storeAll(File* file) const {
    return this->legacy->storeAll(file);
}

/**
 * Save preferences. Preferences are saved using either the
 * {@link jmri.util.prefs.JmriConfigurationProvider} or
 * {@link jmri.util.prefs.JmriPreferencesProvider} as appropriate to the
 * register preferences handler.
 */
//@Override
/*public*/ void JmriConfigurationManager::storePrefs()
{
 log->debug("Saving preferences...");
 Profile* profile = ProfileManager::getDefault()->getActiveProfile();
//    InstanceManager::getList(PreferencesManager.class).stream().forEach((o) -> {
//        log.debug("Saving preferences for {}", o.getClass().getName());
//        o.savePreferences(profile);
//    });
 foreach (QObject* o, *InstanceManager::getList("PreferencesManager"))
 {
  log->debug(tr("Saving preferences for %1").arg(o->metaObject()->className()));
  ((AbstractPreferencesManager*)o)->savePreferences(profile);
 }
}

/**
 * Save preferences. This method calls {@link #storePrefs() }.
 *
 * @param file Ignored.
 */
//@Override
/*public*/ void JmriConfigurationManager::storePrefs(File* file) {
    this->storePrefs();
}

//@Override
/*public*/ void JmriConfigurationManager::storeUserPrefs(File* file) {
    this->legacy->storeUserPrefs(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::storeConfig(File* file) {
    return this->legacy->storeConfig(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::storeUser(File* file)
{
    return this->legacy->storeUser(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::load(File* file)  /*throw (JmriException)*/
{
    return this->load(file, false);
}

//@Override
/*public*/ bool JmriConfigurationManager::load( QUrl file)
{
    return this->load(file, false);
}

//@Override
/*public*/ bool JmriConfigurationManager::
load(File* file, bool registerDeferred)  /*throw (JmriConfigureXmlException)*/
{
    return this->load(FileUtil::fileToURL(file), registerDeferred);
}

//@Override
/*public*/ bool JmriConfigurationManager::load(QUrl file, bool registerDeferred)
{
 log->debug(tr("loading %1 ...").arg(file.path()));
 try {
  if (file.isEmpty()
          || (File(file.toDisplayString()).getName() == ("ProfileConfig.xml")) //NOI18N
          || (File(file.toDisplayString()).getName() == (/*Profile::CONFIG*/"profile.xml")))
  {
   Profile* profile = ProfileManager::getDefault()->getActiveProfile();
   QObjectList* providers =  InstanceManager::getList("PreferencesManager");
   //providers.stream().forEach((provider) -> {
   foreach(QObject* provider, *providers)
   {
    //this->initializeProvider((PreferencesManager*)provider, profile);
    if(provider->metaObject()->className() == "GuiLafPreferencesManager")
       this->initializeProvider((GuiLafPreferencesManager*)provider, profile);
    else
     if(provider->metaObject()->className() == "SystemConsolePreferencesManager")
        this->initializeProvider((SystemConsolePreferencesManager*)provider, profile);
     else
      this->initializeProvider((AbstractPreferencesManager*)provider, profile);
   }//);
   //foreach(QObject* provider, *providers)
   if (!this->initializationExceptions.isEmpty())
   {
    handleInitializationExceptions(profile);
   }
   if (!file.isEmpty() && (File(file.toDisplayString())).getName() == ("ProfileConfig.xml"))
   { // NOI18N
    log->debug("Loading legacy configuration...");
    return this->legacy->load(file, registerDeferred);
   }
   return this->initializationExceptions.isEmpty();
  }
 }
 catch (/*URISyntax*/Exception* ex)
 {
     log->error(tr("Unable to get File* for %1").arg(file.toDisplayString()));
     throw new JmriException(ex->getMessage()+ex->getLocalizedMessage());
 }
 // make this url the default "Store Panels..." file
 JFileChooser* ufc = StoreXmlUserAction::getUserFileChooser();
 ufc->setSelectedFile(new File(/*FileUtil::urlToURI(url)*/file.path()));

 return this->legacy->load(file, registerDeferred);
 // return true; // always return true once legacy support is dropped
}

/*private*/ void JmriConfigurationManager::handleInitializationExceptions(Profile* profile) {
//    if (!GraphicsEnvironment.isHeadless()) {

  //bool isUnableToConnect = false;//new AtomicBoolean(false);
  std::atomic<bool> isUnableToConnect(false);

  QList<QString> errors =  QList<QString>();
  //this.initialized.forEach((provider) -> {
  foreach(PreferencesManager* provider, this->initialized)
  {
   QList<Exception*> exceptions;
   if(QString(provider->self()->metaObject()->className())== "GuiLafPreferencesManager")
       exceptions = ((GuiLafPreferencesManager*)provider->self())->getInitializationExceptions(profile);
   else    if(QString(provider->self()->metaObject()->className())== "SystemConsolePreferencesManager")
       exceptions = ((GuiLafPreferencesManager*)provider->self())->getInitializationExceptions(profile);
   else
       exceptions = ((AbstractPreferencesManager*)provider->self())->getInitializationExceptions(profile);
   if (!exceptions.isEmpty()) {
       //exceptions.forEach((exception) -> {
    foreach(Exception* exception, exceptions)
    {
     if (static_cast<HasConnectionButUnableToConnectException*>(exception)) {
         isUnableToConnect=true;
     }
     errors.append(exception->getLocalizedMessage());
    }//);
   } else if (this->initializationExceptions.value(provider) != nullptr) {
       errors.append(this->initializationExceptions.value(provider)->getLocalizedMessage());
   }
  }//);
  QVariant list = getErrorListObject(errors);

  if (isUnableToConnect.load()) {
      handleConnectionError(errors, list);
  } else {
      displayErrorListDialog(list);
  }
//    }
}

/*private*/ QVariant JmriConfigurationManager::getErrorListObject(QList<QString> errors) {
    QVariant list;
    if (errors.size() == 1) {
        list = errors.at(0);
    } else {
        //list = new JList<>(errors.toArray(new String[0]));
     QVector<QString> v = QVector<QString>(errors.size(),"");
        list = VPtr<JList>::asQVariant(new JList(errors));
    }
    return list;
}

/*protected*/ void JmriConfigurationManager::displayErrorListDialog(QVariant list) {
    JOptionPane::showMessageDialog(nullptr,
       QVariantList {
           /*(list instanceof JList)*/VPtr<JList*>::asPtr(list) ? tr("The following errors occurred in the order listed:") : "",
           list,
           "<html><br></html>", // Add a visual break between list of errors and notes // NOI18N
           tr("Please check the logs for more details."), // NOI18N
           tr("The Preferences window will open so this can be fixed."), // NOI18N
       },
       tr("Error initializing %1").arg(QApplication::applicationName()), // NOI18N
       JOptionPane::ERROR_MESSAGE);
#if 1
        ((JmriPreferencesActionFactory*)InstanceManager::getDefault("JmriPreferencesActionFactory"))
                ->getDefaultAction()->actionPerformed(new JActionEvent(this,JActionEvent::ACTION_PERFORMED,""));
#endif
}

/**
 * Show a dialog with options Quit, Restart, Change profile, Edit connections
 * @param errors the list of error messages
 * @param list A JList or a String with error message(s)
 */
/*private*/ void JmriConfigurationManager::handleConnectionError(QList<QString> errors, QVariant list) {
    QList<QString> errorList = errors;

    errorList.append(" "); // blank line below errors
    errorList.append(tr("Please check the logs for more details."));

    QVariantList options = QVariantList {
        tr("Quit %1").arg(QApplication::applicationName()),
        tr("Continue"),
        tr("Edit connections")
    };

 JList* jlist = nullptr;
 if ((jlist = VPtr<JList>::asPtr(list)))
 {
     QMenu* popupMenu = new QMenu();
     QAction* copyMenuItem = new QAction(tr("Copy"),this);
     TransferActionListener* copyActionListener = new TransferActionListener();
     //copyMenuItem->setActionCommand( TransferHandler.getCopyAction().getValue(Action::NAME));
     copyMenuItem->setData("copyAll");
     //copyMenuItem.addActionListener(copyActionListener);
     connect(copyMenuItem, SIGNAL(triggered()), copyActionListener, SLOT(actionPerformed()));
//     if (SystemType.isMacOSX()) {
//         copyMenuItem.setAccelerator(
//                 KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.META_MASK));
//     } else
     {
//         copyMenuItem.setAccelerator(
//                 KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
      copyMenuItem->setShortcut(Qt::Key_C | Qt::ControlModifier);
     }
//     copyMenuItem->setMnemonic(KeyEvent.VK_C);
     copyMenuItem->setEnabled(jlist->getSelectedIndex() != -1);
     popupMenu->addAction(copyMenuItem);

     QAction* copyAllMenuItem = new QAction(tr("Copy all"), this);
//     ActionListener copyAllActionListener = (ActionEvent e) -> {
//         StringBuilder text = new StringBuilder();
//         for (int i=0; i < ((JList)list).getModel().getSize(); i++) {
//             text.append(((JList)list).getModel().getElementAt(i).toString());
//             text.append(System.getProperty("line.separator")); // NOI18N
//         }
//         Clipboard systemClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
//         systemClipboard.setContents(new StringSelection(text.toString()), null);
//     };
     //copyAllMenuItem.setActionCommand("copyAll"); // NOI18N
     copyAllMenuItem->setData("copyAll");
     //copyAllMenuItem.addActionListener(copyAllActionListener);
     connect(copyAllMenuItem, &QAction::triggered, [=]{
      QString text;// = new StringBuilder();
      for (int i=0; i < ((JListTableModel*)jlist->getModel())->getSize(); i++) {
          text.append(((JListTableModel*)jlist->getModel())->getElementAt(i).toString());
          text.append(System::getProperty("line.separator")); // NOI18N
      }
//      Clipboard systemClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
//      systemClipboard.setContents(new StringSelection(text.toString()), null);
      QClipboard* systemClipboard = QGuiApplication::clipboard();
      systemClipboard->setText(text);
     });
     popupMenu->addAction(copyAllMenuItem);

     jlist->setComponentPopupMenu(popupMenu);

     //jlist->addListSelectionListener((ListSelectionEvent e) -> {
//         copyMenuItem->setEnabled(((JList*)e.getSource()).getSelectedIndex() != -1);
//     });
     jlist->addListSelectionListener(new ListSelectionListener1(copyMenuItem, this));

 }

 JOptionPane* pane = new JOptionPane(
     QVariantList() = {
         (VPtr<QWidget>::asPtr(list)) ? tr("The following errors occurred in the order listed:") : nullptr,
         list,
         "<html><br></html>", // Add a visual break between list of errors and notes // NOI18N
         tr("Please check the logs for more details."), // NOI18N
         tr("If you need to plug in or turn on anything, do so before restarting"), // NOI18N
     },
     JOptionPane::ERROR_MESSAGE,
     JOptionPane::DEFAULT_OPTION,
     QIcon(),
     options
  );


 JDialog* dialog = pane->createDialog(nullptr, tr("Error initializing %1").arg(QApplication::applicationName())); // NOI18N
 dialog->setModal(false);
 dialog->setVisible(true);
 int i = dialog->exec();
 pane->setValue(pane->getOptions().at(i));
 QVariant selectedValue = pane->getValue();

 handleRestartSelection(selectedValue);

}

/*private*/ void JmriConfigurationManager::handleRestartSelection(QVariant selectedValue) {
    if (tr("Quit %1").arg(QApplication::applicationName())== (selectedValue)) {
        // Exit program
        handleQuit();

    } else if (tr("Continue") == (selectedValue)) {
        // Do nothing. Let the program continue

    } else if (tr("Edit connections") ==(selectedValue)) {
       if (isEditDialogRestart()) {
           handleRestart();
       } else {
            // Quit program
            handleQuit();
        }

    } else {
        // Exit program
        handleQuit();
    }
}
/*protected*/ bool JmriConfigurationManager::isEditDialogRestart() {
    return false;
}

/*protected*/ void JmriConfigurationManager::handleRestart() {
    // Restart program
    try {
        ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->restart();
    } catch (Exception* er) {
        log->error("Continuing after error in handleRestart", er);
    }
}

/*private*/ JOptionPane* JmriConfigurationManager::getJOptionPane(QVariant list, QVariantList options) {
 JOptionPane* pane = new JOptionPane(
           QVariantList() = {
               (VPtr<JList>::asPtr(list)) ? tr("The following errors occurred in the order listed:") : nullptr,
               list,
               "<html><br></html>", // Add a visual break between list of errors and notes // NOI18N
               tr("Please check the logs for more details."), // NOI18N
               tr("If you need to plug in or turn on anything, do so before restarting"), // NOI18N
           },
           JOptionPane::ERROR_MESSAGE,
           JOptionPane::DEFAULT_OPTION,
           QIcon(),
           options
   );
}

/*protected*/ void JmriConfigurationManager::handleQuit(){
    try {
        ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->shutdown();
    } catch (Exception* e) {
        log->error("Continuing after error in handleQuit", e);
    }
}

//@Override
/*public*/ bool JmriConfigurationManager::loadDeferred(File* file)  /*throw (JmriException)*/
{
    return this->legacy->loadDeferred(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::loadDeferred( QUrl file)
{
    return this->legacy->loadDeferred(file);
}

//@Override
/*public*/  QUrl JmriConfigurationManager::find(QString filename) {
    return this->legacy->find(filename);
}

//@Override
/*public*/ bool JmriConfigurationManager::makeBackup(File* file) const {
    return this->legacy->makeBackup(file);
}

/*private*/ void JmriConfigurationManager::initializeProvider( PreferencesManager* provider, Profile* profile)
{
 if (!initializing.contains(provider) && !provider->isInitialized(profile) && !provider->isInitializedWithExceptions(profile)) {
  initializing.insert(provider);
  log->debug(tr("Initializing provider %1").arg(provider->self()->metaObject()->className()));
//  provider.getRequires()
//          .forEach(c -> InstanceManager.getList(c)
//                  .forEach(p -> initializeProvider(p, profile)));
  QSet<QString> requires;// = provider->getRequires();
  if(QString(provider->self()->metaObject()->className()) == "GuiLafPreferencesManager")
   requires = qobject_cast<GuiLafPreferencesManager*>(provider->self())->getProvides();
  else
   if(QString(provider->self()->metaObject()->className()) == "SystemConsolePreferencesManager")
    requires = qobject_cast<SystemConsolePreferencesManager*>(provider->self())->getProvides();
  else
   requires = qobject_cast<AbstractPreferencesManager*>(provider->self())->getProvides();
  foreach(QString c, requires )
  {
   foreach(QObject* obj, *InstanceManager::getList(c))
   {
    PreferencesManager* p = (PreferencesManager*)obj;
    initializeProvider(p, profile);
   }
  }
  try {
      //provider->initialize(profile);
   if(QString(provider->self()->metaObject()->className()) == "GuiLafPreferencesManager")
    ((GuiLafPreferencesManager*)provider->self())->initialize(profile);
   else
    if(QString(provider->self()->metaObject()->className()) == "SystemConsolePreferencesManager")
     ((SystemConsolePreferencesManager*)provider->self())->initialize(profile);
   else
    ((AbstractPreferencesManager*)provider->self())->initialize(profile);
  } catch (InitializationException* ex) {
      // log all initialization exceptions, but only retain for GUI display the
      // first initialization exception for a provider
      //if (this->initializationExceptions.putIfAbsent(provider, ex) == null) {
      if(!this->initializationExceptions.contains(provider))
       this->initializationExceptions.insert(provider,ex);
      if(this->initializationExceptions.count() == 1)
      {
          log->error(tr("Exception initializing %1: %2").arg(provider->self()->metaObject()->className(), ex->getMessage()));
      } else {
          log->error(tr("Additional exception initializing %1: %2").arg(provider->self()->metaObject()->className(), ex->getMessage()));
      }
  }
  this->initialized.append(provider);
  log->debug(tr("Initialized provider %1").arg(provider->self()->metaObject()->className()));
  initializing.remove(provider);
 }
}

/*public*/ QHash<PreferencesManager*, InitializationException*> JmriConfigurationManager::getInitializationExceptions() {
    return QHash<PreferencesManager*, InitializationException*> (initializationExceptions);
}

//@Override
/*public*/ void JmriConfigurationManager::setValidate(XmlFile::Validate v) {
    legacy->setValidate(v);
}

//@Override
/*public*/ XmlFile::Validate JmriConfigurationManager::getValidate() {
    return legacy->getValidate();
}

#if 0

//private static final class ErrorDialog extends JDialog {

//    enum Result {
//        EXIT_PROGRAM,
//        RESTART_PROGRAM,
//        NEW_PROFILE,
//        EDIT_CONNECTIONS,
//    }


//    Result result = Result.EXIT_PROGRAM;

ErrorDialog::ErrorDialog(QStringList list) : JDialog()
{
    //super();
    result = Result::EXIT_PROGRAM;

    setTitle(tr("JMRI is unable to connect"));
    setModal(true);
    QWidget* contentPanel = new QWidget();
    //contentPanel.setLayout(new BoxLayout(contentPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* contentPanelLayout = new QVBoxLayout(contentPanel);
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("The following errors occurred in the order listed:")));
    contentPanelLayout->addWidget(panel);

    QWidget* marginPanel = new QWidget();
    QVBoxLayout* marginPanelLayout = new QVBoxLayout(marginPanel);
//    marginPanel.setAlignmentX(java.awt.Component.CENTER_ALIGNMENT);
//    marginPanel.setBorder(javax.swing.BorderFactory.createEmptyBorder(5,5,5,5));
    contentPanelLayout->addWidget(marginPanel);
    QFrame* borderPanel = new QFrame();
    QVBoxLayout* borderPanelLayout= new QVBoxLayout(borderPanel);
//    borderPanel.setAlignmentX(java.awt.Component.CENTER_ALIGNMENT);
//    borderPanel.setBorder(javax.swing.BorderFactory.createLineBorder(java.awt.Color.black));
    marginPanelLayout->addWidget(borderPanel);
    panel = new QWidget();
//    panel.setAlignmentX(java.awt.Component.CENTER_ALIGNMENT);
//    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
//    panel.setBorder(javax.swing.BorderFactory.createEmptyBorder(5,5,5,5));
    for (QString s : list) {
        // Remove html
        s = s.replace("\\<html\\>.*\\<\\/html\\>", "");
        QLabel* label = new QLabel(s);
        //label.setAlignmentX(java.awt.Component.CENTER_ALIGNMENT);
        panelLayout->addWidget(label, 0, Qt::AlignHCenter);
    }
    borderPanelLayout->addWidget(panel);

    panel = new QWidget();
    QPushButton* button = new QPushButton(tr("Exit program"));
//    button.addActionListener((ActionEvent a) -> {
//        result = Result.EXIT_PROGRAM;
//        dispose();
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(onExitProgram()));
    panelLayout->addWidget(button);

    button = new QPushButton(tr("Restart program"));
//    button.addActionListener((ActionEvent a) -> {
//        result = Result.RESTART_PROGRAM;
//        dispose();
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(onRestartProgram()));
    panelLayout->addWidget(button);

    button = new QPushButton(tr("Start with new profile"));
//    button.addActionListener((ActionEvent a) -> {
//        result = Result.NEW_PROFILE;
//        dispose();
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(onRestartProgram()));
    panelLayout->addWidget(button);

    button = new QPushButton(tr("Edit connections"));
//    button.addActionListener((ActionEvent a) -> {
//        result = Result.EDIT_CONNECTIONS;
//        dispose();
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(onRestartProgram()));
    panelLayout->addWidget(button);

    contentPanelLayout->addWidget(panel);

    //setContentPane(contentPanel);
    setLayout(new QVBoxLayout());
    layout()->addWidget(contentPanel);
    pack();

    // Center dialog on screen
    setLocationRelativeTo(nullptr);
    setVisible(true);
}

void ErrorDialog::onExitProgram()
{
 result = Result::EXIT_PROGRAM;
 dispose();
}

void ErrorDialog::onRestartProgram()
{
 result = Result::RESTART_PROGRAM;
 dispose();
}

void ErrorDialog::onNewProfile()
{
 result = Result::NEW_PROFILE;
 dispose();
}
void ErrorDialog::onEditConnections()
{
 result = Result::EDIT_CONNECTIONS;
 dispose();
}
#endif
