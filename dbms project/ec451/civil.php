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

$maxRows_getCivilProblems = 10;
$pageNum_getCivilProblems = 0;
if (isset($_GET['pageNum_getCivilProblems'])) {
  $pageNum_getCivilProblems = $_GET['pageNum_getCivilProblems'];
}
$startRow_getCivilProblems = $pageNum_getCivilProblems * $maxRows_getCivilProblems;

mysql_select_db($database_ec451_conn, $ec451_conn);
$query_getCivilProblems = "SELECT * FROM complain_info WHERE complain_info.complainType = 'Civil' AND complain_info.complainStatus = 'PENDING' ORDER BY complainTime ASC";
$query_limit_getCivilProblems = sprintf("%s LIMIT %d, %d", $query_getCivilProblems, $startRow_getCivilProblems, $maxRows_getCivilProblems);
$getCivilProblems = mysql_query($query_limit_getCivilProblems, $ec451_conn) or die(mysql_error());
$row_getCivilProblems = mysql_fetch_assoc($getCivilProblems);

if (isset($_GET['totalRows_getCivilProblems'])) {
  $totalRows_getCivilProblems = $_GET['totalRows_getCivilProblems'];
} else {
  $all_getCivilProblems = mysql_query($query_getCivilProblems);
  $totalRows_getCivilProblems = mysql_num_rows($all_getCivilProblems);
}
$totalPages_getCivilProblems = ceil($totalRows_getCivilProblems/$maxRows_getCivilProblems)-1;

$queryString_getCivilProblems = "";
if (!empty($_SERVER['QUERY_STRING'])) {
  $params = explode("&", $_SERVER['QUERY_STRING']);
  $newParams = array();
  foreach ($params as $param) {
    if (stristr($param, "pageNum_getCivilProblems") == false && 
        stristr($param, "totalRows_getCivilProblems") == false) {
      array_push($newParams, $param);
    }
  }
  if (count($newParams) != 0) {
    $queryString_getCivilProblems = "&" . htmlentities(implode("&", $newParams));
  }
}
$queryString_getCivilProblems = sprintf("&totalRows_getCivilProblems=%d%s", $totalRows_getCivilProblems, $queryString_getCivilProblems);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>Manage Civil Problems</h1>
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
      <td><?php echo $row_getCivilProblems['complainNo']; ?></td>
      <td><?php echo $row_getCivilProblems['personName']; ?></td>
      <td><?php echo $row_getCivilProblems['personID']; ?></td>
      <td><?php echo $row_getCivilProblems['personType']; ?></td>
      <td><?php echo $row_getCivilProblems['bhawan']; ?></td>
      <td><?php echo $row_getCivilProblems['roomNo']; ?></td>
      <td><?php echo $row_getCivilProblems['phoneNo']; ?></td>
      <td><?php echo $row_getCivilProblems['email']; ?></td>
      <td><?php echo $row_getCivilProblems['availFrom']; ?></td>
      <td><?php echo $row_getCivilProblems['availTill']; ?></td>
      <td><?php echo $row_getCivilProblems['complainDescr']; ?></td>
      <td><?php echo $row_getCivilProblems['complainTime']; ?></td>
      <td><?php echo $row_getCivilProblems['complainStatus']; ?></td>
      <td><a href="changeStatus.php?complainNo=<?php echo $row_getCivilProblems['complainNo']; ?>&amp;complainType=<?php echo $row_getCivilProblems['complainType']; ?>">Resolve</a> This</td>
    </tr>
    <?php } while ($row_getCivilProblems = mysql_fetch_assoc($getCivilProblems)); ?>
</table>
<p>&nbsp;
Records <?php echo ($startRow_getCivilProblems + 1) ?> to <?php echo min($startRow_getCivilProblems + $maxRows_getCivilProblems, $totalRows_getCivilProblems) ?> of <?php echo $totalRows_getCivilProblems ?> </p>
<table border="0">
  <tr>
    <td><?php if ($pageNum_getCivilProblems > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getCivilProblems=%d%s", $currentPage, 0, $queryString_getCivilProblems); ?>"><img src="First.gif" /></a>
    <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getCivilProblems > 0) { // Show if not first page ?>
        <a href="<?php printf("%s?pageNum_getCivilProblems=%d%s", $currentPage, max(0, $pageNum_getCivilProblems - 1), $queryString_getCivilProblems); ?>"><img src="Previous.gif" /></a>
    <?php } // Show if not first page ?></td>
    <td><?php if ($pageNum_getCivilProblems < $totalPages_getCivilProblems) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getCivilProblems=%d%s", $currentPage, min($totalPages_getCivilProblems, $pageNum_getCivilProblems + 1), $queryString_getCivilProblems); ?>"><img src="Next.gif" /></a>
    <?php } // Show if not last page ?></td>
    <td><?php if ($pageNum_getCivilProblems < $totalPages_getCivilProblems) { // Show if not last page ?>
        <a href="<?php printf("%s?pageNum_getCivilProblems=%d%s", $currentPage, $totalPages_getCivilProblems, $queryString_getCivilProblems); ?>"><img src="Last.gif" /></a>
    <?php } // Show if not last page ?></td>
  </tr>
</table>
<p>&nbsp;</p>
</body>
</html>
<?php
mysql_free_result($getCivilProblems);
?>
