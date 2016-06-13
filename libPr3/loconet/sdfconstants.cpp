#include "sdfconstants.h"
#include <QVector>

QVector<int> SdfConstants::wavebrkCodes = QVector<int>() <<
    SdfConstants::loop_GLOBAL<< SdfConstants::loop_INVERT;

/*final*/ /*static*/ QVector<int> SdfConstants::wavebrkMasks = SdfConstants::wavebrkCodes;

/*final*/ /*static*/ QStringList SdfConstants::wavebrkNames = QStringList()
    << "loop_GLOBAL" << "loop_INVERT" << "loop_STD";
/*final*/ /*static*/ QVector<int> SdfConstants::loopCodes = QVector<int>()
    << SdfConstants::loop_till_cam <<  SdfConstants::loop_till_init_TRIG <<  // loop_till_NEVER is same as no_loop
    SdfConstants::loop_till_DIRNOW_CHNG <<  SdfConstants::loop_till_MOVING <<  SdfConstants::loop_till_SND_ACTV11 <<
    SdfConstants::loop_till_F0 <<
    SdfConstants::loop_till_F1 <<
    SdfConstants::loop_till_F2 <<  SdfConstants::loop_till_F3 <<  SdfConstants::loop_till_F4 <<  SdfConstants::loop_till_F5 <<
    SdfConstants::loop_till_F6 <<  SdfConstants::loop_till_F7 <<  SdfConstants::loop_till_F8 <<  SdfConstants::loop_till_F9 <<
    SdfConstants::loop_till_F10 <<  SdfConstants::loop_till_F11 <<  loop_till_F12 <<
    SdfConstants::loop_till_SCAT4 <<  SdfConstants::loop_till_SCAT5 <<  SdfConstants::loop_till_SCAT6 <<  SdfConstants::loop_till_SCAT7;

/*final*/ /*static*/ QVector<int> SdfConstants::loopMasks = SdfConstants::loopCodes;

/*final*/ /*static*/ QStringList SdfConstants::loopNames = QStringList() <<
    "loop_till_cam" <<  "loop_till_init_TRIG" <<
    "loop_till_DIRNOW_CHNG" <<  "loop_till_MOVING" <<  "loop_till_SND_ACTV11" <<
    "loop_till_F0" <<
    "loop_till_F1" <<
    "loop_till_F2" <<  "loop_till_F3" <<  "loop_till_F4" <<  "loop_till_F5" <<
    "loop_till_F6" <<  "loop_till_F7" <<  "loop_till_F8" <<  "loop_till_F9" <<
    "loop_till_F10" <<  "loop_till_F11" <<  "loop_till_F12" <<
    "loop_till_SCAT4" <<  "loop_till_SCAT5" <<  "loop_till_SCAT6" <<  "loop_till_SCAT7" <<
    "no_loop";

/*final*/ /*static*/ QVector<int> SdfConstants::premptCodes =  QVector<int>() << SdfConstants::ZAP <<  SdfConstants::RUN_WHILE_TRIG <<  SdfConstants::NO_PREEMPT_TRIG <<  SdfConstants::NOT_TRIG; // NORMAL matches all (is zero), so left off
/*final*/ /*static*/ QVector<int> SdfConstants::premptMasks = SdfConstants::premptCodes;             // just check 1 bits
/*final*/ /*static*/ QStringList SdfConstants::premptNames =  QStringList() << "ZAP" <<  "RUN_WHILE_TRIG" <<  "NO_PREEMPT_TRIG" <<  "NOT_TRIG" <<  "NORMAL";


