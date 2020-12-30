#ifndef JYTHONWINDOW_H
#define JYTHONWINDOW_H
#include "abstractaction.h"
//#include "PythonQt_QtAll.h"
#include "windowlistener.h"

class JTextArea;
class JFrame;
class QCheckBox;
class UserPreferencesManager;
class QPushButton;
class JythonWindow : public AbstractAction
{
 Q_OBJECT
public:
 explicit JythonWindow(QObject *parent);
 /*public*/ JythonWindow(QString name, QObject *parent);
 /*public*/ JFrame* getFrame();
 static JythonWindow* instance();
 void appendText(QString);
 void setDefaultTextcolor();
 void setTextColors(QColor, QColor);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0);
 void on_autoScroll_toggled(bool);
 void on_alwaysOnTopCheckBox_toggled(bool);
 void on_clearButton_clicked();
 void On_stdErr(QString);
 void On_stdOut(QString);

private:
 void common();
 JTextArea* area = nullptr;
 JFrame* f;
 QCheckBox* autoScroll;
 UserPreferencesManager* pref;
 QPushButton* clearButton;
 QColor defaultTextBackground;
 QColor defaultTextColor;
 QString alwaysOnTopCheck;// = this.getClass().getName() + ".alwaysOnTop";
 QString alwaysScrollCheck;// = this.getClass().getName() + ".alwaysScroll";
 /*private*/ void doAutoScroll(JTextArea* ta, bool scroll);
 static JythonWindow* _instance;
 void closeEvent(QCloseEvent *);
 QString _err;

private slots:

protected:
 /*protected*/ QCheckBox* alwaysOnTopCheckBox;// = new JCheckBox();
 friend class JWWindowListener;
};
class JWWindowListener : public WindowListener
{
 Q_OBJECT
 JythonWindow* parent;
public:
 JWWindowListener(JythonWindow* parent);
 void windowClosing(QCloseEvent *e);
};

#endif // JYTHONWINDOW_H
