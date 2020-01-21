#include "helputil.h"
#include <QMenuBar>
#include <QMenu>
#include "fileutil.h"
#include <QUrl>
#include <QApplication>
#include <QVBoxLayout>
//#include <QtWebKit/QWebView>
#include <QSignalMapper>
#include <QTextStream>
#include <QStatusBar>
#include <QUrl>
#include <QIcon>
#include <QWebEngineHistory>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include "systemconsoleaction.h"
#include "helpbroker.h"
#include "xmlfilelocationaction.h"
#include "reportcontextaction.h"
#include "exceptions.h"
#include "loggerfactory.h"

/* static private*/ HelpUtil* HelpUtil::thisMenu = NULL;
HelpBroker*  HelpUtil::globalHelpBroker = NULL;

HelpUtil::HelpUtil(QObject *parent) :
    QObject(parent)
{
 thisMenu = NULL;
 _frame = NULL;

}

/*static*/ HelpUtil* HelpUtil::instance()
{
 if (thisMenu==NULL) thisMenu = new HelpUtil();
  return thisMenu;
}

/**
 * Common utility methods for working with Java Help.
 * <P>
 * This class was created to contain common Java Help information.
 * <P>
 * It assumes that Java Help 1.1.8 is in use
 *
 * @author Bob Jacobsen  Copyright 2007
 * @version $Revision: 22529 $
 */

// /*public*/ class HelpUtil {

/**
 * @param direct true if this call should complete the help menu
 * by adding the general help
 * @return new Help menu, in case user wants to add more items
 */
/*static*/ /*public*/ QMenu* HelpUtil::helpMenu(QMenuBar* menuBar, QString ref, bool direct)
{
 QMenu* helpMenu = makeHelpMenu(ref, direct, menuBar->parent());
 menuBar->addMenu(helpMenu);
 return helpMenu;
}

/*static*/ /*public*/ QMenu* HelpUtil::makeHelpMenu(QString ref, bool direct, QObject* parent)
{

// if (!initOK())
// {
//  log.warn("help initialization not completed");
//  return NULL;  // initialization failed
// }
 QSignalMapper* mapper = new QSignalMapper;

 QMenu* helpMenu = new QMenu(tr("Help"));
 QAction* item = makeHelpMenuItem(ref);
 if (item == NULL)
 {
  log->error("Can't make help menu item for "+ref/*, parent*/);
  return NULL;
 }
 helpMenu->addAction(item);
 mapper->setMapping(item,item);
 connect(item, SIGNAL(triggered()), mapper, SLOT(map()));

 if (direct)
 {
  item = new QAction(tr("General Help..."), parent);
//  globalHelpBroker->enableHelpOnButton(item, "index", NULL);
  item->setData("index");
  helpMenu->addAction(item);
  mapper->setMapping(item, item);
  connect(item, SIGNAL(triggered()), mapper, SLOT(map()));

  // add standard items
  QAction* license = new QAction(tr("License..."),parent);
  helpMenu->addAction(license);
//  license.addActionListener(new apps.LicenseAction());
  license->setDisabled(true);

  QAction* directories = new QAction(tr("Locations..."),parent);
  //mapper->setMapping(directories, directories);
  //directories->addAction(new XmlFileLocationAction(parent));
  QAction* xmlFileLocation = new XmlFileLocationAction(parent);
  connect(directories, SIGNAL(triggered(bool)),xmlFileLocation, SLOT(actionPerformed()));
  helpMenu->addAction(directories);

  QAction* context = new QAction(tr("Context..."),NULL);
  helpMenu->addAction(context);
//        context.addActionListener(new apps.ReportContextAction());
  ReportContextAction* reportContextAction = new ReportContextAction(parent);
  connect(context, SIGNAL(triggered()), reportContextAction, SLOT(actionPerformed()));

  QMenu* console = new QMenu(tr("System console..."));
  helpMenu->addMenu(console);
//       console.addActionListener(new apps.SystemConsoleAction());
  console->addAction(new SystemConsoleAction());

//  helpMenu.add(new jmri.jmrit.mailreport.ReportAction());

 // Put about dialog in Apple's prefered area on Mac OS X
// if (SystemType.isMacOSX()) {
//            try {
//                Application.getApplication().setAboutHandler(new AboutHandler() {

//                    @Override
//                    /*public*/ void handleAbout(EventObject eo) {
//                        new AboutDialog(NULL, true).setVisible(true);
//                    }
//                });
//            } catch (java.lang.RuntimeException re) {
//                log.error("Unable to put About handler in default location", re);
//            }
//        }
  // Include About in Help menu if not on Mac OS X or not using Aqua Look and Feel
//  if (!SystemType.isMacOSX() || !UIManager.getLookAndFeel().isNativeLookAndFeel()) {
   helpMenu->addSeparator();
   QAction* about = new QAction(tr("About") + " " + QApplication::applicationName(), HelpUtil::instance());
   helpMenu->addAction(about);
//   about.addActionListener(new AboutAction());
   about->setDisabled(true);
//        }
   connect(mapper, SIGNAL(mapped(QObject*)), HelpUtil::instance(), SLOT(On_mapped(QObject*)));
 }
 return helpMenu;
}

