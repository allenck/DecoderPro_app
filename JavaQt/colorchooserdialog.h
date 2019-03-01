#ifndef COLORCHOOSERDIALOG_H
#define COLORCHOOSERDIALOG_H
#include <QColorDialog>
#include "component.h"
#include "actionlistener.h"

class JColorChooser;
class ColorChooserDialog : public QColorDialog
{
 Q_OBJECT
public:
 ColorChooserDialog(QWidget* parent = nullptr);
 /*public*/ ColorChooserDialog(QDialog* dialog, QString string, bool bln, Component* cmpnt, JColorChooser* jcc, ActionListener* al, ActionListener* al1); /*throw HeadlessException*/

private:
 /*private*/ QColor initialColor;
 /*private*/ JColorChooser* chooserPane;
 /*private*/ QPushButton* cancelButton;
};

#endif // COLORCHOOSERDIALOG_H
