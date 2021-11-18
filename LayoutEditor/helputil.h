#ifndef HELPUTIL_H
#define HELPUTIL_H

#include <QObject>
#include <QAction>
#include "logger.h"
#include "jmrijframe.h"
#include <QUrl>
#if QT_VERSION < 0x050000
#include <QtWebKit/QWebView>
#else
#include <QtWebEngineWidgets/QWebEngineView>
#endif
#include "abstractaction.h"
#include "liblayouteditor_global.h"
#include "jmenuitem.h"

class WebHistoryItem;
class QWebView;
class HelpFrame;
class QIcon;
class HelpSet;
class HelpBroker;
class QMenu;
class QMenuBar;
class LIBLAYOUTEDITORSHARED_EXPORT HelpUtil : public QObject
{
    Q_OBJECT
public:
    static /*public */ HelpUtil* instance();
    static /*public*/ QMenu* helpMenu(QMenuBar* menuBar, QString ref, bool direct);
    static /*public*/ QMenu* makeHelpMenu(QString ref, bool direct, QObject* parent);
    static bool init;// = false;
    static bool failed;// = true;
    static /*public*/ bool initOK();
//    static HelpSet* globalHelpSet;
    static HelpBroker* globalHelpBroker;
    static /*public*/ JMenuItem* makeHelpMenuItem(QString ref);
    static /*public*/ void addHelpToComponent(QWidget* component, QString ref);
    /*public*/ static void enableHelpOnButton(QWidget* comp, QString id);
    static /*public*/ void displayHelpRef(QString ref);
    static /*public*/ HelpBroker* getGlobalHelpBroker();
    static /*public*/ JMenuItem* getHelpAction(/*final*/ QString name, /*final*/ QIcon icon, /*final*/ QString id);

signals:

public slots:
    void On_mapped(QObject*);

private:
    explicit HelpUtil(QObject *parent = 0);
    static HelpUtil* thisMenu;
    static Logger* log;
    HelpFrame* _frame = nullptr;
};

class HUAbstractAction : public  AbstractAction
{
 Q_OBJECT
    QString helpID;
    HelpUtil* parent;
 public:
    HUAbstractAction(QString, QIcon, QString, HelpUtil* parent);
public slots:
    void actionPerformed();
};

class MyWebView : public QWebEngineView
{
 Q_OBJECT
public:
    struct WebHistoryItem
    {
     QUrl url;
    };

  MyWebView(QWidget* parent = 0);
  void addHistory(const QUrl &);
private:
//  void contextMenuEvent(QContextMenuEvent *);
  QList<WebHistoryItem> historyList;
  int currHistoryItem;
  QString loadHtml(QString path);
  static Logger* log;

private slots:
  void previous();
  void next();
};
 class HelpFrame : public JmriJFrame
 {
  Q_OBJECT
  public:
  HelpFrame(QString ref);
  void setUrl(QString ref);
  /*public*/ QString getClassName();

 public slots:
  void loadFinished(bool);
  void statusBarMessage(QString);
  void linkClicked(const QUrl &);
  void titleChanged(QString);
  void linkHovered(const QString & link);

 private:
  QString ref;
  MyWebView* view;
  static Logger* log;
  QString loadHtml(QString path);

 };
 /*public*/ /*interface*/class MenuProvider {

 /**
  * Get the menu items to include in the menu. Any menu item that is null will be
  * replaced with a separator.
  *
  * @return the list of menu items
  */
 //@Nonnull
 virtual QList<JMenuItem*> getHelpMenuItems()=0;
 virtual QObject* self() =0;
 };
Q_DECLARE_INTERFACE(MenuProvider, "MenuProvider")
#endif // HELPUTIL_H
