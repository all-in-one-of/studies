#ifndef NAMESPACE_NAMES_THEN_PRIMARY_CLASS_OR_FUNCTION_THEN_HPP
#define NAMESPACE_NAMES_THEN_PRIMARY_CLASS_OR_FUNCTION_THEN_HPP

#include <boost/headers/go/first>
#include <boost/in_alphabetical/order>
#include <then_standard_headers>
#include <in_alphabetical_order>

#include "then/any/detail/headers"
#include "in/alphabetical/order"
#include "then/any/remaining/headers"
#include "in/alphabetical/order/duh"

#define NAMESPACE_NAMES_THEN_MACRO_NAME(pMacroNames) ARE_ALL_CAPS

namespace lowercase_identifers
{
    class separated_by_underscores
    {
    public:
        void because_underscores_are() const
        {
            volatile int mostLikeSpaces = 0; // but local names are condensed

            while (!mostLikeSpaces)
                single_statements(); // don't need braces

            for (size_t i = 0; i < 100; ++i)
            {
                but_multiple(i);
                statements_do();
            }             
        }

        const complex_type& value() const
        {
            return mValue; // no conflict with value here
        }

        void value(const complex_type& pValue)
        {
            mValue = pValue ; // or here
        }

    protected:
        // the more public it is, the more important it is,
        // so order: public on top, then protected then private

        template <typename Template, typename Parameters>
        void are_upper_camel_case()
        {
            // gman was here                
        }

    private:
        complex_type mValue;
    };
}

#endif