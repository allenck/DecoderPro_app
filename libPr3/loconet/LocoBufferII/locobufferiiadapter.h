#ifndef LOCOBUFFERIIADAPTER_H
#define LOCOBUFFERIIADAPTER_H
#include "locobufferadapter.h"

class LocoBufferIIAdapter : public LocoBufferAdapter
{
  Q_OBJECT
 public:
  LocoBufferIIAdapter(QObject *parent = nullptr);
  /*public*/ LocoBufferIIAdapter(LocoNetSystemConnectionMemo* adapterMemo, QObject* parent = nullptr);
  /*public*/ QStringList validBaudRates();
  /*public*/ QString option1Name();
};

#endif // LOCOBUFFERIIADAPTER_H