QVector<int> SdfConstants::triggerCodes =  QVector<int>() <<
    SdfConstants::TRIG_NEVER<< SdfConstants::TRIG_MODE_CHNG<< SdfConstants::TRIG_MATH<< SdfConstants::TRIG_DISTANCE<<
    SdfConstants::TRIG_SPD_INC<< SdfConstants::TRIG_SPD_DEC<< SdfConstants::TRIG_CAM<< SdfConstants::TRIG_NOT_TRIG<<
    SdfConstants::TRIG_SF0<< SdfConstants::TRIG_SF1<< SdfConstants::TRIG_SF2<< SdfConstants::TRIG_SF3<< SdfConstants::TRIG_SF4<<
    SdfConstants::TRIG_SF5<< SdfConstants::TRIG_SF6<< SdfConstants::TRIG_SF7<< SdfConstants::TRIG_SF8<<
    SdfConstants::TRIG_SF9<< SdfConstants::TRIG_SF10<< SdfConstants::TRIG_SF11<< SdfConstants::TRIG_SF12<<
    SdfConstants::TRIG_SF13<< SdfConstants::TRIG_SF14<< SdfConstants::TRIG_SF15<< SdfConstants::TRIG_SF16<<
    SdfConstants::TRIG_SF17<< SdfConstants::TRIG_SF18<< SdfConstants::TRIG_SF19<< SdfConstants::TRIG_SF20<<
    SdfConstants::TRIG_DIRNOW_CHNG<< SdfConstants::TRIG_MOVING<< SdfConstants::TRIG_SND_ACTV11<<
    SdfConstants::TRIG_SF21<< SdfConstants::TRIG_SF22<< SdfConstants::TRIG_SF23<< SdfConstants::TRIG_SF24<<
    SdfConstants::TRIG_SF25<< SdfConstants::TRIG_SF26<< SdfConstants::TRIG_SF27<< SdfConstants::TRIG_SF28<<
    SdfConstants::TRIG_BSC0<< SdfConstants::TRIG_BSC1<< SdfConstants::TRIG_BSC2<< SdfConstants::TRIG_BSC3<<
    SdfConstants::TRIG_BSC4<< SdfConstants::TRIG_BSC5<< SdfConstants::TRIG_BSC6<< SdfConstants::TRIG_BSC7<<
    SdfConstants::TRIG_IN_0<< SdfConstants::TRIG_IN_1<< SdfConstants::TRIG_IN_2<< SdfConstants::TRIG_IN_3<<
    SdfConstants::TRIG_IN_4<< SdfConstants::TRIG_IN_5<< SdfConstants::TRIG_IN_6<< SdfConstants::TRIG_IN_7<<
    SdfConstants::TRIG_NOTCH_CHNG<< SdfConstants::TRIG_TIME_16PPS<< SdfConstants::TRIG_FACTORY_CVRESET<< SdfConstants::TRIG_OPSPROGWR_CV<<
    SdfConstants::TRIG_SCAT0<< SdfConstants::TRIG_SCAT1<< SdfConstants::TRIG_SCAT2<< SdfConstants::TRIG_SCAT3<<
    SdfConstants::TRIG_SCAT4<< SdfConstants::TRIG_SCAT5<< SdfConstants::TRIG_SCAT6<< SdfConstants::TRIG_SCAT7<<
    SdfConstants::T_SPD_MUTE<< SdfConstants::T_SPD_TURNON<< SdfConstants::T_SPD_IDLE<< SdfConstants::T_SPD_ACCEL1<<
    SdfConstants::T_SPD_ACC_CHNG<< SdfConstants::T_SPD_ACCEL2<< SdfConstants::T_SPD_IDLEXIT<< SdfConstants::T_SPD_RUN<<
    SdfConstants::T_SPD_DECEL1<< SdfConstants::T_SPD_DEC_CHNG<< SdfConstants::T_SPD_DECEL2<<
    SdfConstants::T_SPD_DEC_IDLE<< SdfConstants::T_SPD_TURNOFF<< SdfConstants::T_SPD_DEC_SP1<< SdfConstants::T_SPD_DEC_SP2<< SdfConstants::T_SPD_DIR_CHNG;

