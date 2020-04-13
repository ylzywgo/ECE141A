//
// Created by Savyasachi on 1/26/20.
//

#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class QueryResponse;

class ServiceResponse;

class ResponsePrinter;

class ResponsePrinter {
public:
    void printServerResponse(ServiceResponse response);

    void printQueryResponse(QueryResponse response);
};

class ServiceResponse{
public:
    ServiceResponse(int length);

    explicit ServiceResponse(QueryResponse queryResponse);

    int getLength();

    // Add your code here
    operator QueryResponse() const;

    friend class ResponsePrinter;

private:
    int length;

    std::string getResponse();
};

class QueryResponse{
public:
    QueryResponse(int size);

    int getSize();

    // Add your code here
    explicit QueryResponse(ServiceResponse serviceResponse);

    operator ServiceResponse() const;
    friend class ResponsePrinter;

private:
    int size;

    std::string getResponse();
};

#endif // RESPONSE_H
