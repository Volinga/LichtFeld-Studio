#pragma once

#include "tcp_server.hpp"

namespace lfs::tcp {
    class PublisherServer : public TCPServer {
    public:
        PublisherServer(int port, std::shared_ptr<vis::TrainerManager> trainer_manager, core::LogLevel level = core::LogLevel::Info, bool warm_up = true);
        ~PublisherServer() override;
        void start() override;
        void stop() override;

    private:
        static nlohmann::json makeEventMessage(const nlohmann::json& data, const std::string& event_type);

    private:
        std::mutex send_mutex_; // Avoids multiple calls to send by different event threads
        std::atomic<bool> stopped_; // Avoids calls to send when the stop is taking place
        std::vector<std::function<void()>> subscriptions_;
        core::LogLevel level_;
        std::optional<core::LogHandlerToken> log_handler_token_;
    };
}
