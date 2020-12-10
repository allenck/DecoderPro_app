#ifndef CTCCONSTANTS_H
#define CTCCONSTANTS_H
/*public*/ class CTCConstants {
 public:
    /*public*/ static /*final*/ const int LEFTTRAFFIC = 0;            // Indicator lights are presently left traffic
    /*public*/ static /*final*/ const int SIGNALSNORMAL = 1;          // Indicator lights are presently all stop
    /*public*/ static /*final*/ const int RIGHTTRAFFIC = 2;           // Indicator lights are presently right traffic
    /*public*/ static /*final*/ const int OUTOFCORRESPONDENCE = 3;    // Indicator lights are all unlit

    /*public*/ static /*final*/ const int SWITCHNORMAL = 0;           // Indicator lights are presently for normal direction of traffic (typically straight)
    /*public*/ static /*final*/ const int SWITCHREVERSED = 1;         // Indicator lights are presently for reversed direction of traffic (typically curved)

    /*public*/ static /*final*/ const int CTC_UNKNOWN = -1;            // For signals or switches (UNKNOWN is defined by JMRI, ergo the "CTC_" prefix.
};
#endif // CTCCONSTANTS_H
