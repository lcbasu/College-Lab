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

$maxRows_getWaterProblem = 10;
$pageNum_getWaterProblem = 0;
if (isset($_GET['pageNum_getWaterProblem'])) {
  $pageNum_getWaterProblem = $_GET['pageNum_getWaterProblem'];
}
$startRow_getWaterProblem = $pageNum_getWaterProblem * $maxRows_getWaterProblem;

mysql_select_db($database_ec451_conn, $ec451_conn);
$query_getWaterProblem = "SELECT * FROM complain_info WHERE complain_info.complainType = 'Water' AND complain_info.complainStatus = 'PENDING' ORDER BY complainTime ASC";
$query_limit_getWaterProblem = sprintf("%s LIMIT %d, %d", $query_getWaterProblem, $startRow_getWaterProblem, $maxRows_getWaterProblem);
$getWaterProblem = mysql_query($query_limit_getWaterProblem, $ec451_conn) or die(mysql_error());
$row_getWaterProblem = mysql_fetch_assoc($getWaterProblem);

if (isset($_GET['totalRows_getWaterProblem'])) {
  $totalRows_getWaterProblem = $_GET['totalRows_getWaterProblem'];
} else {
  $all_getWaterProblem = mysql_query($query_getWaterProblem);
  $totalRows_getWaterProblem = mysql_num_rows($all_getWaterProblem);
}
$totalPages_getWaterProblem = ceil($totalRows_getWaterProblem/$maxRows_getWaterProblem)-1;

$queryString_getWaterProblem = "";
if (!empty($_SERVER['QUERY_STRING'])) {
  $params = explode("&", $_SERVER['QUERY_STRING']);
  $newParams = array();
  foreach ($params as $param) {
    if (stristr($param, "pageNum_getWaterProblem") == false && 
        stristr($param, "totalRows_getWaterProblem") == false) {
      array_push($newParams, $param);
    }
  }
  if (count($newParams) != 0) {
    $queryString_getWaterProblem = "&" . htmlentities(implode("&", $newParams));
  }
}
$queryString_getWaterProblem = sprintf("&totalRows_getWaterProblem=%d%s", $totalRows_getWaterProblem, $queryString_getWaterProblem);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>Manage Water Complains</h1>
<p>&nbsp;</p>
<p><a href="index.php">Main Menu</a></p>
<p><a href="department.php">Back</a></p>
<p>&nbsp;</p>
<table width="1200"  border="1">
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
    <th scope="col">Description</th>
    <th scope="col">Time</th>
    <th scope="col">Status</th>
    <th scope="col">&nbsp;</th>
  </tr>
  <?php do { ?>
    <tr>
      <td><?php echo $row_getWaterProblem['complainNo']; ?></td>
      <td><?php echo $row_getWaterProblem['personName']; ?></td>
      <td><?php echo $row_getWaterProblem['personID']; ?></td>
      <td><?php echo $row_getWaterProblem['personType']; ?></td>
      <td><?php echo $row_getWaterProblem['bhawan']; ?></td>
      <td><?php echo $row_getWaterProblem['roomNo']; ?></td>
      <td><?php echo $row_getWaterProblem['phoneNo']; ?></td>
      <td><?php echo $row_getWaterProblem['email']; ?></td>
      <td><?php echo $row_getWaterProblem['availFrom']; ?></td>
      <td><?php echo $row_getWaterProblem['availTill']; ?></td>
      <td><?php echo $row_getWaterProblem['complainDescr']; ?></td>
      <td><?php echo $row_getWaterProblem['complainTime']; ?></td>
      <td><?php echo $row_getWaterProblem['complainStatus']; ?></td>
      <td><a href="changeStatus.php?complainNo=<?php echo $row_getWaterProblem['complainNo']; ?>&amp;complainType=<?php echo $row_getWaterProblem['complainType']; ?>">RESOLVE</a> This</td>
    </tr>
    <?php } while ($row_getWaterProblem = mysql_fetch_assoc($getWaterProblem)); ?>
</table>
<p>&nbsp;
Records <?php echo ($startRow_getWaterProblem + 1) ?> to <?php echo min($startRow_getWaterProblem + $maxRows_getWaterProblem, $totalRows_getWaterProblem) ?> of <?php echo $totalRows_getWaterProblem ?> </p>
<table border="0">
  <tr>
    <td><?php if ($pageNum_getWaterProblem > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getWaterProblem=%d%s", $currentPage, 0, $queryString_getWaterProblem); ?>"><img src="First.gif" /></a>
    <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getWaterProblem > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getWaterProblem=%d%s", $currentPage, max(0, $pageNum_getWaterProblem - 1), $queryString_getWaterProblem); ?>"><img src="Previous.gif" /></a>
    <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getWaterProblem < $totalPages_getWaterProblem) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getWaterProblem=%d%s", $currentPage, min($totalPages_getWaterProblem, $pageNum_getWaterProblem + 1), $queryString_getWaterProblem); ?>"><img src="Next.gif" /></a>
    <?php } // Show if not last page ?></td>
    <td><?php if ($pageNum_getWaterProblem < $totalPages_getWaterProblem) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getWaterProblem=%d%s", $currentPage, $totalPages_getWaterProblem, $queryString_getWaterProblem); ?>"><img src="Last.gif" /></a>
    <?php } // Show if not last page ?></td>
  </tr>
</table>
<p>&nbsp;</p>
<p>&nbsp;</p>
</body>
</html>
<?php
mysql_free_result($getWaterProblem);
?>