QStringList SdfConstants::triggerNames   = QStringList() <<
                                              "TRIG_NEVER"<< "TRIG_MODE_CHNG"<< "TRIG_MATH"<< "TRIG_DISTANCE"<<
                                              "TRIG_SPD_INC"<< "TRIG_SPD_DEC"<< "TRIG_CAM"<< "TRIG_NOT_TRIG"<<
                                              "TRIG_SF0"<< "TRIG_SF1"<< "TRIG_SF2"<< "TRIG_SF3"<< "TRIG_SF4"<<
                                              "TRIG_SF5"<< "TRIG_SF6"<< "TRIG_SF7"<< "TRIG_SF8"<<
                                              "TRIG_SF9"<< "TRIG_SF10"<< "TRIG_SF11"<< "TRIG_SF12"<<
                                              "TRIG_SF13"<< "TRIG_SF14"<< "TRIG_SF15"<< "TRIG_SF16"<<
                                              "TRIG_SF17"<< "TRIG_SF18"<< "TRIG_SF19"<< "TRIG_SF20"<<
                                              "TRIG_DIRNOW_CHNG"<< "TRIG_MOVING"<< "TRIG_SND_ACTV11"<<
                                              "TRIG_SF21"<< "TRIG_SF22"<< "TRIG_SF23"<< "TRIG_SF24"<<
                                              "TRIG_SF25"<< "TRIG_SF26"<< "TRIG_SF27"<< "TRIG_SF28"<<
                                              "TRIG_BSC0"<< "TRIG_BSC1"<< "TRIG_BSC2"<< "TRIG_BSC3"<<
                                              "TRIG_BSC4"<< "TRIG_BSC5"<< "TRIG_BSC6"<< "TRIG_BSC7"<<
                                              "TRIG_IN_0"<< "TRIG_IN_1"<< "TRIG_IN_2"<< "TRIG_IN_3"<<
                                              "TRIG_IN_4"<< "TRIG_IN_5"<< "TRIG_IN_6"<< "TRIG_IN_7"<<
                                              "TRIG_NOTCH_CHNG"<< "TRIG_TIME_16PPS"<< "TRIG_FACTORY_CVRESET"<< "TRIG_OPSPROGWR_CV"<<
                                              "TRIG_SCAT0"<< "TRIG_SCAT1"<< "TRIG_SCAT2"<< "TRIG_SCAT3"<<
                                              "TRIG_SCAT4"<< "TRIG_SCAT5"<< "TRIG_SCAT6"<< "TRIG_SCAT7"<<
                                              "T_SPD_MUTE"<< "T_SPD_TURNON"<< "T_SPD_IDLE"<< "T_SPD_ACCEL1"<<
                                              "T_SPD_ACC_CHNG"<< "T_SPD_ACCEL2"<< "T_SPD_IDLEXIT"<< "T_SPD_RUN"<<
                                              "T_SPD_DECEL1"<< "T_SPD_DEC_CHNG"<< "T_SPD_DECEL2"<<
                                              "T_SPD_DEC_IDLE"<< "T_SPD_TURNOFF"<<
                                              "T_SPD_DEC_SP1"<< "T_SPD_DEC_SP2"<< "T_SPD_DIR_CHNG";


/*final*/ /*static*/ QVector<int> SdfConstants::trigLogicCodes =  QVector<int>() <<
    SdfConstants::TRIG_TRUE;

/*final*/ /*static*/ QVector<int> SdfConstants::trigLogicMasks = loopCodes;

/*final*/ /*static*/ QStringList SdfConstants::trigLogicNames = QStringList() <<
    "TRIG_TRUE" << "TRIG_FALSE";

/*final*/ /*static*/ QVector<int> SdfConstants::modControlCodes =  QVector<int>() <<
    SdfConstants::MTYPE_TIME <<  SdfConstants::MTYPE_GAIN <<  SdfConstants::MTYPE_PITCH << SdfConstants:: MTYPE_BLEND <<
    SdfConstants::MTYPE_SCATTER <<  SdfConstants::MTYPE_SNDCV <<  SdfConstants::MTYPE_WORK_IMMED <<  SdfConstants::MTYPE_WORK_INDIRECT
;
/*final*/ /*static*/ QStringList SdfConstants::modControlNames =  QStringList() <<
    "MTYPE_TIME" <<  "MTYPE_GAIN" <<  "MTYPE_PITCH" <<  "MTYPE_BLEND" <<
    "MTYPE_SCATTER" <<  "MTYPE_SNDCV" <<  "MTYPE_WORK_IMMED" <<  "MTYPE_WORK_INDIRECT";

/*final*/ /*static*/ int SdfConstants::IMMED_GAIN_MODIFY = 0x80; // set new GAIN to [CV# 6 bit offset in ARG1] *CV58 , CV120 base
/*final*/ /*static*/ int SdfConstants::ANALOG_GAIN_MODIFY = 0xA0; // modify INIT GAIN by analog chnl in 5 ls bits

