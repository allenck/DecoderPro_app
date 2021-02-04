#include "combooffradiobutton.h"

//ComboOffRadioButton::ComboOffRadioButton(QWidget *parent) :
//    ComboRadioButtons(parent)
//{
//}
/* Represents a JComboBox as a JPanel containing just the "off" button
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 17977 $
 */
// /*public*/ class ComboOffRadioButton extends ComboRadioButtons {

ComboOffRadioButton::ComboOffRadioButton(QComboBox* box, EnumVariableValue* var, QWidget *parent) : ComboRadioButtons(box, var, parent)
{
    //super(box, var);
    for(int i =0; i < v->count(); i++)
        addToPanel(v->at(i), i);
}

/**
 * Make only the "on" button visible
 */
void ComboOffRadioButton::addToPanel(QRadioButton* b, int i)
{
 if (i==0)
  b->setVisible(true);
 else b->setVisible(false);
}
