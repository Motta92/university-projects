<?php
  // Setting the cookie
  /*
  $name = "user_id";
  $value = 0;
  $expire = time() + (60*60);
  setcookie($name, $value, $expire);
  $name = "username";
  $value = 0;
  setcookie($name, $value, $expire);
  */
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
  $user_pass_error = FALSE;

  if(isset($_POST["submit"]))
  {
    $user = make_safe($_POST["user"],$connection);
    $pass = make_safe($_POST["pass"],$connection);
    $query = "SELECT email, pass, id, nivel";
    $query .= " FROM usuario";
    $query .= " WHERE email ='$user'";
    $result = mysqli_query($connection, $query);
    if($result == NULL){
      $user_pass_error = TRUE;
    } else {
      $usuario = mysqli_fetch_assoc($result);
      $hasher = new PasswordHash($hash_cost_log2, $hash_portable);
      $user_pass_error = !($hasher->CheckPassword($pass, $usuario['pass']));
      unset($hasher);
      mysqli_free_result($result);
      if(!$user_pass_error){
        $_SESSION["user_id"] = $usuario["id"];
        $_SESSION["user_level"] = $usuario["nivel"];
        redirect_to("perfil.php?idusuario=".$usuario['id']);
      }
    }
  }

?>
  <body class="login">
    <?php include('app/nav.php'); ?>
     <div class="container">
      <?php
      // Error handling  
        if($user_pass_error == TRUE){
          ?>
      <div class="alert alert-danger" role="alert"> Usuario o contraseña incorrectos!</div>
        <?php } ?>
      <form action="login.php" method="post" class="form-signin" role="form">
        <h2 class="form-signin-heading">Inico de sesión</h2>

        <input type="email" name="user" class="form-control" placeholder="Dirección Email" value="" required autofocus>
        <input type="password" name="pass" class="form-control" placeholder="Contraseña" value="" required>
        
        <button class="btn btn-lg btn-primary btn-block" name="submit" type="submit">Iniciar sesión</button>

      </form>
      
      <hr>
    </div>
<?php 
include('app/footer.php');
// Close connection with MySQL
  mysqli_close($connection);
?>