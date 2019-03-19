#ifndef GRIDBAGLAYOUT_H
#define GRIDBAGLAYOUT_H
#include <QGridLayout>
#include "javaqt_global.h"
#include "gridbagconstraints.h"

class JAVAQTSHARED_EXPORT GridBagLayout : public QGridLayout
{
    Q_OBJECT
 public:
    GridBagLayout(QWidget* parent = 0);
    void addWidget(QWidget* widget, GridBagConstraints gbc);
    void columnWidths(QList<int> columns);
    void rowHeights(QList<int> rows);
    void setConstraints(GridBagConstraints gbc);

private:
    GridBagConstraints gbc;
};

#endif // GRIDBAGLAYOUT_H
