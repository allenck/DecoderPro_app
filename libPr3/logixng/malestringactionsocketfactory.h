#ifndef MALESTRINGACTIONSOCKETFACTORY_H
#define MALESTRINGACTIONSOCKETFACTORY_H
#include "malesocketfactory.h"

/**
 * Factory class for MaleStringActionSocket classes.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*interface*/class  MaleStringActionSocketFactory : public MaleSocketFactory/*<MaleStringActionSocket> */{
  Q_INTERFACES(MaleSocketFactory)
 public:
};
Q_DECLARE_INTERFACE(MaleStringActionSocketFactory, "MaleStringActionSocketFactory")
#endif // MALESTRINGACTIONSOCKETFACTORY_H
