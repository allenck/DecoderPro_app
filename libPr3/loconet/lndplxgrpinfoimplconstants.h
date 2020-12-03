#ifndef LNDPLXGRPINFOIMPLCONSTANTS_H
#define LNDPLXGRPINFOIMPLCONSTANTS_H
enum LnDplxGrpInfoImplConstants
{
 GENERAL_BYTE_MASK = 0xFF,
 GENERAL_DECIMAL_RADIX = 10,

 // helpers for defining and checking Duplex Group Information
 DPLX_NAME_LEN = 8,
 DPLX_PW_LEN = 4,
 DPLX_MAX_GR_CHANNEL_LEN = 2,
 DPLX_MAX_GR_ID_LEN = 3,
 DPLX_MIN_ID = 0,
 DPLX_MAX_ID = 127,
 DPLX_MIN_CH = 11,
 DPLX_MAX_CH = 26,

 // helpers for performing LocoNet operations
 IPL_QUERY_DELAY = 1300, // # milliseconds to wait for results from IPL query
 DPLX_QUERY_DELAY = 300, // # milliseconds to wait for response to Duplex info query
 DPLX_SCAN_DELAY = 200, // # milliseconds to wait for response to scan query
 DPLX_SCAN_LOOP_COUNT = 25
};
#endif // LNDPLXGRPINFOIMPLCONSTANTS_H
