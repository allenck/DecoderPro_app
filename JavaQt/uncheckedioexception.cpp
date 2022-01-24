#include "uncheckedioexception.h"

UncheckedIOException::UncheckedIOException()
{

}

UncheckedIOException::UncheckedIOException(QString msg)
{
 this->msg = msg;
}

UncheckedIOException::UncheckedIOException(Throwable* e)
{
 this->cause = e;
}
