<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<html> 
<body>
  <h2>My CD Collection</h2>
<table border="1">
    <tr bgcolor="#9acd32">
      <th style="text-align:left">Artis</th>
      <th style="text-align:left">Title</th>
      <th style="text-align:left">Year</th>
      <th style="text-align:left">Country</th>
      <th style="text-align:left">Price</th>
    </tr>
    <xsl:for-each select="catalog/cd[country='USA']">
    <xsl:sort select = "artist" order = "ascending" />
        <tr>
          <xsl:choose>
            <xsl:when test = "country = 'USA'">
              <td><xsl:value-of select="artist"/></td>
              <xsl:choose>
                <xsl:when test = "price &gt; 10">
                  <td bgcolor = "violet"><xsl:value-of select="title"/></td>
                  </xsl:when>
                <xsl:when test = "price &gt; 9">
                  <td bgcolor = "yellow"><xsl:value-of select="title"/></td>
                  </xsl:when>
                <xsl:otherwise>
                  <td><xsl:value-of select="title"/></td>
                </xsl:otherwise>
              </xsl:choose>
              <td><xsl:value-of select="year"/></td>
              <td><xsl:value-of select="country"/></td>
              <td><xsl:value-of select="price"/></td>
            </xsl:when>
          </xsl:choose>
        </tr>
      </xsl:for-each>
  </table>

</body>
</html>
</xsl:template>
</xsl:stylesheet>

