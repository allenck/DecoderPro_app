#ifndef VSDOPTIONSDIALOG_H
#define VSDOPTIONSDIALOG_H
#include "jdialog.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class JActionEvent;
class QComboBox;
class VSDOptionsDialog : public JDialog, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)

public:
 //explicit VSDOptionsDialog(QWidget *parent = 0);
 /*public*/ static /*final*/ QString OPTIONS_PROPERTY;// = "Options"; // NOI18N
 /*public*/ VSDOptionsDialog(QWidget* parent, QString title);
 /*public*/ void initComponents();
  QObject* pself() override {return (QObject*)this;}

signals:
 void propertyChange(PropertyChangeEvent*) override;

public slots:

private:
/*private*/ QComboBox* opsTrainComboBox;
private slots:
 /*private*/ void closeButtonActionPerformed(JActionEvent* ae = 0);

};

#endif // VSDOPTIONDIALOG_H
