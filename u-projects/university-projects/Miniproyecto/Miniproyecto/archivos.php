<?php include 'app/header.php'; ?>
<body class="login">
<?php include 'app/nav.php'; ?>
<div class="container">
  <form class="form-horizontal" role="form" action="app/uploader.php" method="post" enctype="multipart/form-data">
<?php 
  if (is_null($gb_user_id)) {
  ?>
 <div class="alert alert-danger text-left">
  <p>No se encuentra logeado, no puede subir imagenes.</p>
  </div>
<?php
  }
  else
  {
  ?>
    <div class="form-group">
      <label for="nombreObra" class="col-sm-2 control-label">Nombre</label>
      <div class="col-sm-10">
        <input type="text" class="form-control" id="nombreObra" name="name" placeholder="Nombre de la obra" required autofocus>
      </div>
    </div>
    <div class="form-group">
      <label for="descrip" class="col-sm-2 control-label">Descripción</label>
      <div class="col-sm-10">
        <input type="text" class="form-control" id="descrip" name="desc" placeholder="Descripción de la obra" required>
      </div>
    </div>
    <div class="form-group">
      <label for="acrea" class="col-sm-2 control-label">Año de creación</label>
      <div class="col-sm-10">
        <input type="text" class="form-control" id="acrea" name="yearc" placeholder="Año de creación de la obra" required>
      </div>
    </div>
    <div class="form-group">
      <label for="estilo" class="col-sm-2 control-label">Estilo</label>
      <div class="col-sm-10">
        <input type="text" class="form-control" id="estilo" name="style" placeholder="Estilo de la obra" required>
      </div>
    </div>
    <div class="form-group">
      <label for="file" class="col-sm-2 control-label">Cargar imagen</label>
      <input type="file" id="file" name="file" required>
      <p class="help-block col-sm-offset-2">La imagen no puede ser superior a 8Mb, los formatos aceptados son gif,jpg,jpeg,png.</p>
    </div>
    <div class="form-group">
      <div class="col-sm-offset-2 col-sm-10">
        <button type="submit" class="btn btn-default"  name="Subir">Subir imagen</button>
      </div>
    </div>
    <?php } ?>
  </form>
</div>

<?php include 'app/footer.php'; ?>