/*final*/ /*static*/ QVector<int> SdfConstants::workRegCodes =  QVector<int>() <<
    SdfConstants::WORK_SPEED <<  SdfConstants::WORK_NOTCH <<  SdfConstants::WORK_SERVO <<  SdfConstants::WORK_MVOLTS <<
    SdfConstants::WORK_USER_LINES <<  SdfConstants::WORK_TIMEBASE <<  SdfConstants::WORK_STATUS_BITS <<
    SdfConstants::WORK_GLBL_GAIN <<  SdfConstants::WORK_GAIN_TRIM <<  SdfConstants::WORK_PITCH_TRIM <<  SdfConstants::WORK_SPEED_DELTA <<
    SdfConstants::WORK_SCATTER4 <<  SdfConstants::WORK_SCATTER5 <<  SdfConstants::WORK_SCATTER6 <<  SdfConstants::WORK_SCATTER7 <<
    SdfConstants::WORK_ACHNL_7F <<  SdfConstants::WORK_ACHNL_7E <<  SdfConstants::WORK_SKAT_FAST <<  SdfConstants::WORK_SKAT_SLOW <<
    SdfConstants::WORK_DISTANCE <<  SdfConstants::WORK_PEAK_SPD <<  SdfConstants::WORK_USER_0 <<  SdfConstants::WORK_USER_1 <<
    SdfConstants::WORK_USER_2 <<  SdfConstants::WORK_USER_3 <<  SdfConstants::WORK_USER_4 <<  SdfConstants::WORK_USER_5;

/*final*/ /*static*/ QStringList SdfConstants::workRegNames =  QStringList() <<
    "WORK_SPEED" <<  "WORK_NOTCH" <<  "WORK_SERVO" <<  "WORK_MVOLTS" <<
    "WORK_USER_LINES" <<  "WORK_TIMEBASE" <<  "WORK_STATUS_BITS" <<
    "WORK_GLBL_GAIN" <<  "WORK_GAIN_TRIM" <<  "WORK_PITCH_TRIM" <<  "WORK_SPEED_DELTA" <<
    "WORK_SCATTER4" <<  "WORK_SCATTER5" <<  "WORK_SCATTER6" <<  "WORK_SCATTER7" <<
    "WORK_ACHNL_7F" <<  "WORK_ACHNL_7E" <<  "WORK_SKAT_FAST" <<  "WORK_SKAT_SLOW" <<
    "WORK_DISTANCE" <<  "WORK_PEAK_SPD" <<  "WORK_USER_0" <<  "WORK_USER_1" <<
    "WORK_USER_2" <<  "WORK_USER_3" <<  "WORK_USER_4" <<  "WORK_USER_5";

/*final*/ /*static*/ int SdfConstants::WKSB_ANALOG_BIT = 0; // 1=is in ANALOG mode [STATUS mirror]
/*final*/ /*static*/ int SdfConstants::WKSB_ANALOG_MASK = 0x01; // bit involved

/*final*/ /*static*/ int SdfConstants::WKSB_DIRNOW_BIT = 1; // 1= rev direction ?[STATUS mirror]
/*final*/ /*static*/ int SdfConstants::WKSB_DIRNOW_MASK = 0x02; // bit involved

/*final*/ /*static*/ int SdfConstants::WKSB_RUN_BIT = 2; // 0= stop motor PWM, non-primemover sounds RUN
/*final*/ /*static*/ int SdfConstants::WKSB_RUN_MASK = 0x04; // bit involved

/*final*/ /*static*/ int SdfConstants::WKSB_ACEL_BIT = 3; // 1= is ACCEL state
/*final*/ /*static*/ int SdfConstants::WKSB_ACEL_MASK = 0x08; // bit involved

/*final*/ /*static*/ int SdfConstants::WKSB_SPDDELTA_BIT = 4; // 1= change SPD by unsigned SPD_DELTA work REG only
/*final*/ /*static*/ int SdfConstants::WKSB_SPDDELTA_MASK = 0x10; // bit involved

/*final*/ /*static*/ int SdfConstants::WKSB_MATH_BIT = 7; // result from last MODIFY math action (can test with
/*final*/ /*static*/ int SdfConstants::WKSB_MATH_MASK = 0x80; // bit involved

/*final*/ /*static*/ QVector<int> SdfConstants::workStatusBitCodes =  QVector<int>() <<
    SdfConstants::WKSB_ANALOG_MASK  <<  SdfConstants::WKSB_DIRNOW_MASK  <<  SdfConstants::WKSB_RUN_MASK  <<  SdfConstants::WKSB_ACEL_MASK  <<  SdfConstants::WKSB_SPDDELTA_MASK  <<  SdfConstants::WKSB_MATH_MASK;

