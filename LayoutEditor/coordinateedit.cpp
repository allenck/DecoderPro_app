#include "coordinateedit.h"
#include "inputangledlg.h"
#include "layouteditor.h"
#include "positionablepopuputil.h"
#include "jtextfield.h"
#include <QAction>
#include "jtextfield.h"

Positionable* CoordinateEdit::pos = NULL;
QString CoordinateEdit::title = "";


/**
 * Displays and allows user to modify x & y coordinates of
 * positionable labels
 * This class has been generalized to provide popup edit dialogs for
 * positionable item properties when TextFields are needed to input data.
 * <P>
 * The class name no longer identifies the full purpose of the class, However
 * the name is retained because coordinate editing was the genesis.
 * The current list of properties served for editing is:
 * <LI>
 *  modify x & y coordinates
 *  modify level
 *  modify tooltip
 *  modify border size
 *  modify margin size
 *  modify fixed size
 *  modify rotation degrees
 *  modify scaling
 *  modify text labels
 *  modify zoom scaling
 *  modify panel name
 *  </LI>
 * To use, write a static method that provides the dialog frame.  Then
 * write an initX method that customizes the dialog for the property.
 *
 * @author Dan Boudreau Copyright (C) 2007
 * @author Pete Cressman Copyright (C) 2010
 * @version $Revision: 22320 $
 */

///*public*/ class CoordinateEdit extends JmriJFrame {
/*public*/ /*static*/ QAction* CoordinateEdit::getCoordinateEditAction(/*final*/ Positionable* pos, CoordinateEdit* parent)
{
//    return new AbstractAction(Bundle.getMessage("SetXY")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("SetXY"), pos, true);
//                f.initSetXY();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
  CoordinateEdit::pos = pos;
  QAction* setXYAction = new QAction(tr("SetXY"),parent);
  connect(setXYAction, SIGNAL(triggered()), parent, SLOT(on_setXYAction_triggered()));
  return setXYAction;
}
void CoordinateEdit::on_setXYAction_triggered()
{
 CoordinateEdit* f = new CoordinateEdit();
 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("Set x & y%1").arg(""), pos, true);
 f->initSetXY();
 f->setVisible(true);
 //f->setLocationRelativeTo((Component)pos);

}

//////////////////////////////////////////////////////////////
/*public*/ /*static*/ QAction* CoordinateEdit::getLevelEditAction(/*final*/ Positionable* /*pos*/, CoordinateEdit* parent)
{
//    return new AbstractAction(Bundle.getMessage("SetLevel")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("SetLevel"), pos, true);
//                f.initSetLevel();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
 QAction* levelEditAction = new QAction(tr("Set Level"),parent);
 connect(levelEditAction, SIGNAL(triggered()), parent, SLOT(on_levelEditAction_triggered()));
 return levelEditAction;
}
void CoordinateEdit::on_levelEditAction_triggered()
{
 CoordinateEdit* f = new CoordinateEdit();
 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("Set Level%1").arg(""), pos,true);
 f->initSetLevel();
 f->setVisible(true);
 //                f.setLocationRelativeTo((Component)pos);
}

//////////////////////////////////////////////////////////////
/*public*/ /*static*/ AbstractAction* CoordinateEdit::getTooltipEditAction(/*final*/ Positionable* pos, QObject* parent)
{
 return new TooltipEditAction(pos, tr("Set Tooltip"), (CoordinateEdit*)parent);
// {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("SetTooltip"), pos, true);
//                f.initSetTip();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
}
TooltipEditAction::TooltipEditAction(Positionable* pos, QString name, CoordinateEdit *coordinateEdit) : AbstractAction(name, coordinateEdit)
{
 this->pos = pos;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
void TooltipEditAction::actionPerformed(ActionEvent *)
{
 CoordinateEdit* f = new CoordinateEdit();
 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("Set Tooltip%1").arg(""),pos, true);
 f->initSetTip();
 f->setVisible(true);
// f->setLocationRelativeTo((QObject*)pos);
}

//////////////////////////////////////////////////////////////
/*public*/ /*static*/ QAction* CoordinateEdit::getBorderEditAction(/*final*/ Positionable* pos, QObject* parent)
{
 SetBorderSizeActionListener* actionListener = new SetBorderSizeActionListener(pos);
 QAction* act = new QAction(tr("Set Border Size"),parent);
 connect(act, SIGNAL(triggered()), actionListener, SLOT(actionPerformed()));
//    {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    CoordinateEdit f = new CoordinateEdit();
//                    f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                    f.init(Bundle.getMessage("SetBorderSize"), pos, true);
//                    f.initBorder();
//                    f.setVisible(true);
//                    f.setLocationRelativeTo((Component)pos);
//                }
//            };
//  this->pos = pos;
//  QAction* setBorderSizeAction = new QAction(tr("Set Border size"), parent);
//  connect(setBorderSizeAction, SIGNAL(triggered()), pos, SLOT(on_setBorderSizeAction_triggered()));
   return act;
}
SetBorderSizeActionListener::SetBorderSizeActionListener(Positionable *pos)
{
 this->pos = pos;
}

