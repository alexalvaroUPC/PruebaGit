#include <stdio.h>
#include <my_global.h>
#include <string.h>
#include <mysql.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	MYSQL *conn;
	int err;
	
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf ("Error de conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect (conn, "localhost", "root", "mysql", "videojuego",0, NULL, 0);
	if (conn == NULL) {
		printf ("Error al inicializar la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1)
	}
	
	char username[40];
	printf("Escribe el username\n");
	scanf("%s", username);
	
	char consulta[80];
	strcpy(consulta, "SELECT PARTIDA.ID,PARTIDA.FECHA,PARTIDA.DURACION FROM JUGADOR, PARTIDA, PARTICIPACIONES WHERE PARTIDA.GANADOR = '");
	strcat(consulta, username);
	strcat(consulta, "' AND PARTIDA.DURACION = '30' AND PARTICIPACIONES.JUGADOR = JUGADOR.ID AND PARTICIPACIONES.PARTIDA = PARTIDA.ID");
	
	err = mysql_query (conn, consulta);
	if (err != 0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	if (row == NULL) 
		printf ("No se han obtenido datos en la consulta"\n);
	else
		while (row != NULL) {
			printf ("%s\n", row[0]);
			row = mysql_fetch_row (resultado);
		}
	mysql_close(conn);
	exit(0);
}

