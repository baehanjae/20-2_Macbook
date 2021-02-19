<html>
<body>
<header style="border : 1px solid blue"> <h1>Tournament Winner</h1> </header>
<section>
  <div style="float:left; border: 1px solid blue">
    <h3>Table for Tournament Winner</h3>
    <form action="TournamentWinnerTable.php" method="post" style="border : 1px solid blue">
      Tournament : <input type="text" name="tournament"><br>
      Year : <input type="text" name="year"><br>
      Winner : <input type="text" name="winner"><br>
      <input type="submit"><br>
    </form>
  </div>
  <div style="float:left; border : 1px solid blue">
    <h3>Tennis Tournament</h2>
    <form action="PlayerDOB.php" method="post" style="border : 1px solid blue">
      Player : <input type="text" name="player"><br>
      Date of Birth : <input type="text" name="dob"><br>
      <input type="submit"><br>
    </form>
  </div>
</section>
<br>
<p style="clear:both">
  <a href = "http://localhost:8088/php/tournament/lastprj.html">Home Site</a>
</p>
<footer style="clear:left; border : 1px solid blue">TennisTournament.php<br></footer>
<!-- Your email address is: <?php  echo "by" ?> -->


</body>
</html>
