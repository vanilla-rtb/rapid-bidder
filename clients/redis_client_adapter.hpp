/* 
 * File:   redis_client_adapter.hpp
 * Author: arseny.bushev@gmail.com
 *
 * Created on 31 марта 2017 г., 12:00
 */

#ifndef REDIS_CLIENT_ADAPTER_HPP
#define REDIS_CLIENT_ADAPTER_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include "deps/redisclient/src/redisclient/redisasyncclient.h"

namespace vanilla {

    class redis_client_adapter {
    public:
        using connection_ok_handler_type = std::function<void(boost::asio::io_service&)>;
        using connection_fail_handler_type = std::function<void(const std::string&, boost::asio::io_service&)>;
        using get_handler_type = std::function<void(boost::asio::io_service&, const std::string&)>;

        redis_client_adapter(boost::asio::io_service &io) :
            io{io}, client{io}
        {
        }

        void connect(const std::string &host, uint16_t port, const connection_ok_handler_type &connection_ok_handler, const connection_fail_handler_type &connection_fail_handler) {
            client.connect(boost::asio::ip::address::from_string(host), port, [this, &connection_ok_handler, &connection_fail_handler](bool ok, const std::string & err) {
                if (!ok) {
                    connection_fail_handler(err, this->io);
                } else {
                    connection_ok_handler(this->io);
                }
            });
        }

        void get(const std::string &key, std::string &data, const get_handler_type &get_handler) {
            client.command("GET",{key}, [this, &data, &get_handler](const redisclient::RedisValue & redis_value) {
                data = redis_value.toString();
                get_handler(this->io, data);
            });
        }

        bool connected() const {
            return client.isConnected();
        }
    private:
        boost::asio::io_service &io;
        redisclient::RedisAsyncClient client;
    };
}
#endif /* REDIS_CLIENT_ADAPTER_HPP */

