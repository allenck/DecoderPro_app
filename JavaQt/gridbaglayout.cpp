#include "gridbaglayout.h"
#include "gridbagconstraints.h"

GridBagLayout::GridBagLayout(QWidget* parent) : QGridLayout(parent)
{

}
void GridBagLayout::addWidget(QWidget *widget, GridBagConstraints gb)
{
 int x;
 int y;
 if(gb.insets->top == 0)
  lastY = -1;
 if(gb.insets->left == 0)
  lastX = -1;
 if(gb.gridy ==  GridBagConstraints::_RELATIVE /*&& (gb.gridwidth != GridBagConstraints::REMAINDER) */)
  y = ++lastY;
 else
  y = gb.gridy;
 if(gb.gridx ==  GridBagConstraints::_RELATIVE /*&& (gb.gridheight != GridBagConstraints::REMAINDER)*/)
  x = ++lastX;
 else
  x = gb.gridx;
 QGridLayout::addWidget(widget, y, x, gb.rowSpan(), gb.colSpan()/*, gb.align()*/);
}

void GridBagLayout::columnWidths(QList<int> columns)
{
 for(int i =0; i < columns.count(); i++)
  setColumnMinimumWidth(i, columns.at(i));
}
void GridBagLayout::rowHeights(QList<int> rows)
{
 for(int i =0; i < rows.count(); i++)
  setRowMinimumHeight(i, rows.at(i));
}

void GridBagLayout::setConstraints(GridBagConstraints gbc)
{
 this->gbc = gbc;
}
