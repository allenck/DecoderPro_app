#include "defaultconditionalngscaffold.h"
#include "defaultsymboltable.h"

/**
 * A ConditionalNG class that always has a symbol table.
 *
 * @author Daniel Bergqvist 2020
 */
// /*public*/ class DefaultConditionalNGScaffold extends DefaultConditionalNG {

    /*public*/ DefaultConditionalNGScaffold::DefaultConditionalNGScaffold(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : DefaultConditionalNG(sys, user, parent){
        //super(sys, user);
        setSymbolTable(new DefaultSymbolTable((ConditionalNG*)this));
    }

    /*public*/ DefaultConditionalNGScaffold::DefaultConditionalNGScaffold(QString sys, QString user, int threadID, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : DefaultConditionalNG(sys, user, threadID, parent){
        //super(sys, user, threadID);
        setSymbolTable(new DefaultSymbolTable((ConditionalNG*)this));
    }