/*final*/ /*static*/ QStringList SdfConstants::workStatusBitNames =  QStringList() <<
    "WKSB_ANALOG_MASK"  <<  "WKSB_DIRNOW_MASK"  <<  "WKSB_RUN_MASK"  <<  "WKSB_ACEL_MASK"  <<  "WKSB_SPDDELTA_MASK"  <<  "WKSB_MATH_MASK";

/*static*/ /*final*/ QVector<int> SdfConstants::fixedCVCodes =  QVector<int>() <<
    SdfConstants::SNDCV_CONFIGA  <<  SdfConstants::SNDCV_CONFIGB  <<  SdfConstants::SCV_DCONFIG  <<  SdfConstants::SCV_NOTCH  <<
    SdfConstants::SNDCV_STEAM  <<  SdfConstants::SCV_STGEAR  <<  SdfConstants::SCV_MUTE_VOL  <<  SdfConstants::SCV_MAIN_PITCH  <<
    SdfConstants::SCV_137  <<  SdfConstants::SCV_138  <<  SdfConstants::SCV_DISTANCE_RATE  <<  SdfConstants::SCV_FREEFORM;

/*static*/ /*final*/ QStringList SdfConstants::fixedCVNames =  QStringList() <<
    "SNDCV_CONFIGA"  <<  "SNDCV_CONFIGB"  <<  "SCV_DCONFIG"  <<  "SCV_NOTCH"  <<
    "SNDCV_STEAM"  <<  "SCV_STGEAR"  <<  "SCV_MUTE_VOL"  <<  "SCV_MAIN_PITCH"  <<
    "SCV_137"  <<  "SCV_138"  <<  "SCV_DISTANCE_RATE"  <<  "SCV_FREEFORM";

/*static*/ int SdfConstants::STEAM_CAM_BIT = 7;

/*final*/ /*static*/ QVector<int> SdfConstants::arg3ModCodes =  QVector<int>() <<
    SdfConstants::DITHER  <<
    SdfConstants::LOW_DITH  <<  SdfConstants::MID_DITH  << SdfConstants:: MAX_DITH  <<  // MIN_DITH is zero  <<  a no-op
    SdfConstants::SCALE_F  <<  SdfConstants::SCALE_C  <<  SdfConstants::SCALE_8  <<  SdfConstants::SCALE_6  <<  SdfConstants::SCALE_5  <<  SdfConstants::SCALE_4  <<  SdfConstants::SCALE_2;

/*final*/ /*static*/ QVector<int> SdfConstants::arg3ModMasks =  QVector<int>() <<   SdfConstants::DITHER  <<
    0x60  <<  0x60  <<  0x60  <<
    0x0F  <<  0x0F  <<  0x0F  <<  0x0F  <<  0x0F  <<  0x0F  <<  0x0F;

/*final*/ /*static*/ QStringList SdfConstants::arg3ModNames =  QStringList() <<
    "DITHER"  <<
    "LOW_DITH"  <<  "MID_DITH"  <<  "MAX_DITH"  <<
    "SCALE_F"  <<  "SCALE_C"  <<  "SCALE_8"  <<  "SCALE_6"  <<  "SCALE_5"  <<  "SCALE_4"  <<  "SCALE_2";

/*final*/ /*static*/ QVector<int> SdfConstants::ditherGCodes =  QVector<int>() <<
    SdfConstants::DITHERG_DIESEL  <<  SdfConstants::DITHERG_WHISTLE  <<  SdfConstants::DITHERG_NONE;
/*final*/ /*static*/ QStringList SdfConstants::ditherGNames =  QStringList() <<
    "DITHERG_DIESEL"  <<  "DITHERG_WHISTLE"  <<  "DITHERG_NONE";

/*final*/ /*static*/ QVector<int> SdfConstants::ditherPCodes =  QVector<int>() <<
    SdfConstants::DITHERP_DIESEL  <<  SdfConstants::DITHERP_WHISTLE  <<  SdfConstants::DITHERP_NONE;

/*final*/ /*static*/ QStringList SdfConstants::ditherPNames =  QStringList() <<
    "DITHERP_DIESEL"  <<  "DITHERP_WHISTLE"  <<  "DITHERP_NONE";

