#ifndef JTEXTCOMPONENT_H
#define JTEXTCOMPONENT_H

#include <QLineEdit>
#include <QtXml>
#include "javaqt_global.h"
#include <QTextBrowser>

class Document;
class JAVAQTSHARED_EXPORT JTextComponent : public QTextBrowser
{
    Q_OBJECT
public:
    explicit JTextComponent(QWidget *parent = 0);
    /*public*/ void setDocument(Document* doc);
    /*public*/ Document* getDocument();

signals:

public slots:
private:
    /**
     * The document model.
     */
    /*private*/ Document* model;

};

#endif // JTEXTCOMPONENT_H