void SetBorderSizeActionListener::actionPerformed(ActionEvent */*e*/)
{
 CoordinateEdit* f = new CoordinateEdit();
 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("Set Border Size%1").arg(""),CoordinateEdit::pos, true);
 f-> initBorder();
 f->setVisible(true);
}
    //////////////////////////////////////////////////////////////

/*public*/ /*static*/ QAction* CoordinateEdit::getMarginEditAction(/*final*/ Positionable* pos, PositionablePopupUtil* parent)
{
//    return new AbstractAction(Bundle.getMessage("SetMarginSize")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("SetMarginSize"), pos, true);
//                f.initMargin();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
  CoordinateEdit::pos = pos;
  QAction* actionMarginEdit = new QAction(tr("Set Margin Size"), (QObject*)parent);
  connect(actionMarginEdit, SIGNAL(triggered()), parent, SLOT(on_actionMarginEdit_triggered()));
  return actionMarginEdit;
}
void PositionablePopupUtil::on_actionMarginEdit_triggered()
{
 CoordinateEdit* f = new CoordinateEdit();

 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("Set Margin Size%1").arg(""), CoordinateEdit::pos, true);
 f->initMargin();
 f->setVisible(true);
 //                f.setLocationRelativeTo((Component)pos);

}

//////////////////////////////////////////////////////////////

/*public*/ /*static*/ QAction* CoordinateEdit::getFixedSizeEditAction(/*final*/ Positionable* pos, PositionablePopupUtil* parent)
{
//    return new AbstractAction(Bundle.getMessage("SetFixedSize")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("SetFixedSize"), pos, true);
//                f.initFixedSize();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
    CoordinateEdit::pos = pos;
  QAction* actionGetFixedSizeEdit = new QAction(tr("Set Fixed Size"),parent);
  connect(actionGetFixedSizeEdit, SIGNAL(triggered()), parent, SLOT(on_actionGetFixedSizeEdit_triggered())); // TODO:
  return actionGetFixedSizeEdit;
}
void PositionablePopupUtil::on_actionGetFixedSizeEdit_triggered()
{
 CoordinateEdit* f = new CoordinateEdit();
 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("Set Fixed Size%1").arg(""), CoordinateEdit::pos, true);
 f->initFixedSize();
 f->setVisible(true);
    //                f.setLocationRelativeTo((Component)pos);
}

//////////////////////////////////////////////////////////////

/*public*/ /*static*/ QAction* CoordinateEdit::getRotateEditAction(/*final*/ Positionable* pos, CoordinateEdit* parent)
{
//    return new AbstractAction(Bundle.getMessage("rotate")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("rotate"), pos, true);
//                f.initRotate();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
 QAction* rotateAction = new QAction(tr("Rotate (degrees)"), parent);
 parent->pos = pos;
 connect(rotateAction, SIGNAL(triggered()), parent, SLOT(on_rotateAction_triggered()));
 return rotateAction;
}
void CoordinateEdit::on_rotateAction_triggered()
{
//    CoordinateEdit* f = new CoordinateEdit();
//    //f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//    f->init(tr("rotate"), pos, true);
//    f->initRotate();
//    f->setVisible(true);
    //f.setLocationRelativeTo((Component)pos);
    initRotate();
}

//////////////////////////////////////////////////////////////

/*public*/ /*static*/ QAction* CoordinateEdit::getScaleEditAction(/*final*/ Positionable* /*pos*/, CoordinateEdit* parent)
{
//    return new AbstractAction(Bundle.getMessage("scale")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("scale"), pos, true);
//                f.initScale();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
 QAction* scaleEditAction = new QAction(tr("Scale (percentage)"), parent);
 connect(scaleEditAction, SIGNAL(triggered()), parent, SLOT(on_getScaleEditAction_triggered()));
 return scaleEditAction;
}
void CoordinateEdit::on_getScaleEditAction_triggered()
{
    CoordinateEdit* f = new CoordinateEdit();
    //f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
    f->init(tr("Scale percentage: %1").arg(""), pos, true);
    f->initScale();
    f->setVisible(true);
    //f.setLocationRelativeTo((Component)pos);
}

//////////////////////////////////////////////////////////////