/*final*/ /*static*/ int SdfConstants::FCMD_NONE = 0x00; // NO PITCH MODIFY task RUN
/*final*/ /*static*/ int SdfConstants::FCMD_MASK = 0xE0; // 3 ms bits 1st CMD decode

// type 8 PITCH
/*final*/ /*static*/ int SdfConstants::CV_PITCH_MODIFY = 0x80; // set new PITCH to [CV# 6 bit offset in ARG1] , CV120 base
/*final*/ /*static*/ int SdfConstants::ANALOG_PITCH_MODIFY = 0xA0; // modify INIT PITCH by analog chnl in 5 ls bits

/*final*/ /*static*/ QVector<int> SdfConstants::blendArg2Codes =  QVector<int>() <<
    SdfConstants::BLENDG_DSL_ACCEL0  <<  SdfConstants::BLENDG_DSL_ACCEL1  <<  SdfConstants::BLENDG_DSL_ACCEL1;

/*final*/ /*static*/ QStringList SdfConstants::blendArg2Names =  QStringList() <<
    "BLENDG_DSL_ACCEL0"  <<  "BLENDG_DSL_ACCEL1"  <<  "BLENDG_DSL_ACCEL1";

/*final*/ /*static*/ QVector<int> SdfConstants::blendArg3Codes =  QVector<int>() <<
    SdfConstants::BLENDF_DSL_ACCEL0  <<  SdfConstants::BLENDF_DSL_ACCEL1  <<  SdfConstants::BLENDF_DSL_ACCEL1;

/*final*/ /*static*/ QStringList SdfConstants::blendArg3Names =  QStringList() <<
    "BLENDF_DSL_ACCEL0"  <<  "BLENDF_DSL_ACCEL1"  <<  "BLENDF_DSL_ACCEL1";

/*final*/ /*static*/ QVector<int> SdfConstants::maxPCodes =  QVector<int>() <<
    SdfConstants::MAXP_WHISTLE  <<  SdfConstants::MAXP_DIESEL  <<  SdfConstants::MAXP_STEAM;

/*final*/ /*static*/ QStringList SdfConstants::maxPNames =  QStringList() <<
    "MAXP_WHISTLE"  <<  "MAXP_DIESEL"  <<  "MAXP_STEAM";

  /*final*/ /*static*/ QVector<int> SdfConstants::maxGCodes =  QVector<int>() <<
    SdfConstants::MAXG_WHISTLE  <<  SdfConstants::MAXG_DIESEL  <<  SdfConstants::MAXG_STEAM;

  /*final*/ /*static*/ QStringList SdfConstants::maxGNames =  QStringList() <<
    "MAXG_WHISTLE"  <<  "MAXG_DIESEL"  <<  "MAXG_STEAM";

/*final*/ /*static*/ QVector<int> SdfConstants::scatCommandCodes =  QVector<int>() <<
    SdfConstants::SCAT_CMD_PERIOD << SdfConstants::SCAT_CMD_PERIOD_REV << SdfConstants::SCAT_CMD_SAWTOOTH << SdfConstants::SCAT_CMD_SAWTOOTH_REV;

/*final*/ /*static*/ QStringList SdfConstants::scatCommandNames =  QStringList() <<
    "SCAT_CMD_PERIOD"  <<  "SCAT_CMD_PERIOD_REV"  <<  "SCAT_CMD_SAWTOOTH"  <<  "SCAT_CMD_SAWTOOTH_REV";

/*final*/ /*static*/ int SdfConstants::SCAT_PERIOD_POLARITY_BIT = 3; // 1= reverse WORK influence
/*final*/ /*static*/ int SdfConstants::SKATTER_INCREMENT = 8; // phase INCREMENT

/*final*/ /*static*/ QVector<int> SdfConstants::scatChannelCodes =  QVector<int>() <<
    SdfConstants::SCAT_CHNL0  <<  SdfConstants::SCAT_CHNL1  <<  SdfConstants::SCAT_CHNL2  <<  SdfConstants::SCAT_CHNL3  <<  SdfConstants::SCAT_CHNL4  <<  SdfConstants::SCAT_CHNL5  <<  SdfConstants::SCAT_CHNL6  <<  SdfConstants::SCAT_CHNL7;

