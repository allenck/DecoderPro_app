#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include "jdialog.h"
#include "actionlistener.h"
#include "jpanel.h"
#include "windowlistener.h"
#include "changeevent.h"
#include "jcomponent.h"
#include "changelistener.h"

class CDChangeListener;
class QFontDialog;
class CDWindowListener;
class CDActionListener;
class PositionablePopupUtil;
class QFrame;
class JColorChooser;
class Logger;
class ColorDialog : public JDialog
{
 Q_OBJECT
public:
 explicit ColorDialog(QWidget *parent = nullptr);
 /*public*/ ColorDialog(QWidget* client, QWidget *t, int type, ActionListener* ca);

 /*public*/ static /*final*/ int STRUT;// = 6;

enum COPTIONS
{
 ONLY = 0,
 BORDER = 1, //DecoratorPanel.BORDER, // (= 1)
 MARGIN = 2, //DecoratorPanel.MARGIN; // (= 2)
 FWIDTH = 3, //DecoratorPanel.FWIDTH; // (= 3)
 FHEIGHT = 4, //DecoratorPanel.FHEIGHT;   // (= 4)
 FONT = 5,
 TEXT = 6
};
Q_ENUM(COPTIONS)

signals:

public slots:
 void onDoneButton();
 void cancel();
 /*public*/ void stateChanged(ChangeEvent* e);

private:
 static Logger* log;
 JColorChooser* _chooser;
 QWidget* _target = nullptr;
 QWidget* _compTarget = nullptr;
 int _type;
 QColor _saveColor;
 bool _saveOpaque;
 QString _saveText;
 PositionablePopupUtil* _util;
 PositionablePopupUtil* _saveUtil;
 ActionListener* _colorAction;
 JPanel* _preview;
 JPanel* makePanel(JPanel* p);
 JPanel* makeTextSpinnerPanel();
 JPanel* makeTextPanel();
 /*private*/ void update();
 QFontDialog* fontPanel = nullptr;
 bool _done = false;
 CDChangeListener* changeListener;

protected:
 /*protected*/ JPanel* makeDoneButtonPanel();

friend class CDActionListener;
friend class CDWindowListener;
friend class CDChangeListener;
};

class CDActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 ColorDialog* colorDialog;
public:
 CDActionListener(ColorDialog* colorDialog) {this->colorDialog = colorDialog;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0) override{colorDialog->update();}
};

class CDWindowListener : public WindowListener
{
 Q_OBJECT
 ColorDialog* colorDialog;
public:
 CDWindowListener(ColorDialog* colorDialog) {this->colorDialog = colorDialog;}
 void windowClosing(QCloseEvent *) {
  if(!colorDialog->_done)
  colorDialog->cancel();
 }
};

class CDChangeListener : public ChangeListener
{
 Q_OBJECT
 ColorDialog* colorDialog;
public:
 CDChangeListener(ColorDialog* colorDialog) {this->colorDialog = colorDialog;}
public slots:
 void stateChanged(ChangeEvent* evt)
 {
  colorDialog->stateChanged(evt);
 }
};
#endif // COLORDIALOG_H
