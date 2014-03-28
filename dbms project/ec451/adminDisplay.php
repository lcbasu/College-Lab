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

$currentPage = $_SERVER["PHP_SELF"];

$maxRows_getComplainValueAdmin = 10;
$pageNum_getComplainValueAdmin = 0;
if (isset($_GET['pageNum_getComplainValueAdmin'])) {
  $pageNum_getComplainValueAdmin = $_GET['pageNum_getComplainValueAdmin'];
}
$startRow_getComplainValueAdmin = $pageNum_getComplainValueAdmin * $maxRows_getComplainValueAdmin;

mysql_select_db($database_ec451_conn, $ec451_conn);


if (isset($_GET['complainStatus']) && $_GET['complainStatus'] != 'Choose' && $_GET['complainStatus'] != '' ) {
  $colname_Recordset1 = $_GET['complainStatus'];
	$query_getComplainValueAdmin = sprintf("SELECT * FROM complain_info WHERE complainStatus = %s", GetSQLValueString($colname_Recordset1, "text"));  
}



if (isset($_GET['complainType']) && $_GET['complainType'] != 'Choose' && $_GET['complainType'] != '' ) {
  $colname_Recordset1 = $_GET['complainType'];
	$query_getComplainValueAdmin = sprintf("SELECT * FROM complain_info WHERE complainType = %s", GetSQLValueString($colname_Recordset1, "text"));  
}

if (isset($_GET['bhawan']) && $_GET['bhawan'] != 'Choose' && $_GET['bhawan'] != '' ) {
  $colname_Recordset1 = $_GET['bhawan'];
	$query_getComplainValueAdmin = sprintf("SELECT * FROM complain_info WHERE bhawan = %s", GetSQLValueString($colname_Recordset1, "text"));  
}



if (isset($_GET['personType']) && $_GET['personType'] != 'Choose' && $_GET['personType'] != '' ) {
  $colname_Recordset1 = $_GET['personType'];
	$query_getComplainValueAdmin = sprintf("SELECT * FROM complain_info WHERE personType = %s", GetSQLValueString($colname_Recordset1, "text"));  
}


if (isset($_GET['personID']) && $_GET['personID'] != '') {
  $colname_Recordset1 = $_GET['personID'];
	$query_getComplainValueAdmin = sprintf("SELECT * FROM complain_info WHERE personID = %s", GetSQLValueString($colname_Recordset1, "int"));  
}

if (isset($_GET['complainNo']) && $_GET['complainNo'] != '') {
  $colname_Recordset1 = $_GET['complainNo'];
$query_getComplainValueAdmin = sprintf("SELECT * FROM complain_info WHERE complainNo = %s", GetSQLValueString($colname_Recordset1, "int"));  
}

if(isset($_GET['query']))
{
	if($_GET['query'] == 1)
		$query_getComplainValueAdmin = "SELECT * FROM complain_info ORDER BY complainTime ASC";
	
	if($_GET['query'] == 2)
		$query_getComplainValueAdmin = "SELECT * FROM complain_info M, resolved R WHERE M.complainNo = R.complainNo AND (TIMESTAMPDIFF(HOUR, M.complainTime, R.resolveTime) < 24) ORDER BY R.resolveTime DESC";	

		
	
}

//$query_getComplainValueAdmin = "SELECT * FROM complain_info ORDER BY complainTime ASC";
$query_limit_getComplainValueAdmin = sprintf("%s LIMIT %d, %d", $query_getComplainValueAdmin, $startRow_getComplainValueAdmin, $maxRows_getComplainValueAdmin);
$getComplainValueAdmin = mysql_query($query_limit_getComplainValueAdmin, $ec451_conn) or die(mysql_error());
$row_getComplainValueAdmin = mysql_fetch_assoc($getComplainValueAdmin);

