#include "common_resolver.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <new>  // para el std::bad_alloc
#include <stdexcept>

Resolver::Resolver(const char* hostname, const char* servicename,
                   bool passive) {
    struct addrinfo hints;
    this->result = this->next_ = nullptr;

    /*
     * getaddrinfo nos puede retornar multiples direcciones incluso de
     * protocolos/tecnologias que no nos interesan.
     * Para pre-seleccionar que direcciones nos interesan le pasamos
     * un hint, una estructura con algunos campos completados (no todos)
     * que le indicaran que tipo de direcciones queremos.
     * */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = passive ? AI_PASSIVE : 0;
    /* AI_PASSIVE for server; 0 for client */


    /* Obtengo la (o las) direcciones segun el nombre de host y servicio que
     * busco
     *
     * De todas las direcciones posibles, solo me interesan aquellas que sean
     * IPv4 y TCP (segun lo definido en hints)
     *
     * El resultado lo guarda en result que es un puntero al primer nodo
     * de una lista simplemente enlazada.
     * */
    int s = getaddrinfo(hostname, servicename, &hints, &this->result);

    /* Es muy importante chequear los errores.
     * En caso de uno, usar gai_strerror para traducir el codigo de error (s)
     * a un mensaje humanamente entendible.
     * */
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        throw std::runtime_error("");
    }

    this->next_ = this->result;
}

bool Resolver::has_next() {
    return this->next_ != NULL;
}

struct addrinfo* Resolver::next() {
    struct addrinfo *ret = this->next_;
    this->next_ = ret->ai_next;
    return ret;
}

Resolver::~Resolver() {
    /*
     * Como la lista reservada por getaddrinfo() es dinamica requiere
     * una desinicializacion acorde.
     *
     * Podes imaginarte que getaddrinfo() hace un malloc() y que
     * el freeaddrinfo() es su correspondiente free()
     *
     * Dado que el Resolver podria haberse movido y perdido el ownership
     * de la lista, debemos liberarla solo si aun somos responsables
     * (dueños de ella)
     * */
    if (this->result)
        freeaddrinfo(this->result);
}

Resolver::Resolver(Resolver&& other) {
    this->result = other.result;
    this->next_ = other.next_;

    // Le robamos al otro resolver su lista de direcciones.
    // A partir de aqui somos nosotros (this) los dueños
    // de ella.
    //
    // Hubo una transferencia de ownership y por lo tanto
    // debemos hacer que el destructor del otro resolver no
    // libere los recursos.
    //
    // En nuestro caso necesitamos poner results a nullptr
    // y modificar el destructor ~Resolver para que no lo
    // libere si es nullptr
    other.result = other.next_ = nullptr;
}

Resolver& Resolver::operator=(Resolver&& other) {
    // Este es un caso borde donde alguien codeo
    //  resolver = resolver;
    //
    // Si alguien quiere "moverse a si mismo" no hacemos nada.
    if (this == &other)
        return *this;

    // A diferencia del constructor por movimiento, nosotros
    // somos un objeto ya construido.
    // Antes de tomar el ownership del otro resolver debemos
    // liberar nuestro propio recurso.
    if (this->result)
        freeaddrinfo(this->result);

    // A partir de aqui hacemos lo mismo que en el constructor
    // por movimiento.
    //
    // Le robamos el recurso al otro, transferimos el ownership
    // del recurso del otro resolver hacia el nuestro.
    this->result = other.result;
    this->next_ = other.next_;

    other.result = other.next_ = nullptr;
    return *this;
}
