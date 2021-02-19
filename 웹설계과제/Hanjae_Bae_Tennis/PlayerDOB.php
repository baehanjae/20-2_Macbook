<html>
<body>

PlayerDOB.php<br>


Player : <?php echo $_POST["player"]; ?><br>
Date of Birth : <?php echo $_POST["dob"] ;?><br>


<?php
echo "database insertion <br> ";
$mysqli = mysqli_connect("localhost", "root", "", "homework");

if (mysqli_connect_errno()) {
	printf("Connect failed: %s\n", mysqli_connect_error());
	exit();
} else {
	$sql = "INSERT INTO playerdob (Player, DOB) VALUES ('".$_POST["player"]."','".$_POST["dob"]."' )";
	$res = mysqli_query($mysqli, $sql);

	if ($res === TRUE) {
	   	echo "A record for player and DOB has been inserted.";
	} else {
		printf("Could not insert record: %s\n", mysqli_error($mysqli));
	}

	mysqli_close($mysqli);
}
?>

<br>
<a href = "http://localhost:8088/php/tournament/lastprj.html">Home Site</a>

</body>
</html>
