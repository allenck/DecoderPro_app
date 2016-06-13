#ifndef ENGINESOUNDEVENT_H
#define ENGINESOUNDEVENT_H
#include "soundevent.h"
#include <QDomElement>
#include "libPr3_global.h"

class Logger;
class EnginePane;
class LIBPR3SHARED_EXPORT EngineSoundEvent : public SoundEvent
{
 Q_OBJECT
public:
 //explicit EngineSoundEvent(QObject *parent = 0);
 /*public*/ EngineSoundEvent(QObject *parent) ;
 /*public*/ EngineSoundEvent(QString n, QObject *parent=0);
 /*public*/ EngineSoundEvent(QString n, QString bl, QObject *parent=0) ;
 /*public*/ bool hasButton() ;
 /*public*/ bool hasEnginePane();
 /*public*/ void setXml(QDomElement el, VSDFile* vf);
 /*public*/ QAbstractButton* getButton();
 /*public*/ EnginePane* getEnginePane();
 /*public*/ void setEnginePane(EnginePane* e);
 /*public*/ void setButtonLabel(QString bl);
 /*public*/ QString getButtonLabel();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement el);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ void guiAction(PropertyChangeEvent* evt);

private:
 EnginePane* engine_pane;
 Logger* log;
protected:
 /*protected*/ ButtonTrigger* setupButtonAction(QDomElement te);

};

#endif // ENGINESOUNDEVENT_H