/*public*/ /*static*/ QAction* CoordinateEdit::getTextEditAction(/*const*/ Positionable* /*pos*/, const QString title, CoordinateEdit* parent)
{
 CoordinateEdit::title = title;
 QAction* textEditAction = new QAction(title, parent);
 connect(textEditAction, SIGNAL(triggered()), parent, SLOT(on_getTextEditAction_triggered()));
 return textEditAction;

//    return new AbstractAction((title)) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                CoordinateEdit f = new CoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage(title), pos, false);
//                f.initText();
//                f.setVisible(true);
//                f.setLocationRelativeTo((Component)pos);
//            }
//        };
}
void CoordinateEdit::on_getTextEditAction_triggered()
{
 CoordinateEdit* f = new CoordinateEdit();
// f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init((title), pos, false);
 f->initText();
 f->setVisible(true);
// f.setLocationRelativeTo((Component)pos);
}
//////////////////////////////////////////////////////////////
#if 0
    /*public*/ static AbstractAction getZoomEditAction(final Positionable pos) {
        return new AbstractAction(Bundle.getMessage("Zoom")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    CoordinateEdit f = new CoordinateEdit();
                    f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
                    f.init(Bundle.getMessage("Zoom"), pos, false);
                    f.initZoom();
                    f.setVisible(true);
                    //f.setLocation(100,100);
                    f.setLocationRelativeTo(pos.getEditor().getTargetPanel());
                }
            };
    }
    //////////////////////////////////////////////////////////////
#endif
    /*public*/ /*static*/ QAction* CoordinateEdit::getNameEditAction(/*final*/ Positionable* /*pos*/) {
       QAction* act = new QAction(tr("Rename Panel Menu"),this);
       connect(act, SIGNAL(triggered()), this, SLOT(renamePanelMenu()));
       return act;
}
/*public*/ void CoordinateEdit::renamePanelMenu(/*ActionEvent e*/) {
    CoordinateEdit* f = new CoordinateEdit();
//    f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
    f->init(tr("Rename Panel Menu"), pos, false);
    f->initSetName();
    f->setVisible(true);
    //f.setLocation(100,100);
//    f->setLocationRelativeTo(pos->getEditor()->getTargetPanel());
}
    //////////////////////////////////////////////////////////////
CoordinateEdit::CoordinateEdit(QWidget *parent) : JmriJFrame("<CoordinateEdit>", false,false, parent)
{
 this->parent = parent;
 nameText = new QLabel();
 okButton = new QPushButton();
 cancelButton = new QPushButton();
 setMinimumSize(200,100);
 log = new Logger("CoordinateEdit");
}
#if 0
    /*public*/ void windowClosed(java.awt.event.WindowEvent e) {
        super.windowClosed(e);
    }
#endif
/*public*/ void CoordinateEdit::init(QString title, Positionable* pos, bool showName)
{
 pl = pos;
 //ps = qobject_cast<PositionableLabel*>(pos);
 if (showName)
 {
  //nameText->setText(/*java.text.MessageFormat.format(Bundle.getMessage("namelabel"),*/ ((PositionableLabel*)pos)->getNameString());
  nameText->setText(QString("Name: %1").arg(((PositionableLabel *)pos)->getNameString()));
  nameText->setVisible(true);
 }
 okButton->setText(tr("Set"));
 okButton->setVisible(true);

 cancelButton->setText(tr("Cancel"));
 cancelButton->setVisible(true);

 QSize dim = QSize(79,26);
 okButton->setMinimumSize(dim);
 //okButton->setFixedHeight(dim.height());
 cancelButton->setMinimumSize(dim);
 //cancelButton->setFixedHeight(dim.height());
 setWindowTitle(title);
   //setLocation(pl->getLocation());
}

