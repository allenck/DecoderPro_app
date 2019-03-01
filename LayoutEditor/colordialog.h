#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include "jdialog.h"
#include "actionlistener.h"
#include "jpanel.h"
#include "windowlistener.h"
#include "changeevent.h"
#include "jcomponent.h"

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
 /*public*/ ColorDialog(QWidget* client, JComponent *t, int type, ActionListener* ca);

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
 JComponent* _target;
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

protected:
 /*protected*/ JPanel* makeDoneButtonPanel();

friend class CDActionListener;
friend class CDWindowListener;
};

class CDActionListener : public ActionListener
{
 Q_OBJECT
 ColorDialog* colorDialog;
public:
 CDActionListener(ColorDialog* colorDialog) {this->colorDialog = colorDialog;}
public slots:
 void actionPerformed() {colorDialog->update();}
};

class CDWindowListener : public WindowListener
{
 Q_OBJECT
 ColorDialog* colorDialog;
public:
 CDWindowListener(ColorDialog* colorDialog) {this->colorDialog = colorDialog;}
 void windowClosing(QCloseEvent *) {colorDialog->cancel(); }
};
#endif // COLORDIALOG_H
