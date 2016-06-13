#ifndef DIALOGSIGNALGROUPSTABLEWIDGET_H
#define DIALOGSIGNALGROUPSTABLEWIDGET_H

#include <QDialog>

namespace Ui {
class DialogSignalGroupsTableWIdget;
}

class DialogSignalGroupsTableWIdget : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSignalGroupsTableWIdget(QWidget *parent = 0);
    ~DialogSignalGroupsTableWIdget();

private:
    Ui::DialogSignalGroupsTableWIdget *ui;
};

#endif // DIALOGSIGNALGROUPSTABLEWIDGET_H
