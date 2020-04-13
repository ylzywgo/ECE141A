#include <iostream>
#include "Response.hpp"
#include "AccessSpecifierClass.hpp"


int main(int argc, const char *argv[]) {
    // Part: 1

    {
        QueryResponse queryResponse = QueryResponse(5);
        ServiceResponse serviceResponse = ServiceResponse(9);

        // Add Your Code here

        QueryResponse convertedQueryResponse = QueryResponse(serviceResponse);
        ServiceResponse convertedServiceResponse = ServiceResponse(queryResponse);

        std::cout << "It should output 5: " << convertedServiceResponse.getLength() << std::endl;
        std::cout << "It should output 9: " << convertedQueryResponse.getSize() << std::endl;
    }

    // Part: 2

    {
        QueryResponse queryResponse(5);
        ServiceResponse serviceResponse(9);

        // Add Your Code here

        QueryResponse convertedQueryResponse = serviceResponse;
        ServiceResponse convertedServiceResponse = queryResponse;

        std::cout << "It should output 5: " << convertedServiceResponse.getLength() << std::endl;
        std::cout << "It should output 9: " << convertedQueryResponse.getSize() << std::endl;
    }

    // // Part 3

    {
        QueryResponse queryResponse(5);
        ServiceResponse serviceResponse(9);

        ResponsePrinter responsePrinter = ResponsePrinter();

        // The following code should print the response

        responsePrinter.printServerResponse(serviceResponse);
        responsePrinter.printQueryResponse(queryResponse);
    }

}
