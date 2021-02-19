<html>
<body>



<header style="border : 1px solid blue"> <h1>cancleTwoRecords.php</h1> </header>
<section>
  <div style="float:left; border: 1px solid blue; margin-right:100px;">
    <h3>Delete Tournament</h3>
    <?php

    if(@$_POST["db"]){
      #echo $_POST["db"];
      echo "<br>";
      $parsed = explode("/",$_POST["db"]);
      #echo $parsed[2];

     $mysqli = mysqli_connect("localhost", "root", "", "homework");

      if (mysqli_connect_errno()) {
      	printf("Connect failed: %s\n", mysqli_connect_error());
      	exit();
      } else {
        if(0 ==strcmp($parsed[0],"volvo")) {}
          else{
          	$sql = "DELETE FROM tournament WHERE Winner = '$parsed[2]' && Tournament = '$parsed[0]' && Year = '$parsed[1]'";
          	$res = mysqli_query($mysqli, $sql);

          	if ($res === TRUE) {
          	   	#echo "A record for player and DOB has been deleted.";
          	} else {
          		printf("Could not delete record: %s\n", mysqli_error($mysqli));
              echo "fail!!";
          	}

          	mysqli_close($mysqli);
          }
      }

      echo "<a href='http://localhost:8088/php/tournament/cancelTwoRecords.php'> Would you like to delete another? </a>";
      echo "<h2> Record(s) Deleted </h2>";
    }
    else{
      $mysqli = mysqli_connect("localhost", "root", "", "homework");
      if (mysqli_connect_errno()) {
      	printf("Connect failed: %s\n", mysqli_connect_error());
      	exit();
      } else{

      $sql = "SELECT * FROM tournament";
      $result = mysqli_query($mysqli, $sql);

      if (mysqli_num_rows($result) > 0) {
        // output data of each row
        echo "<form action='cancelTwoRecords.php' method='post'>";
        echo "<select name='db' id='touranment'>";
        echo "<option value='volvo'>--Select One--</option>";
        while($row = mysqli_fetch_assoc($result)) {
          echo "<option>" .$row["Tournament"]."/".$row["Year"]."/".$row["Winner"]. "</option>";

        }
        echo "</select>";
        echo "<br>";
        echo "<input type='submit' value='submit'>";
        echo "</form>";
      } else {
        echo "<form action='cancelTwoRecords.php' method='post'>";
        echo "<select name='db' id='touranment'>";
        echo "<option value='volvo'>--Select One--</option>";
        echo "</select>";
        echo "<br>";
        echo "<input type='submit' value='submit'>";
        echo "</form>";
      }
      }

      mysqli_close($mysqli);
    }

    ?>
    <h3>Delete Player DOB</h3>
    <?php

    if(@$_POST["db"]){
      #echo $_POST["db"];
      echo "<br>";
      $parsed = explode("/",$_POST["db"]);
      #echo $parsed[2];

     $mysqli = mysqli_connect("localhost", "root", "", "homework");

      if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
      } else {
        $sql = "DELETE FROM playerdob WHERE player = '$parsed[0]'";
        $res = mysqli_query($mysqli, $sql);

        if ($res === TRUE) {
            #echo "A record for player and DOB has been deleted.";
        } else {
          printf("Could not delete record: %s\n", mysqli_error($mysqli));
        }

        mysqli_close($mysqli);
      }

      echo "<a href='http://localhost:8088/php/tournament/cancelTwoRecords.php'> Would you like to delete another? </a>";
      echo "<h2> Record(s) Deleted </h2>";
    }
    else{
      $mysqli = mysqli_connect("localhost", "root", "", "homework");
      if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
      } else{

      $sql = "SELECT * FROM playerdob";
      $result = mysqli_query($mysqli, $sql);

      if (mysqli_num_rows($result) > 0) {
        // output data of each row
        echo "<form action='cancelTwoRecords.php' method='post'>";
        echo "<select name='db' id='touranment'>";
        echo "<option value='volvo'>--Select One--</option>";
        while($row = mysqli_fetch_assoc($result)) {
          echo "<option>" .$row["Player"]."/".$row["DOB"]."</option>";

        }
        echo "</select>";
        echo "<br>";
        echo "<input type='submit' value='submit'>";
        echo "</form>";
      } else {
        echo "<form action='cancelTwoRecords.php' method='post'>";
        echo "<select name='db' id='touranment'>";
        echo "<option value='volvo'>--Select One--</option>";
        echo "</select>";
        echo "<br>";
        echo "<input type='submit' value='submit'>";
        echo "</form>";
      }
      }

      mysqli_close($mysqli);
    }

    ?>


  </div>
  <div style="float:left;">
    <h3 style="color:red;">Pohang Tennis Tournament</h2>
    <h4>Senior Tennis Match</h4>
    <p>Senior tennis match is held twice per year for people over 70 years old.</p>
    <br>
    <h4>Handong Tennis Tournament</h4>
    <p style="width:600px;">With the Handong Tennis Tournament, all the freshmen from Kyungbuk area universitise are invited. </p>
    <div style="background-color:cyan; width:300px; margin-left:150px;">Apply Junior Tennis Match<br>January 15 2021</div>
  </div>
</section>
<br>
<p style="clear:both">
  <a href = "http://localhost:8088/php/tournament/lastprj.html">Home Site</a>
</p>

<footer style="clear:left; border : 1px solid blue">TennisTournament.php<br></footer>



</body>
</html>
