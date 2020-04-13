//
// Created by Savyasachi on 1/26/20.
//

#include <iostream>
#include "Response.hpp"

// ResponsePrinter 

void ResponsePrinter::printServerResponse(ServiceResponse response) {
    std::cout << response.getResponse() << std::endl;
}

void ResponsePrinter::printQueryResponse(QueryResponse response) {
    std::cout << response.getResponse() << std::endl;
}


// ServiceResponse

ServiceResponse::ServiceResponse(int length) : length(length) {}

int ServiceResponse::getLength() {
    return length;
}

std::string ServiceResponse::getResponse() {
    return "{'length': " + std::to_string(length) + "}";
}

// Add your code for ServiceResponse here

ServiceResponse::ServiceResponse(QueryResponse queryResponse){
    length = queryResponse.getSize();
}

ServiceResponse::operator QueryResponse() const{
    QueryResponse temp = QueryResponse(length); 
    return temp;
}

// QueryResponse

QueryResponse::QueryResponse(int size) : size(size) {}

std::string QueryResponse::getResponse() {
    return "{'size': " + std::to_string(size) + "}";
}

int QueryResponse::getSize() {
    return size;
}

// Add your code for QueryResponse here
QueryResponse::QueryResponse(ServiceResponse serviceResponse){
    size = serviceResponse.getLength();
}

QueryResponse::operator ServiceResponse() const{
    ServiceResponse temp = ServiceResponse(size); 
    return temp;
}