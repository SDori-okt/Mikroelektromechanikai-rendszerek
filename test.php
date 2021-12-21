<?php

if(isset($_GET["state"])) {
   $state = $_GET["state"]; // get temperature value from HTTP GET

   $servername = "localhost";
   $username = "uno";
   $password = "";
   $dbname = "ajto";

   // Create connection
   $conn = new mysqli($servername, $username, $password, $dbname);
   // Check connection
   if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
   }

   $sql = "INSERT INTO idopontok (nyit) VALUES ($state)";

   if ($conn->query($sql) === TRUE) {
      echo "New record created successfully";
   } else {
      echo "Error: " . $sql . " => " . $conn->error;
   }

   $conn->close();
} else {
   echo "temperature is not set";
}
?>