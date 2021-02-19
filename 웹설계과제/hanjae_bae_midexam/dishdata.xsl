<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<html>
  <head>
    <style>
      h1 {
      width: 450px;
      height: 50px;
      fort-weight:bold;
      border: 1px solid blue;
      text-shadow: 3px 3px 1px red;
      }

      #one {
      background-color: cyan;
      width: 150px;
      height: 23px;
      display:block;
      transition : all ease 3s;
      }

      #one:hover{
      background-color:grey;
      color:purple;
      border:2px solid red;
      width: 200px;
      height: 100px;
      transform:rotate(180deg);
      }

      #two {
      background-color: cyan;
      width: 150px;
      height: 23px;
      position: relative;
      transition : all ease 3s;

      }
      #two:hover{
      animation: mymove 3s infinite alternate-reverse;
      background:grey;
      color:purple;
      width: 200px;
      height: 50px;
      }
      @keyframes mymove {
      from {left:50px;}
      to {left:0px;}

      }

      #three {
      background-color: cyan;
      width: 150px;
      height: 23px;
      display:block;

      }
      #three:hover{
      transform:skewY(15deg);
      text-align:center;
      background:green;
      color:red;

      }


      #four {
      background-color: cyan;
      width: 150px;
      height: 23px;
      display:block;
      transition : width 2s, height 2s, transfomr 2s;
      }
      #four:hover{
      width:200px;
      height: 100px;
      background-color: grey;
      color:blue;
      transmition : width 2s, height 2s transform 2s;
      }

      #five {
      background-color: cyan;
      width: 150px;
      height: 23px;
      display:block;
      }
      #five:hover {
      text-shadow: 3px 3px 1px red;
      color: blue;
      background:yellow;
      text-align:center;
      width:180;
      height:35;
      }

      #six {
      background-color: cyan;
      width: 150px;
      height: 23px;
      display:block;

      }
      #six:hover{
      width: 170px;
      height: 30px;
      transform:skewX(15deg);
      text-align:center;
      background:grey;
      color:blue;

      }


      #last{
      color: purple;
      }
      ul{
      background-color: orange;
      width:400;
      height:40;
      }

    </style>
  </head>
  
<body>
  <h1>Specials -- <xsl:value-of select="special-menu/menu-date"/></h1>
  
  <h2 id="one">Appetizer</h2>
  <ul>
  <li id="box">
    <xsl:value-of select="special-menu/special-appetizer"/>
  </li>
  <li>
    Price : <xsl:value-of select="special-menu/special-appetizer/@price"/>
  </li>
  </ul>


  <h2 id="two">Soup</h2>
  <ul>  
  <li id="box">
    <xsl:value-of select="special-menu/special-soup"/>
  </li>
  <li>
    Price : <xsl:value-of select="special-menu/special-soup/@price"/>
  </li>
  </ul>





  <h2 id="three">Fish</h2>
  <ul>
  <li id="box">
    <xsl:value-of select="special-menu/special-fish"/>
  </li>
  <li>
    Price : <xsl:value-of select="special-menu/special-fish/@price"/>
  </li>
</ul>
  
  
  
  
  <h2 id="four">Pasta</h2>
  <ul>
  <li id="box">
    <xsl:value-of select="special-menu/special-pasta"/>
 </li>
  <li>
    Price : <xsl:value-of select="special-menu/special-pasta/@price"/>
  </li>
  </ul>
  

  <h2 id="five">Entree</h2>
  <ul>
    <li id="box">
      <xsl:value-of select="special-menu/special-meat"/>
    </li>
    <li>
      Price : <xsl:value-of select="special-menu/special-meat/@price"/>
    </li>
  </ul>

  <h2 id="six">Dessert</h2>
  <ul>
  <li id="box">
    <xsl:value-of select="special-menu/special-sweet"/>
  </li>
  <li>
    Price : <xsl:value-of select="special-menu/special-sweet/@price"/>
  </li>
  </ul>
  
  
  
  
  
  <br/>
  <br/>

  <p id="last">
    Specials menus are available abery day from opening untill noon.
  </p>
  <p id="last">
    Welcome tour visit!
  </p>

</body>
</html>
</xsl:template>
</xsl:stylesheet>

