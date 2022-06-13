#include <stdio.h>
#include <iostream>

#include "client_client.h"

#define ARGS_REQUIRED 3

int main(int argc, char const *argv[]) {
	if (argc != ARGS_REQUIRED) {
		std::cerr << "Es necesario introducir " << ARGS_REQUIRED << 
		" argumentos. Finalizando..." << std::endl;
		return 1;
	}
	int return_value = 0;
	try {
		Client client(argv[1], argv[2]);
		return_value = client.client_run();
	}
	catch (std::invalid_argument const&) {
		std::cerr << "Datos invalidos. Cliente error." << std::endl;
		return 1;
	}
	catch (std::logic_error const&) {
		std::cerr << "Socket communication error." << std::endl;
		return 1;
	}
	catch(std::exception const&){
		std::cerr << "Error en el cliente." << std::endl;
		return 1;
	}
	return return_value;
}
