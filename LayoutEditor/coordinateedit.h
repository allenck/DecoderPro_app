#ifndef COORDINATEEDIT_H
#define COORDINATEEDIT_H

#include <QObject>
#include <QAction>
#include "positionable.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include "positionablelabel.h"
#include "positionableicon.h"
#include "sensoricon.h"
#include "liblayouteditor_global.h"
#include "jmrijframe.h"
#include "abstractaction.h"

class JTextField;
class LIBLAYOUTEDITORSHARED_EXPORT CoordinateEdit : public JmriJFrame
{
    Q_OBJECT
public:
    explicit CoordinateEdit(QWidget* parent = 0);
    /*public*/ static QAction* getTextEditAction(/*const*/ Positionable* pos, const QString title, QObject* parent);
    /*public*/ static QAction* getLevelEditAction(/*final*/ Positionable* pos, QObject *parent);
    /*public*/ static QAction* getCoordinateEditAction(/*final*/ Positionable* pos, QObject *parent);
    /*public*/ void init(QString title, Positionable* pos, bool showName);
    /*public*/ void initSetXY();
    /*public*/ void initSetLevel();
    /*public*/ void initText();
    /*public*/ static QAction* getRotateEditAction(/*final*/ Positionable* pos, QObject *parent);
    /*public*/ static QAction* getScaleEditAction(/*final*/ Positionable* pos, CoordinateEdit* parent);
    /*public*/ void initRotate();
    /*public*/ void initScale();
    /*public*/ static QAction* getMarginEditAction(/*final*/ Positionable* pos, PositionablePopupUtil* parent);
    /*public*/ static QAction* getFixedSizeEditAction(/*final*/ Positionable* pos, PositionablePopupUtil* parent);
    /*public*/ void initMargin();
    /*public*/ void initFixedSize();
    //static Positionable* pos;
    /*public*/ static QAction* getBorderEditAction(/*final*/ Positionable* pos, QObject *parent);
    /*public*/ void initBorder();
    /*public*/ /*static*/ QAction* getNameEditAction(/*final*/ Positionable* pos);
    /*public*/ void  initSetName();
    /*public*/ static AbstractAction* getTooltipEditAction(/*final*/ Positionable* pos, QObject *parent);
    /*public*/ void initSetTip();
 /*public*/ static AbstractAction* getLinkEditAction(/*final*/ Positionable* pos, /*final*/ QString title, QObject* parent);
 /*public*/ static AbstractAction* getZoomEditAction(/*final*/ Positionable* pos, QObject *parent);
 /*public*/ void initZoom();
 /*public*/ void initLink();
 /*public*/ QString getClassName();

signals:
    
public slots:
//    /*public*/ void renamePanelMenu(/*ActionEvent e*/);
 void on_okButton_clicked();
 void on_cancelButton_clicked();
 void onOK_rotate();
 void onLinkOK();
 void onLinkCancel();

private:
 QObject *parent;
 Positionable* pl; 			// positional label tracked by this frame
 //PositionableLabel* ps;
 int oldX;
 int oldY;
 double oldD;
 QString oldStr;
 //static QString title;

 // member declarations
 QLabel* nameText;// = new QLabel();
 QLabel* textX;
 QLabel* textY;

 // buttons
 QPushButton* okButton;// = new QPushButton();
 QPushButton* cancelButton;// = new QPushButton();

 // text field
 JTextField* xTextField;
 JTextField* yTextField;

 //SpinnerNumberModel _spinModel;
 QSpinBox* spinX;
 QSpinBox* spinY;


