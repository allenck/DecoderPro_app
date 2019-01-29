#ifndef JTEXTAREA_H
#define JTEXTAREA_H

#include <QWidget>
#include "QTextEdit"
#include <QTextDocument>
#include "javaqt_global.h"

class Document : public QTextDocument
{
 Q_OBJECT
};
class JAVAQTSHARED_EXPORT JTextArea : public QTextEdit
{
    Q_OBJECT
public:
    //explicit JTextArea(QWidget *parent = 0);
    /*public*/ JTextArea(QString text, QWidget *parent = 0);
    /*public*/ JTextArea(QString text, int rows, int columns, QWidget *parent = 0);
    /*public*/ JTextArea(Document* doc, QString text, int rows, int columns, QWidget *parent = 0);
    /*public*/ JTextArea(Document* doc, QWidget *parent = 0);
    /*public*/ JTextArea(int rows, int columns, QWidget *parent= 0);
    /*public*/ JTextArea(QWidget *parent = 0);
    void setEditable(bool);
    /*public*/ void append(QString str);
    void setTabSize(int width);
    /*public*/ int getRows();
    /*public*/ void setRows(int rows);
    /*public*/ int getColumns();
    /*public*/ void setColumns(int columns);
    /*public*/ void setLineWrap(bool);
    /*public*/ bool getLineWrap();
    /*public*/ void setWrapStyleWord(bool);
    /*public*/ bool getWrapStyleWord();
    /*public*/ void setOpaque(bool);

public slots:
private:
    // --- variables -------------------------------------------------

    /*private*/ int rows;
    /*private*/ int columns;
    /*private*/ int columnWidth;
    /*private*/ int rowHeight;
    /*private*/ bool wrap;
    /*private*/ bool word;
    Document* doc;
    QString text;
    void common();
    QTextOption::WrapMode textOption;

protected:
    /*protected*/ Document* createDefaultModel();
    /*protected*/ int getRowHeight();
    /*protected*/ int getColumnWidth();

};

#endif // JTEXTAREA_H
