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
<form id="form1" name="form1" method="post" action="">
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
    <input type="text" name="bhawan" id="bhawan" />
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
    <label for="complainDescr">Complain Descriptio</label>
    <textarea name="complainDescr" id="complainDescr" cols="45" rows="5"></textarea>
  </p>
  <p>&nbsp;</p>
  <p>
    <input type="submit" name="insert" id="insert" value="Update Complain" />
  </p>
</form>
<p>&nbsp;</p>
</body>
</html>