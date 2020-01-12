#ifndef ROSTEMEDIA_H
#define ROSTEMEDIA_H

#include <QWidget>
#include <logger.h>
#include "libPr3_global.h"

namespace Ui {
class RosterMediaPane;
}

class RosterEntry;
class LIBPR3SHARED_EXPORT RosterMediaPane : public QWidget
{
    Q_OBJECT

public:
    explicit RosterMediaPane(RosterEntry* re, QWidget *parent = 0);
    ~RosterMediaPane();

private:
    Ui::RosterMediaPane *ui;
    RosterEntry* re;
    Logger* log;
    QString fileName;
    void processFile(QString fileName);
    void dragEnterEvent(QDragEnterEvent*);
    void dragMoveEvent(QDragMoveEvent*);
    void dropEvent(QDropEvent*);

private slots:
    void on_customContexMenuRequest(QPoint);
    void on_removeAction_triggered();
    void on_removeIcon_triggered();
    void on_addImageAction_triggered();
    void on_addIconAction_triggered();
    void dropImage(QString fileName);
    void dropIcon(QString fileName);
    void on_edWebReference_textEdited(QString);
};

#endif // ROSTEMEDIA_H