/*final*/ /*static*/ QStringList SdfConstants::scatChannelNames =  QStringList() <<
    "SCAT_CHNL0"  <<  "SCAT_CHNL1"  <<  "SCAT_CHNL2"  <<  "SCAT_CHNL3"  <<  "SCAT_CHNL4"  <<  "SCAT_CHNL5"  <<  "SCAT_CHNL6"  <<  "SCAT_CHNL7";

/*final*/ /*static*/ QVector<int> SdfConstants::sintenCodes =  QVector<int>() <<
    SdfConstants::SINTEN_IMMED  <<  SdfConstants::SINTEN_HIGH  <<  SdfConstants::SINTEN_MID  <<  SdfConstants::SINTEN_LOW  <<  SdfConstants::SINTEN_MIN  <<  SdfConstants::SINTEN_OFF;

/*final*/ /*static*/ QStringList SdfConstants::sintenNames =  QStringList() <<  "SINTEN_IMMED"  <<  "SINTEN_HIGH"  <<  "SINTEN_MID"  <<  "SINTEN_LOW"  <<  "SINTEN_MIN"  <<  "SINTEN_OFF";

/*final*/ /*static*/ int SdfConstants::DEFAULT_GLBL_GAIN = 0xC0;
/*final*/ /*static*/ int SdfConstants::MERGE_ALL_MASK = 0; // any 0 bit is involved

// ----2222--------------
// 2ND modify ARG
/*final*/ /*static*/ int SdfConstants::SNDCV_SRC = 0x80; // this bit set chngs from IMMED to SND_CV to control EFFECT span
/*final*/ /*static*/ int SdfConstants::SNDCV_SRC_BIT = 7; // 1=ls 7 bits SCV#, 0=ls 7 bits immed arg data

// ls 7 bit ARGS
/*final*/ /*static*/ int SdfConstants::MAXG_NONE = 0x00; // value of 0 means no scaling, SRC is 100% GAIN
/*final*/ /*static*/ int SdfConstants::MAXP_NONE = 0x00; // value of 0 means no scaling, SRC is 100% PITCH

// ---------------
// values for MATH functions on WORK regs
  /*final*/ /*static*/ int SdfConstants::FMATH_LODE = 0x00; // load DATA,,MATH_FLAG SET shows whole WORK is ZERO- DEFAULT task
  /*final*/ /*static*/ int SdfConstants::FMATH_AND = 0x20; // use to CLR bit(s),MATH_FLAG SET shows whole WORK is ZERO
  /*final*/ /*static*/ int SdfConstants::FMATH_OR = 0x40; // use to SET  bit(S), MATH FLAG SET shows whole WORK is 1's
  /*final*/ /*static*/ int SdfConstants::FMATH_XOR = 0x60; // use to flip bit(s), MATH FLAG SET if all flipped bits are now 0

//;FMATH_ADD	EQU	0x80	;add signed value  (commented out in original Digitrax file)
  /*final*/ /*static*/ int SdfConstants::FMATH_INTEGRATE = 0xA0; // add signed value to WORK,MATH_FLAG SET if over/underflo,or clamp LIMIT
  /*final*/ /*static*/ int SdfConstants::FMATH_TEST_ZERO = 0xC0; // see if WORK under MASK is ZERO, if ZERO set MATH bit

// -----1111----------------
// FIRST modify ARG- COMMAND
  /*final*/ /*static*/ int SdfConstants::GCMD_NONE = 0x00; // NO gain MODIFY task RUN
  /*final*/ /*static*/ int SdfConstants::GCMD_MASK = 0xE0; // 3 ms bits 1st CMD decode

/*static*/ /*final*/ QVector<int> SdfConstants::arg1ModCodes =  QVector<int>() <<
      SdfConstants::FMATH_LODE << SdfConstants::FMATH_AND  <<  SdfConstants::FMATH_OR<< SdfConstants::FMATH_XOR  <<  SdfConstants::FMATH_INTEGRATE  <<  SdfConstants::FMATH_TEST_ZERO  <<  SdfConstants::GCMD_MASK;

/*static*/ /*final*/ QStringList SdfConstants::arg1ModNames =  QStringList() <<
      "FMATH_LODE"  <<  "FMATH_AND"  <<  "FMATH_OR"  <<  "FMATH_XOR"  <<  "FMATH_INTEGRATE"  <<  "FMATH_TEST_ZERO"  <<  "GCMD_MASK";

