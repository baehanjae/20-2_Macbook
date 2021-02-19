<html>
<body>

RegisterEvent.php<br>

<h1>TournamentWinnerTable.php</h1><br>

Name: <?php echo $_POST["name"]; ?><br>
City : <?php echo $_POST["city"] ;?><br>
DOB : <?php echo $_POST["dob"] ;?><br>

<?php
echo "database insertion <br> ";
$mysqli = mysqli_connect("localhost", "root", "", "homework");

if (mysqli_connect_errno()) {
	printf("Connect failed: %s\n", mysqli_connect_error());
	exit();
} else {
	$sql = "INSERT INTO registermatch (Name, City, DOB) VALUES ('".$_POST["name"]."','".$_POST["city"]."','".$_POST["dob"]."' )";
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
