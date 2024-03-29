#include <stdio.h>
#include <iostream>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include "server_config.h"
#include "server_server.h"

#define ARGS_REQUIRED 2

int main(int argc, char const *argv[]) {
	if (argc != ARGS_REQUIRED) {
		std::cerr << "Es necesario introducir " << ARGS_REQUIRED << 
		" argumentos. Finalizando..." << std::endl;
		return 1;
	}
	try {
        Config c(argv[1]);
		Server server(&c);
		server.server_run();
    } catch (YAML::BadFile& e) {
        std::cerr << "Error en la lectura del YAML" << std::endl;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
		return 1;
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