/*static*/ /*public*/ QAction* HelpUtil::makeHelpMenuItem(QString ref)
{
 if (!initOK()) return NULL;  // initialization failed

 QAction* menuItem = new QAction(tr("Window Help..."), NULL);
 menuItem->setData(ref);
// globalHelpBroker->enableHelpOnButton(menuItem, ref, NULL);

 // start help to see what happend
// log.debug("help: "+globalHelpSet->getHomeID()+":"+globalHelpSet->getTitle()+":"+globalHelpSet->getHelpSetURL());
    return menuItem;
}

/*static*/ /*public*/ void HelpUtil::addHelpToComponent(QWidget* component, QString ref)
{
 if (globalHelpBroker!=NULL)
  globalHelpBroker->enableHelpOnButton(component, ref, NULL);
}


/*static*/ /*public*/ void HelpUtil::displayHelpRef(QString ref)
{
  if (globalHelpBroker == NULL)
  {
   log->debug("can't display "+ref+" help page because help system reference is NULL");
        return;
    }
//    try
//    {
        globalHelpBroker->setCurrentID(ref);
        globalHelpBroker->setDisplayed(true);
//    } catch (BadIDException e) {
//        log.error("unable to show help page "+ref+" due to "+e.ge);
//    }
}

/*static*/ bool HelpUtil::init = false;
/*static*/ bool HelpUtil::failed = true;

/*static*/ /*public*/ bool HelpUtil::initOK()
{
 if (!init)
 {
  init = true;
#if 0
//  try
//  {
   //Locale locale = Locale.getDefault();
   QString language = /*locale.getLanguage()*/"en";
   QString helpsetName = "help/"+language+"/JmriHelp_"+language+".hs";
   QUrl hsURL = FileUtil::findURL(helpsetName);
   if (!hsURL.isEmpty())
   {
    log.debug("JavaHelp using "+helpsetName);
   }
   else
   {
    log.warn("JavaHelp: File "+helpsetName+" not found, dropping to default");
    language = "en";
    helpsetName = "help/"+language+"/JmriHelp_"+language+".hs";
    hsURL = FileUtil::findURL(helpsetName);
   }
   try
   {
    globalHelpSet = new HelpSet(NULL, hsURL);
   }
   catch (NoClassDefFoundError ee)
   {
//    log.debug("classpath="+System.getProperty("java.class.path","<unknown>"));
//    log.debug("classversion="+System.getProperty("java.class.version","<unknown>"));
    log.error("Help classes not found, help system omitted");
    return false;
   }
   catch (Exception e2)
   {
    log.error("HelpSet "+helpsetName+" not found, help system omitted");
    return false;
   }
   globalHelpBroker = globalHelpSet->createHelpBroker();

//  }
//  catch (NoSuchMethodError e2) {
//    log.error("Is jh.jar available? Error starting help system: "+e2);
//}
failed = false;
#endif
     globalHelpBroker = new HelpBroker();
    }
    //return !failed;
 return true;
}

/*static*/ /*public*/ HelpBroker* HelpUtil::getGlobalHelpBroker() {
    return globalHelpBroker;
}

/*static*/ /*public*/ QAction* HelpUtil::getHelpAction(/*final*/ QString name, /*final*/ QIcon icon, /*final*/ QString id)
{
//    return new AbstractAction(name, icon) {
//        String helpID = id;
//        /*public*/ void actionPerformed(ActionEvent event) {
//            globalHelpBroker.setCurrentID(helpID);
//            globalHelpBroker.setDisplayed(true);
//        }
//    };
 return new HUAbstractAction(name, icon, id, NULL);
}

HUAbstractAction::HUAbstractAction(QString /*name*/, QIcon /*icon*/, QString id, HelpUtil* parent) : AbstractAction(parent)
{
 this->helpID = id;
 this->parent = parent;
 //connect(this, SIGNAL(triggered()), this, actionPerformed());
}

