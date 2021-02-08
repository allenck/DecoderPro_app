#include "throttle.h"

//Throttle::Throttle(QObject *parent) :
//    QObject(parent)
//{
//}
    /**
     * Constant used in getThrottleInfo.
     */
    /*public*/ /*static*/ /*final*/ QString Throttle::SPEEDSTEPMODE = "SpeedStepsMode"; // speed steps NOI18N

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
      * Constants to represent Function Groups.
      * <p>
      * The are the same groupings for both normal Functions and Momentary.
      */
     /*public*/ /*static*/ /*final*/ const QVector<int>Throttle::FUNCTION_GROUPS = QVector<int>{ 1, 1, 1, 1, 1, /** 0-4 */
         2, 2, 2, 2, /** 5-8 */   3, 3, 3, 3, /** 9-12 */
         4, 4, 4, 4, 4, 4, 4, 4, /** 13-20 */ 5, 5, 5, 5, 5, 5, 5, 5 /** 21-28 */
     };

     /**
      * Get Function 0 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF0() {
         return getFunction(0);
     }

     /**
      * Get Function 1 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF1() {
         return getFunction(1);
     }

     /**
      * Get Function 2 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF2() {
         return getFunction(2);
     }

     /**
      * Get Function 3 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF3() {
         return getFunction(3);
     }

     /**
      * Get Function 4 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF4() {
         return getFunction(4);
     }

     /**
      * Get Function 5 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF5() {
         return getFunction(5);
     }

     /**
      * Get Function 6 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF6() {
         return getFunction(6);
     }

     /**
      * Get Function 7 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF7() {
         return getFunction(7);
     }

     /**
      * Get Function 8 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF8() {
         return getFunction(8);
     }

     /**
      * Get Function 9 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF9() {
         return getFunction(9);
     }

     /**
      * Get Function 10 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF10() {
         return getFunction(10);
     }

     /**
      * Get Function 11 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF11() {
         return getFunction(11);
     }

     /**
      * Get Function 12 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF12() {
         return getFunction(12);
     }

     /**
      * Get Function 13 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF13() {
         return getFunction(13);
     }

     /**
      * Get Function 14 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF14() {
         return getFunction(14);
     }

     /**
      * Get Function 15 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF15() {
         return getFunction(15);
     }

     /**
      * Get Function 16 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF16() {
         return getFunction(16);
     }

     /**
      * Get Function 17 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF17() {
         return getFunction(17);
     }

     /**
      * Get Function 18 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF18() {
         return getFunction(18);
     }

     /**
      * Get Function 19 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF19() {
         return getFunction(19);
     }

     /**
      * Get Function 20 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF20() {
         return getFunction(20);
     }

     /**
      * Get Function 21 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF21() {
         return getFunction(21);
     }

     /**
      * Get Function 22 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF22() {
         return getFunction(22);
     }

     /**
      * Get Function 23 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF23() {
         return getFunction(23);
     }

     /**
      * Get Function 24 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF24() {
         return getFunction(24);
     }

     /**
      * Get Function 25 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF25() {
         return getFunction(25);
     }

     /**
      * Get Function 26 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF26() {
         return getFunction(26);
     }

     /**
      * Get Function 27 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF27() {
         return getFunction(27);
     }

     /**
      * Get Function 28 Status.
      * @return true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ bool Throttle::getF28() {
         return getFunction(28);
     }

     /**
      * Set Function 0 Status.
      * @param f0 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF0(bool f0) {
         setFunction(0,f0);
     }

     /**
      * Set Function 1 Status.
      * @param f1 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF1(bool f1) {
         setFunction(1,f1);
     }

     /**
      * Set Function 2 Status.
      * @param f2 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF2(bool f2) {
         setFunction(2,f2);
     }

     /**
      * Set Function 3 Status.
      * @param f3 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF3(bool f3) {
         setFunction(3,f3);
     }

     /**
      * Set Function 4 Status.
      * @param f4 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF4(bool f4) {
         setFunction(4,f4);
     }

     /**
      * Set Function 5 Status.
      * @param f5 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF5(bool f5) {
         setFunction(5,f5);
     }

     /**
      * Set Function 6 Status.
      * @param f6 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF6(bool f6) {
         setFunction(6,f6);
     }

     /**
      * Set Function 7 Status.
      * @param f7 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF7(bool f7) {
         setFunction(7,f7);
     }

     /**
      * Set Function 8 Status.
      * @param f8 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF8(bool f8) {
         setFunction(8,f8);
     }

     /**
      * Set Function 9 Status.
      * @param f9 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF9(bool f9) {
         setFunction(9,f9);
     }

     /**
      * Set Function 10 Status.
      * @param f10 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF10(bool f10) {
         setFunction(10,f10);
     }

     /**
      * Set Function 11 Status.
      * @param f11 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF11(bool f11) {
         setFunction(11,f11);
     }

     /**
      * Set Function 12 Status.
      * @param f12 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF12(bool f12) {
         setFunction(12,f12);
     }

     /**
      * Set Function 13 Status.
      * @param f13 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF13(bool f13) {
         setFunction(13,f13);
     }

     /**
      * Set Function 14 Status.
      * @param f14 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF14(bool f14) {
         setFunction(14,f14);
     }

     /**
      * Set Function 15 Status.
      * @param f15 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF15(bool f15) {
         setFunction(15,f15);
     }

     /**
      * Set Function 16 Status.
      * @param f16 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF16(bool f16) {
         setFunction(16,f16);
     }

     /**
      * Set Function 17 Status.
      * @param f17 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF17(bool f17) {
         setFunction(17,f17);
     }

     /**
      * Set Function 18 Status.
      * @param f18 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF18(bool f18) {
         setFunction(18,f18);
     }

     /**
      * Set Function 19 Status.
      * @param f19 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF19(bool f19) {
         setFunction(19,f19);
     }

     /**
      * Set Function 20 Status.
      * @param f20 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF20(bool f20) {
         setFunction(20,f20);
     }

     /**
      * Set Function 21 Status.
      * @param f21 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF21(bool f21) {
         setFunction(21,f21);
     }

     /**
      * Set Function 22 Status.
      * @param f22 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF22(bool f22) {
         setFunction(22,f22);
     }

     /**
      * Set Function 23 Status.
      * @param f23 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF23(bool f23) {
         setFunction(23,f23);
     }

     /**
      * Set Function 24 Status.
      * @param f24 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF24(bool f24) {
         setFunction(24,f24);
     }

     /**
      * Set Function 25 Status.
      * @param f25 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF25(bool f25) {
         setFunction(25,f25);
     }

     /**
      * Set Function 26 Status.
      * @param f26 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF26(bool f26) {
         setFunction(26,f26);
     }

     /**
      * Set Function 27 Status.
      * @param f27 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF27(bool f27) {
         setFunction(27,f27);
     }

     /**
      * Set Function 28 Status.
      * @param f28 true for Function On, false for Function Off.
      */
     /*public*/ /*default*/ void Throttle::setF28(bool f28) {
         setFunction(28,f28);
     }

 // functions momentary status - note that we use the naming for DCC,
     // though that's not the implication;
     // see also DccThrottle interface

     /**
      * Get Momentary Function 0 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF0Momentary() {
         return getFunctionMomentary(0);
     }

     /**
      * Get Momentary Function 1 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF1Momentary() {
         return getFunctionMomentary(1);
     }

     /**
      * Get Momentary Function 2 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF2Momentary() {
         return getFunctionMomentary(2);
     }

     /**
      * Get Momentary Function 3 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF3Momentary() {
         return getFunctionMomentary(3);
     }

     /**
      * Get Momentary Function 4 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF4Momentary() {
         return getFunctionMomentary(4);
     }

     /**
      * Get Momentary Function 5 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF5Momentary() {
         return getFunctionMomentary(5);
     }

     /**
      * Get Momentary Function 6 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF6Momentary() {
         return getFunctionMomentary(6);
     }

     /**
      * Get Momentary Function 7 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF7Momentary() {
         return getFunctionMomentary(7);
     }

     /**
      * Get Momentary Function 8 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF8Momentary() {
         return getFunctionMomentary(8);
     }

     /**
      * Get Momentary Function 9 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF9Momentary() {
         return getFunctionMomentary(9);
     }

     /**
      * Get Momentary Function 10 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF10Momentary() {
         return getFunctionMomentary(10);
     }

     /**
      * Get Momentary Function 11 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF11Momentary() {
         return getFunctionMomentary(11);
     }

     /**
      * Get Momentary Function 12 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF12Momentary() {
         return getFunctionMomentary(12);
     }

     /**
      * Get Momentary Function 13 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF13Momentary() {
         return getFunctionMomentary(13);
     }

     /**
      * Get Momentary Function 14 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF14Momentary() {
         return getFunctionMomentary(14);
     }

     /**
      * Get Momentary Function 15 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF15Momentary() {
         return getFunctionMomentary(15);
     }

     /**
      * Get Momentary Function 16 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF16Momentary() {
         return getFunctionMomentary(16);
     }

     /**
      * Get Momentary Function 17 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF17Momentary() {
         return getFunctionMomentary(17);
     }

     /**
      * Get Momentary Function 18 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF18Momentary() {
         return getFunctionMomentary(18);
     }

     /**
      * Get Momentary Function 19 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF19Momentary() {
         return getFunctionMomentary(19);
     }

     /**
      * Get Momentary Function 20 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF20Momentary() {
         return getFunctionMomentary(20);
     }

     /**
      * Get Momentary Function 21 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF21Momentary() {
         return getFunctionMomentary(21);
     }

     /**
      * Get Momentary Function 22 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF22Momentary() {
         return getFunctionMomentary(22);
     }

     /**
      * Get Momentary Function 23 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF23Momentary() {
         return getFunctionMomentary(23);
     }

     /**
      * Get Momentary Function 24 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF24Momentary() {
         return getFunctionMomentary(24);
     }

     /**
      * Get Momentary Function 25 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF25Momentary() {
         return getFunctionMomentary(25);
     }

     /**
      * Get Momentary Function 26 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF26Momentary() {
         return getFunctionMomentary(26);
     }

     /**
      * Get Momentary Function 27 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF27Momentary() {
         return getFunctionMomentary(27);
     }

     /**
      * Get Momentary Function 28 Status.
      * @return true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ bool Throttle::getF28Momentary() {
         return getFunctionMomentary(28);
     }

     /**
      * Set Momentary Function 0 Status.
      * @param f0Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF0Momentary(bool f0Momentary) {
         setFunctionMomentary(0,f0Momentary);
     }

     /**
      * Set Momentary Function 1 Status.
      * @param f1Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF1Momentary(bool f1Momentary) {
         setFunctionMomentary(1,f1Momentary);
     }

     /**
      * Set Momentary Function 2 Status.
      * @param f2Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF2Momentary(bool f2Momentary) {
         setFunctionMomentary(2,f2Momentary);
     }

     /**
      * Set Momentary Function 3 Status.
      * @param f3Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF3Momentary(bool f3Momentary) {
         setFunctionMomentary(3,f3Momentary);
     }

     /**
      * Set Momentary Function 4 Status.
      * @param f4Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF4Momentary(bool f4Momentary) {
         setFunctionMomentary(4,f4Momentary);
     }

     /**
      * Set Momentary Function 5 Status.
      * @param f5Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF5Momentary(bool f5Momentary) {
         setFunctionMomentary(5,f5Momentary);
     }

     /**
      * Set Momentary Function 6 Status.
      * @param f6Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF6Momentary(bool f6Momentary) {
         setFunctionMomentary(6,f6Momentary);
     }

     /**
      * Set Momentary Function 7 Status.
      * @param f7Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF7Momentary(bool f7Momentary) {
         setFunctionMomentary(7,f7Momentary);
     }

     /**
      * Set Momentary Function 8 Status.
      * @param f8Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF8Momentary(bool f8Momentary) {
         setFunctionMomentary(8,f8Momentary);
     }

     /**
      * Set Momentary Function 9 Status.
      * @param f9Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF9Momentary(bool f9Momentary) {
         setFunctionMomentary(9,f9Momentary);
     }

     /**
      * Set Momentary Function 10 Status.
      * @param f10Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF10Momentary(bool f10Momentary) {
         setFunctionMomentary(10,f10Momentary);
     }

     /**
      * Set Momentary Function 11 Status.
      * @param f11Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF11Momentary(bool f11Momentary) {
         setFunctionMomentary(11,f11Momentary);
     }

     /**
      * Set Momentary Function 12 Status.
      * @param f12Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF12Momentary(bool f12Momentary) {
         setFunctionMomentary(12,f12Momentary);
     }

     /**
      * Set Momentary Function 13 Status.
      * @param f13Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF13Momentary(bool f13Momentary) {
         setFunctionMomentary(13,f13Momentary);
     }

     /**
      * Set Momentary Function 14 Status.
      * @param f14Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF14Momentary(bool f14Momentary) {
         setFunctionMomentary(14,f14Momentary);
     }

     /**
      * Set Momentary Function 15 Status.
      * @param f15Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF15Momentary(bool f15Momentary) {
         setFunctionMomentary(15,f15Momentary);
     }

     /**
      * Set Momentary Function 16 Status.
      * @param f16Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF16Momentary(bool f16Momentary) {
         setFunctionMomentary(16,f16Momentary);
     }

     /**
      * Set Momentary Function 17 Status.
      * @param f17Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF17Momentary(bool f17Momentary) {
         setFunctionMomentary(17,f17Momentary);
     }

     /**
      * Set Momentary Function 18 Status.
      * @param f18Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF18Momentary(bool f18Momentary) {
         setFunctionMomentary(18,f18Momentary);
     }

     /**
      * Set Momentary Function 19 Status.
      * @param f19Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF19Momentary(bool f19Momentary) {
         setFunctionMomentary(19,f19Momentary);
     }

     /**
      * Set Momentary Function 20 Status.
      * @param f20Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF20Momentary(bool f20Momentary) {
         setFunctionMomentary(20,f20Momentary);
     }

     /**
      * Set Momentary Function 21 Status.
      * @param f21Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF21Momentary(bool f21Momentary) {
         setFunctionMomentary(21,f21Momentary);
     }

     /**
      * Set Momentary Function 22 Status.
      * @param f22Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF22Momentary(bool f22Momentary) {
         setFunctionMomentary(22,f22Momentary);
     }

     /**
      * Set Momentary Function 23 Status.
      * @param f23Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF23Momentary(bool f23Momentary) {
         setFunctionMomentary(23,f23Momentary);
     }

     /**
      * Set Momentary Function 24 Status.
      * @param f24Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF24Momentary(bool f24Momentary) {
         setFunctionMomentary(24,f24Momentary);
     }

     /**
      * Set Momentary Function 25 Status.
      * @param f25Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF25Momentary(bool f25Momentary) {
         setFunctionMomentary(25,f25Momentary);
     }

     /**
      * Set Momentary Function 26 Status.
      * @param f26Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF26Momentary(bool f26Momentary) {
         setFunctionMomentary(26,f26Momentary);
     }

     /**
      * Set Momentary Function 27 Status.
      * @param f27Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF27Momentary(bool f27Momentary) {
         setFunctionMomentary(27,f27Momentary);
     }

     /**
      * Set Momentary Function 28 Status.
      * @param f28Momentary true for Momentary Function On, else false.
      */
     /*public*/ /*default*/ void Throttle::setF28Momentary(bool f28Momentary) {
         setFunctionMomentary(28,f28Momentary);
     }

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
      * Commonly used string in Throttle property change listeners.ThrottleListener l
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
     // /*public*/ abstract bool[] getFunctions();

     /**
      * Get copy of function momentary status array.
      * Typically returns array length of 29, i.e. 0-28.
      * @return momentary function array, length dependant by hardware type.
      */
     //@Nonnull
     ///*public*/ /*abstract*/ QVector<bool> getFunctionsMomentary();
