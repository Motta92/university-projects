<?php
include('app/header.php'); 
require('app/PasswordHash.php');
// connection to a database
$connection = mysqli_connect($db_host,$db_user, $db_pass, $db_name);

if(mysqli_connect_errno()){
  $not_connected = "database connection failed: " .
  mysqli_connect_error() .
  " (" . mysqli_connect_errno() . ")";
  // Error handling
  die($not_connected);
  }

  // Variable usada para el checkeo del email
  $valid_email = TRUE;
 $register_error = FALSE;

  // Obtenemos los valores enviados por un formulario
if(isset($_POST["registrarse"])){
  $Nombre = make_safe($_POST["name"],$connection);
  $Apellido = make_safe($_POST["lastname"],$connection);
  $User = make_safe($_POST["email"],$connection);
  $Pass = make_safe($_POST["password"],$connection);

  // Revisa si el correo tiene un formato valido
  $valid_email = check_email($User);
  if (check_email)
  {
    // Utilizamos phpass para crear los hash a partir del password obtenido
    $hasher = new PasswordHash($hash_cost_log2, $hash_portable);
    $hash = $hasher->HashPassword($Pass);
    if (strlen($hash) < 20)
      fail('Hubo un fallo al crear el hash del password');
    unset($hasher);

    $query = "SELECT email";
    $query .= " FROM usuario";
    $query .= " WHERE email = ";
    $query .= $User;
   
    $result = mysqli_query($connection, $query);
    if ($result != NULL){
      $register_error = TRUE;
      mysqli_free_result($result);
    }
    //$nul = var_dump(is_null($result));
    //while($users = mysqli_fetch_row($result)){}
    //echo $users[$User];
    else{
      $query = "INSERT INTO usuario ";
      $query .= "(nombre, apellido, email, pass)";
      $query .= " VALUES ('{$Nombre}','{$Apellido}','{$User}','{$hash}')";
      echo $query;
      $result2 = mysqli_query($connection, $query);

      if($result2){
        mysqli_free_result($result2);
        redirect_to("index.php");
      }
      else{
        die("Database query failed." . mysqli_error($connection));
      }   
    }
  }
}

?>


  <body class="login">
<?php include('app/nav.php'); ?>
     <div class="container">
      <?php 
      // Error handling 
        if($register_error == TRUE){
          ?>
          <div class="alert alert-danger" role="alert"> Email ya registrado</div>
        <?php } elseif($valid_email == FALSE) {?>
          <div class="alert alert-danger" role="alert"> Email inválido</div>
        <?php } ?>
      <form action="registro.php" method="post" class="form-signin" role="form">
        <h2 class="form-signin-heading">Registro</h2>
        <input type="email" name="email" class="form-control" placeholder="Dirección Email" required autofocus>
        <input type="text" name="name" class="form-control" placeholder="Nombre" required>
        <input type="text" name="lastname" class="form-control" placeholder="Apellido" required>
        <input type="password" name="password" class="form-control" placeholder="Contraseña" required>
        <button class="btn btn-lg btn-primary btn-block" name="registrarse" type="submit">Registrarse</button>
      </form>
      </form>

      

      <hr>
    </div>

<?php 
  include('app/footer.php');

  mysqli_close($connection);
?>