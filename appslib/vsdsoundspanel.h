#ifndef VSDSOUNDSPANEL_H
#define VSDSOUNDSPANEL_H
#include "jmripanel.h"
#include "appslib_global.h"

class VSDecoderPane;
class APPSLIBSHARED_EXPORT VSDSoundsPanel : public JmriPanel
{
 Q_OBJECT
public:
 explicit VSDSoundsPanel(QWidget *parent = 0);
 /*public*/ VSDSoundsPanel(QString dec, VSDecoderPane* dad,QWidget *parent = 0);
 /*public*/ void init() ;
 /*public*/ void initContext(QVariant context);
 /*public*/ void initComponents();

signals:

public slots:

private:
 QString decoder_id;
 VSDecoderPane* main_pane;
 void common();
 Logger* log;

};

#endif // VSDSOUNDSPANEL_H
