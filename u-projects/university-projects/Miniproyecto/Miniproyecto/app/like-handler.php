<?php 
  define('SQ_PHP_SECURITY', true);
  require 'app-config.php';
  require 'functions.php';

  if (isset($_POST['like']))
  {
    $cookie_name = "counter_gang".$_POST['imagen'];
    if(isset($_COOKIE[$cookie_name]))
    {
      redirect_to("../vista-obra.php?liked=2&idimagen=".$_POST['imagen']);
    } else {
      // Conection to the database
    	$connection = mysqli_connect($db_host,$db_user, $db_pass, $db_name);

      if(mysqli_connect_errno()){
        $not_connected = "database connection failed: " .
        mysqli_connect_error() .
        " (" . mysqli_connect_errno() . ")";
        // Error handling
        fail($not_connected);
      }
      // Cookie para limitar la votacion por dia
      setcookie($cookie_name, "liked", time()+3600*24, "/", "artpoof.hol.es");

      // Obtenemos el total de likes de la imagen
      $query = "UPDATE imagen set likes = likes + 1 WHERE idimagen=%d";
      $query = sprintf($query, $_POST['imagen']);
      $result = mysqli_query($connection, $query);

      redirect_to("../vista-obra.php?liked=1&idimagen=".$_POST['imagen']);
    }
  }
?>