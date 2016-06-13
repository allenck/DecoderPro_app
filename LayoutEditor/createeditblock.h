#ifndef CREATEEDITBLOCK_H
#define CREATEEDITBLOCK_H

#include <QMainWindow>
#include "layoutblock.h"
#include <QStringList>
#include "liblayouteditor_global.h"

namespace Ui {
class CreateEditBlock;
}

class LIBLAYOUTEDITORSHARED_EXPORT CreateEditBlock : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CreateEditBlock(QString blockName, LayoutEditor* editor, QWidget *parent = 0);
    ~CreateEditBlock();
    
private:
    Ui::CreateEditBlock *ui;
    LayoutBlock* layoutBlock;
    QStringList _Colors;
    QList<QColor> _colors;
    LayoutEditor* editor;

private slots:
    void on_blockEditDone_clicked();
    void on_blockEditCancel_clicked();
    const QIcon* getColourIcon(QColor color);
    void on_sensorNameField_textChanged(QString);
};

#endif // CREATEEDITBLOCK_H
