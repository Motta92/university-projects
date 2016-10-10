    <?php 

    $idusuario = $_SESSION['user_id'];
    echo $idusuario;
    if($idusuario == NULL){
      $button1 = "Registrarse";
      $button2 = "Iniciar Sesión";
      $nav_button_1 = "registro.php";
      $nav_button_2 = "login.php";
      $button_type = "success";
    }
    else{
      $button1 = "Perfil";
      $button2 = "Log out";
      $nav_button_1 = "perfil.php?idusuario=$idusuario";
      $nav_button_2 = "index.php";
      //$nav_button_1 = "registro.php";
      //$nav_button_2 = "login.php";
      $button_type = "danger";
    }
    ?>
    <?php
    // connection to a database
    
    ?>
    <nav class="navbar navbar-inverse navbar-static-top" role="navigation">
      <div class="container">
        <div class="navbar-header">
          <a class="navbar-brand" href="<?php echo $baseUrl; ?>/">¡Galería de Arte!</a>
        </div>
         <div class="btn-group navbar-right">
          <a href="<?php echo $baseUrl; ?>/<?php echo $nav_button_1; ?>">
          <button type="button" class="btn btn-success navbar-btn"><?php echo $button1; ?></button></a>

          <a href="<?php echo $baseUrl; ?>/<?php echo $nav_button_2; ?>">
          <button type="button" class="btn btn-<?php echo $button_type;?> navbar-btn"><?php echo $button2; ?></button>
          <?php 
          if($button2 == "log out"){
            $_SESSION["user_id"] = NULL; 
            $_SESSION["username"] = NULL;
          }
          ?>
          </a>

        </div>
      </div>
    </nav>