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

	if($_GET['complainType'] == 'Water')
	{
		$updateSQL1 = sprintf("UPDATE complain_info SET complainStatus='RESOLVED' WHERE complainNo=%s",
                       GetSQLValueString($_GET['complainNo'], "int"));
					   
		$updateSQL2 = sprintf("INSERT into resolved (complainNo) VALUES(%s)",
                       GetSQLValueString($_GET['complainNo'], "int"));					   

	mysql_select_db($database_ec451_conn, $ec451_conn);
$Result1 = mysql_query($updateSQL1, $ec451_conn) or die(mysql_error());
$Result2 = mysql_query($updateSQL2, $ec451_conn) or die(mysql_error());
		header('Location:water.php');	
	}
	else if($_GET['complainType'] == 'Electrical')
	{
		$updateSQL1 = sprintf("UPDATE complain_info SET complainStatus='RESOLVED' WHERE complainNo=%s",
                       GetSQLValueString($_GET['complainNo'], "int"));
					   
		$updateSQL2 = sprintf("INSERT into resolved (complainNo) VALUES(%s)",
                       GetSQLValueString($_GET['complainNo'], "int"));					   

		mysql_select_db($database_ec451_conn, $ec451_conn);
		$Result1 = mysql_query($updateSQL1, $ec451_conn) or die(mysql_error());	
		$Result2 = mysql_query($updateSQL2, $ec451_conn) or die(mysql_error());		
		header('Location:electrical.php');
	}
	else if($_GET['complainType'] == 'Civil')
	{
		$updateSQL1 = sprintf("UPDATE complain_info SET complainStatus='RESOLVED' WHERE complainNo=%s",
                       GetSQLValueString($_GET['complainNo'], "int"));

		$updateSQL2 = sprintf("INSERT into resolved (complainNo) VALUES(%s)",
                       GetSQLValueString($_GET['complainNo'], "int"));						   

		mysql_select_db($database_ec451_conn, $ec451_conn);
		$Result1 = mysql_query($updateSQL1, $ec451_conn) or die(mysql_error());	
		$Result2 = mysql_query($updateSQL2, $ec451_conn) or die(mysql_error());
		
		header('Location:civil.php');				
	}
?>



<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
</head>

<body>
</body>
</html>