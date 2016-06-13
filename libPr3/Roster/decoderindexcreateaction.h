#ifndef DECODERINDEXCREATEACTION_H
#define DECODERINDEXCREATEACTION_H
#include "jmriabstractaction.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DecoderIndexCreateAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit DecoderIndexCreateAction(QObject *parent = 0);
 ~DecoderIndexCreateAction() {}
 DecoderIndexCreateAction(const DecoderIndexCreateAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
 /*public*/ DecoderIndexCreateAction(QString s, WindowInterface* wi);
 /*public*/ DecoderIndexCreateAction(QString s, QIcon i, WindowInterface* wi );
 /*public*/ DecoderIndexCreateAction(QString s, QObject *parent);
 /*public*/ void setIncrement(bool increment);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();
 bool increment;// = false;

};
Q_DECLARE_METATYPE(DecoderIndexCreateAction)
#endif // DECODERINDEXCREATEACTION_H
