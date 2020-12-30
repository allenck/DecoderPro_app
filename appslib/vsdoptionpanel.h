#ifndef VSDOPTIONSPANEL_H
#define VSDOPTIONSPANEL_H
#include "jmripanel.h"
#include "appslib_global.h"

class JActionEvent;
class VSDecoderPane;
class Train;
class QComboBox;
class APPSLIBSHARED_EXPORT VSDOptionPanel : public JmriPanel
{
 Q_OBJECT
public:
 explicit VSDOptionPanel(QWidget *parent = 0);
 /*public*/ VSDOptionPanel(QString dec, VSDecoderPane* dad);
 /*public*/ void init();
 /*public*/ void initContext(QVariant context);
 /*public*/ void initComponents();

signals:

public slots:
 /*public*/ void opsTrainSelectAction(JActionEvent* e = 0);

private:
 /*private*/ QComboBox* hornOptionComboBox;
 /*private*/ QComboBox* opsTrainComboBox;

 /*private*/ Train* selected_train;

 QString decoder_id;
 VSDecoderPane* main_frame;

};

#endif // VSDOPTIONSPANEL_H
