<?php
require_once('/lib/nusoap.php');

// Create a client for the service
$objClienteSOAP = new nusoap_client('http://mottz.info/ictac2015/ExponerServiciosWebICTAC.php?wsdl','wsdl');
$param = array('ID' => '1144052533', 'tipoID' => 'ID');

$resultado1 = $objClienteSOAP->call('ConsultarInfoUsuario', $param);
$resultado2 = $objClienteSOAP->call('ConsultarDescargaCertificado', $param);
$resultado3 = $objClienteSOAP->call('ConsultarCertificadoUsuario', $param);

    
echo '<br>';
print_r($resultado1);
echo '<br>';

echo '<br>';
print_r($resultado2);
echo '<br>';

echo '<br>';
print_r($resultado3);
echo '<br>';
     
?>