/*public*/ void CoordinateEdit::initSetXY()
{
 resize(182,130);
 textX = new QLabel(this);
 textY = new QLabel(this);

 if(pl != NULL)
 {
  oldX = pl->getX();
  oldY = pl->getY();

  textX->setText("x= " + QString("%1").arg(pl->getX()));
  textY->setText("y= " + QString("%1").arg(pl->getY()));
 }
 textX->setVisible(true);
 textY->setVisible(true);

 //SpinnerNumberModel model = new SpinnerNumberModel(0,0,10000,1);
//    ChangeListener listener = new ChangeListener() {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                int x = ((Number)spinX.getValue()).intValue();
//                int y = ((Number)spinY.getValue()).intValue();
//                pl.setLocation(x, y);
//                textX.setText("x= " + pl.getX());
//                textY.setText("y= " + pl.getY());
//            }
//        };

 spinX = new QSpinBox(/*model*/);
 spinX->setMinimum(-1000);
 spinX->setMaximum(1000);
 spinX->setValue((pl->getX()));
 spinX->setToolTip(tr("Enter x coordinate"));
 spinX->setMaximumSize(QSize(spinX->maximumSize().width(), spinX->maximumSize().height()));
 //spinX.addChangeListener(listener);
 //model = new javax.swing.SpinnerNumberModel(0,0,10000,1);
 spinY = new QSpinBox(/*model*/);
 spinY->setMinimum(-1000);
 spinY->setMaximum(1000);
 spinY->setValue((pl->getY()));
 spinY->setToolTip("Enter y coordinate");
 spinY->setMaximumSize(spinY->maximumSize().width(), spinY->maximumSize().height());
 //spinY->addChangeListener(listener);
 connect(spinX, SIGNAL(valueChanged(int)), this, SLOT(on_setXYSpinnerValues_changed()));
 connect(spinY, SIGNAL(valueChanged(int)), this, SLOT(on_setXYSpinnerValues_changed()));

 //getContentPane().setLayout(new GridBagLayout());
 QWidget* centralWidget = new QWidget;
 setCentralWidget(centralWidget);
 gridLayout = new QGridLayout(centralWidget);
gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
 addSpinItems(true);


//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int x = ((Number)spinX.getValue()).intValue();
//            int y = ((Number)spinY.getValue()).intValue();
//            pl.setLocation(x, y);
//            textX.setText("x= " + pl.getX());
//            textY.setText("y= " + pl.getY());
//            dispose();
//        }
//    });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_setXYOkButton_clicked()));
//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            pl.setLocation(oldX, oldY);
//            dispose();
//        }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_setXYCancelButton_clicked()));
 adjustSize();
}
void CoordinateEdit::on_setXYOkButton_clicked()
{
//    int x = ((Number)spinX.getValue()).intValue();
//    int y = ((Number)spinY.getValue()).intValue();
 int x = spinX->value();
 int y = spinY->value();
 if(pl != NULL)
 {
  pl->setLocation(x, y);
  textX->setText("x= " + QString("%1").arg(pl->getX()));
  textY->setText("y= " + QString("%1").arg(pl->getY()));
 }
 //accept();
 //dispose();
 close();
}
void CoordinateEdit::on_setXYCancelButton_clicked()
{
 if(pl != NULL)
  pl->setLocation(oldX, oldY);

 //reject();
 //dispose();
 close();
}
void CoordinateEdit::on_setXYSpinnerValues_changed()
{
 int x = spinX->value();
 int y = spinY->value();
 if(pl != NULL)
 {
  pl->setLocation(x, y);
  textX->setText("x= " + QString("%1").arg(pl->getX()));
  textY->setText("y= " + QString("%1").arg(pl->getY()));
 }
}


/*public*/ void CoordinateEdit::initSetLevel()
{
 textX = new QLabel();
 textX->setText(tr("Display level"));
 if(pl != NULL)
 {
  oldX = pl->getDisplayLevel();
  textX->setText("level= " +QString::number(pl->getDisplayLevel()));
 }
 textX->setVisible(true);

 //SpinnerNumberModel model = new SpinnerNumberModel(0,0,10,1);
 spinX = new QSpinBox(/*model*/);
 spinX->setMinimum(0);
 spinX->setMaximum(10);
 spinX->setValue(pl->getDisplayLevel());
 spinX->setToolTip("Enter display level");
 spinX->setMaximumSize(QSize(spinX->maximumSize().width(), spinX->maximumSize().height()));

    //getContentPane().setLayout(new GridBagLayout());
 QWidget* centralWidget = new QWidget;
 setCentralWidget(centralWidget);
 gridLayout = new QGridLayout(centralWidget);
 gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
 addSpinItems(false);

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int l = ((Number)spinX.getValue()).intValue();
//            pl.setDisplayLevel(l);
//            textX.setText("level= " + l);
//            dispose();
//        }
//    });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_setLevelOkButton_clicked()));
//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            pl.setDisplayLevel(oldX);
//            dispose();
//        }
//    });
    pack();
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_setLevelCancelButton_clicked()));
}
void CoordinateEdit::on_setLevelOkButton_clicked()
{
 if(pl != NULL)
 {
  pl->setLevel(spinX->value());
 }
 //accept();
 close();
}
void CoordinateEdit::on_setLevelCancelButton_clicked()
{
 if(pl != NULL)
 {
  pl->setLevel(oldX);
 }
 //reject();
 close();
}

