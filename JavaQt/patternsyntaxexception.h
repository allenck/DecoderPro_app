#ifndef PATTERNSYNTAXEXCEPTION_H
#define PATTERNSYNTAXEXCEPTION_H
#include "exceptions.h"

class PatternSyntaxException : public IllegalArgumentException
{
public:
 PatternSyntaxException();
};

#endif // PATTERNSYNTAXEXCEPTION_H
