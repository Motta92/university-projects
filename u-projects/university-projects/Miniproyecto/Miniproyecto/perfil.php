<?php 
$titulo = "Perfil";
include 'app/header.php';
?>
<body>
<?php include 'app/nav.php'; ?>
  <?php 
    // Obtener el nombre del usuario
          $idusuario = $_GET['idusuario']; 
          // connection to a database
          $connection = mysqli_connect($db_host,$db_user, $db_pass, $db_name);

          if(mysqli_connect_errno()){
            $not_connected = "database connection failed: " .
            mysqli_connect_error() .
            " (" . mysqli_connect_errno() . ")";
            // Error handling
            fail($not_connected);
          }

          // Query para seleccionar las ultimas imagenes subidas
          $query = "SELECT idimagen, direccion, nombre";
          $query .= " FROM imagen";
          $query .= " WHERE idusuario = ";
          $query .= $idusuario;
          $query .= " ORDER BY fechaSubida DESC";
          $result = mysqli_query($connection, $query);

          // Query para obtener los datos del usuario
          $query = "SELECT nombre, apellido, email, id";
          $query .= " FROM usuario";
          $query .= " WHERE id = ";
          $query .= $idusuario;
          $result2 = mysqli_query($connection, $query);
          
          $imgs = mysqli_fetch_assoc($result);
          $user_info = mysqli_fetch_assoc($result2);
          $self_profile = ($user_info == NULL) ? FALSE : ($user_info['id'] == $gb_user_id); 
      
    ?>
<div class="jumbotron user-banner"  style="background-image:url('img/banner.png')"></div>
    
    <div class="container">
      <div class="row">
        <div class="col-md-3 text-center">
          <?php if ($user_info == NULL) { ?>
          <div class="alert alert-danger text-left">
            <p>Usuario no encontrado.</p>
          </div>
          <?php } else { ?>
          <img src="http://www.gravatar.com/avatar/<?php echo md5( strtolower( $user_info['email'] ) ); ?>?s=140&d=mm" 
          class="img-circle" height="140" width="140">
          <p class="text-center"><h3> <?php echo $user_info['nombre']; ?> <?php echo $user_info['apellido']; ?></h3></p>
          <?php if ($self_profile) { ?>
          <p><a class="btn btn-default" href="cambio-password.php" role="button">Cambiar contraseña</a></p>
          <p><a class="btn btn-default" href="https://signup.wordpress.com/signup/?ref=oauth2&oauth2_redirect=6ef91cd1594689d84ca83fb307b52795%40https%3A%2F%2Fpublic-api.wordpress.com%2Foauth2%2Fauthorize%2F%3Fclient_id%3D1854%26response_type%3Dcode%26blog_id%3D0%26state%3D3f1c694335dafd57ec483babb6bf006ea7b87901c7732089a908ee94133c4ee6%26redirect_uri%3Dhttps%253A%252F%252Fen.gravatar.com%252Fconnect%252F%253Faction%253Drequest_access_token%26jetpack-code%26jetpack-user-id%3D0%26action%3Doauth2-login&wpcom_connect=1" role="button">Cambiar imagen</a></p>
          <?php } ?>
          <p><small>Avatares cortesia de <a href="https://es.gravatar.com/">Gravatar</a></small></p>
          <?php mysqli_free_result($result2); } ?>
        </div>
        <div class="col-md-9" role="main">
          <!-- Ultimas obras!! -->
          <h2>Obras <?php if($self_profile) { ?><small><a class="btn btn-primary btn-sm" href="archivos.php">Subir una obra</a></small><?php } ?></h2>
          <?php if ($imgs == NULL) {  ?>
          <div class="alert alert-info">
            <p>No se han encontrado obras del artista.</p>
          </div>

          
          <?php } else{ 
            $imgs_total = mysqli_num_rows($result);
            do{ ?>
          <div class="col-md-4">
            <div class="thumbnail">
              <a href="vista-obra.php<?php echo "?idimagen=". $imgs['idimagen']; ?>">
                <img src="img/<?php echo $imgs['direccion']; ?>" height="200" width="300">
              </a>
              <div class="caption">
                <span class="glyphicon glyphicon-picture"></span>
                <span><?php echo $imgs['nombre']; ?></span>
                <?php if ($self_profile!=FALSE) {
                  ?>
                  <div class="btn-group">
                  <button type="button" class="btn btn-default" name="Delbut">Delete</button>
                  </div>  
                  <div class="alert alert-warning fade in" role="alert" aria-hidden="true" hidden="true">
                  <button type="button" class="close" data-dismiss="alert"><span aria-hidden="true">×</span><span class="sr-only">Close</span></button>
                  <strong>Estas seguro</strong> de borrar esta imagen.
                  <p><button type="button" class="btn btn-danger">Borrar</button></p>
                  </div>
                  <?php } ?>
              </div>
            </div>
          </div>
          <?php } while ($imgs = mysqli_fetch_assoc($result));
          mysqli_free_result($result); } ?>
       </div>
      </div>
      <hr>
    </div>
<?php 
include('app/footer.php');

// Close connection with MySQL
mysqli_close($connection);
?>