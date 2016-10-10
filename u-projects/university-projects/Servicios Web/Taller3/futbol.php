<?php
require_once('/lib/nusoap.php');
$objClienteSOAP = new nusoap_client('http://footballpool.dataaccess.eu/data/info.wso?WSDL',TRUE);
$param=array();
$resultado = $objClienteSOAP->call('AllCards', $param);

  if ($resultado->fault) { // si
        $error = $resultado->getError();
    if ($error) { // Hubo algun error
            echo 'Error:  ' . $resultado->faultstring;
        }     
        die();
    }  
    

    echo "<pre>";
    print_r($resultado);
    echo "</pre>";
    /*
    $temp = $resultado['AllCardsResult'];
    foreach($temp['tCardInfo'] as $cosa){
        echo $cosa['sPlayerName'];
        echo "<br>";
        echo $cosa['sGameTeam1'];
        echo "<br>";
        echo "<br>"; 
    }
    */
    
     
?>
