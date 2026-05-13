#pragma once

#include "tcp_server.hpp"

namespace lfs::tcp {
    class ResponderServer : public TCPServer {
    public:
        explicit ResponderServer(int port, std::shared_ptr<vis::TrainerManager> trainer_manager);
        ~ResponderServer() override;
        void start() override;
        void stop() override;
        void join() override;

    private:
        void run();
        [[nodiscard]] nlohmann::json generateResponse(const nlohmann::json& request);
        [[nodiscard]] nlohmann::json getValue(std::string_view parameter, bool& success);

    private:
        std::thread response_thread_;
        std::atomic<bool> running_;
    };
}