 /*private*/ void addTextItems() ;
// /*private*/ void addItem(QObject* c, int x, int y, int w, bool horzExpand);
 QGridLayout* gridLayout;
 Logger* log;
 QAction* setXYAction;
 QAction* levelEditAction;
 QAction* textEditAction;

private slots:
// void on_getTextEditAction_triggered();
// void on_levelEditAction_triggered();
// void on_setXYAction_triggered();
 void on_setXYOkButton_clicked();
 void on_setXYCancelButton_clicked();
 void on_setXYSpinnerValues_changed();
 void on_setLevelOkButton_clicked();
 void on_setLevelCancelButton_clicked();
 void on_editTextOkButton_clicked();
 void on_editTextCancelButton_clicked();
// void on_rotateAction_triggered();
// void on_getScaleEditAction_triggered();
 //void on_actionMarginEdit_triggered();
 void on_initMarginOkButton_clicked();
 void on_initMarginCancelButton_clicked();
 void on_initFixedSizeOkBubbon_clicked();
 void on_initFixedSizeCancelButton_clicked();
 //void on_setBorderSizeAction_triggered();
 void on_initBorderOkButton_clicked();
 void on_initBorderCancelButton_clicked();
 void on_okSetTip_clicked();
 void on_cancel();
 void on_scaleOk_clicked();
 void on_scaleCancel_clicked();
 void on_okSetName_clicked();
 void on_cancelSetName_clicked();

protected:
 /*protected*/ void addSpinItems(bool addY);
 /*protected*/ Editor* changeView(QString className);

 friend class MemoryIconCoordinateEdit;
};

class SetBorderSizeActionListener : public ActionListener
{
 Q_OBJECT
    Positionable* pos;
    QObject* parent;
public:
    SetBorderSizeActionListener(Positionable* pos, QObject* parent);
 public slots:
    void actionPerformed(JActionEvent *e = 0);
};

class LevelEditAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
public:
 LevelEditAction(Positionable* pos, QString name, QObject* parent);
public slots:
 void on_levelEditAction_triggered();
};

class TooltipEditAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
public:
 TooltipEditAction(Positionable* pos, QString name, QObject* parent);
public slots:
 void actionPerformed(ActionEvent * = 0);
};

class ActionMarginEdit : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
public:
 ActionMarginEdit(Positionable* pos, QString name, QObject* parent);
public slots:
 void on_actionMarginEdit_triggered();
};

class ScaleEditAction : public AbstractAction
{
 Q_OBJECT
 CoordinateEdit* parent;
 Positionable* pos;
public:
 ScaleEditAction(Positionable* pos, QString name, CoordinateEdit* parent);
public slots:
 void on_getScaleEditAction_triggered();
};

class GetNameEditAction : public AbstractAction
{
 Q_OBJECT
 CoordinateEdit* parent;
 Positionable* pos;
public:
 GetNameEditAction(Positionable* pos, QString name, CoordinateEdit* parent);
public slots:
 void renamePanelMenu();
};

class ActionFixedSizeEdit : public AbstractAction
{
 Q_OBJECT
 PositionablePopupUtil* parent;
 Positionable* pos;
public:
 ActionFixedSizeEdit(Positionable* pos, QString name, PositionablePopupUtil* parent);
public slots:
 void on_actionGetFixedSizeEdit_triggered();
};
class RotateAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
public:
 RotateAction(Positionable* pos, QString name, QObject *parent);
public slots:
 void on_rotateAction_triggered();
};

class TextEditAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
 QString title;

public:
 TextEditAction(Positionable* pos, QString title, QObject* parent);
public slots:
 void on_getTextEditAction_triggered();
};

class SetXYAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
public:
 SetXYAction(Positionable* pos, QString name, QObject* parent);
public slots:
 void on_setXYAction_triggered();
};

class GetZoomEditAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
public:
 GetZoomEditAction(Positionable* pos, QString name, QObject* parent);
public slots:
 void on_getZoomEditAction_triggered();
};

class LinkEditAction : public AbstractAction
{
 Q_OBJECT
 QObject* parent;
 Positionable* pos;
 QString title;
public:
 LinkEditAction(Positionable* pos, QString title, QObject* parent);
public slots:
 void actionPerformed();
};
#endif // COORDINATEEDIT_H
