<?php require_once('Connections/ec451_conn.php'); ?>
<?php
if (!function_exists("GetSQLValueString")) {
function GetSQLValueString($theValue, $theType, $theDefinedValue = "", $theNotDefinedValue = "") 
{
  if (PHP_VERSION < 6) {
    $theValue = get_magic_quotes_gpc() ? stripslashes($theValue) : $theValue;
  }

  $theValue = function_exists("mysql_real_escape_string") ? mysql_real_escape_string($theValue) : mysql_escape_string($theValue);

  switch ($theType) {
    case "text":
      $theValue = ($theValue != "") ? "'" . $theValue . "'" : "NULL";
      break;    
    case "long":
    case "int":
      $theValue = ($theValue != "") ? intval($theValue) : "NULL";
      break;
    case "double":
      $theValue = ($theValue != "") ? doubleval($theValue) : "NULL";
      break;
    case "date":
      $theValue = ($theValue != "") ? "'" . $theValue . "'" : "NULL";
      break;
    case "defined":
      $theValue = ($theValue != "") ? $theDefinedValue : $theNotDefinedValue;
      break;
  }
  return $theValue;
}
}

mysql_select_db($database_ec451_conn, $ec451_conn);
$query_getComplainFrequency = "SELECT complainType AS Complain, COUNT(*) AS Frequency FROM complain_info GROUP BY complainType ORDER BY Frequency DESC;";
$getComplainFrequency = mysql_query($query_getComplainFrequency, $ec451_conn) or die(mysql_error());
$row_getComplainFrequency = mysql_fetch_assoc($getComplainFrequency);
$totalRows_getComplainFrequency = mysql_num_rows($getComplainFrequency);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>Complain Frequency</h1>
<p>&nbsp;</p>
<p><a href="index.php">Main Menu</a></p>
<p><a href="admin.php">Admin Menu</a></p>
<p>&nbsp;</p>
<table width="500" border="1">
  <tr>
    <th scope="col">Complain Type</th>
    <th scope="col">Frequency</th>
  </tr>
  <?php do { ?>
    <tr>
      <td><?php echo $row_getComplainFrequency['Complain']; ?></td>
      <td><?php echo $row_getComplainFrequency['Frequency']; ?></td>
    </tr>
    <?php } while ($row_getComplainFrequency = mysql_fetch_assoc($getComplainFrequency)); ?>
</table>
<p>&nbsp;</p>
<p>&nbsp;</p>
</body>
</html>
<?php
mysql_free_result($getComplainFrequency);
?>