/*final*/ /*static*/ QVector<int> SdfConstants::blendArg1Codes =  QVector<int>() <<
      SdfConstants::BLEND_CURRENT_CHNL  <<  SdfConstants::BLEND_ALL  <<
      SdfConstants::BLEND_GAIN0  <<  SdfConstants::BLEND_GAIN1  <<
      SdfConstants::BLEND_FASE0  <<  SdfConstants::BLEND_FASE1;
//  };
/*final*/ /*static*/ QVector<int> SdfConstants::blendArg1Masks =  QVector<int>() <<
      SdfConstants::BLEND_TGTMASK  <<  SdfConstants::BLEND_TGTMASK  <<
      SdfConstants::BLEND_GAINMASK  <<  SdfConstants::BLEND_GAINMASK  <<
      SdfConstants::BLEND_FASEMASK  <<  SdfConstants::BLEND_FASEMASK;
//  };
/*final*/ /*static*/ QStringList SdfConstants::blendArg1Names =  QStringList() <<
      "BLEND_CURRENT_CHNL"  <<  "BLEND_ALL"  <<
      "BLEND_GAIN0"  <<  "BLEND_GAIN1"  <<
      "BLEND_FASE0"  <<  "BLEND_FASE1";
//  };

/*final*/ /*static*/ QStringList SdfConstants::editorTriggerNames =  QStringList() <<
    "TRIG_NEVER" <<  "TRIG_MODE_CHNG" <<  "TRIG_MATH" <<  "TRIG_DISTANCE" <<
    "TRIG_SPD_INC" <<  "TRIG_SPD_DEC" <<  "TRIG_CAM" <<  "TRIG_NOT_TRIG" <<
    "Function 0 On" <<  "Function 1 On" <<  "Function 2 On" <<  "Function 3 On" <<
    "Function 4 On" <<  "Function 5 On" <<  "Function 6 On" <<  "Function 7 On" <<
    "Function 8 On" <<  "Function 9 On" <<  "Function 10 On" <<  "Function 11 On" <<
    "Function 12 On" <<  "Function 13 On" <<  "Function 14 On" <<  "Function 15 On" <<
    "Function 16 On" <<  "Function 17 On" <<  "Function 18 On" <<  "Function 19 On" <<
    "Function 20 On" <<
    "TRIG_DIRNOW_CHNG" <<  "TRIG_MOVING" <<  "TRIG_SND_ACTV11" <<
    "Function 21 On" <<  "Function 22 On" <<  "Function 23 On" <<  "Function 24 On" <<
    "Function 25 On" <<  "Function 26 On" <<  "Function 27 On" <<  "Function 28 On" <<
    "TRIG_BSC0" <<  "TRIG_BSC1" <<  "TRIG_BSC2" <<  "TRIG_BSC3" <<
    "TRIG_BSC4" <<  "TRIG_BSC5" <<  "TRIG_BSC6" <<  "TRIG_BSC7" <<
    "TRIG_IN_0" <<  "TRIG_IN_1" <<  "TRIG_IN_2" <<  "TRIG_IN_3" <<
    "TRIG_IN_4" <<  "TRIG_IN_5" <<  "TRIG_IN_6" <<  "TRIG_IN_7" <<
    "TRIG_NOTCH_CHNG" <<  "TRIG_TIME_16PPS" <<  "TRIG_FACTORY_CVRESET" <<  "TRIG_OPSPROGWR_CV" <<
    "TRIG_SCAT0" <<  "TRIG_SCAT1" <<  "TRIG_SCAT2" <<  "TRIG_SCAT3" <<
    "TRIG_SCAT4" <<  "TRIG_SCAT5" <<  "TRIG_SCAT6" <<  "TRIG_SCAT7" <<
    "T_SPD_MUTE" <<  "T_SPD_TURNON" <<  "T_SPD_IDLE" <<  "T_SPD_ACCEL1" <<
    "T_SPD_ACC_CHNG" <<  "T_SPD_ACCEL2" <<  "T_SPD_IDLEXIT" <<  "T_SPD_RUN" <<
    "T_SPD_DECEL1" <<  "T_SPD_DEC_CHNG" <<  "T_SPD_DECEL2" <<
    "T_SPD_DEC_IDLE" <<  "T_SPD_TURNOFF" <<
    "T_SPD_DEC_SP1" <<  "T_SPD_DEC_SP2" <<  "T_SPD_DIR_CHNG";
