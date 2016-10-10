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
  fail($not_connected);
  }

// Variable usada para el checkeo del email
$change_success = FALSE;
$invalid_pass = FALSE;
$inconsistent_pass = FALSE;

// Obtenemos los valores enviados por un formulario
if(isset($_POST["cambiar"]) and $gb_user_id != NULL){
  $oldpassword = make_safe($_POST["oldpassword"],$connection);
  $newpassword = make_safe($_POST["newpassword"],$connection);
  $repeatpassword = make_safe($_POST["repeatpassword"],$connection);

  if ($newpassword != $repeatpassword)
  {
    $inconsistent_pass = TRUE;
  } else {

    // Utilizamos phpass para crear los hash a partir del password obtenido
    $hasher = new PasswordHash($hash_cost_log2, $hash_portable);
    $hash = $hasher->HashPassword($newpassword);
    if (strlen($hash) < 20)
      fail('Hubo un fallo al crear el hash del password');

    $query = "SELECT pass";
    $query .= " FROM usuario";
    $query .= " WHERE id = ";
    $query .= $gb_user_id;
   
    $result = mysqli_query($connection, $query);
    if ($result != NULL)
    {
      $info = mysqli_fetch_assoc($result);
      if($hasher->CheckPassword($oldpassword, $info['pass']))
      {
        $query = "UPDATE usuario SET pass = '%s' WHERE id = %d";
        $query = sprintf($query, $hash, $gb_user_id);
        $result2 = mysqli_query($connection, $query);

        if($result2)
        {
          mysqli_free_result($result2);
          $change_success = TRUE;
          redirect_to("index.php");
        }
        else{
          fail("Database query failed." . mysqli_error($connection));
        }
      } else { $invalid_pass = TRUE; }
      mysqli_free_result($result);
    }
    unset($hasher);
  }
}

?>


  <body class="login">
<?php include('app/nav.php'); ?>
     <div class="container">
      <?php if($change_success == TRUE) { ?>
        <div class="alert alert-success" role="alert"> Contraseña cambiada</div>
      <?php } if($inconsistent_pass == TRUE) { ?>
        <div class="alert alert-warning" role="alert"> La contraseña nueva no coincide.</div>
      <?php } elseif($invalid_pass == TRUE) { ?>
        <div class="alert alert-warning" role="alert"> La contraseña vieja es inválida.</div>
      <?php } ?>
      <?php if($gb_user_id == NULL) { ?>
        <div class="alert alert-danger" role="alert"> Debes estar registrado y logueado para acceder a esta sección.</div>
      <?php } else { ?>
      <form action="cambio-password.php" method="post" class="form-signin" role="form">
        <h2 class="form-signin-heading">Camniar contraseña</h2>
        <input type="password" name="oldpassword" class="form-control" placeholder="Contraseña actual" required autofocus>
        <input type="password" name="newpassword" class="form-control" placeholder="Nueva contraseña" required>
        <input type="password" name="repeatpassword" class="form-control" placeholder="Repetir contraseña" required>
        <button class="btn btn-lg btn-primary btn-block" name="cambiar" type="submit">Registrarse</button>
      </form>
      <?php } ?>
      <hr>
    </div>

<?php 
  include('app/footer.php');

  mysqli_close($connection);
?>