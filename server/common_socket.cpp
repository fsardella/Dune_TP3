#include "common_socket.h"
#include "common_resolver.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>

#define ERROR 1

Socket::Socket(const char *hostname, const char *servicename) :
    skt(-1), closed(true) {
    Resolver resolver(hostname, servicename, false);
    int s;
    int skt = -1;
    while (resolver.has_next()) {
        struct addrinfo *addr = resolver.next();

        /* Cerramos el socket si nos quedo abierto de la iteracion
         * anterior
         * */
        if (skt != -1)
            ::close(skt);

        /* Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
           el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0)*/
        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        /* Intentamos conectarnos al servidor cuya direccion
         * fue dada por getaddrinfo()
         * */
        s = connect(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        // Conexion exitosa!
        this->skt = skt;
        this->closed = false;
        return;
    }

    // No hay q olvidarse de cerrar el socket en caso de
    // que lo hayamos abierto
    if (skt != -1)
        ::close(skt);
    throw std::runtime_error("Socket connection failed");
}

Socket::Socket(const char *servicename) : skt(-1), closed(true) {
    Resolver resolver(nullptr, servicename, true);

    int s = 0;
    int skt = -1;
    while (resolver.has_next()) {
        struct addrinfo *addr = resolver.next();

        /* Cerramos el socket si nos quedo abierto de la iteracion
         * anterior
         * */
        if (skt != -1)
            ::close(skt);

        /* Creamos el socket definiendo la misma familia, tipo y protocolo
         * que tiene la direccion que estamos por probar.
         * Por ejemplo deberia ser la familia AF_INET IPv4,
         * el tipo de socket SOCK_STREAM TCP  y el protocolo 0.
         *
         * Ya que usamos getaddrinfo() no conviene hardcodear esos valores
         * sino usar los mismos que ya estan cargados en la direccion
         * que estamos probando.
         * */
        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        /*
         * Como el sistema operativo puede mantener ocupado (en TIME_WAIT)
         * un puerto que fue usado recientemente, no queremos que nuesta
         * aplicacion falle a la hora de hacer un bind() por algo que sabemos
         * que es temporal.
         *
         * Un puerto en TIME_WAIT esta "ocupado" solo temporalmente por
         * el sistema operativo.
         *
         * Entonces queremos decirle que "queremos reutilizar la direccion"
         * aun si esta en TIME_WAIT (de otro modo obtendriamos un error al
         * llamar a bind() con un "Address already in use")
         * */
        int val = 1;
        s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (s == -1) {
            continue;
        }

        // Hacemos le bind: enlazamos el socket a una direccion local
        // para escuchar
        s = bind(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        // Ponemos el socket a escuchar. Ese 20 (podria ser otro valor)
        // indica cuantas conexiones a la espera de ser aceptadas se toleraran
        // No tiene nada q ver con cuantas conexiones totales el server tendra
        s = listen(skt, 20);
        if (s == -1) {
            continue;
        }

        // setupeamos el socket! Ahora esta escuchando
        // en una de las direcciones obtenidas por getaddrinfo()
        // y esta listo para aceptar conexiones.
        this->skt = skt;
        this->closed = false;
        return;
    }

    // No hay q olvidarse de cerrar el socket en caso de
    // que lo hayamos abierto
    if (skt != -1)
        ::close(skt);
    throw std::runtime_error("socket setup failed");
}
/*
 * Constructor que inicializa el socket pasandole directamente el file
 * descriptor.
 *
 * No queremos que el codigo del usuario este manipulando el file descriptor,
 * queremos q interactue con él *solo* a traves de Socket.
 *
 * Por ello ponemos este constructor privado (vease socket.h).
 * */
Socket::Socket(int skt) : skt(skt), closed(false) {
}

int Socket::recvsome(void *data, unsigned int sz) {
    int s = recv(this->skt, (char*)data, sz, 0);
    if (s <= 0) {
        // Si s == 0, puede ser o no un error, dependera del protocolo.
        // Alguno protocolo podria decir "se reciben datos hasta
        // que la conexion se cierra" en cuyo caso el cierre del socket
        // no es un error sino algo esperado.
        if (s < 0)
            // 99% casi seguro que es un error real
            throw std::runtime_error("socket recv failed");
        throw ClosedSocketException();
    } else {
        return s;
    }
}

int Socket::sendsome(const void *data, unsigned int sz) {
    int s = send(this->skt, (char*)data, sz, MSG_NOSIGNAL);
    if (s <= 0) {
        // Puede o no ser un error (vease el comentario en recvsome())

        // Este es un caso especial: cuando enviamos algo pero en el medio
        // se detecta un cierre del socket no se sabe bien cuanto se logro
        // enviar (y fue recibido por el peer) y cuanto se perdio.
        //
        // Se dice que la "tuberia esta rota" o en ingles, "broken pipe"
        //
        // En Linux el sistema operativo envia una signal (SIGPIPE) que
        // mata al proceso. El flag MSG_NOSIGNAL evita eso y nos permite
        // checkear y manejar la condicion mas elegantemente
        if (s < 0 && errno != EPIPE)
            // 99% casi seguro que es un error
            throw std::runtime_error("socket send failed");
        throw ClosedSocketException();
    } else {
        return s;
    }
}

int Socket::recvall(void *data, unsigned int sz) {
    unsigned int received = 0;

    while (received < sz) {
        int s = this->recvsome((char*)data + received, sz - received);
        // Al estar la excepcion en revsome, no necesita chequeos.
        received += s;
    }

    return sz;
}



int Socket::sendall(const void *data, unsigned int sz) {
    unsigned int sent = 0;

    while (sent < sz) {
        int s = this->sendsome((char*)data + sent, sz - sent);
        // Al estar la excepcion en sendsome, no necesita chequeos.
        sent += s;
    }

    return sz;
}


Socket Socket::accept() {
    int skt = ::accept(this->skt, nullptr, nullptr);
    if (skt == -1) {
        // perror("socket accept failed");
        // No tira perror porque es comportamiento esperable
        // al cerrar el Socket aceptador.
        throw ClosedSocketException();
    }
    /*
     * Creamos un Socket en el scope de Socket::accept() y lo retornamos.
     * Por default C y C++ harian una copia pero copiar un Socket no tiene
     * sentido y ya tenemos al constructor por copia deshabilitado
     * asi que no funcionara.
     *
     * Lo que queremos es que este Socket siga vivo y se mueva al scope
     * superior (a quien llamo a Socket::accept().
     *
     * Este es el corazon de Move Semantics.
     * */
    return Socket(skt);
}


int Socket::shutdown(int how) {
    if (::shutdown(this->skt, how) == -1) {
        perror("socket shutdown failed");
        return -1;  // "No exceptions in destructors"
    }

    return 0;
}

int Socket::close() {
    this->closed = true;
    return ::close(this->skt);
}

void Socket::closeSkt() {
    ::shutdown(this->skt, SHUT_RDWR);
    ::close(this->skt);
}

Socket::~Socket() {
    if (!this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }
}

Socket::Socket(Socket&& other) {
    this->skt = other.skt;
    this->closed = other.closed;

    // Le robamos al otro socket su file descriptor.
    // A partir de aqui somos nosotros (this) los dueños
    // del recurso.
    //
    // Hubo una transferencia de ownership y por lo tanto
    // debemos hacer que el destructor del otro socket no
    // libere los recursos.
    //
    // Para Socket con esto alcanza (mirate Resolver)
    other.skt = -1;
    other.closed = true;
}

Socket& Socket::operator=(Socket&& other) {
    // Este es un caso borde donde alguien codeo
    //  skt = skt;
    //
    // Si alguien quiere "moverse a si mismo" no hacemos nada.
    if (this == &other)
        return *this;

    // A diferencia del constructor por movimiento, nosotros
    // somos un objeto ya construido.
    // Antes de tomar el ownershipt del otro socket debemos
    // liberar nuestro propio recurso.
    if (!this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }

    // A partir de aqui hacemos lo mismo que en el constructor
    // por movimiento.
    //
    // Le robamos el recurso al otro, transferimos el ownership
    // del recurso del otro socket hacia el nuestro.
    this->skt = other.skt;
    this->closed = other.closed;

    other.skt = -1;
    other.closed = true;

    return *this;
}
