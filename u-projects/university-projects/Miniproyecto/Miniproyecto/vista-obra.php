<?php //session_start(); 
?>
<?php include('app/header.php'); ?>
  <body>
    <?php include('app/nav.php') ?>
    <div class="container">
      <!-- Example row of columns -->
      <div class="row">
        <div class="col-md-12">
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
          // Query para seleccionar la imagen subidas
          $query = "SELECT b.nombre as unombre, apellido, idusuario, idimagen, direccion, a.nombre as inombre, descripcion, anoCreacion, fechaSubida, estilo, likes";
          $query .= " FROM imagen a INNER JOIN usuario b ON a.idusuario = b.id";
          $query .= " WHERE idimagen=%d";
          $query = sprintf($query, $_GET['idimagen']);
          $result = mysqli_query($connection, $query);
           ?>
              <?php if ($result == NULL){ ?>
          <div class="row">
            <img class="center-block" src="http://placehold.it/900x600">
          </div>
                <div class="alert alert-warning" role="alert">Imagen no encontrada!</div>
              <?php } else {
                $imagen = mysqli_fetch_assoc($result);
                ?>
          <div class="row">
            <img class="center-block" src="img/<?php echo $imagen['direccion']; ?>" style="max-width: 100%">
          </div>
          <div class="row main-desc">
            <div class="col-md-9">
              <div class="pane panel-default">
                <div class="panel-heading">
                  <h2><?php echo $imagen['inombre']; ?> <small>por <a href="perfil.php<?php echo "?idusuario=".$imagen['idusuario']; ?>"><?php echo $imagen['unombre']." "
                  .$imagen['apellido']; ?></a>.</small></h2>
                </div>
                <div class="panel-body">
                  <p><span class="glyphicon glyphicon-calendar"></span> Publicado el <?php echo $imagen['fechaSubida']; ?></p>
                  <p><span class="glyphicon glyphicon-picture"></span> Año de craeción: <?php echo $imagen['anoCreacion']; ?></p>
                  <p><span class="glyphicon glyphicon-pencil"></span> Estilo: <?php echo $imagen['estilo']; ?></p>
                  <p><span class="glyphicon glyphicon-book"></span> Desripción: <?php echo $imagen['descripcion']; ?></p>
                </div>
              </div>
            </div>
            <div class="col-md-3">
              <div class="contador-likes">
                <p class="lead"><?php echo $imagen['likes']; ?> likes</p>
                <form action="app/like-handler.php" method="post" role="form">
                  <input type="hidden" name="imagen" value="<?php echo $imagen['idimagen']; ?>">
                  <button type="submit" name="like" class="btn btn-default"><span class="glyphicon glyphicon-thumbs-up"></span> Me gusta</button>
                </form>
              </div>
              <?php if($_GET['liked'] == 1) { ?>
              <div class="alert alert-success" role="alert">Like agregado</div>
              <?php } elseif($_GET['liked'] == 2 ) { ?>
              <div class="alert alert-warning" role="alert">Ya has dado like</div>
              <?php } ?>
            </div>
              <?php mysqli_free_result($result);} ?>
          </div>
        </div>
      </div>
      <hr>
    </div>
<?php include('app/footer.php'); 
mysqli_close($connection);
?>