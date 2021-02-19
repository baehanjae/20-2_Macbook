<html>
<body>

<h1>TournamentWinnerTable.php</h1><br>

Tournament: <?php echo $_POST["tournament"]; ?><br>
Year : <?php echo $_POST["year"] ;?><br>
Winner : <?php echo $_POST["winner"] ;?><br>


<?php
echo "database insertion <br> ";
$mysqli = mysqli_connect("localhost", "root", "", "homework");

if (mysqli_connect_errno()) {
	printf("Connect failed: %s\n", mysqli_connect_error());
	exit();
} else {
	$sql = "INSERT INTO tournament (Tournament, Year, Winner) VALUES ('".$_POST["tournament"]."','".$_POST["year"]."','".$_POST["winner"]."' )";
	$res = mysqli_query($mysqli, $sql);

	if ($res === TRUE) {
	   	echo "A record for tournament winner has been inserted.";
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
