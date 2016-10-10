<?php
require('dbManager.php');

$ID = '1144052533';
$tipoID = 'ID';
$nombreActividad = 'Conference';
/*
$conn = startConnection();
$sql = "SELECT documento, tipoDoc FROM Persona WHERE documento = '" . $ID . "' and tipoDoc = '" . $tipoID . "'";
echo $sql;
echo '<br>';
$result = $conn->query($sql);
$inDB = 0;
if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
    }
}
closeConnection($conn);
*/
/*
$contactInfo = array();
$conn = startConnection();
$query = "SELECT nombre, apellido, documento, tipoDoc FROM Persona WHERE documento = '" . $ID . "' and tipoDoc = '" . $tipoID . "'";
$result = $conn->query($query);
if ($result->num_rows > 0) {
	checkCertificateDownload($ID, $nombreActividad, $conn);
    // output data of each row
    while($row = $result->fetch_assoc()) {
    	array_push($contactInfo, array('nombre' => $row['nombre'], 'apellido' => $row['apellido']));
    	echo $row['nombre'] . ' ' . $row['apellido'];
    }
    
}
*/

//validateCertificateDownload($ID, $tipoID);

//echo '<br>';
//echo $contactInfo;

$res = ConsultarInfoUsuarioDB($ID, $tipoID);
echo 'Consultar info: ';
print_r($res);
/*
closeConnection($conn);
*/

?>