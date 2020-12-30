#ifndef VARTEXTFIELD_H
#define VARTEXTFIELD_H
#include "jtextfield.h"
#include "logger.h"
#include "libPr3_global.h"

class VarTextField;
class VariableValue;
class JActionEvent;
class PropertyChangeEvent;
class LIBPR3SHARED_EXPORT VarTextField : public JTextField
{
    Q_OBJECT
public:
    //explicit VarTextField(QWidget *parent = 0);
 VarTextField(Document* doc, QString text, int col, VariableValue* var, QWidget* parent = 0);
 // void thisActionPerformed(ActionEvent* /*e*/);
 void originalPropertyChanged(PropertyChangeEvent* e);
 Document* getDocument();
signals:

public slots:
 void thisActionPerformed(JActionEvent* e = 0);
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
//DecVariableValue* _var;
VariableValue* _var;
Document* doc;
int col;
Logger* logit;
};

#endif // VARTEXTFIELD_H
