#ifndef APPSLAUNCHPANE_H
#define APPSLAUNCHPANE_H

#include <QWidget>
#include "appslib_global.h"

class PropertyChangeEvent;
class ConnectionConfig;
class QLabel;
class FlowLayout;
class Logger;
class APPSLIBSHARED_EXPORT AppsLaunchPane : public QWidget
{
 Q_OBJECT
public:
 explicit AppsLaunchPane(QWidget *parent = 0);
 /*public*/ static void ynstrument(QString path);
// static /*public*/ QString getConnection1() __attribute__ ((deprecated));
// static /*public*/ QString getConnection2() __attribute__ ((deprecated));
// static /*public*/ QString getConnection3() __attribute__ ((deprecated));
// static /*public*/ QString getConnection4() __attribute__ ((deprecated));
 static /*public*/ QString getConfigFileName();
 static /*public*/ QWidget* buttonSpace();

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* ev);

private:
 static QString profileFilename;
 Logger* log;
 FlowLayout* buttonSpaceLayout;
 static QWidget* _buttonSpace;
 static QWidget* _jynstrumentSpace;// = null;
 // line 4
 QLabel* cs4;//= new JLabel();
 // line 5 optional
 QLabel* cs5;// = new JLabel();
 // line 6 optional
 QLabel* cs6;// = new JLabel();
 // line 7 optional
 QLabel* cs7;// = new JLabel();
 QList<ConnectionConfig*> connection;// = {NULL, NULL, NULL, NULL};


protected:
 /*protected*/ /*final*/ void addToActionModel();
 /*protected*/ void setButtonSpace();
 /*protected*/ void setJynstrumentSpace();
 /*protected*/ virtual QString line1();
 /*protected*/ virtual QString line2();
 /*protected*/ virtual QString line3();
 /*protected*/ void buildLine4(QWidget* pane);
 /*protected*/ void buildLine5(QWidget* pane);
 /*protected*/ void buildLine6(QWidget* pane);
 /*protected*/ void buildLine7(QWidget* pane);
 /*protected*/ void buildLine(ConnectionConfig* conn, QLabel* cs, QWidget* pane);
 /*protected*/ void updateLine(ConnectionConfig* conn, QLabel* cs);
 /*protected*/ QString line8();
 /*protected*/ QString line9();
 /*protected*/ virtual QString logo();
 /*protected*/ virtual QWidget* statusPanel();
 static /*protected*/ void setJmriSystemProperty(QString key, QString value);
 static /*protected*/ void setConfigFilename(QString def, QStringList args);
 /*protected*/ /*abstract*/ virtual QString windowHelpID();
 friend class AppsLaunchFrame;
};

#endif // APPSLAUNCHPANE_H
