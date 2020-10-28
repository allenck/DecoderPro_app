#include "throttle.h"

//Throttle::Throttle(QObject *parent) :
//    QObject(parent)
//{
//}
    /**
     * Properties strings sent to property change listeners
     */

    /**
     * Constant sent by Throttle on Property Change.
     */
    /*public*/ /*static*/ /*final*/ QString Throttle::SPEEDSTEPS = "SpeedSteps"; // speed steps NOI18N

    /*public*/ /*static*/ /*final*/ QString Throttle::SPEEDSETTING = "SpeedSetting"; // speed setting NOI18N
    /*public*/ /*static*/ /*final*/ QString Throttle::ISFORWARD = "IsForward"; // direction setting NOI18N
    /*public*/ /*static*/ /*final*/ QString Throttle::SPEEDINCREMENT = "SpeedIncrement"; // direction setting NOI18N

    /**
     * Constants to represent the functions F0 through F28.
     */
     QString Throttle::F0 = "F0"; // NOI18N
     QString Throttle::F1 = "F1"; // NOI18N
     QString Throttle::F2 = "F2"; // NOI18N
     QString Throttle::F3 = "F3"; // NOI18N
     QString Throttle::F4 = "F4"; // NOI18N
     QString Throttle::F5 = "F5"; // NOI18N
     QString Throttle::F6 = "F6"; // NOI18N
     QString Throttle::F7 = "F7"; // NOI18N
     QString Throttle::F8 = "F8"; // NOI18N
     QString Throttle::F9 = "F9"; // NOI18N
     QString Throttle::F10 = "F10"; // NOI18N
     QString Throttle::F11 = "F11"; // NOI18N
     QString Throttle::F12 = "F12"; // NOI18N
     QString Throttle::F13 = "F13"; // NOI18N
     QString Throttle::F14 = "F14"; // NOI18N
     QString Throttle::F15 = "F15"; // NOI18N
     QString Throttle::F16 = "F16"; // NOI18N
     QString Throttle::F17 = "F17"; // NOI18N
     QString Throttle::F18 = "F18"; // NOI18N
     QString Throttle::F19 = "F19"; // NOI18N
     QString Throttle::F20 = "F20"; // NOI18N
     QString Throttle::F21 = "F21"; // NOI18N
     QString Throttle::F22 = "F22"; // NOI18N
     QString Throttle::F23 = "F23"; // NOI18N
     QString Throttle::F24 = "F24"; // NOI18N
     QString Throttle::F25 = "F25"; // NOI18N
     QString Throttle::F26 = "F26"; // NOI18N
     QString Throttle::F27 = "F27"; // NOI18N
     QString Throttle::F28 = "F28"; // NOI18N
    /**
     * Constants to represent the functions F0 through F28.
     */
     QString Throttle::F0Momentary = "F0Momentary"; // NOI18N
     QString Throttle::F1Momentary = "F1Momentary"; // NOI18N
     QString Throttle::F2Momentary = "F2Momentary"; // NOI18N
     QString Throttle::F3Momentary = "F3Momentary"; // NOI18N
     QString Throttle::F4Momentary = "F4Momentary"; // NOI18N
     QString Throttle::F5Momentary = "F5Momentary"; // NOI18N
     QString Throttle::F6Momentary = "F6Momentary"; // NOI18N
     QString Throttle::F7Momentary = "F7Momentary"; // NOI18N
     QString Throttle::F8Momentary = "F8Momentary"; // NOI18N
     QString Throttle::F9Momentary = "F9Momentary"; // NOI18N
     QString Throttle::F10Momentary = "F10Momentary"; // NOI18N
     QString Throttle::F11Momentary = "F11Momentary"; // NOI18N
     QString Throttle::F12Momentary = "F12Momentary"; // NOI18N
     QString Throttle::F13Momentary = "F13Momentary"; // NOI18N
     QString Throttle::F14Momentary = "F14Momentary"; // NOI18N
     QString Throttle::F15Momentary = "F15Momentary"; // NOI18N
     QString Throttle::F16Momentary = "F16Momentary"; // NOI18N
     QString Throttle::F17Momentary = "F17Momentary"; // NOI18N
     QString Throttle::F18Momentary = "F18Momentary"; // NOI18N
     QString Throttle::F19Momentary = "F19Momentary"; // NOI18N
     QString Throttle::F20Momentary = "F20Momentary"; // NOI18N
     QString Throttle::F21Momentary = "F21Momentary"; // NOI18N
     QString Throttle::F22Momentary = "F22Momentary"; // NOI18N
     QString Throttle::F23Momentary = "F23Momentary"; // NOI18N
     QString Throttle::F24Momentary = "F24Momentary"; // NOI18N
     QString Throttle::F25Momentary = "F25Momentary"; // NOI18N
     QString Throttle::F26Momentary = "F26Momentary"; // NOI18N
     QString Throttle::F27Momentary = "F27Momentary"; // NOI18N
     QString Throttle::F28Momentary = "F28Momentary"; // NOI18N


     /**
      * Get the Function String for a particular Function number.
      * Commonly used string in Throttle property change listeners.
      * @param functionNum Function Number, minimum 0.
      * @return function string, e.g. "F0" or "F7".
      */
     /*public*/ /*static*/ QString Throttle::getFunctionString(int functionNum){
//         StringBuilder sb = new StringBuilder(3);
//         sb.append("F"); // NOI18N
//         sb.append(functionNum);
//         return sb.toString();
      return QString(tr("F%1").arg(functionNum));
     }

     /**
      * Get the Momentary Function String for a particular Function number.
      * Commonly used string in Throttle property change listeners.
      * @param momentFunctionNum Momentary Function Number, minimum 0.
      * @return momentary function string, e.g. "F0Momentary" or "F7Momentary".
      */
     /*public*/ /*static*/ QString Throttle::getFunctionMomentaryString(int momentFunctionNum){
//         StringBuilder sb = new StringBuilder(12);
//         sb.append("F"); // NOI18N
//         sb.append(momentFunctionNum);
//         sb.append("Momentary"); // NOI18N
//         return sb.toString();
      return QString(tr("F%1Momentary").arg(momentFunctionNum));
     }

     /**
      * Get copy of function array.
      * Typically returns array length of 29, i.e. 0-28.
      * @return function array, length dependant by hardware type.
      */
     //@Nonnull
     // /*public*/ abstract boolean[] getFunctions();

     /**
      * Get copy of function momentary status array.
      * Typically returns array length of 29, i.e. 0-28.
      * @return momentary function array, length dependant by hardware type.
      */
     //@Nonnull
     ///*public*/ /*abstract*/ QVector<bool> getFunctionsMomentary();
