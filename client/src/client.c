#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "hola soy un log!");

	config = iniciar_config();

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor

	valor = config_get_string_value( config,  "CLAVE"   );

	ip = config_get_string_value( config,  "IP"   );

	puerto = config_get_string_value( config,  "PUERTO"   );
	//Loggear valor de config

	printf("Escriba algo para almacenar en log \n");
	leer_consola(logger);



	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servidor
	enviar_mensaje(valor, conexion);


	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger; // = malloc(sizeof(t_log));

	nuevo_logger = log_create("cliente.log", "client", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("tp0.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	log_info(logger, leido);

	free(leido);
	// Acá la idea es que imprimas por el log lo que recibis de la consola.


}

void paquete(int conexion)
{
	//Ahora toca lo divertido!
	char* leido;

	t_paquete* paquete;

	paquete = crear_paquete();

	printf("ingrese textos para enviar en un paquete \n");

//	char *texto1;

//	texto1 = "texto ejemplo 1";

	///texto1[strlen(texto1)] = '\0';

//	agregar_a_paquete( paquete, texto1, strlen(texto1) +1 );

//	char * texto2 = "texto ejemplo 2";

//	texto2[strlen(texto2)] = '\0';
//agregar_a_paquete( paquete, texto2, strlen(texto2) +1  );
	//char* leido;
//	t_paquete* paquete;
	//paquete = crear_paquete();
	leido = readline(">");
	while(strcmp(leido,"") != 0)
	{
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
		leido = readline(">");		

	}
	free(leido);
	

	enviar_paquete( paquete , conexion );

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{

	liberar_conexion(conexion);

	log_destroy(logger);

	config_destroy(config);

	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
