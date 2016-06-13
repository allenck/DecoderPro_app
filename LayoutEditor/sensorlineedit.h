#ifndef SENSORLINEEDIT_H
#define SENSORLINEEDIT_H

#include <QLineEdit>

class SensorLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SensorLineEdit(QWidget *parent = 0);
    void dragMoveEvent(QDragMoveEvent *e);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void setText(const QString &);
signals:
    void sensorChanged(QString);
public slots:

};

#endif // SENSORLINEEDIT_H
