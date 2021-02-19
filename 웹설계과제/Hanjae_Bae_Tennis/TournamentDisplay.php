<html>
<body>

TournamentDisplay.php<br>

<h2>Matches Year Winner</h2>

<?php

  $mysqli = mysqli_connect("localhost", "root", "", "homework");

  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

  else{
    $sql = "SELECT * FROM tournament";
    $result = mysqli_query($mysqli, $sql);

    if (mysqli_num_rows($result) > 0) {
      // output data of each row
      while($row = mysqli_fetch_assoc($result)) {
        echo "<p>" .$row["Tournament"]."/".$row["Year"]."/".$row["Winner"]."</option>";

      }
    }

    else {
      echo "0 results";
    }


  mysqli_close($mysqli);
}

?>

<br>

<h2>Player DOB</h2>

<?php

  $mysqli = mysqli_connect("localhost", "root", "", "homework");

  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

  else{
    $sql = "SELECT * FROM playerdob";
    $result = mysqli_query($mysqli, $sql);

    if (mysqli_num_rows($result) > 0) {
      // output data of each row
      while($row = mysqli_fetch_assoc($result)) {
        echo "<p>" .$row["Player"]."/".$row["DOB"]."</option>";

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
