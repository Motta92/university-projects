<?php
define('SQ_PHP_SECURITY', true);
include 'app-config.php';
include 'functions.php';
$allowedExts = array("gif", "jpeg", "jpg", "png");
$temp = explode(".", $_FILES["file"]["name"]);
$extension = end($temp);
$db_con = mysqli_connect($db_host,$db_user,$db_pass,$db_name);
if(mysqli_connect_errno()){
  $not_connected = "database connection failed: " .
  mysqli_connect_error() .
  " (" . mysqli_connect_errno() . ")";
  // Error handling
  fail($not_connected);
}

$query = "select idimagen from imagen having MAX(idimagen)";
$result = mysqli_query($db_con,$query);
if($result == NULL){
$nname="0";}
else{
$line = mysqli_fetch_assoc($result);
$nname = $line['idimagen']+1;
mysqli_free_result($result);
}
$imagename=$nname.".".$extension;
if (is_null($gb_user_id)) {
  fail("No se encuentra logeado, no puede subir imagenes.");
}
if(isset($_POST["Subir"])) {
  $Nombre = make_safe($_POST["name"],$db_con);
  $Descripcion = make_safe($_POST["desc"],$db_con);
  $Creacion = make_safe($_POST["yearc"],$db_con);
  $Estilo = make_safe($_POST["style"],$db_con);
  $query = "INSERT INTO imagen ";
  $query .= "(idusuario, nombre, descripcion, anoCreacion, estilo, direccion)";
  $query .= " VALUES ('{$gb_user_id}','{$Nombre}','{$Descripcion}','{$Creacion}','{$Estilo}','{$imagename}')";
  $result2 = mysqli_query($db_con, $query);
  mysqli_free_result($result2);
}
mysqli_close($db_con);
$dir = "../img/".$nname.".".$extension;
if ((($_FILES["file"]["type"] == "image/gif")
|| ($_FILES["file"]["type"] == "image/jpeg")
|| ($_FILES["file"]["type"] == "image/jpg")
|| ($_FILES["file"]["type"] == "image/pjpeg")
|| ($_FILES["file"]["type"] == "image/x-png")
|| ($_FILES["file"]["type"] == "image/png"))
&& ($_FILES["file"]["size"]/125000 < 8)
&& in_array($extension, $allowedExts)) {
  if ($_FILES["file"]["error"] > 0) {
    echo "Error: " . $_FILES["file"]["error"] . "<br>";
  } else {
    echo "Upload: " . $_FILES["file"]["name"] . "<br>";
    echo "Type: " . $_FILES["file"]["type"] . "<br>";
    echo "Size: " . ($_FILES["file"]["size"] / 125000) . " Mb<br>";
    echo "Temporal store in: " . $_FILES["file"]["tmp_name"]."<br>";
    if (file_exists($dir)) {
      echo $dir. " already exists. ";
    } else {
      move_uploaded_file($_FILES["file"]["tmp_name"],
      $dir);
      echo "Stored in: " . $dir;
      redirect_to("../perfil.php?idusuario=".$gb_user_id);
    }
  }
} else {
  echo "Invalid file<br/>";
  echo $_FILES["file"]["error"];
}
?>