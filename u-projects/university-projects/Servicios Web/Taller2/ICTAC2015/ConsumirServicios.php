<?php
require_once('/lib/nusoap.php');
$objClienteSOAP = new nusoap_client('http://mottz.info/ictac2015/ExponerServiciosWebICTAC.php?wsdl');
$param = array('ID' => '1144052533', 'tipoID' => 'ID');
$param2 = array();
$resultado = $objClienteSOAP->call('ConsultarInfoUsuario', $param);
$resultado2 = $objClienteSOAP->call('HelloComplexWorld', $param2);

  if ($resultado2->fault) { // si
        $error = $resultado2->getError();
    if ($error) { // Hubo algun error
            echo 'Error:  ' . $resultado2->faultstring;
        }     
        die();
    }  

    echo '<br>';
    echo '<h1>';
    echo $resultado;
    echo '</h1>';
    echo '<br>';

    echo '<br>';
    print_r($resultado2);
    echo '<br>';
    
     
?>
