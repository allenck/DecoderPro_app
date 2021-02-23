#include "gridbaglayout.h"
#include "gridbagconstraints.h"

GridBagLayout::GridBagLayout(QWidget* parent) : QGridLayout(parent)
{

}

void GridBagLayout::addWidget(QWidget *widget, GridBagConstraints gb)
{
 this->gbc = gb;
 int x;
 int y;
 if(gbc.insets->top == 0)
  lastY = -1;
 if(gbc.insets->left == 0)
  lastX = -1;
 if(gbc.gridy ==  GridBagConstraints::_RELATIVE && (gbc.gridwidth != GridBagConstraints::REMAINDER) )
  y = ++lastY;
 else
  y = gbc.gridy;
 if(gbc.gridx ==  GridBagConstraints::_RELATIVE && (gbc.gridheight != GridBagConstraints::REMAINDER))
  x = ++lastX;
 else
  x = gbc.gridx;
 if(gbc.anchor == 0)
  QGridLayout::addWidget(widget, y, x, gbc.rowSpan(), gbc.colSpan()/*, gb.align()*/);
 else
  QGridLayout::addWidget(widget, y, x, gbc.rowSpan(), gbc.colSpan(), gbc.align());
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

GridBagConstraints GridBagLayout::getConstraints()
{
 return gbc;
}
