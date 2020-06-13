#ifndef WF_TEST_UTILS_WS_SERVER2_HPP
#define WF_TEST_UTILS_WS_SERVER2_HPP

#include <jansson.h>
#include <string>

namespace webfuse_test
{

class IIvokationHandler
{
public:
    virtual ~IIvokationHandler() = default;
    virtual std::string Invoke(char const * method, json_t * params) = 0;
};

class WsServer2
{
    WsServer2(WsServer2 const &) = delete;
    WsServer2 & operator=(WsServer2 const & ) = delete;
public:
    WsServer2(
        IIvokationHandler& handler,
        std::string const & protocol,
        int port = 0);
    virtual ~WsServer2();
    bool IsConnected();
    std::string const & GetUrl() const;
private:
    class Private;
    Private * d;
};

}

#endif
