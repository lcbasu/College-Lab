<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>

<body>
<h1>IIT Roorkee Complaint Administrator </h1>
<p><a href="index.php">Main Menu</a></p>
<form id="form1" name="form1" method="get" action="adminDisplay.php">
  <p><a href="adminDisplay.php?query=1">All Complaints</a></p>
    <p><a href="adminDisplay.php?query=2">Resolved Fast</a></p>
    <p><a href="adminAggr1.php">Type Frequency</a></p>
    <p><a href="adminAggr2.php">Spatial Frequency</a></p>
    
  <p>Filters: </p>
  <p>
    <label for="complainNo">Complain No:</label>
    <input type="text" name="complainNo" id="complainNo" />
  </p>

  <p>
    <label for="personID">Person ID:</label>
    <input type="text" name="personID" id="personID" />
  </p>

  <p>
    <label for="personType">Person Type:</label>
    <select name="personType" id="personType">
      <option value="Student">Student</option>
      <option value="Employee">Employee</option>
      <option value="Choose" selected="selected">Choose...</option>
    </select>
  </p>
  <p>
    <label for="bhawan">Bhawan:</label>
    <select name="bhawan" id="bhawan">
      <option value="Govind">Govind</option>
      <option value="Ravindra">Ravindra</option>
      <option value="Rajendra">Rajendra</option>
      <option value="Hill View">Hill View</option>
      <option value="Kasturba">Kasturba</option>
      <option value="Choose" selected="selected">Choose...</option>
    </select>
  </p>
  <p>
    <label for="complainType">Complain Type:</label>
    <select name="complainType" id="complainType">
      <option value="Electrical">Electrical</option>
      <option value="Civil">Civil</option>
      <option value="Water">Water</option>
      <option value="Choose" selected="selected">Choose...</option>
    </select>
  </p>
  <p>
    <label for="complainStatus">Complain Status</label>
    <select name="complainStatus" id="complainStatus">
      <option value="Choose" selected="selected">Choose...</option>
      <option value="PENDING">PENDING</option>
      <option value="RESOLVED">RESOLVED</option>
    </select>
  </p>
  <p>
    <input type="submit" name="submit" id="submit" value="Submit" />
  </p>
</form>
<p>&nbsp;</p>
<p>&nbsp;</p>
</body>
</html>