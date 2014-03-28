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

$editFormAction = $_SERVER['PHP_SELF'];
if (isset($_SERVER['QUERY_STRING'])) {
  $editFormAction .= "?" . htmlentities($_SERVER['QUERY_STRING']);
}

if ((isset($_POST["MM_insert"])) && ($_POST["MM_insert"] == "form1")) {
  $insertSQL = sprintf("INSERT INTO complain_info (personName, personID, personType, bhawan, roomNo, phoneNo, email, availFrom, availTill, complainType, complainDescr) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)",
                       GetSQLValueString($_POST['personName'], "text"),
                       GetSQLValueString($_POST['personID'], "int"),
                       GetSQLValueString($_POST['personType'], "text"),
                       GetSQLValueString($_POST['bhawan'], "text"),
                       GetSQLValueString($_POST['roomNo'], "text"),
                       GetSQLValueString($_POST['phoneNo'], "int"),
                       GetSQLValueString($_POST['email'], "text"),
                       GetSQLValueString($_POST['availFrom'], "int"),
                       GetSQLValueString($_POST['availTill'], "int"),
                       GetSQLValueString($_POST['complainType'], "text"),
                       GetSQLValueString($_POST['complainDescr'], "text"));

  mysql_select_db($database_ec451_conn, $ec451_conn);
  $Result1 = mysql_query($insertSQL, $ec451_conn) or die(mysql_error());

  $insertGoTo = "user.php";
  if (isset($_SERVER['QUERY_STRING'])) {
    $insertGoTo .= (strpos($insertGoTo, '?')) ? "&" : "?";
    $insertGoTo .= $_SERVER['QUERY_STRING'];
  }
  header(sprintf("Location: %s", $insertGoTo));
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>Register Your Problem</h1>
<p>&nbsp;</p>
<p><a href="index.php">Main Menu</a></p>
<p><a href="user.php">Back</a></p>
<p>&nbsp;</p>
<form id="form1" name="form1" method="POST" action="<?php echo $editFormAction; ?>">
  <p>
    <label for="personName">Person Name</label>
    <input type="text" name="personName" id="personName" />
  </p>
  <p>
    <label for="personID">Person ID</label>
    <input type="text" name="personID" id="personID" />
  </p>
  <p>
    <label for="personType">Person Type</label>
    <select name="personType" id="personType">
      <option value="Student" selected="selected">Student</option>
      <option value="Employee">Employee</option>
    </select>
  </p>
  <p>
    <label for="bhawan">Bhawan</label>
    <select name="bhawan" id="bhawan">
      <option value="Govind" selected="selected">Govind</option>
      <option value="Ravindra">Ravindra</option>
      <option value="Rajendra">Rajendra</option>
      <option value="Hill View">Hill View</option>
      <option value="Kasturba">Kasturba</option>
    </select>
  </p>
  <p>
    <label for="roomNo">Room No</label>
    <input type="text" name="roomNo" id="roomNo" />
  </p>
  <p>
    <label for="phoneNo">Phone No</label>
    <input type="text" name="phoneNo" id="phoneNo" />
  </p>
  <p>
    <label for="email">Email</label>
    <input type="text" name="email" id="email" />
  </p>
  <p>
    <label for="availFrom">Available From</label>
    <select name="availFrom" id="availFrom">
      <option value="0000">0000</option>
      <option value="0001">0001</option>
      <option value="0002">0002</option>
      <option value="0003">0003</option>
      <option value="0004">0004</option>
      <option value="0005">0005</option>
      <option value="0006">0006</option>
      <option value="0007">0007</option>
      <option value="0008">0008</option>
      <option value="0009">0009</option>
      <option value="0010" selected="selected">0010</option>
      <option value="0011">0011</option>
      <option value="0012">0012</option>
      <option value="0013">0013</option>
      <option value="0014">0014</option>
      <option value="0015">0015</option>
      <option value="0016">0016</option>
      <option value="0017">0017</option>
      <option value="0018">0018</option>
      <option value="0019">0019</option>
      <option value="0020">0020</option>
      <option value="0021">0021</option>
      <option value="0022">0022</option>
      <option value="0023">0023</option>
    </select>
  </p>
  <p>
    <label for="availTill">Available Till</label>
    <select name="availTill" id="availTill">
      <option value="0000">0000</option>
      <option value="0001">0001</option>
      <option value="0002">0002</option>
      <option value="0003">0003</option>
      <option value="0004">0004</option>
      <option value="0005">0005</option>
      <option value="0006">0006</option>
      <option value="0007">0007</option>
      <option value="0008">0008</option>
      <option value="0009">0009</option>
      <option value="0010">0010</option>
      <option value="0011">0011</option>
      <option value="0012">0012</option>
      <option value="0013">0013</option>
      <option value="0014">0014</option>
      <option value="0015">0015</option>
      <option value="0016">0016</option>
      <option value="0017">0017</option>
      <option value="0018" selected="selected">0018</option>
      <option value="0019">0019</option>
      <option value="0020">0020</option>
      <option value="0021">0021</option>
      <option value="0022">0022</option>
      <option value="0023">0023</option>
    </select>
  </p>
  <p>
    <label for="complainType">Complain Type</label>
    <select name="complainType" id="complainType">
      <option value="Civil">Civil</option>
      <option value="Water">Water</option>
      <option value="Electrical" selected="selected">Electrical</option>
    </select>
  </p>
  <p>
    <label for="complainDescr">Complain Description</label>
    <textarea name="complainDescr" id="complainDescr" cols="45" rows="5"></textarea>
  </p>
  <p>&nbsp;</p>
  <p>
    <input type="submit" name="insert" id="insert" value="Complain" />
  </p>
  <input type="hidden" name="MM_insert" value="form1" />
</form>
<p>&nbsp;</p>
</body>
</html>