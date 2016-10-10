<?php

// Funcion que permite iniciar la conexion a la DB
function startConnection(){
	$servername = "sql203.cuccfree.com";
	$username = "cucch_15800625";
	$password = "cfMotta2306";
	$dbName = "cucch_15800625_ictac2015";
	$conn = new mysqli($servername, $username, $password, $dbName);
	// Check connection
	if ($conn->connect_error) {
		echo '<h1>Failed to connect</h1>';
	    die("Connection failed: " . $conn->connect_error);
	}
	return $conn;
}

// Funcion que permite terminar la conexion a la DB
function closeConnection($conn){
	$conn->close();
}

// Consulta a la base de datos para saber si el usuario se encuentra en la DB
function consultarCertificadoUsuarioDB($id, $tipoId){
	
	$stripID = strip_tags($id);
	$hscID = htmlspecialchars($stripID);

	$stripType = strip_tags($tipoId);
	$hscType = htmlspecialchars($stripType);
	

	$inDB = false;
	$conn = startConnection();

	// Por alguna razon este query funciona en SoapUI, pero no en python, ruby y php
	//$sql = 'SELECT documento, tipoDoc FROM Persona WHERE documento = ' . $hscID . ' and tipoDoc = ' . $hscType;

	// Por alguna razon este query funciona en php, python y ruby, pero no en soapUI
	$sql = 'SELECT documento, tipoDoc FROM Persona WHERE documento = ' . "'" .$hscID . "'".' and tipoDoc = ' . "'".$hscType."'";

	$result = $conn->query($sql);
	
	if ($result->num_rows > 0) {
	    // output data of each row
	    $inDB = true;
	}

	closeConnection($conn);

	return $inDB;
}

// Consulta a la base de datos para obtener el nombre y apellido de la persona
function ConsultarInfoUsuarioDB($id, $tipoId){
	$stripID = strip_tags($id);
	$hscID = htmlspecialchars($stripID);

	$stripType = strip_tags($tipoId);
	$hscType = htmlspecialchars($stripType);

	$conn = startConnection();

	/*
	// Por alguna razon este query funciona en SoapUI, pero no en python, ruby y php
	$sql = 'SELECT nombre, apellido, documento, tipoDoc';
	$sql .= ' FROM Persona WHERE documento = '; 
	$sql .= $hscID . ' and tipoDoc = ' . $hscType;
	*/
	
	// Por alguna razon este query funciona en php, python y ruby, pero no en soapUI
	$sql = 'SELECT nombre, apellido, documento, tipoDoc';
	$sql .= ' FROM Persona WHERE documento = '; 
	$sql .= "'".$hscID."'" . ' and tipoDoc = ' . "'".$hscType."'";
	
	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
		$row = $result->fetch_assoc();
	}
	closeConnection($conn);

	return $row;
}

// Consulta la base de datos para saber que certificados fueron descargados
function ConsultarDescargaCertificadoDB($id, $tipoId){
	$stripID = strip_tags($id);
	$hscID = htmlspecialchars($stripID);

	$stripType = strip_tags($tipoId);
	$hscType = htmlspecialchars($stripType);

	$conn = startConnection();
	$checked = false;

	/*
	// Por alguna razon este query funciona en SoapUI, pero no en python, ruby y php
	$sql = "SELECT Persona_x_Actividad.descargado  ";
	$sql .= "FROM Persona inner join Persona_x_Actividad ";
	$sql .= "WHERE Persona_x_Actividad.id_persona = Persona.id_persona ";
	$sql .= "and Persona.documento = ";
	$sql .= $hscID;
	$sql .= " and Persona.tipoDoc = ";
	$sql .= $hscType;
	*/

	// Por alguna razon este query funciona en php, python y ruby, pero no en soapUI
	$sql = "SELECT Persona_x_Actividad.descargado  ";
	$sql .= "FROM Persona inner join Persona_x_Actividad ";
	$sql .= "WHERE Persona_x_Actividad.id_persona = Persona.id_persona ";
	$sql .= "and Persona.documento = ";
	$sql .= "'".$hscID."'";
	$sql .= " and Persona.tipoDoc = ";
	$sql .= "'".$hscType."'";

	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	    // output data of each row
	    while($row = $result->fetch_assoc()) {
	    	if($row['descargado'] == 1){
	    		$checked = true;
	    	}
	    }
	}
	closeConnection($conn);
	return $checked;
}


// Valida y actualiza la base de datos para identificar que certificados fueron 
// descargados
function checkCertificateDownload($doc, $nombreActividad, $conn){
	$sql = "UPDATE Persona_x_Actividad inner join Persona inner join Actividad ";
	$sql .= "SET Persona_x_Actividad.descargado = 1 ";
	$sql .= "WHERE Persona_x_Actividad.id_persona = Persona.id_persona and Persona_x_Actividad.id_actividad = Actividad.id_actividad ";
	$sql .= "and Persona.documento = ";
	$sql .= $doc;
	$sql .= " and Actividad.nombre = ";
	$sql .= '"'.$nombreActividad.'"';

	if ($conn->query($sql) === TRUE) {
    	//echo "Record updated successfully";
    	return True;
	} else {
	    //echo "Error updating record: " . $conn->error;
	    return False;
	}

}


// Funcion de prueba
function validateCertificateDownload($doc, $tipoDoc){
	$conn = startConnection();

	$sql = "SELECT Persona.nombre, Persona.documento, Persona_x_Actividad.descargado  ";
	$sql .= "FROM Persona inner join Persona_x_Actividad ";
	$sql .= "WHERE Persona_x_Actividad.id_persona = Persona.id_persona ";
	$sql .= "and Persona.documento = ";
	$sql .= $doc;
	$sql .= " and Persona.tipoDoc = ";
	$sql .= '"'.$tipoDoc.'"';

	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	    // output data of each row
	    while($row = $result->fetch_assoc()) {
	    	if($row['descargado'] == 1){
	    		$checked = True;
	    	}
	    }
	}
	closeConnection($conn);

}

	

?>