#include "itemdialog.h"
#include "itempanel.h"

//ItemDialog::ItemDialog(QWidget *parent) :
//    QDialog(parent)
//{
//}
/**
 * @author Pete Cressman  Copyright (c) 2010
 */

// /*public*/ class ItemDialog extends JDialog {


/**
*/
/*public*/ ItemDialog::ItemDialog(QString type, QString family, QString title, ItemPanel* parent, bool mode) : JDialog((QWidget*)parent->_paletteFrame, title, mode)
{
 //super(parent._paletteFrame, title, mode);
 _type = type;
 _family = family;
 _parent = parent;
}

/*protected*/ void ItemDialog::sizeLocate()
{
 //setSize(_parent->size().width(), this->sizeHint().height());
 resize(_parent->size().width(), this->sizeHint().height());
// setLocationRelativeTo(_parent);
 setVisible(true);
 pack();
}

/*protected*/ QString ItemDialog::getDialogType()
{
 return _type;
}