#if 1
/*public*/ void CoordinateEdit::initSetTip()
{
 oldStr = pl->toolTip();
 textX = new QLabel();
 textX->setText("Tooltip ");
 textX->setVisible(true);

 xTextField = new JTextField(15);
 xTextField->setText(pl->toolTip());
 xTextField->setToolTip("Enter Tooltip");
//		xTextField.setMaximumSize(new Dimension(
//				xTextField.getMaximumSize().width+100, xTextField.getPreferredSize().height));

 //getContentPane().setLayout(new GridBagLayout());
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 setCentralWidget(centralWidget);
 gridLayout = new QGridLayout;
 centralWidgetLayout->addLayout(gridLayout);

 addTextItems();

// okButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         pl.getTooltip().setText(xTextField.getText());
//         dispose();
//     }
// });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_okSetTip_clicked()));

// cancelButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         pl.getTooltip().setText(oldStr);
//         dispose();
//     }
// });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancel()));
 adjustSize();
}
#endif
void CoordinateEdit::on_okSetTip_clicked()
{
 //pl->getTooltip().setText(xTextField.getText());
 pl->setToolTip(xTextField->text());
 pl->updateScene();
 dispose();
}

void CoordinateEdit::on_cancel()
{
 pl->setToolTip(oldStr);
 pl->updateScene();
 dispose();
}

/*public*/ void CoordinateEdit::initBorder()
{
 pl = CoordinateEdit::pos;
 Q_ASSERT(pl != NULL);

 //ps = (PositionableLabel*)pos;
 PositionablePopupUtil* util = pl->getPopupUtility();
 oldX = util->getBorderSize();

 textX = new QLabel();
 textX->setText("Border= "+util->getBorderSize());
 textX->setVisible(true);

 //SpinnerNumberModel model = new SpinnerNumberModel(0,0,1000,1);
 spinX = new QSpinBox;
 spinX->setValue(util->getBorderSize());
 spinX->setToolTip("Enter border size");
 spinX->setMaximumSize(QSize(spinX->maximumSize().width(), spinX->maximumSize().height()));

 //getContentPane().setLayout(new GridBagLayout());
 QVBoxLayout *centralWidgetLayout;
 if(getContentPane() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  centralWidget->setLayout( centralWidgetLayout = new QVBoxLayout(centralWidget));
  setCentralWidget(centralWidget);
 }
 else
  centralWidgetLayout = new QVBoxLayout(centralWidget());

 gridLayout = new QGridLayout();
 centralWidgetLayout->addLayout(gridLayout);
 gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

 addSpinItems(false);

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int l = ((Number)spinX.getValue()).intValue();
//            pl.getPopupUtility().setBorderSize(l);
//            textX.setText("Border= " + l);
//            dispose();
//        }
//    });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_initBorderOkButton_clicked()));

//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            pl.getPopupUtility().setBorderSize(oldX);
//            dispose();
//        }
//    });
 pack();
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_initBorderCancelButton_clicked()));
}

void CoordinateEdit::on_initBorderOkButton_clicked()
{
 int l = spinX->value();
 ((PositionableLabel*)pl)->getPopupUtility()->setBorderSize(l);
 ((PositionableLabel*)pl)->_editor->addToTarget(pl);

 textX->setText("Border= " + l);
    //            dispose();
    //accept();
 close();
}
void CoordinateEdit::on_initBorderCancelButton_clicked()
{
 ((PositionableLabel*)pl)->getPopupUtility()->setBorderSize(oldX);
 //reject();
 close();

}
void CoordinateEdit::initMargin()
{
 pl = CoordinateEdit::pos;
 Q_ASSERT(pl != NULL);

 PositionablePopupUtil* util = ((PositionableLabel*)pl)->getPopupUtility();
 oldX = util->getMargin();

 textX = new QLabel();
 textX->setText(tr("Margin= ")+QString("%1").arg(util->getMargin()));
 textX->setVisible(true);

 //SpinnerNumberModel model = new SpinnerNumberModel(0,0,1000,1);
 spinX = new QSpinBox(/*model*/);
 spinX->setValue((util->getMargin()));
 spinX->setToolTip(tr("Enter margin size"));
 spinX->setMaximumSize( QSize(spinX->maximumSize().width(), spinX->maximumSize().height()));

 //getContentPane().setLayout(new GridBagLayout());
 QVBoxLayout *centralWidgetLayout;
 if(getContentPane() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  centralWidget->setLayout( centralWidgetLayout = new QVBoxLayout);
 }
 else
  centralWidgetLayout = (QVBoxLayout*)getContentPane()->layout();

 gridLayout = new QGridLayout();
 centralWidgetLayout->addLayout(gridLayout);
 gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

 addSpinItems(false);

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int l = ((Number)spinX.getValue()).intValue();
//            pl.getPopupUtility().setMargin(l);
//            textX.setText("Margin= " + l);
//            dispose();
//        }
//    });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_initMarginOkButton_clicked()));
//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            pl.getPopupUtility().setMargin(oldX);
//            dispose();
//        }
//    });
 adjustSize();
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_initMarginCancelButton_clicked()));
}
void CoordinateEdit::on_initMarginOkButton_clicked()
{
 int l = (spinX->value());
 ((PositionableLabel*)pl)->getPopupUtility()->setMargin(l);
 textX->setText("Margin= " + QString("%1").arg(l));
 //accept();
 close();
}
void CoordinateEdit::on_initMarginCancelButton_clicked()
{
 ((PositionableLabel*)pl)->getPopupUtility()->setMargin(oldX);
 //reject();
 close();
}