if (isset($_GET['totalRows_getComplainValueAdmin'])) {
  $totalRows_getComplainValueAdmin = $_GET['totalRows_getComplainValueAdmin'];
} else {
  $all_getComplainValueAdmin = mysql_query($query_getComplainValueAdmin);
  $totalRows_getComplainValueAdmin = mysql_num_rows($all_getComplainValueAdmin);
}
$totalPages_getComplainValueAdmin = ceil($totalRows_getComplainValueAdmin/$maxRows_getComplainValueAdmin)-1;

$queryString_getComplainValueAdmin = "";
if (!empty($_SERVER['QUERY_STRING'])) {
  $params = explode("&", $_SERVER['QUERY_STRING']);
  $newParams = array();
  foreach ($params as $param) {
    if (stristr($param, "pageNum_getComplainValueAdmin") == false && 
        stristr($param, "totalRows_getComplainValueAdmin") == false) {
      array_push($newParams, $param);
    }
  }
  if (count($newParams) != 0) {
    $queryString_getComplainValueAdmin = "&" . htmlentities(implode("&", $newParams));
  }
}
$queryString_getComplainValueAdmin = sprintf("&totalRows_getComplainValueAdmin=%d%s", $totalRows_getComplainValueAdmin, $queryString_getComplainValueAdmin);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
 <h1>Filtered Result </h1>
 <p>&nbsp;</p>
 <p><a href="admin.php">Back</a></p>
 <p><a href="index.php">Main Menu</a></p>
<p>&nbsp;</p>
<table width="1200" border="1">
  <tr>
    <th scope="col">C No.</th>
    <th scope="col">Name</th>
    <th scope="col">Person ID</th>
    <th scope="col">Designation</th>
    <th scope="col">Bhawan</th>
    <th scope="col">Room No</th>
    <th scope="col">Phone</th>
    <th scope="col">E-Mail</th>
    <th scope="col">Avail. Form</th>
    <th scope="col">Avail. Till</th>
    <th scope="col">Type</th>    
    <th scope="col">Description</th>
    <th scope="col">Time</th>
    <th scope="col">Status</th>
  </tr>
  <?php do { ?>
    <tr>
      <td><?php echo $row_getComplainValueAdmin['complainNo']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['personName']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['personID']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['personType']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['bhawan']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['roomNo']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['phoneNo']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['email']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['availFrom']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['availTill']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['complainType']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['complainDescr']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['complainTime']; ?></td>
      <td><?php echo $row_getComplainValueAdmin['complainStatus']; ?></td>
    </tr>
    <?php } while ($row_getComplainValueAdmin = mysql_fetch_assoc($getComplainValueAdmin)); ?>
</table>
<table border="0">
  <tr>
    <td><?php if ($pageNum_getComplainValueAdmin > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getComplainValueAdmin=%d%s", $currentPage, 0, $queryString_getComplainValueAdmin); ?>"><img src="First.gif" /></a>
        <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getComplainValueAdmin > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getComplainValueAdmin=%d%s", $currentPage, max(0, $pageNum_getComplainValueAdmin - 1), $queryString_getComplainValueAdmin); ?>"><img src="Previous.gif" /></a>
        <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getComplainValueAdmin < $totalPages_getComplainValueAdmin) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getComplainValueAdmin=%d%s", $currentPage, min($totalPages_getComplainValueAdmin, $pageNum_getComplainValueAdmin + 1), $queryString_getComplainValueAdmin); ?>"><img src="Next.gif" /></a>
        <?php } // Show if not last page ?></td>
    <td><?php if ($pageNum_getComplainValueAdmin < $totalPages_getComplainValueAdmin) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getComplainValueAdmin=%d%s", $currentPage, $totalPages_getComplainValueAdmin, $queryString_getComplainValueAdmin); ?>"><img src="Last.gif" /></a>
        <?php } // Show if not last page ?></td>
  </tr>
</table>
<p>&nbsp;</p>
</body>
</html>
<?php
mysql_free_result($getComplainValueAdmin);
?>
