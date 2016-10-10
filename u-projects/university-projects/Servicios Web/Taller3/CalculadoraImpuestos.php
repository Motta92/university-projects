<?php  
require_once('lib/nusoap.php');
$ns="http://localhost:8080/CalculadoraImpuestos/";
$server= new nusoap_server();
$server->configureWSDL('CalculadoraImpuestos',$ns);
$server->register('calcularIva', array('amount'=>'xsd:int'), 
	array('return'=>'xsd:float'),
	$ns);
$server->register('sumarMotz', array('valor1'=>'xsd:int', 'valor2'=>'xsd:int'), 
	array('return'=>'xsd:int'),
	$ns);
$server->register('restarMotz', array('valor1'=>'xsd:int', 'valor2'=>'xsd:int'), 
	array('return'=>'xsd:int'),
	$ns);
$server->register('multiplicarMotz', array('valor1'=>'xsd:int', 'valor2'=>'xsd:int'), 
	array('return'=>'xsd:int'),
	$ns);

function calcularIva($amount){
	$tax=$amount*0.16;
	return new soapval('return', 'xsd:float',$tax);
}

function sumarMotz($valor1, $valor2){
	$result = $valor1 + $valor2;
	return new soapval('return', 'xsd:int',$result);
}

function restarMotz($valor1, $valor2){
	$result = $valor1 - $valor2;
	return new soapval('return', 'xsd:int',$result);
}

function multiplicarMotz($valor1, $valor2){
	$result = $valor1 * $valor2;
	return new soapval('return', 'xsd:int',$result);
}

if ( !isset( $HTTP_RAW_POST_DATA ) )
    $HTTP_RAW_POST_DATA = file_get_contents( 'php://input' );

$server->service($HTTP_RAW_POST_DATA);

?>