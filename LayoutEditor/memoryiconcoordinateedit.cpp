#include "memoryiconcoordinateedit.h"

//MemoryIconCoordinateEdit::MemoryIconCoordinateEdit(QObject *parent) :
//    CoordinateEdit(parent)
//{
//}
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
 *  modify rotation degress
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

///*public*/ class MemoryIconCoordinateEdit extends CoordinateEdit {


/*public*/ void MemoryIconCoordinateEdit::init(QString title, MemoryIcon* pos, bool showName) {
    CoordinateEdit::init(title, (Positionable*)pos, showName);
    pl = pos;
}

/*public*/ /*static*/ QAction* MemoryIconCoordinateEdit::getCoordinateEditAction(/*final*/ MemoryIcon* pos, QWidget* parent)
{
//    return new AbstractAction(Bundle.getMessage("SetXY")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                MemoryIconCoordinateEdit f = new MemoryIconCoordinateEdit();
//                f.addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
//                f.init(Bundle.getMessage("SetXY"), pos, true);
//                f.initSetXY();
//                f.setVisible(true);
//                f.setLocationRelativeTo(pos);
//            }
//        };
    SetXYAbstractAction* setXYAct = new SetXYAbstractAction(pos, parent);
    connect(setXYAct, SIGNAL(triggered()), setXYAct, SLOT(onSetXYAction()));

    return setXYAct;
}
SetXYAbstractAction::SetXYAbstractAction(MemoryIcon *pos, QWidget *parent) : QAction(parent)
{
 this->pos = pos;
 this->parent = parent;
 setText(tr("SetXY"));
}

void SetXYAbstractAction::onSetXYAction()
{
 MemoryIconCoordinateEdit* f = new MemoryIconCoordinateEdit();
 f->addHelpMenu("package.jmri.jmrit.display.CoordinateEdit", true);
 f->init(tr("SetXY"), (MemoryIcon*)pos, true);
 f->initSetXY();
 f->setVisible(true);
 //f.setLocationRelativeTo(pos);
}

/*public*/ void MemoryIconCoordinateEdit::initSetXY() {
    oldX = pl->getOriginalX();
    oldY = pl->getOriginalY();

    textX = new QLabel();
    textX->setText("x= " + QString("%1").arg(pl->getOriginalX()));
    textX->setVisible(true);
    textY = new QLabel();
    textY->setText("y= " + QString("%1").arg(pl->getOriginalY()));
    textY->setVisible(true);

    //SpinnerNumberModel model = new SpinnerNumberModel(0,0,10000,1);
//    ChangeListener* listener = new ChangeListener()
//    {
//            /*public*/ void stateChanged(ChangeEvent e) {
//            int x = ((Number)spinX.getValue()).intValue();
//            int y = ((Number)spinY.getValue()).intValue();
//            pl.setLocation(x, y);
//            textX.setText("x= " + pl.getOriginalX());
//            textY.setText("y= " + pl.getOriginalY());
//}
//};
    spinX = new QSpinBox();
    spinX->setMaximum(10000);
    spinX->setValue((pl->getOriginalX()));
    spinX->setToolTip(tr("Enter x coordinate"));
    spinX->setMaximumSize( QSize(
                              spinX->maximumSize().width(), spinX->maximumSize().height()));
    //spinX->addChangeListener(listener);
    //model = new javax.swing.SpinnerNumberModel(0,0,10000,1);
    spinY = new QSpinBox();
    spinY->setMaximum(10000);
    spinY->setValue(pl->getOriginalY());
    spinY->setToolTip(tr("Enter y coordinate"));
    spinY->setMaximumSize( QSize(
                               spinY->maximumSize().width(), spinY->maximumSize().height()));
    //spinY.addChangeListener(listener);

    //getContentPane().setLayout(new GridBagLayout());
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    addSpinItems(true);

//    okButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            int x = ((Number)spinX.getValue()).intValue();
//            int y = ((Number)spinY.getValue()).intValue();
//            pl.setLocation(x, y);
//            textX.setText("x= " + pl.getOriginalX());
//            textY.setText("y= " + pl.getOriginalY());
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
//    pack();

}
void MemoryIconCoordinateEdit::on_setXYOkButton_clicked()
{
 int x = spinX->value();
 int y = spinY->value();
    pl->setLocation(x, y);
    textX->setText("x= " + QString("%1").arg(pl->getOriginalX()));
    textY->setText("y= " + QString("%1").arg(pl->getOriginalY()));
    //dispose();
    //accept();
    close();
}
void MemoryIconCoordinateEdit::on_setXYCancelButton_clicked()
{
  pl->setLocation(oldX, oldY);
  //reject();
  close();
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(MemoryIconCoordinateEdit.class.getName());
//}
