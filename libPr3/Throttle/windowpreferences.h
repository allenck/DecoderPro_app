#ifndef WINDOWPREFERENCES_H
#define WINDOWPREFERENCES_H
#include <QtXml>
#include "jmrijframe.h"

class WindowPreferences
{
public:
 WindowPreferences();
 /*public*/ static QDomElement getPreferences(JmriJFrame* c);
 /*public*/ static void setPreferences(JmriJFrame* c, QDomElement e);
 /*public*/ static QDomElement getPreferences(QWidget* c);
 /*public*/ static void setPreferences(QWidget* c, QDomElement e, bool ignorePosition);
 /*public*/ static void setPreferences(QWidget* c, QDomElement e);

};

#endif // WINDOWPREFERENCES_H
