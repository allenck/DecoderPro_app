#ifndef HELPBROKER_H
#define HELPBROKER_H

#include <QObject>

class QPushButton;
class QSignalMapper;
class QAction;
//class Map;
class HelpSet;
class HelpBroker : public  QObject
{
    Q_OBJECT
public:
    explicit HelpBroker(QObject *parent = 0);
    ~HelpBroker();
 ///*public*/ virtual interface HelpBroker {
#if 0
     /*public*/ virtual void setHelpSet(HelpSet* hs);

     /*public*/ virtual HelpSet* getHelpSet();

     /*public*/ virtual void setHelpSetPresentation(HelpSet::Presentation prsntn);

     /*public*/ virtual QLocale getLocale();

     /*public*/ virtual void setLocale(Locale locale);

     /*public*/ virtual QFont getFont();

     /*public*/ virtual void setFont(Font font);

     /*public*/ virtual void setCurrentView(QString string);

     /*public*/ virtual QString getCurrentView();

     /*public*/ virtual void initPresentation();

     /*public*/ virtual void setDisplayed(boolean bln) throw (UnsupportedOperationException);

     /*public*/ virtual bool isDisplayed();

     /*public*/ virtual void setLocation(Point point) throw (UnsupportedOperationException);

     /*public*/ virtual QPoint getLocation() throw (UnsupportedOperationException);

     /*public*/ virtual void setSize(Dimension dmnsn) throw (UnsupportedOperationException);

     /*public*/ virtual QSize getSize() throw (UnsupportedOperationException);

     /*public*/ virtual void setScreen(int i) throw (UnsupportedOperationException);

     /*public*/ virtual int getScreen() throw (UnsupportedOperationException);

     /*public*/ virtual void setViewDisplayed(bool bln);

     /*public*/ virtual bool isViewDisplayed();

     /*public*/ virtual void showID(Map::ID id, QString string, QString string1) throw (InvalidHelpSetContextException);

     /*public*/ virtual void showID(QString string, QString string1, QString string2) throw (BadIDException);

     /*public*/ virtual void setCurrentID(Map::ID id) throw (InvalidHelpSetContextException);

     /*public*/ virtual void setCurrentID(QString string) throw (BadIDException);

     /*public*/ virtual Map::ID getCurrentID();

     /*public*/ virtual void setCurrentURL(URL url);

     /*public*/ virtual QUrl* getCurrentURL();

     /*public*/ virtual void enableHelpKey(Component cmpnt, QString string, HelpSet hs);

     /*public*/ virtual void enableHelpKey(Component cmpnt, QString string, HelpSet hs, QString string1, String string2);

     /*public*/ virtual void enableHelp(Component cmpnt, QString string, HelpSet hs);

     /*public*/ virtual void enableHelp(QAction* mi, QString string, HelpSet hs);

     /*public*/ virtual void enableHelpOnButton(QWidget* cmpnt, QString string, HelpSet hs) throw (IllegalArgumentException);
#endif
     /*public*/ virtual void enableHelpOnButton(QObject* mi, QString string, HelpSet* hs);
#if 0
     /*public*/ virtual void enableHelpOnButton(QObject* o, QString string, HelpSet hs, QString string1, QString string2) throw (IllegalArgumentException);
#endif
signals:

public slots:
 void on_action(QString);

private:
 //QMap<QString, QString> hMap;
 QSignalMapper* mapper;
};

#endif // HELPBROKER_H
