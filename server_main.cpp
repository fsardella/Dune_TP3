#include <stdio.h>
#include <iostream>

#include "server_server.h"

#define ARGS_REQUIRED 2

int main(int argc, char const *argv[]) {
	if (argc != ARGS_REQUIRED) {
		std::cerr << "Es necesario introducir " << ARGS_REQUIRED << 
		" argumentos. Finalizando..." << std::endl;
		return 1;
	}
	try {
		Server server(argv[1]);
		server.server_run();
	} catch(std::invalid_argument const&){
		std::cerr << "Datos invalidos. Servidor error." << std::endl;
		return 1;
	} catch (std::logic_error const&) {
		std::cerr << "Socket communication error." << std::endl;
		return 1;
	} catch(std::exception const&){
		std::cerr << "Error en el servidor." << std::endl;
		return 1;
	} catch (...) {
        return 1;
    }
	return 0;
}
