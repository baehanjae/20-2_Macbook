<html>
<body>

RegistrationDisplay.php<br>

<h2>Upconming Tennis Tournament</h2>

<h3>Name    City    DOB</h3>

<?php

  $mysqli = mysqli_connect("localhost", "root", "", "homework");

  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

  else{
    $sql = "SELECT * FROM registermatch";
    $result = mysqli_query($mysqli, $sql);

    if (mysqli_num_rows($result) > 0) {
      // output data of each row
      while($row = mysqli_fetch_assoc($result)) {
        echo "<p>" .$row["Name"]."/".$row["City"]."/".$row["DOB"]."</option>";

      }
    }

    else {
      echo "0 results";
    }


  mysqli_close($mysqli);
}

?>

<br>
<br>
<a href = "http://localhost:8088/php/tournament/lastprj.html">Home Site</a>

</body>
</html>
