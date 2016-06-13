#ifndef DROPPUSHBUTTON_H
#define DROPPUSHBUTTON_H

#include <QPushButton>

class NamedIcon;
class DropPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DropPushButton(QWidget *parent = 0);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
signals:
    void iconChanged(NamedIcon*);
public slots:

};

#endif // DROPPUSHBUTTON_H
