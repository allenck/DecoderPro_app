#include "itemdialog.h"
#include "familyitempanel.h"

//ItemDialog::ItemDialog(QWidget *parent) :
//    QDialog(parent)
//{
//}
/**
 * @author Pete Cressman  Copyright (c) 2010
 */

// /*public*/ class ItemDialog extends JDialog {

/*private*/ /*static*/ ItemDialog* ItemDialog::_instance = nullptr;		// only let one dialog at a time

/**
*/
/*public*/ ItemDialog::ItemDialog(QString type, QString title, QWidget *parent)
 : JmriJFrame(title, true, true, parent)
{
 if (_instance != nullptr) {
     _instance->dispose();
 }
 _instance = this;
 _type = type;
}

/*protected*/ QString ItemDialog::getDialogType()
{
 return _type;
}

/*protected*/ void ItemDialog::closeDialogs() {
}

//@Override
/*public*/ void ItemDialog::dispose() {
    closeDialogs();
    JmriJFrame::dispose();
    _instance = nullptr;	// remove reference to allow gc
}

/*public*/ QString ItemDialog::getClassName() {return "jmri.jmrit.display.palette.ItemDialog";}
