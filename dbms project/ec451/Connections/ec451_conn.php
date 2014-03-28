<?php
# FileName="Connection_php_mysql.htm"
# Type="MYSQL"
# HTTP="true"
$hostname_ec451_conn = "localhost";
$database_ec451_conn = "course_project";
$username_ec451_conn = "lokesh";
$password_ec451_conn = "lokesh";
$ec451_conn = mysql_pconnect($hostname_ec451_conn, $username_ec451_conn, $password_ec451_conn) or trigger_error(mysql_error(),E_USER_ERROR); 
?>