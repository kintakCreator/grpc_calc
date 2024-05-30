#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "service.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using calculator::ResultReply;
using calculator::Arguments;
using calculator::CalculatorService;

class CalculatorServiceClient {
public:
    CalculatorServiceClient(std::shared_ptr<Channel> channel)
        : stub_(CalculatorService::NewStub(channel)) {}

    std::pair<long long, std::string> sendAddRequest(int a, int b) {
        Arguments request;
        request.set_a(a);
        request.set_b(b);
        
        ResultReply reply;
        ClientContext context;
        
        Status status = stub_->sendAddRequest(&context, request, &reply);

        if (status.ok()) {
            return std::make_pair(reply.result(), reply.errormessage());
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << '\n';
            return std::make_pair(0, "RPC failed");
        }
    }

    std::pair<long long, std::string> sendSubRequest(int a, int b) {
        Arguments request;
        request.set_a(a);
        request.set_b(b);
        
        ResultReply reply;
        ClientContext context;
        
        Status status = stub_->sendSubRequest(&context, request, &reply);

        if (status.ok()) {
            return std::make_pair(reply.result(), reply.errormessage());
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << '\n';
            return std::make_pair(0, "RPC failed");
        }
    }

    std::pair<long long, std::string> sendMulRequest(int a, int b) {
        Arguments request;
        request.set_a(a);
        request.set_b(b);
        
        ResultReply reply;
        ClientContext context;
        
        Status status = stub_->sendMulRequest(&context, request, &reply);

        if (status.ok()) {
            return std::make_pair(reply.result(), reply.errormessage());
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << '\n';
            return std::make_pair(0, "RPC failed");
        }
    }
    
    std::pair<long long, std::string> sendDivRequest(int a, int b) {
        Arguments request;
        request.set_a(a);
        request.set_b(b);
        
        ResultReply reply;
        ClientContext context;
        
        Status status = stub_->sendDivRequest(&context, request, &reply);

        if (status.ok()) {
            return std::make_pair(reply.result(), reply.errormessage());
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << '\n';
            return std::make_pair(0, "RPC failed");
        }
    }
private:
    std::unique_ptr<CalculatorService::Stub> stub_;
};

void RunClient() {
    std::string target_address("0.0.0.0:50051");
    // Instantiates the client
    CalculatorServiceClient client(
        // Channel from which RPCs are made - endpoint is the target_adress
        grpc::CreateChannel(target_address,
                            // Indicate when channel is not authenticated
                            grpc::InsecureChannelCredentials()));
    int a;
    std::cout << "Enter first integer: ";
    std::cin >> a;
    
    int b;
    std::cout << "Enter second integer: ";
    std::cin >> b;

    char operation;
    do {
        std::cout << "Enter operation(+, -, /, *): ";
        std::cin >> operation;
    }
    while (operation != '+' && operation != '-' && operation != '*' && operation != '/');

    switch (operation) {
        case '+': {
            std::pair<int, std::string> response = client.sendAddRequest(a, b);
            std::cout << response.first << '\n';
            break;            
        }
        case '-': {
            std::pair<int, std::string> response = client.sendSubRequest(a, b);
            std::cout << response.first << '\n';
            break;     
        }
        case '*': {
            std::pair<int, std::string> response = client.sendMulRequest(a, b);
            std::cout << response.first << '\n';
            break;           
        }
        case '/': {
            std::pair<int, std::string> response = client.sendDivRequest(a, b);
            if (response.second.size() > 0)
                std::cout << response.second << '\n';
            else
                std::cout << response.first << '\n';
            break;  
        }
    }
}
    
int main(int argc, char** argv) {
    RunClient();
    return 0;
}
