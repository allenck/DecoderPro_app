#ifndef EDITPROPERTIESDLG_H
#define EDITPROPERTIESDLG_H

#include <QDialog>

namespace Ui {
class EditPropertiesDlg;
}

class PositionablePropertiesUtil : public QDialog
{
    Q_OBJECT
    
public:
    explicit PositionablePropertiesUtil(QWidget *parent = 0);
    ~PositionablePropertiesUtil();
    
private:
    Ui::EditPropertiesDlg *ui;
 QStringList _fontcolors;
};

#endif // EDITPROPERTIESDLG_H
