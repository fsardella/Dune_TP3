#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <exception>

// Excepcion para catchear especificamente!
class ClosedSocketException: public std::exception {};

/*
 * Socket.
 * Por simplificacion este TDA se enfocara solamente
 * en sockets IPv4 para TCP.
 * */
class Socket {
    int skt;
    bool closed;

    explicit Socket(int skt);

    public:
    /*
     * Construye el socket tanto para conectarse a un servidor
     * (primer constructor) como para inicializarlo para ser usado
     * por un servidor (segundo constructor).
     *
     * Muchas librerias de muchos lenguajes ofrecen una unica formal de inicializar
     * los sockets y luego metodos (post-inicializacion) para establer
     * la conexion o ponerlo en escucha.
     *
     * Otras librerias/lenguajes van por tener una inicializacion para
     * el socket activo y otra para el pasivo.
     *
     * Este codigo es un ejemplo de ello.
     *
     * */
    //Socket(const char *hostname, const char *servicename);
    explicit Socket(const char *servicename);

    Socket();

    // Por qué no seguir con el constructor que estaba? Este approach hace que puedas
    // tener un socket "vacío", entonces todos los otros métodos podrían tener errores
    // porque necesitan que el socket esté conectado.
    void socketConnect(const char *hostname, const char *servicename);

    /* Socket::sendsome() lee hasta sz bytes del buffer y los envia. La funcion
     * puede enviar menos bytes sin embargo.
     *
     * Socket::recvsome() por el otro lado recibe hasta sz bytes y los escribe
     * en el buffer (que debe estar pre-allocado). La funcion puede recibir
     * menos bytes sin embargo.
     *
     * Si el socket detecto que la conexion fue cerrada o un error, tira una 
     * excepcion.
     *
     * Lease man send y man recv
     * */
    int sendsome(const void *data, unsigned int sz);
    int recvsome(void *data, unsigned int sz);

    /*
     * Socket::sendall() envia exactamente sz bytes leidos del buffer, ni mas,
     * ni menos. Socket::recvall() recibe exactamente sz bytes.
     *
     * Si hay un error o el socket se cerro durante el envio/recibo de los bytes
     * no hay forma certera de saber cuantos bytes realmente se enviaron/recibieron.
     *
     * Si el socket detecto que la conexion fue cerrada o un error, tira una 
     * excepcion.
     * */
    int sendall(const void *data, unsigned int sz);
    int recvall(void *data, unsigned int sz);

    /*
     * Acepta una conexion entrante y construye con ella un Socket peer.
     * Dicho Socket peer es retornado por move semantics.
     * */
    Socket accept();

    /*
     * Cierra la conexion ya sea parcial o completamente.
     * Lease man 2 shutdown
     * */
    int shutdown(int how);

    /*
     * Cierra el socket. El cierre no implica un shutdown
     * que debe ser llamado explicitamente.
     * */
    int close();

    /*
     * Desinicializa el socket. Si aun esta conectado,
     * se llamara a Socket::shutdown() y Socket::close()
     * automaticamente.
     * */
    ~Socket();

    /*
     * Copiar un Socket carece de todo sentido. Como lo copiarias?
     * Estarian conectados al mismo server? Que pasaria del lado del server
     * si ahora su cliente tiene 2 sockets hacia él?
     *
     * Simplemente no tiene sentido.
     *
     * Ya que C++ nos crea por default el constructor y el operador asignacion
     * por copia, lo unico razonable es prohibir los.
     * */
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    /*
     * Socket es movible
     * */
    Socket(Socket&&);
    Socket& operator=(Socket&&);
};

#endif

