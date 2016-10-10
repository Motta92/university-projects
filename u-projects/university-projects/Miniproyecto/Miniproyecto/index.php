<?php 
$title = "Inicio";
?>
<?php include('app/header.php') ?>
  <body>
  <?php include('app/nav.php') ?>
    <div class="jumbotron" style="background-image:url('img/index_banner.jpg')">
      <div class="container" style="background-color: rgba(0, 0, 0, 0.4);">
        <h1><font color="white">¡Bienvenido a ArtPoof!</h1>
        <p>¡Aquí podras encontrar los elementos que necesitas para subir y compartir tu arte con el mundo en un Poof! ^'.w.'^</p></font>
      </div>
    </div>

    <div class="container">
      <div class="row">
        <div class="col-md-3">
          <h2>ArtPoof</h2>
          <p>ArtPoof te permite ver obras de arte con solo un Poof, sube tus obras y compartelas con el mundo </p>
          <p><a class="btn btn-primary" href="artistas.php" role="button">Ver artistas &raquo;</a></p>
        </div>
        <div class="col-md-9" role="main">

          <!-- Ultimas obras!! -->
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
          $query = "SELECT idimagen, direccion, nombre";
          $query .= " FROM imagen";
          $query .= " ORDER BY fechaSubida DESC";
          $result = mysqli_query($connection, $query);
          $imgs_total = mysqli_num_rows($result);
          $imgs = mysqli_fetch_assoc($result);

          ?>

          <h2>Obras</h2>
          <?php if ($imgs == NULL) {  ?>
          <div class="alert alert-info">
            <p>No hay resultados.</p>
          </div>
          <?php } else { do { ?>

          <div class="col-md-4">
            <div class="thumbnail" style="height: 250px">
              <a href="vista-obra.php?idimagen=<?php echo $imgs['idimagen'] ?>">
                <!-- http://placehold.it/300x200 -->
                <?php 
                
                if($current_index_pag%$maxRows_img== $actual_img){
                //$current_index_pag = $current_index_pag + 1;
                ?>
                <img src="img/<?php echo $imgs['direccion']; ?>" style="width: 100%;height: 85%">
                <?php
                }
                else{
                  ?>
                  <div class="alert alert-info">
                  <p>No hay resultados.</p>
                  </div>
                  continue;
                  <?php
                }
                ?>
              </a>
              <div class="caption">
                <span class="glyphicon glyphicon-picture"></span>
                <span><?php echo $imgs['nombre']; ?></span>
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
