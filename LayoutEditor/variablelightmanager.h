#ifndef VARIABLELIGHTMANAGER_H
#define VARIABLELIGHTMANAGER_H
#include "variablelight.h"
#include "manager.h"

/*public*/ /*interface*/class  VariableLightManager : public virtual Manager/*<VariableLight>*/
{
  Q_INTERFACES(Manager)
 public:
    /** {@inheritDoc} */
    //@Override
    virtual /*public*/ void dispose()=0;

    /**
     * Locate a VariableLight by its user name.
     *
     * @param s the user name
     * @return the light or null if not found
     */
//    @CheckReturnValue
//    @CheckForNull
//    @Override
    virtual/*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString s)const =0;

    /**
     * Locate a VariableLight by its system name.
     *
     * @param s the system name
     * @return the light or null if not found
     */
//    @CheckReturnValue
//    @CheckForNull
//    @Override
    virtual /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString s) const =0;

};
Q_DECLARE_INTERFACE(VariableLightManager, "VariableLightManager")
#endif // VARIABLELIGHTMANAGER_H
