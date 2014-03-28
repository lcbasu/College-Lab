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

$maxRows_getElectricalProblems = 10;
$pageNum_getElectricalProblems = 0;
if (isset($_GET['pageNum_getElectricalProblems'])) {
  $pageNum_getElectricalProblems = $_GET['pageNum_getElectricalProblems'];
}
$startRow_getElectricalProblems = $pageNum_getElectricalProblems * $maxRows_getElectricalProblems;

mysql_select_db($database_ec451_conn, $ec451_conn);
$query_getElectricalProblems = "SELECT * FROM complain_info WHERE complain_info.complainType = 'Electrical' AND complain_info.complainStatus = 'PENDING' ORDER BY complainTime ASC";
$query_limit_getElectricalProblems = sprintf("%s LIMIT %d, %d", $query_getElectricalProblems, $startRow_getElectricalProblems, $maxRows_getElectricalProblems);
$getElectricalProblems = mysql_query($query_limit_getElectricalProblems, $ec451_conn) or die(mysql_error());
$row_getElectricalProblems = mysql_fetch_assoc($getElectricalProblems);

if (isset($_GET['totalRows_getElectricalProblems'])) {
  $totalRows_getElectricalProblems = $_GET['totalRows_getElectricalProblems'];
} else {
  $all_getElectricalProblems = mysql_query($query_getElectricalProblems);
  $totalRows_getElectricalProblems = mysql_num_rows($all_getElectricalProblems);
}
$totalPages_getElectricalProblems = ceil($totalRows_getElectricalProblems/$maxRows_getElectricalProblems)-1;

$queryString_getElectricalProblems = "";
if (!empty($_SERVER['QUERY_STRING'])) {
  $params = explode("&", $_SERVER['QUERY_STRING']);
  $newParams = array();
  foreach ($params as $param) {
    if (stristr($param, "pageNum_getElectricalProblems") == false && 
        stristr($param, "totalRows_getElectricalProblems") == false) {
      array_push($newParams, $param);
    }
  }
  if (count($newParams) != 0) {
    $queryString_getElectricalProblems = "&" . htmlentities(implode("&", $newParams));
  }
}
$queryString_getElectricalProblems = sprintf("&totalRows_getElectricalProblems=%d%s", $totalRows_getElectricalProblems, $queryString_getElectricalProblems);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>Manage Electrical Problems</h1>
<p>&nbsp;</p>
<p><a href="index.php">Main Menu</a></p>
<p><a href="department.php">Back</a></p>
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
    <th scope="col">Description</th>
    <th scope="col">Time</th>
    <th scope="col">Status</th>
    <th scope="col">&nbsp;</th>
  </tr>
  <?php do { ?>
    <tr>
      <td><?php echo $row_getElectricalProblems['complainNo']; ?></td>
      <td><?php echo $row_getElectricalProblems['personName']; ?></td>
      <td><?php echo $row_getElectricalProblems['personID']; ?></td>
      <td><?php echo $row_getElectricalProblems['personType']; ?></td>
      <td><?php echo $row_getElectricalProblems['bhawan']; ?></td>
      <td><?php echo $row_getElectricalProblems['roomNo']; ?></td>
      <td><?php echo $row_getElectricalProblems['phoneNo']; ?></td>
      <td><?php echo $row_getElectricalProblems['email']; ?></td>
      <td><?php echo $row_getElectricalProblems['availFrom']; ?></td>
      <td><?php echo $row_getElectricalProblems['availTill']; ?></td>
      <td><?php echo $row_getElectricalProblems['complainDescr']; ?></td>
      <td><?php echo $row_getElectricalProblems['complainTime']; ?></td>
      <td><?php echo $row_getElectricalProblems['complainStatus']; ?></td>
      <td><a href="changeStatus.php?complainNo=<?php echo $row_getElectricalProblems['complainNo']; ?>&amp;complainType=<?php echo $row_getElectricalProblems['complainType']; ?>">Resolve</a> This</td>
    </tr>
    <?php } while ($row_getElectricalProblems = mysql_fetch_assoc($getElectricalProblems)); ?>
</table>
<p>&nbsp;
Records <?php echo ($startRow_getElectricalProblems + 1) ?> to <?php echo min($startRow_getElectricalProblems + $maxRows_getElectricalProblems, $totalRows_getElectricalProblems) ?> of <?php echo $totalRows_getElectricalProblems ?> </p>
<table border="0">
  <tr>
    <td><?php if ($pageNum_getElectricalProblems > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getElectricalProblems=%d%s", $currentPage, 0, $queryString_getElectricalProblems); ?>"><img src="First.gif" /></a>
    <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getElectricalProblems > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getElectricalProblems=%d%s", $currentPage, max(0, $pageNum_getElectricalProblems - 1), $queryString_getElectricalProblems); ?>"><img src="Previous.gif" /></a>
    <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getElectricalProblems < $totalPages_getElectricalProblems) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getElectricalProblems=%d%s", $currentPage, min($totalPages_getElectricalProblems, $pageNum_getElectricalProblems + 1), $queryString_getElectricalProblems); ?>"><img src="Next.gif" /></a>
    <?php } // Show if not last page ?></td>
    <td><?php if ($pageNum_getElectricalProblems < $totalPages_getElectricalProblems) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getElectricalProblems=%d%s", $currentPage, $totalPages_getElectricalProblems, $queryString_getElectricalProblems); ?>"><img src="Last.gif" /></a>
    <?php } // Show if not last page ?></td>
  </tr>
</table>
<p>&nbsp;</p>
</body>
</html>
<?php
mysql_free_result($getElectricalProblems);
?>
