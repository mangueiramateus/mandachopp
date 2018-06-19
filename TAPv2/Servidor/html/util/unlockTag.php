<?php
        require "lib.php";
        require "config.php";

        $db = new mysqli($host_db,$user_db,$password_db,$db_name);

        $tag_number = $_POST["tag_number"];
        if(istagexist($tag_number,$db)){
                if(istagused($tag_number,$db)){
                        resetflagbytagnumber($tag_number,$db);
                }
                else{
                        echo "Tag não usada";
                }
        }
        else{
                echo "Tag não cadastrada";
        }
        $db->close();
?>


