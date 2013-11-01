<?php
error_log(var_export($_GET,true),3,"log.log");
error_log(var_export($_POST,true),3,"log.log");
error_log(var_export($_FILES,true),3,"log.log");
@mkdir("uploader");
if(!empty($_FILES)){
	foreach($_FILES as $file){
		move_uploaded_file($file['tmp_name'],"uploader/".$file['name']);
	}
}
?>