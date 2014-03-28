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
$query_getSpatialFrequency = "SELECT bhawan, COUNT(*) AS cc FROM complain_info GROUP BY bhawan ORDER BY cc DESC";
$getSpatialFrequency = mysql_query($query_getSpatialFrequency, $ec451_conn) or die(mysql_error());
$row_getSpatialFrequency = mysql_fetch_assoc($getSpatialFrequency);
$totalRows_getSpatialFrequency = mysql_num_rows($getSpatialFrequency);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>Spatial Frequency </h1>
<p>&nbsp;</p>
<p><a href="index.php">Main Menu</a></p>
<p><a href="admin.php">Admin Menu</a></p>
<p>&nbsp;</p>
<table width="500" border="1">
  <tr>
    <th scope="col">Bhawan</th>
    <th scope="col">Frequency</th>
  </tr>
  <?php do { ?>
    <tr>
      <td><?php echo $row_getSpatialFrequency['bhawan']; ?></td>
      <td><?php echo $row_getSpatialFrequency['cc']; ?></td>
    </tr>
    <?php } while ($row_getSpatialFrequency = mysql_fetch_assoc($getSpatialFrequency)); ?>
</table>
<p>&nbsp;</p>
</body>
</html>
<?php
mysql_free_result($getSpatialFrequency);
?>
