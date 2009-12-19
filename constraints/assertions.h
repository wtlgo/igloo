#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include <stack>
#include "ioperator.h"
#include "logicaloperator.h"
#include "constraint.h"
#include "notoperator.h"
#include "andoperator.h"
#include "equaltoconstraint.h"
#include "greaterthanconstraint.h"
#include "lessthanconstraint.h"
#include "evaluatedconstraint.h"
#include "operatorstack.h"
#include "expression.h"
#include "is.h"

namespace igloo {

  class Assert {
  public:

    template <typename T>
    static void That(T actual, Expression& expression)
    {
      if (!expression.Evaluate(actual))
      {
        throw AssertionException(CreateErrorText(expression, actual));
      }
    }

    static void That(const char* actual, Expression& constraint)
    {
      return That<std::string > (std::string(actual), constraint);
    }

    static void That(bool& actual)
    {
      if (!actual)
      {
        throw AssertionException("Expected condition to be true");
      }
    }

  private:
    template <typename T>
    static std::string CreateErrorText(const Expression& expression, const T& actual)
    {
      std::ostringstream str;
      str << "Expected: ";
      str << expression.GetExpectationText();
      str << std::endl;
      str << "Actual: " << actual;
      str << std::endl;

      return str.str();
    }
  };
}
#endif	/* _ASSERTIONS_H */

