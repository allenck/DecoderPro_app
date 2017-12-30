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
//#include <QtWebkitWidgets/QtWebKitWidgets>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QWebView>
#endif
#include "abstractaction.h"
#include "liblayouteditor_global.h"

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
    static /*public*/ QAction* makeHelpMenuItem(QString ref);
    static /*public*/ void addHelpToComponent(QWidget* component, QString ref);
//    static /*public*/ void displayHelpRef(QString ref);
    static /*public*/ HelpBroker* getGlobalHelpBroker();
    static /*public*/ QAction* getHelpAction(/*final*/ QString name, /*final*/ QIcon icon, /*final*/ QString id);

signals:

public slots:
    void On_mapped(QObject*);

private:
    explicit HelpUtil(QObject *parent = 0);
    static HelpUtil* thisMenu;
    Logger* log;
    HelpFrame* _frame;
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

class MyWebView : public QWebView
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
  void contextMenuEvent(QContextMenuEvent *);
  QList<WebHistoryItem> historyList;
  int currHistoryItem;
  QString loadHtml(QString path);

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
 public slots:
  void loadFinished(bool);
  void statusBarMessage(QString);
  void linkClicked(const QUrl &);
  void titleChanged(QString);
  void linkHovered(const QString & link, const QString & title, const QString & textContent);

 private:
  QString ref;
  MyWebView* view;
  Logger* log;
  QString loadHtml(QString path);

 };

#endif // HELPUTIL_H
