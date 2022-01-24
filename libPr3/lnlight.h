#ifndef LNLIGHT_H
#define LNLIGHT_H
#include "abstractlight.h"

class LnTrafficController;
class LnLightManager;
class LnLight : public AbstractLight
{
    Q_OBJECT
public:
    //explicit LnLight(QObject *parent = 0);
 /*public*/ LnLight(QString systemName, LnTrafficController* tc, LnLightManager* mgr, QObject *parent = 0);
 /*public*/ LnLight(QString systemName, QString userName, LnTrafficController* tc, LnLightManager* mgr, QObject *parent = 0);
    /** State value indicating output intensity is at or above maxIntensity */
    /*public*/ static /*final*/ const int ON          = 0x02;

    /** State value indicating output intensity is at or below minIntensity */
    /*public*/ static /*final*/ const  int OFF         = 0x04;

    /** State value indicating output intensity is
     * less than maxIntensity and more than minIntensity,
     * and no transition is in progress */
    /*public*/ static /*final*/ const  int INTERMEDIATE         = 0x08;


    /** State value indicating output intensity is currently changing toward higher intensity, and will
        continue until full ON is reached */
    /*public*/ static /*final*/ const  int TRANSITIONINGTOFULLON   = 0x310;

    /** State value indicating output intensity is currently changing toward higher intensity. The current
        transition will stop before full ON is reached. */
    /*public*/ static /*final*/ const  int TRANSITIONINGHIGHER 	      = 0x210;

    /** State value indicating output intensity is currently changing toward lower intensity. The current
        transition will stop before full OFF is reached. */
    /*public*/ static /*final*/ const  int TRANSITIONINGLOWER        = 0x110;

    /** State value indicating output intensity is currently changing toward lower intensity, and will
        continue until full OFF is reached */
    /*public*/ static /*final*/ const  int TRANSITIONINGTOFULLOFF = 0x010;

    /** State value mask representing status where output is changing due to a request to transition. */
    /*public*/ static /*final*/ const  int TRANSITIONING         = 0x010;

    //QObject* self() override {return this;}
signals:

public slots:
private:
 LnTrafficController* tc;
 LnLightManager* mgr;
 /*private*/ void initializeLight(QString systemName);
 int mBit;// = 0;                // address bit
 /*protected*/ void doNewState(int oldState, int newState);
Logger* log;
};

#endif // LNLIGHT_H
