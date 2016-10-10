<?php 
require ('generarPDF.php');

$servername = "sql203.cuccfree.com";
$username = "cucch_15800625";
$password = "cfMotta2306";
$dbName = "cucch_15800625_ictac2015";

$conn = new mysqli($servername, $username, $password, $dbName);

// Check connection
if ($conn->connect_error) {
	echo '<h1>NO!</h1>';
    die("Connection failed: " . $conn->connect_error);
}

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

$result = $conn->query($sql);


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
} 
else {
    header("Location: index.php", TRUE, 301);
            
}

$conn->close();


?>