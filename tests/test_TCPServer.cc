// Jakub Rozkosz

#define BOOST_TEST_MODULE TCPServerTest
#include <boost/test/included/unit_test.hpp>
#include "../backend/TCPServer.h"
#include "../backend/TCPClient.h"
#include <memory>

BOOST_AUTO_TEST_CASE(TestTCPServerInitialization) {
    TCPServer server(4000);

    BOOST_CHECK(true);
}