/*public*/ void CoordinateEdit::initFixedSize()
{
 PositionablePopupUtil* util = ((PositionableLabel*)pl)->getPopupUtility();
 oldX = util->getFixedHeight();
 oldY = util->getFixedWidth();

 textX = new QLabel();
 textX->setText("Height= " + QString("%1").arg(util->getFixedHeight()));
 textX->setVisible(true);
 textY = new QLabel();
 textY->setText("Width= " + QString("%1").arg(util->getFixedWidth()));
 textY->setVisible(true);

 //SpinnerNumberModel model = new SpinnerNumberModel(0,0,1000,1);
 spinX = new QSpinBox();
 spinX->setMaximum(1000);
 spinX->setValue((util->getFixedHeight()));
 spinX->setToolTip(tr("FixedSizeHeight"));
 spinX->setMaximumSize( QSize(spinX->maximumSize().width(), spinX->maximumSize().height()));
//    model = new javax.swing.SpinnerNumberModel(0,0,1000,1);
 spinY = new QSpinBox();
 spinY->setMaximum(1000);
 spinY->setValue((util->getFixedWidth()));
 spinY->setToolTip(tr("FixedSizeWidth"));
 spinY->setMaximumSize( QSize(spinY->maximumSize().width(), spinY->maximumSize().height()));

    //getContentPane().setLayout(new GridBagLayout());
 QWidget* centralWidget = new QWidget;
 setCentralWidget(centralWidget);
 gridLayout = new QGridLayout(centralWidget);
 gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

 addSpinItems(true);

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int height = ((Number)spinX.getValue()).intValue();
//            int width = ((Number)spinY.getValue()).intValue();
//            PositionablePopupUtil util = pl.getPopupUtility();
//            util.setFixedSize(width, height);
//            textX.setText("Height= " + util.getFixedHeight());
//            textY.setText("Width= " + util.getFixedWidth());
//            dispose();
//        }
//    });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_initFixedSizeOkBubbon_clicked()));
//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            pl.getPopupUtility().setFixedSize(oldY, oldX);
//            dispose();
//        }
//    });
 adjustSize();
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_initFixedSizeCancelButton_clicked()));
}

void CoordinateEdit::on_initFixedSizeCancelButton_clicked()
{
 ((PositionableLabel*)pl)->getPopupUtility()->setFixedSize(oldY, oldX);
 //reject();
 close();
}
void CoordinateEdit::on_initFixedSizeOkBubbon_clicked()
{
 int height = (spinX->value());
 int width = (spinY->value());
 PositionablePopupUtil* util = ((PositionableLabel*)pl)->getPopupUtility();
 util->setFixedSize(width, height);
 textX->setText("Height= " + QString("%1").arg(util->getFixedHeight()));
 textY->setText("Width= " + QString("%1").arg(util->getFixedWidth()));
 //accept();
 close();
}

/*public*/ void CoordinateEdit::initRotate()
{
 //oldX = pl->getDegrees();
 //ps = qobject_cast<PositionableLabel*>(pos);

//    textX = new javax.swing.JLabel();
//    int deg = oldX;
//    textX.setText(java.text.MessageFormat.format(Bundle.getMessage("Angle"), deg));
//    textX.setVisible(true);

//    SpinnerNumberModel model = new SpinnerNumberModel(0,-360,360,1);
//    spinX = new javax.swing.JSpinner(model);
////        spinX.setValue(Integer.valueOf(((NamedIcon)pLabel.getIcon()).getDegrees()));
//    spinX.setValue(deg);
//    spinX.setToolTipText(Bundle.getMessage("enterDegrees"));
//    spinX.setMaximumSize(new Dimension(
//            spinX.getMaximumSize().width, spinX.getPreferredSize().height));

//    getContentPane().setLayout(new GridBagLayout());

//    addSpinItems(false);

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int k = ((Number)spinX.getValue()).intValue();
//            pl.getEditor().setSelectionsRotation(k, pl);
//            textX.setText(java.text.MessageFormat.format(Bundle.getMessage("Angle"), k));
//            dispose();
//        }
//    });
//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            dispose();
//        }
//    });
    pack();
 InputAngleDlg* dlg = new InputAngleDlg(pos->getDegrees(),this);
 if(dlg->exec() == QDialog::Accepted)
 {
  //(PositionableLabel*)pl->getEditor()->setSelectionsRotation(dlg->angle(), pl);
  Editor* editor =   pos->getEditor();
  editor->setSelectionsRotation(dlg->angle(), (Positionable*)pos);
 }
}

