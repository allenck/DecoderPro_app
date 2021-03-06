#ifndef JEDITORPANE_H
#define JEDITORPANE_H
#include "jtextcomponent.h"

class JEditorPane : public JTextComponent
{
 Q_OBJECT
public:
 explicit JEditorPane(QWidget *parent = 0);
 /*public*/ JEditorPane(QUrl* initialPage, QWidget *parent = 0);
 /*public*/ JEditorPane(QString url, QWidget *parent = 0);
 /*public*/ JEditorPane(QString type, QString text, QWidget *parent = 0);

signals:

public slots:
private:
 void common();
};

#endif // JEDITORPANE_H
