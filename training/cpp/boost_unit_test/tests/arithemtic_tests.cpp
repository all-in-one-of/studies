#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE arithmetic
#include <boost/test/unit_test.hpp>

#include "../arithmetic.h" 

BOOST_AUTO_TEST_CASE(simple_test) {
    
    BOOST_CHECK(add(2, 2) == 4);

}