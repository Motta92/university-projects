<?php 
require 'app-config.php';
require 'PasswordHash.php';

/* Sin finalizar */

// Obtenemos los valores enviados por un formulario
// TODO: Falta revisar la integridad de los datos
$user = $_POST['user'];
$pass = $_POST['password'];

// Utilizamos phpass para crear los hash a partir del password obtenido
$hasher = new PasswordHash($hash_cost_log2, $hash_portable);
$hash = $hasher->HashPassword($pass);
if (strlen($hash) < 20)
	fail('Hubo un fallo al crear el hash del password');
unset($hasher);

/* TODO: conectar y guardar los datos en la BD */

 ?>