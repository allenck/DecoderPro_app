#ifndef FUNCTIONLABELSMEDIADLG_H
#define FUNCTIONLABELSMEDIADLG_H

#include "../../LayoutEditor/jmrijframe.h"
#include "logger.h"
#include <QFile>
#include "libPr3_global.h"

namespace Ui {
class FunctionLabelsMediaDlg;
}

class RosterEntry;
class LIBPR3SHARED_EXPORT FunctionLabelsMediaDlg : public JmriJFrame
{
    Q_OBJECT

public:
    explicit FunctionLabelsMediaDlg(RosterEntry* re, QWidget *parent = 0);
    ~FunctionLabelsMediaDlg();

private:
    Ui::FunctionLabelsMediaDlg *ui;
    RosterEntry* re;
 Logger* log;
private slots:

    void on_btnSave_clicked();
protected:

};

#endif // FUNCTIONLABELSMEDIADLG_H