void HUAbstractAction::actionPerformed()
{
// parent->globalHelpBroker->setCurrentID(helpID);
// parent->globalHelpBroker->setDisplayed(true);
}


#if 0
/*static*/ HelpSet* HelpUtil::globalHelpSet = NULL;
/*static*/ HelpBroker* HelpUtil::globalHelpBroker = NULL;
#endif
HelpFrame::HelpFrame(QString ref)
{
 this->ref = ref.replace(".", QDir::separator());
 QWidget* centralWidget = new QWidget;
 centralWidget->setLayout(new QVBoxLayout);
 setCentralWidget(centralWidget);
 setMinimumSize(500,400);
 view = new MyWebView;
#if 0 // TODO:
 view->page()->setLinkDelegationPolicy(QWebEnginePage::DelegateAllLinks);
 view->page()->settings()->setAttribute(QWebEnginePage::PluginsEnabled, true);
#endif
 connect(view, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
 connect(view->page(), SIGNAL(statusBarMessage(QString)), this, SLOT(statusBarMessage(QString)));
 centralWidget->layout()->addWidget(view);
 //connect(view, SIGNAL(linkClicked(QUrl)), this, SLOT(linkClicked(QUrl)));
 connect(view->page(), SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
 connect(view->page(), SIGNAL(linkHovered(QString)), this, SLOT(linkHovered(QString)));
 QString path = FileUtil::getProgramPath()+ "help" + QDir::separator()+ "en" +  QDir::separator() + ref ;
 QString html;
 if(path.endsWith("index"))
  path = path.append(".html");
 else
 {
  path = path.append(".shtml");
  html = loadHtml(path);
 }
 QFileInfo info(path);
 if(!info.exists())
 {
  log->debug("File does not exist: " + path );
  return;
 }
 QUrl url = QUrl::fromUserInput(path);
 log->debug(tr("url %1 valid =  ").arg(url.toString()) + (url.isValid()?"true":"false") + " baseUrl="+info.path());
 if(!html.isEmpty())
   view->setHtml(html, QUrl::fromLocalFile(info.path()+QDir::separator()));
 else
   view->setUrl(url);
  resize(800,600);
  view->show();
  statusBar()->showMessage("file://" +path);
  show();
  adjustSize();
  view->addHistory(url);

// }
// else
//     log->debug("File does not exist: " + path );
}
 void HelpUtil::On_mapped(QObject * o)
 {
  QAction* act = (QAction*)o;
  QString ref = act->data().toString();
  if(_frame == NULL)
  {
   _frame = new HelpFrame(ref);
  _frame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  }
  else
   _frame->setUrl(ref);
 }

void HelpFrame::loadFinished(bool b)
{
 statusBar()->setEnabled(true);
 statusBar()->showMessage(tr("load ") + (b?"true":"false"));
 if(b)
 {

 }
}
void HelpFrame::statusBarMessage(QString msg)
{
 statusBar()->showMessage(msg);
}

void HelpFrame::setUrl(QString ref)
{
 QString path = FileUtil::getProgramPath()+ "help" + QDir::separator()+ "en" +  QDir::separator() + ref.replace(".", QDir::separator());
 if(path.endsWith("index"))
  path = path.append(".html");
 else
  path = path.append(".shtml");

 QString html = loadHtml(path);
 if(!html.isEmpty())
 {
  log->debug("file://" +path);
  QFileInfo info(path);
     //view->load(QUrl("file://" +path));
  view->setHtml(html, QUrl::fromLocalFile(info.path()+QDir::separator()));
  view->show();
  toFront();
  show();
  adjustSize();
  view->addHistory(QUrl::fromLocalFile(path));
 }
}
void HelpFrame::linkClicked(const QUrl & url)
{
 log->debug(tr("Link clicked: %1").arg(url.toString()));
 QString html;
 QString path = url.toString();
 if(path.endsWith(".png",Qt::CaseInsensitive) || path.endsWith(".gif",Qt::CaseInsensitive) || path.endsWith(".jpg",Qt::CaseInsensitive)) return;
 if(path.startsWith("file://"))
 {
  path = path.mid(7);
 }
 else
 {
   view->setUrl(QUrl(path));
   view->show();
   view->addHistory(url);
   return;
 }
 QString anchor;
 if(path.contains("#"))
 {
  int i = path.indexOf("#");
  anchor = path.mid(i);
  path = path.mid(0,i);
 }
 html = loadHtml(path);
 if(!html.isEmpty())
 {
  QFileInfo info(path);
  QUrl url = QUrl::fromUserInput(path);
  log->debug(tr("url %1 valid =  ").arg(url.toString()) + (url.isValid()?"true":"false") + " baseUrl="+info.path());
     //view->setUrl(url);
  view->setHtml(html, QUrl::fromLocalFile(info.path()+QDir::separator()));
  view->show();
 }
 else
  log->debug(tr("link %1 doesn't exist").arg(path));
 if(!anchor.isEmpty())
 {
  view->load(QUrl(anchor));
  view->show();
 }
 view->addHistory(url);
}
void HelpFrame::titleChanged(QString t)
{
 setWindowTitle(t);
}
QString HelpFrame::loadHtml(QString path)
{
 QFile file( path);
 QString html;
 if(file.exists())
 {
  if(file.open(QIODevice::ReadOnly| QIODevice::Text))
  {
   while (!file.atEnd())
   {
    QTextStream in(&file);
    while (!in.atEnd())
    {
     QString line = in.readLine();
     html = html.append(line);
    }
   }
  }
  log->debug("file://" +path);
 }
 return html;
}
void HelpFrame::linkHovered(const QString &link)
{
 statusBar()->showMessage(link);
}

MyWebView::MyWebView(QWidget *parent) : QWebEngineView(parent)
{
 historyList = QList<WebHistoryItem>();
 currHistoryItem = 0;
}

void MyWebView::contextMenuEvent(QContextMenuEvent *)
{
 QMenu*menu = new QMenu;
 QAction* back = new QAction(QIcon(QPixmap(":/resources/icons/throttles/previous.png")), tr("Previous"),this);
 menu->addAction(back);
 connect(back, SIGNAL(triggered()), this, SLOT(previous()));
 QAction* forward = new QAction(QIcon(":/resources/icons/throttles/next.png"), tr("Next"),this);
 menu->addAction(forward);
 connect(forward, SIGNAL(triggered()), this, SLOT(next()));

 menu->exec(QCursor::pos());
}
void MyWebView::previous()
{
// QWebHistory* _history  = history();
// QList<QWebHistoryItem> hl = _history->backItems(5);
// QString prevUrl;
// if(_history->canGoBack())
// {
//  prevUrl = _history->backItem().url().toString();
//  linkClicked(prevUrl);
//  return;
// }
// back();
 if(currHistoryItem > 0)
 {
  WebHistoryItem hItem = historyList.at(currHistoryItem -1);
  currHistoryItem--;
  if(hItem.url.path().contains(".shtml"))
  {
   QString html = loadHtml(hItem.url.path());
   QFileInfo info(hItem.url.path());
   setHtml(html,QUrl::fromLocalFile(info.path()+QDir::separator()));
  }
  else
   load(hItem.url);
 }
}
QString MyWebView::loadHtml(QString path)
{
 QFile file( path);
 QString html;
 if(file.exists())
 {
  if(file.open(QIODevice::ReadOnly| QIODevice::Text))
  {
   while (!file.atEnd())
   {
    QTextStream in(&file);
    while (!in.atEnd())
    {
     QString line = in.readLine();
     html = html.append(line);
    }
   }
  }
  //log->debug("file://" +path);
 }
 return html;
}
void MyWebView::next()
{
 if (currHistoryItem < historyList.count()-1)
 {
  WebHistoryItem hItem = historyList.at(currHistoryItem +1);
  currHistoryItem++;
  if(hItem.url.path().contains(".shtml"))
  {
   QString html = loadHtml(hItem.url.path());
   QFileInfo info(hItem.url.path());
   setHtml(html, QUrl::fromLocalFile(info.path()+QDir::separator()));
  }
  else
   load(hItem.url);
 }
}
void MyWebView::addHistory(const QUrl & url)
{
 WebHistoryItem hItem;
 hItem.url = url;
 historyList.append(hItem);
 currHistoryItem++;
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* HelpUtil::log = LoggerFactory::getLogger("HelpUtil");
/*private*/ /*final*/ /*static*/ Logger* HelpFrame::log = LoggerFactory::getLogger("HelpUtil");
/*private*/ /*final*/ /*static*/ Logger* MyWebView::log = LoggerFactory::getLogger("HelpUtil");
/*public*/ QString HelpFrame::getClassName()
{
 return "jmri.help.HelpFrame";
}
