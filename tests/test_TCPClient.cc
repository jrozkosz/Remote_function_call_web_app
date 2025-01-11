// Jakub Rozkosz

#define BOOST_TEST_MODULE TCPClientTest
#include <boost/test/included/unit_test.hpp>
#include "../backend/TCPClient.h"

BOOST_AUTO_TEST_CASE(TestTCPClientInitialization) {
    TCPClient client;
    
    BOOST_CHECK(true);
}