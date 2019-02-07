#ifndef MIXERPROVIDER_H
#define MIXERPROVIDER_H

#include <QObject>
#include "mixer.h"

class MixerProvider : public QObject
{
 Q_OBJECT
public:
 explicit MixerProvider(QObject *parent = nullptr);
 /*public*/ bool isMixerSupported(Mixer::Info* info);
 /*public*/ /*abstract*/virtual QList<Mixer::Info*>* getMixerInfo();
 /*public*/ /*abstract*/ QList<Mixer::Info*>* getMixer(Mixer::Info*);

signals:

public slots:
};

#endif // MIXERPROVIDER_H
