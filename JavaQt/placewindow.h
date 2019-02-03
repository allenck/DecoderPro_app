#ifndef PLACEWINDOW_H
#define PLACEWINDOW_H

#include <QObject>

class Logger;
class PlaceWindow : public QObject
{
 Q_OBJECT
public:
 //explicit PlaceWindow(QObject *parent = nullptr);
// /*public*/ static int getScreen(QWidget parent, QWidget target);
 /*public*/ static QPoint nextTo(QWidget* parent, QWidget* comp, QWidget* target);

signals:

public slots:

private:
 static Logger* log;
 static QList<QSize> _screenSize;
 // static /*private*/ QSize getScreenSizeOf(int screenNum) {

};

#endif // PLACEWINDOW_H
