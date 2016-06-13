#ifndef EDITTURNOUT_H
#define EDITTURNOUT_H

#include "jmrijframe.h"
#include "layoutturnout.h"
#include <QCompleter>

namespace Ui {
class EditTurnout;
}

class LayoutTurnout;
class EditTurnout : public JmriJFrame
{
 Q_OBJECT
    
public:
 explicit EditTurnout(LayoutTurnout* to, QWidget *parent);
 ~EditTurnout();
    
private:
 Ui::EditTurnout *ui;
 LayoutTurnout* to;
 int type;
 int turnoutClosedIndex;
 int turnoutThrownIndex;
 QWidget *parent;

private slots:
 void on_additionalTurnout_toggled(bool bchecked);
 void on_turnoutEditBlock_clicked();
 void on_turnoutEditBlockB_clicked();
 void on_turnoutEditBlockC_clicked();
 void on_turnoutEditBlockD_clicked();
 void on_turnoutEditDone_clicked();
 void on_turnoutEditCancel_clicked();
 void on_blockNameField_textEdited(QString text);
 void on_blockBNameField_textEdited(QString text);
 void on_blockCNameField_textEdited(QString text);
 void on_blockDNameField_textEdited(QString text);

};

#endif // EDITTURNOUT_H
