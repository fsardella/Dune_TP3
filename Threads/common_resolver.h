#ifndef RESOLVER_H
#define RESOLVER_H

struct addrinfo;

/*
 * Resolverdor de hostnames y service names.
 * Por simplificacion este TDA se enfocara solamente
 * en direcciones IPv4 para TCP.
 * */
class Resolver {
    struct addrinfo *result;
    struct addrinfo *next_;

    public:
    /* Inicializa la estructura y resuelve el dado nombre del host y servicio.
     * Si passive es True, la resolucion se hace pensando que se quiere
     * inicializar un socket pasivo, de otro modo sera para un socket activo.
     *
     * Retorna 0 en caso de exito, -1 en caso de error.
     * */
    Resolver(const char* hostname, const char* servicename, bool passive);


    /* Retorna si hay o no una direccion siguiente para testear.
     * Si la hay, se debera llamar a Resolver::next() para obtenerla.
     *
     * Si no la hay se puede asumir que el resolver esta extinguido.
     * */
    bool has_next();

    /* Retorna la siguiente direccion para testear e internamente
     * mueve el iterador a la siguiente direccion.
     *
     * Si no existe una siguiente direccion el resultado es indefinido.
     * */
    struct addrinfo* next();

    /*
     * Libera los recursos.
     * */
    ~Resolver();

    /*
     * Es poco probable que alguien quiera realmente copiar un resolver.
     * Es mas probable que alguien copie uno "sin querer" ya que en C++
     * el default es pasaje por copia.
     *
     * Lo mas saludable es prohibir la copia asi el compilador puede
     * darse cuenta de una copia no desada.
     * */
    Resolver(const Resolver&) = delete;
    Resolver& operator=(const Resolver&) = delete;

    /*
     * Resolver es movible
     * */
    Resolver(Resolver&&);
    Resolver& operator=(Resolver&&);
};

#endif
