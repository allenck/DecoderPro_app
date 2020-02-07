#include "rawstatus.h"

/**
 * Raw status.  Used when LocoNet interface returns undeciphered data.
 *
 * @author Bob Milhaupt Copyright (C) 2017
 */
// /*public*/ class RawStatus {

/*public*/ RawStatus::RawStatus(int rawdata0, int rawdata1, int rawdata2, int rawdata3, int rawdata4,
                     int rawdata5, int rawdata6, int rawdata7,QObject *parent)
  : QObject(parent)
 {
        raw[0] = rawdata0;
        raw[1] = rawdata1;
        raw[2] = rawdata2;
        raw[3] = rawdata3;
        raw[4] = rawdata4;
        raw[5] = rawdata5;
        raw[6] = rawdata6;
        raw[7] = rawdata7;
        setObjectName("RawStatus");
    }


