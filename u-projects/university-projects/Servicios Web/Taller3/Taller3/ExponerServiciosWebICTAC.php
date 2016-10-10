<?php  
require_once('lib/nusoap.php');
require('dbManager.php');
// namespace
$ns="http://mottz.info/ictac2015";
$server= new nusoap_server();
$server->configureWSDL('ExponerServiciosWebICTAC',$ns);

// Adding complex type
$server->wsdl->addComplexType('contactInfo',
    'complexType',
    'struct',
    'all',
    '',
    array('first_name' => array('name' => 'first_name', 'type' => 'xsd:string'),
          'last_name' => array('name' => 'last_name', 'type' => 'xsd:string')
    )
);

//Create a complex type
$server->wsdl->addComplexType('MyComplexType','complexType','struct','all','',
        array( 'contact' => array('name' => 'contact','type' => 'xsd:string'),
               'email' => array('name' => 'email','type' => 'xsd:string')));

// Registrar servicios
$server->register('ConsultarCertificadoUsuario', array('ID'=>'xsd:string', 'tipoID'=>'xsd:string'), 
	array('return'=>'xsd:boolean'),
	$ns);


$server->register('ConsultarInfoUsuario', array('ID'=>'xsd:string', 'tipoID'=>'xsd:string'), 
	array('return'=>'tns:contactInfo'),
	$ns);

$server->register('ConsultarDescargaCertificado', array('ID'=>'xsd:string', 'tipoID'=>'xsd:string'), 
	array('return'=>'xsd:boolean'),
	$ns);

$server->register('sumarMotz', array('valor1'=>'xsd:int', 'sumar2'=>'xsd:int'), 
	array('return'=>'xsd:int'),
	$ns);

//Register our method using the complex type
$server->register(
                // method name:
                'HelloComplexWorld',
                // parameter list:
                array(),
                // return value(s):
                array('return'=>'tns:MyComplexType'),
                // namespace:
                $ns);



function ConsultarCertificadoUsuario($ID, $tipoID){
	$inDB = ConsultarCertificadoUsuarioDB($ID, $tipoID);

	return new soapval('return', 'xsd:boolean', $inDB);
}

function ConsultarInfoUsuario($ID, $tipoID){
	$res = ConsultarInfoUsuarioDB($ID, $tipoID);
	$list = array('first_name' => $res['nombre'], 'last_name' => $res['apellido']);

	return $list;
}

function ConsultarDescargaCertificado($ID, $tipoID){
	$checked = ConsultarDescargaCertificadoDB($ID, $tipoID);

	return new soapval('return', 'xsd:boolean', $checked);
}



function sumarMotz($valor1, $valor2){
	$result = $valor1 + $valor2;
	return new soapval('return', 'xsd:int', $result);
}

// Definir operaciones de los servicios

//Our complex method
function HelloComplexWorld()
{
    //return $mycomplextype;
    $result = array();
    $result[] = array( 'contact' => 'Manoj', 'email' => 'manoj@gmail.com');
    //$result[] = array( 'contact' => 'munna', 'email' => 'munna@gmail.com');
 
    return $result;
}




if ( !isset( $HTTP_RAW_POST_DATA ) )
    $HTTP_RAW_POST_DATA = file_get_contents( 'php://input' );

$server->service($HTTP_RAW_POST_DATA);

?>