/*public*/ void CoordinateEdit::initScale()
{
 //int scale = (int)Math.round(pl.getScale()*100);
 oldD = pl->getScale();

 textX = new QLabel();
 textX->setText(tr("Scale percent %1").arg(oldD*100));
 textX->setVisible(true);

 SpinnerNumberModel* model = new SpinnerNumberModel(100.0,10.0,5000.0,1.0);
 spinX = new QSpinBox(/*model*/);
 spinX->setValue(model->getValue().toInt());
 spinX->setMinimum(model->getMinimum().toInt());
 spinX->setMaximum(model->getMaximum().toInt());
 spinX->setSingleStep(model->getStepSize().toInt());
 if (log->isDebugEnabled()) { log->debug("scale%= "+(int)qRound(oldD*100));
 }
 spinX->setValue((int)qRound(oldD*100));
 spinX->setToolTip(tr("Enter scale percentage"));
 spinX->setMaximumSize(QSize(
                        spinX->sizeHint().width(), spinX->sizeHint().height()));

 //getContentPane().setLayout(new GridBagLayout());
 QWidget* centralWidget = new QWidget;
 setCentralWidget(centralWidget);
 centralWidget->setLayout(new QGridLayout);

 addSpinItems(false);

// okButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         double s = ((Number)spinX.getValue()).doubleValue()/100;
//         pl.getEditor().setSelectionsScale(s, pl);
//         textX.setText(java.text.MessageFormat.format(Bundle.getMessage("Scale"), pl.getScale()*100));
//         dispose();
//     }
// });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_scaleOk_clicked()));
 // cancelButton.addActionListener(new java.awt.event.ActionListener() {
 //     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
 //         dispose();
 //     }
 // });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_scaleCancel_clicked()));
 adjustSize();
}

void CoordinateEdit::on_scaleOk_clicked()
{
 double s = spinX->value()/100;
 pl->getEditor()->setSelectionsScale(s, pl);
 textX->setText(tr("Scale percent %1").arg( pl->getScale()*100));
 dispose();
}
void CoordinateEdit::on_scaleCancel_clicked()
{
 dispose();
}

/*public*/ void CoordinateEdit::initText()
{
    PositionableLabel* pLabel = (PositionableLabel*)pl;
    oldStr = pLabel->getUnRotatedText();
    textX = new QLabel();
    textX->setText("Text= ");
    textX->setVisible(true);

    xTextField = new JTextField();
    xTextField->setMaxLength(15);
    xTextField->setText(pLabel->getUnRotatedText());
    xTextField->setToolTip("Enter Text");

    //getContentPane().setLayout(new GridBagLayout());
    gridLayout = new QGridLayout(this);
    addTextItems();

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            PositionableLabel pp = (PositionableLabel)pl;
//            QString t = xTextField.getText();
//            boolean hasText = (t!=null && t.length()>0);
//            if (pp.isIcon() || hasText) {
//                pp._text = hasText;
//                pp.setText(t);
//                pp.updateSize();
//                dispose();
//            } else {
//                xTextField.setText("Item disappears with null text!");
//            }
//        }
//    });
    connect(okButton, SIGNAL(clicked()), this, SLOT(on_editTextOkButton_clicked()));
//    cancelButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            PositionableLabel pp = (PositionableLabel)pl;
//            pp.setText(oldStr);
//            pp.updateSize();
//            dispose();
//        }
//    });
    pack();
    connect(cancelButton, SIGNAL(clicked()),this, SLOT(on_editTextCancelButton_clicked()));
}
void CoordinateEdit::on_editTextOkButton_clicked()
{
 PositionableLabel* pp = (PositionableLabel*)pl;
 QString t = xTextField->text();
 bool hasText = (!t.isEmpty());
 if (pp->isIcon() || hasText)
 {
  pp->_text = hasText;
  pp->setText(t);
  pp->updateSize();
  //accept();
  close();
   //                dispose();
 } else
 {
  xTextField->setText("Item disappears with null text!");
 }
}
void CoordinateEdit::on_editTextCancelButton_clicked()
{
 PositionableLabel* pp = (PositionableLabel*)pl;
 pp->setText(oldStr);
 pp->updateSize();
 //reject();
 close();
}

