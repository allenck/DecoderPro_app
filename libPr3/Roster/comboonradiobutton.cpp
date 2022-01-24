#include "comboonradiobutton.h"

//ComboOnRadioButton::ComboOnRadioButton(QWidget *parent) :
//    ComboRadioButtons(parent)
//{
//}
/* Represents a JComboBox as a JPanel containing just the "on" button
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version
 */
// /*public*/ class ComboOnRadioButton extends ComboRadioButtons {

ComboOnRadioButton::ComboOnRadioButton(QComboBox* box, EnumVariableValue* var, QWidget *parent) : ComboRadioButtons(box,var, parent)
{
    //super(box, var);
    for(int i =0; i < v->count(); i++)
        addToPanel(v->at(i), i);
}

/**
 * Make only the "on" button visible
 */
void ComboOnRadioButton::addToPanel(QRadioButton* b, int i)
{
 if(i !=0)
  b->setVisible(true);
 else b->setVisible(false);
}
