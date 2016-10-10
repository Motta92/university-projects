<?php 
/* Manejo de errores */
function fail($pub, $pvt = '')
{
	$msg = $pub;
	if ($pvt !== '')
		$msg .= ": $pvt";
	die("An error occurred ($msg).\n");
}

/* Redirecciona el navegador */
function redirect_to($new_location){
	header("Location: " . $new_location);
	exit;
}

/* Revisa si un usuario existe en la base de datos */
function user_exists($user) {
$query = "select usuario from usuario where usuario='$user'";
$result = mysql_query($query);
if($result == NULL){
return false;}else{
$line = mysql_fetch_array($result, MYSQL_ASSOC);
mysql_free_result($result);
return $line !== FALSE;
}}

/* Revisa si un email tiene un formato valido */
function check_email($variable){
if(preg_match("/^[_a-zA-Z0-9-]+(\.[_a-zA-Z0-9-]+)*@([_a-zA-Z0-9-]+\.)*[a-zA-Z0-9-]{2,200}\.[a-zA-Z]{2,6}$/", $variable ))
	return true;
return false;
}

/* Altera un parametro para evitar una inyeccion SQL */
function make_safe($variable, $db) {
$variable = htmlentities($variable, ENT_QUOTES);
if (get_magic_quotes_gpc()) {
$variable = stripslashes($variable);
}
$variable = mysqli_real_escape_string($db,trim($variable));
$variable = strip_tags($variable);
return $variable;
}

?>