<html>
<body>

TournamentDOBJoin.php<br>

<?php

  $mysqli = mysqli_connect("localhost", "root", "", "homework");

  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

  else{
    $sql = "SELECT * FROM tournament inner Join playerdob on tournament.Winner = playerdob.Player";
    $result = mysqli_query($mysqli, $sql);

    if (mysqli_num_rows($result) > 0) {
      // output data of each row
      while($row = mysqli_fetch_assoc($result)) {
        echo "<p>" .$row["Tournament"]."/".$row["Year"]."/".$row["Winner"]."/".$row["DOB"]."</option>";

      }
    }

    else {
      echo "0 results";
    }


  mysqli_close($mysqli);
}

?>

<br>
<a href = "http://localhost:8088/php/tournament/lastprj.html">Home Site</a>
</body>
</html>
