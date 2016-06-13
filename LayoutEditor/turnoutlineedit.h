#ifndef TURNOUTLINEEDIT_H
#define TURNOUTLINEEDIT_H

#include <QLineEdit>

class TurnoutLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TurnoutLineEdit(QWidget *parent = 0);
    void dragMoveEvent(QDragMoveEvent *e);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void setText(const QString &s);

signals:

public slots:

};

#endif // TURNOUTLINEEDIT_H