#if 0
    /*public*/ void initZoom() {
        oldD = pl.getScale();

        textX = new javax.swing.JLabel();
        textX.setText(java.text.MessageFormat.format(Bundle.getMessage("Scale"), oldD*100));
        textX.setVisible(true);

        SpinnerNumberModel model = new SpinnerNumberModel(100.0,1.0,5000.0,1.0);
        spinX = new javax.swing.JSpinner(model);
        if (log.isDebugEnabled()) { log.debug("scale%= "+(int)Math.round(oldD*100));
        }
        spinX.setToolTipText(Bundle.getMessage("enterZoom"));
        spinX.setMaximumSize(new Dimension(
                spinX.getMaximumSize().width, spinX.getPreferredSize().height));

        getContentPane().setLayout(new GridBagLayout());

        addSpinItems(false);

        okButton.addActionListener(new java.awt.event.ActionListener() {
            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                double s = ((Number)spinX.getValue()).doubleValue()/100;
                pl.setScale(s);
                pl.getEditor().setPaintScale(s);
                textX.setText(java.text.MessageFormat.format(Bundle.getMessage("Scale"), pl.getScale()*100));
                dispose();
            }
        });
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                dispose();
            }
        });
        pack();
    }

#endif
    /*public*/ void  CoordinateEdit::initSetName()
{
 oldStr = pl->getEditor()->getName();

 textX = new JLabel();
 textX->setText(tr("Name: %1").arg(oldStr));
 textX->setVisible(true);

 xTextField = new JTextField(15);
 xTextField->setText(oldStr);
 xTextField->setToolTip(tr("Enter new name:"));
//		xTextField.setMaximumSize(new Dimension(1000, xTextField.getPreferredSize().height));
//				xTextField.getMaximumSize().width+100, xTextField.getPreferredSize().height));
 //getContentPane().setLayout(new GridBagLayout());
 QWidget* centralWidget = new QWidget;
 setCentralWidget(centralWidget);
 centralWidget->setLayout(new QGridLayout);

 addTextItems();

// okButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         QString t = xTextField.getText();
//         Editor ed = pl.getEditor();
//         ed.setName(t);
//         ed.setTitle();
//         textX.setText(java.text.MessageFormat.format(Bundle.getMessage("namelabel"), t));
//         dispose();
//     }
// });
 connect(okButton, SIGNAL(clicked()), this, SLOT(on_okSetName_clicked()));
// cancelButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         pl.getEditor().setName(oldStr);
//         dispose();
//     }
// });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelSetName_clicked()));
 pack();
}

void CoordinateEdit::on_okSetName_clicked()
{
 QString t = xTextField->text();
 Editor* ed = pl->getEditor();
 ed->setName(t);
 ed->setTitle();
 textX->setText(tr("Name: %1").arg(t));
 dispose();
}

void CoordinateEdit::on_cancelSetName_clicked()
{
 pl->getEditor()->setName(oldStr);
 dispose();
}

/*protected*/ void CoordinateEdit::addSpinItems(bool addY)
{
  gridLayout->addWidget(nameText, 0, 0, 1, 2);
  gridLayout->addWidget(textX, 1, 0, 1, 1);
  gridLayout->addWidget(spinX, 1, 1, 1, 1);
  if (addY)
  {
   gridLayout->addWidget(textY, 2, 0, 1, 1);
   gridLayout->addWidget(spinY, 2, 1, 1, 1);
   gridLayout->addWidget(cancelButton, 3, 0, 1, 1);
   gridLayout->addWidget(okButton, 3, 1, 1, 1);
  }
  else
  {
   gridLayout->addWidget(cancelButton, 2, 0, 1, 1);
   gridLayout->addWidget(okButton, 2, 1, 1, 1);
  }
  //validate();
  QMetaObject::connectSlotsByName(this);
}


/*private*/ void CoordinateEdit::addTextItems()
{
 gridLayout->addWidget(nameText, 0, 0, 1, 2);
 gridLayout->addWidget(textX, 1, 0, 1, 1);
 gridLayout->addWidget(xTextField, 1, 1, 1, 2);
 gridLayout->addWidget(cancelButton, 2, 0, 1, 1);
 gridLayout->addWidget(okButton, 2, 1, 1, 1);
 //validate();
}
#if 0
//private void CoordinateEdit::addItem(QObject* c, int x, int y, int w, bool horzExpand) {
//    GridBagConstraints gc = new GridBagConstraints();
//    gc.gridx = x;
//    gc.gridy = y;
//    gc.gridwidth = w;
//    gc.weightx = 100.0;
//    gc.weighty = 100.0;
//    gc.anchor = java.awt.GridBagConstraints.CENTER;
//    if (horzExpand) {
//        gc.fill = java.awt.GridBagConstraints.HORIZONTAL;  // text field will expand
//    }
//    getContentPane().add(c, gc);
//}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CoordinateEdit.class.getName());
//}
#endif
