#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calculator::ResultReply;
using calculator::Arguments;
using calculator::CalculatorService;

class CalculatorServiceImplementation final : public CalculatorService::Service {
    Status sendAddRequest(ServerContext* context, const Arguments* request,
                          ResultReply* reply) override {
        int a = request->a();
        int b = request->b();
        long long result = a + b;
        reply->set_result(result);
        reply->set_errormessage("");
        return Status::OK;
    }

    Status sendSubRequest(ServerContext* context, const Arguments* request,
                          ResultReply* reply) override {
        int a = request->a();
        int b = request->b();
        long long result = a - b;
        reply->set_result(result);
        reply->set_errormessage("");
        return Status::OK;
    }

    Status sendMulRequest(ServerContext* context, const Arguments* request,
                          ResultReply* reply) override {
        int a = request->a();
        int b = request->b();
        long long result = a * 1ll * b;
        reply->set_result(result);
        reply->set_errormessage("");
        return Status::OK;
    }

    Status sendDivRequest(ServerContext* context, const Arguments* request,
                          ResultReply* reply) override {
        int a = request->a();
        int b = request->b();
        if (b == 0) {
            reply->set_result(0);
            reply->set_errormessage("Division by zero.");
            return Status::OK;
        }
        long long result = a / b;
        reply->set_result(result);
        reply->set_errormessage("");
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    CalculatorServiceImplementation service;

    ServerBuilder builder;
    // Listen on the given address without any auth mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which
    // communication with client takes place
    builder.RegisterService(&service);

    // Assembling the server
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
