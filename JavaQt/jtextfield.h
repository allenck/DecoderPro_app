#ifndef JTEXTFIELD_H
#define JTEXTFIELD_H

#include "jtextcomponent.h"
#include <QtXml>
#include "logger.h"
#include "javaqt_global.h"
#include "jcomponent.h"
#include "changelistener.h"
#include "focuslistener.h"
#include "keyadapter.h"
#include "keylistener.h"

class PropertyChangeEvent;
class InputVerifier;
class Document;
class Action;
class PropertyChangeListener;
class ActionListener;
class JAVAQTSHARED_EXPORT JTextField : public /*JTextComponent*/QLineEdit, public JComponent, public KeyListener
{
    Q_OBJECT
    Q_INTERFACES(JComponent KeyListener)
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
    QColor getForeground();
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
    /*public*/ QObject* jself() {return (QObject*)this;}
    /*public*/ bool isOpaque();
    /*public*/ QFont getFont();
    /*public*/ void setBorder(Border* border) override {this->_border = border;}
    /*public*/ Border* getBorder() {return _border;}
    /*public*/ void setData(QVariant v) {_data = v;}
    /*public*/ QVariant getDatat() {return _data;}
    /*public*/ void addChangeListener(ChangeListener* l);
    /*public*/ void removeChangeListener(ChangeListener* l);
    /*public*/ void addFocusListener(FocusListener *l);
    /*public*/ void removeFocusListener(FocusListener* l);
    /*public*/ void addKeyListener(KeyAdapter*);
    /*public*/ void removeKeyListener(KeyAdapter*);
    QObject* self() {return (QObject*)this;}
    /*public*/ void setEnabled(bool b) override {QLineEdit::setEnabled(b);}
    /*public*/ void setEditable(bool b) {setEnabled(b);}

signals:
 void enterField();
 void leaveField();
 void propertyChange(PropertyChangeEvent*);
 /*public*/ void focusGained(FocusEvent* fe);
 /*public*/ void focusLost(FocusEvent* fe);
 /*public*/ void stateChanged(ChangeEvent*);

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
 Border* _border = nullptr;
 QVariant _data;
 /*private*/ void focusInEvent(QFocusEvent* e);
 /*private*/ void focusOutEvent(QFocusEvent* e);
 QColor backgroundColor = Qt::white;
 QColor textColor = Qt::black;
 bool _opaque = true;
// void keyPressEvent(QKeyEvent *);
// void keyReleaseEvent(QKeyEvent*);
 QList<KeyAdapter*> keyAdapterList = QList<KeyAdapter*>();

private slots:
 void updateShare();
 //void on_edited();

protected:
 /*protected*/ Document* createDefaultModel();
 /*protected*/ int getColumnWidth();


};

#endif // JTEXTFIELD_H
