<?php 
$title = "Artistas";
include('app/header.php');
?>
  <body>
  <?php include('app/nav.php') ?>
    <div class="container">
      <div class="row">
        <div class="col-md-12" role="main">

          <!-- Artistas!! -->
          <?php 
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
          $query = "SELECT nombre, apellido, id, email";
          $query .= " FROM usuario";
          $query .= " ORDER BY nombre DESC";
          $result = mysqli_query($connection, $query);
          $artist = mysqli_fetch_assoc($result);

          ?>

          <h2>Artistas</h2>
          <?php if ($artist == NULL) {  ?>
          <div class="col-md-12">
            <div class="alert alert-warning">
              <p>No hay resultados.</p>
            </div>
          </div>
          <?php } else { do { ?>
          <div class="col-md-3 col-xs-6">
            <div class="thumbnail">
              <a href="perfil.php?idusuario=<?php echo $artist['id'] ?>">
                <!-- http://placehold.it/300x200 -->
                <img src="http://www.gravatar.com/avatar/<?php echo md5( strtolower( $artist['email'] ) ); ?>?s=140&d=mm" class="img-circle" height="140" width="140">
              </a>
              <div class="caption text-center">
                <span class="glyphicon glyphicon-user"></span>
                <span><?php echo $artist['nombre']; ?> <?php echo $artist['apellido']; ?></span>
              </div>
            </div>
          </div>
          <?php } while ($artist = mysqli_fetch_assoc($result));
          mysqli_free_result($result); 
          } ?>
       </div>
      </div>
      <hr>
    </div>
<?php 
include('app/footer.php');

// Close connection with MySQL
mysqli_close($connection);
?>
