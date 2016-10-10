<?php 
require ('generarPDF.php');
require('dbManager.php');

$selection = $_POST['ActualSelection'];
$stripTagsHtml=strip_tags($_POST["id_man"]);
$htmlSpecialChars= htmlspecialchars($stripTagsHtml);

// Posibles Roles que se le asignan a una persona en la base de datos y su traduccion
$validarSeleccion = array('AU' => 'Author', 'OR' => 'Organizer', 'AS' => 'Assistant');

$sql = "SELECT Persona_x_Actividad.Rol, Persona.nombre, Persona.tipoDoc, Persona.documento, Actividad.nombre as Anombre ";
$sql .= "FROM Persona inner join Persona_x_Actividad inner join Actividad ";
$sql .= "WHERE Persona_x_Actividad.id_persona = Persona.id_persona and Persona_x_Actividad.id_actividad = Actividad.id_actividad ";
$sql .= "and Persona.documento = ";
$sql .= $htmlSpecialChars;
$sql .= " and Actividad.nombre = ";
$sql .= '"'.$selection.'"';



$connection = startConnection();
$result = $connection->query($sql);

if ($result->num_rows > 0) {
	$pdf = new PDF('L');
    
    // output data of each row
    while($row = $result->fetch_assoc()) {
    	$name = $row['nombre'];
    	$docType = $row['tipoDoc'];
    	$id = $row['documento'];
    	$Rol = $validarSeleccion[$row['Rol']];
    	$pdf = crearNuevoPdf($pdf, $name, $docType, $id, $Rol);
    }
    $pdf->Output();
    $check = checkCertificateDownload($htmlSpecialChars, $selection, $connection);
    if ($check == False)
        echo 'Shet motherfucker';
}   
else {
    header("Location: index.php", TRUE, 301);
            
}

closeConnection($connection);


?>