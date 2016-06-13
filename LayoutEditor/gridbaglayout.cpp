#include "gridbaglayout.h"
#include "gridbagconstraints.h"

GridBagLayout::GridBagLayout(QWidget* parent) : QGridLayout(parent)
{

}
void GridBagLayout::addWidget(QWidget *widget, GridBagConstraints gb)
{
 QGridLayout::addWidget(widget, gb.gridy, gb.gridx, gb.rowSpan(), gb.colSpan(), gb.align());
}

