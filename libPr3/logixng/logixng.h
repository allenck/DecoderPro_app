#ifndef LOGIXNG_H
#define LOGIXNG_H
#include "namedbean.h"
#include "base.h"
#include "abstractnamedbean.h"
#include "defaultconditionalng.h"
#include <QHash>

/**
 * LogixNG.
 *
 * @author Daniel Bergqvist Copyright 2018
 * @author Dave Sand        Copyright 2021
 */
/*public*/ /*interface*/ class LogixNG : public NamedBean, public Base
{
  //Q_OBJECT
  Q_INTERFACES(Base NamedBean)
public:
//  LogixNG() {}
//  LogixNG(QString sys, QString user, QObject *parent = nullptr) : AbstractNamedBean(sys, user, parent) {}
    /**
     * Set whenether this LogixNG is enabled or disabled.
     * <P>
     * This method must call registerListeners() / unregisterListeners() and
     * also call execute() if enable is true.
     *
     * @param enable true if this LogixNG should be enabled, false otherwise
     */
    /*public*/ virtual void setEnabled(bool enable) =0;

    /**
     * Determines whether this LogixNG is enabled.
     *
     * @return true if the LogixNG is enabled, false otherwise
     */
    //@Override
    /*public*/ virtual bool isEnabled()=0;

    /**
     * Set the system name for the conditionalNG at the specified position in this list
     * @param index index of the element to set the system name
     * @return the system name
     */
  /*public*/ virtual QString getConditionalNG_SystemName(int index){return "";}

    /**
     * Set the system name for the conditionalNG at the specified position in this list
     * @param index index of the element to set the system name
     * @param systemName the new system name
     */
  /*public*/ virtual void setConditionalNG_SystemName(int index, QString systemName){}

    /**
     * Get number of ConditionalNGs for this LogixNG.
     *
     * @return the number of conditionals
     */
  /*public*/ virtual int getNumConditionalNGs(){return 0;}

    /**
     * Move 'row' to 'nextInOrder' and shift all between 'nextInOrder' and 'row'
     * up one position. Requires {@code row > nextInOrder}.
     *
     * @param nextInOrder target order for ConditionalNG at row
     * @param row         position of ConditionalNG to move
     */
  /*public*/ virtual void swapConditionalNG(int nextInOrder, int row){}

    /**
     * Returns the conditionalNG that will calculate in the specified order.
     * This is also the order the ConditionalNG is listed in the
     * Add/Edit LogixNG dialog. If 'order' is greater than the number of
     * ConditionalNGs for this LogixNG, null is returned.
     *
     * @param order order in which the ConditionalNG calculates
     * @return the conditionalNG or null
     */
    /*public*/ virtual ConditionalNG* getConditionalNG(int order){return nullptr;}

    /**
     * Add a child ConditionalNG to the parent LogixNG.
     * <p>
     * The first part handles adding conditionalNGs to the LogixNG list
     * during file loading.
     * <p>
     * The second part handles normal additions using the GUI, Logix imports or tests.
     *
     * @param conditionalNG The ConditionalNG object.
     * @return true if the ConditionalNG was added, false otherwise.
     */
  /*public*/ virtual bool addConditionalNG(DefaultConditionalNG* conditionalNG){return false;}

    /**
     * Get a ConditionalNG belonging to this LogixNG.
     *
     * @param systemName The name of the ConditionalNG object.
     * @return the ConditionalNG object or null if not found.
     */
    /*public*/ virtual ConditionalNG* getConditionalNG(QString systemName){return nullptr;}

    /**
     * Get a ConditionalNG belonging to this LogixNG.
     *
     * @param userName The name of the ConditionalNG object.
     * @return the ConditionalNG object or null if not found.
     */
    /*public*/ virtual ConditionalNG* getConditionalNGByUserName(QString userName){return nullptr;}

    /**
     * Delete a ConditionalNG from this LogixNG.
     * <p>
     * Note: Since each LogixNG must have at least one ConditionalNG, the last
     * ConditionalNG will not be deleted.
     * <p>
     * Returns An array of names used in an error message explaining why
     * ConditionalNG should not be deleted.
     *
     * @param conditionalNG The ConditionalNG to delete
     */
  /*public*/ virtual void deleteConditionalNG(ConditionalNG* conditionalNG) {}

    /**
     * Execute all ConditionalNGs if the LogixNG is enabled and activated.
     */
  /*public*/ virtual void execute(){}

    /**
     * Execute all ConditionalNGs if the LogixNG is enabled and activated.
     * @param allowRunDelayed true if it's ok to run delayed, false otherwise
     */
  /*public*/ virtual void execute(bool allowRunDelayed) {}

  QObject* self() override{return (QObject*)this;}
};

inline bool operator==(const LogixNG& e1, const LogixNG& e2)
{
 return (e2.NamedBean::getSystemName() == e1.NamedBean::getSystemName())
   && (e2.NamedBean::getUserName() == e1.NamedBean::getUserName());
}
inline size_t qHash(const LogixNG &key, size_t seed)
{
    return qHash(key.NamedBean::getSystemName(), seed) ^ qHash(key.NamedBean::getUserName(), seed);
}

Q_DECLARE_INTERFACE(LogixNG, "LogixNG")
#endif // LOGIXNG_H
