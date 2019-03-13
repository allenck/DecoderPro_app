#include "gridbaglayout.h"
#include "gridbagconstraints.h"

GridBagLayout::GridBagLayout(QWidget* parent) : QGridLayout(parent)
{

}
void GridBagLayout::addWidget(QWidget *widget, GridBagConstraints gb)
{

 QGridLayout::addWidget(widget, gb.gridy, gb.gridx, gb.rowSpan(), gb.colSpan(), gb.align());
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
