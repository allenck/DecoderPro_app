#ifndef JTEXTFIELD_H
#define JTEXTFIELD_H

#include "jtextcomponent.h"
#include <QtXml>
#include "logger.h"
#include "javaqt_global.h"

class PropertyChangeEvent;
class InputVerifier;
class Document;
class Action;
class PropertyChangeListener;
class ActionListener;
class JAVAQTSHARED_EXPORT JTextField : public /*JTextComponent*/QLineEdit
{
    Q_OBJECT
public:
    explicit JTextField(QWidget *parent = 0);
    /*public*/ JTextField(QString text, QWidget *parent = 0);
    /*public*/ JTextField(int columns, QWidget *parent = 0);
    /*public*/ JTextField(QString text, int columns, QWidget *parent = 0);
    /*public*/ JTextField(Document* doc, QString text, int columns, QWidget *parent = 0);
    /*public*/ void setDocument(Document* doc);
    /*public*/ int getColumns();
    /*public*/ void setColumns(int columns);
    /*public*/ /*synchronized*/ void addActionListener(ActionListener* l);
    QColor getBackground();
    void setBackground(QColor);
    /*public*/ QSize getPreferredSize();
    /*public*/ void setFont(QFont f);
    /*public*/ void setForeground(QColor);
    void setOpaque(bool);
    /*public*/ void setShare(JTextField* share);
    /*public*/ void setName(QString name);
    /*public*/ Document* getDocument();
    /*public*/ void setInputVerifier(InputVerifier* inputVerifier);


signals:
 void enterField();
 void leaveField();
 void propertyChange(PropertyChangeEvent*);

public slots:
private:
 void init();
 int columns;
 int columnWidth;
 Document* doc;
 /*private*/ Action* action;
 /*private*/ PropertyChangeListener* actionPropertyChangeListener;
 QMutex mutex;
 JTextField* share;
 QString ss;
 void enterEvent(QEvent*);
 void leaveEvent(QEvent *);
 Logger* log;
 bool nameExplicitlySet;
 InputVerifier* inputVerifier;

private slots:
 void updateShare();
protected:
 /*protected*/ Document* createDefaultModel();
 /*protected*/ int getColumnWidth();


};

#endif // JTEXTFIELD_H
