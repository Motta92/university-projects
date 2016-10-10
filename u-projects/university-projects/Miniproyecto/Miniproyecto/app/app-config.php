<?php 
/* very VERY basic security */
if( !defined('SQ_PHP_SECURITY') ) {
   die("Intento de Hacking");
}
/*
 * Valoriables de configuración de la aplicación.
 */

/*
 * Variables necesarias para realizar una conexion con la Base de datos.
 */

$db_host = 'mysql.hostinger.es'; // Host de la BD.
//$db_port = 3306; // Puerto de conexion.
$db_user = 'u408523480_bot'; // Nombre de usuario de la BD.
$db_pass = 'mlp123'; // Password del usuario de la BD.
$db_name = 'u408523480_artp'; // Nombre de la Base de Datos.

/*
 * Necesario para el manejo de archivos
 */
$baseUrl = ""; // Define cual sera la carpeta raiz, por ejemplo "/micarpeta" o "/carpeta/micarpeta", por defecto vacio

/*
 * Configuracion de paginado
 */

$maxRows_img = 9; // Numero maximo de imagenes por pagina.

/*
 * Necesarias para el uso de phpass (PasswordHash.php).
 */

// Base-2 logarithm of the iteration count used for password stretching.
$hash_cost_log2 = 8;

// Do we require the hashes to be portable to older systems (less secure)?
$hash_portable = FALSE;


 ?>