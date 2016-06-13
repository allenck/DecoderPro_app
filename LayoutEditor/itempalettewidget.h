#ifndef ITEMPALETTEWIDGET_H
#define ITEMPALETTEWIDGET_H

#include <QWidget>

namespace Ui {
class ItemPaletteWidget;
}

class ItemPaletteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemPaletteWidget(QWidget *parent = 0);
    ~ItemPaletteWidget();

private:
    Ui::ItemPaletteWidget *ui;
};

#endif // ITEMPALETTEWIDGET_H
