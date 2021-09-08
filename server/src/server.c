#include "server.h"

int main(void) {
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);

	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");

			t_list_iterator* iterador;

			int tam = list_size(lista);

			iterador = list_iterator_create(lista);

			int contador = 1;


			while(list_iterator_has_next(iterador) ){

				char * i = (char *)list_iterator_next( iterador);

				printf("Valor  %d: \t %s \n", contador ,  i );

				contador++;

			};


		//	list_iterate(lista, (void*) iterator);  No me funcaba
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,	"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}

void iterator(t_log* logger, char* value) {
	printf("Valor :  %s \n", value);
	log_info(logger,"%s\n", value);
}
