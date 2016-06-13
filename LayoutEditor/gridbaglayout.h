#ifndef GRIDBAGLAYOUT_H
#define GRIDBAGLAYOUT_H
#include <QGridLayout>

class GridBagConstraints;
class GridBagLayout : public QGridLayout
{
    Q_OBJECT
 public:
    GridBagLayout(QWidget* parent = 0);
    void addWidget(QWidget* widget, GridBagConstraints gbc);
};

#endif // GRIDBAGLAYOUT_H
