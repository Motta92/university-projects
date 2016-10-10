<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <title>Certificates</title>
    <!-- Bootstrap -->
    <link href="../bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/myCSS.css" rel="stylesheet">
  </head>
  <body>
  
    <div class="container" id="logo"> 
      <figure id="icta2015_logo">
        <a href="http://www.ictac2015.co/">
          <img src="images/ICTAC2015_Logo.png"/>
        </a>
      </figure> 
    </div>

    <div class="container">
      <nav class="navbar navbar-default">
        <div class="container-fluid">
          <!-- Brand and toggle get grouped for better mobile display -->
          <div class="navbar-header">
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
              <span class="sr-only">Toggle navigation</span>
              <span class="icon-bar"></span>
              <span class="icon-bar"></span>
              <span class="icon-bar"></span>
            </button>
            <!-- <a class="navbar-brand" href="ictac2015/index.html"> </a> -->
          </div>

          <!-- Collect the nav links, forms, and other content for toggling -->
          <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
            <ul class="nav navbar-nav">
              <li><a href="http://www.ictac2015.co/">Home<span class="sr-only">(current)</span></a></li>
              <li><a href="#">Call for Papers</a></li>
              <li><a href="#">Invited Speakers</a></li>
              <li><a href="#">Committees</a></li>
              <li class="dropdown">
                <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false">Events <span class="caret"></span></a>
                <ul class="dropdown-menu" role="menu">
                  <li><a href="#">Summer School</a></li>
                  <li><a href="#">Workshops</a></li>
                </ul>
              </li>
              <li class="active"><a href="">Certificates</a></li>
              <li><a href="#">News</a></li>
            </ul>
          </div><!-- /.navbar-collapse -->
        </div><!-- /.container-fluid -->
      </nav>
    </div>

    <div id="title_wrapper">
      <div class="container">
        <h3>Certificates</h3>
      </div>
    </div>

    <div class="container" id="mainText">
      <p>Please introduce a document and select the type of document on the fields below.</p>
      <p>Select the type of document</p>

      <form role="form" method="post" action="poofPDF.php">
        <div class="form-group">
          <label for="usr">ID number:</label>
          <input type="text" class="form-control" id="user" name="id_man">
        </div>

        <div class="form-group">
          <select name="ActualSelection" class="form-control">
            <option>Conference</option>
            <option>Workshop</option>
            <option>Summer School</option>
          </select>
        </div>

        <div <div class="submit form-group"><input type="submit" class="btn btn-primary btn-lg active" name="contact-submit" id="contact-submit" value="GO" /></div>
        <!-- <button type="button" class="btn btn-primary btn-lg active">Go</button> -->
      </form>
    </div>
    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="../bootstrap/js/bootstrap.min.js"></script>
  </body>
</html>