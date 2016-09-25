<?php
    $warnings = array(0 => "you can't stay on the same place ", 1 => "you can't eat your figures", 2 => "no figure on choosen cell");                                                              
	$input = file_get_contents("input.txt");                                                
	if(strlen($input) != 0)
		$list = explode(" ", $input);                                                           
	for($i = 0;$i < 64;++ $i)
		if(!isset($list[$i]))
			$list[$i] = 0;
	$a = array();                                     
	function get_link($black, $cell_black, $type){
		$figures = array(0 => "pawn", 1 => "rook", 2 => "horse", 3 => "bishop", 4 => "queen", 5 => "king");
		$link = ($black == 1 ? "images/black_" : "images/white_");
		$link .= $figures[$type];
		$link .= ($cell_black == 1 ? "_on_black.png" : "_on_white.png");
		return $link;
	}
	function make_table(&$a, $list){
	    $uk = 0;
		for($i = 1;$i <= 8;++ $i){
			for($j = 1;$j <= 8;++ $j){
			    $color = ($i + $j) % 2;
			    if($list[$uk] == 0)
			    	$a[$i][$j] = get_empty_cell($color);
			    else if($list[$uk] == 3)
			    	$a[$i][$j] = get_plus_cell($color);
			    else
			    	$a[$i][$j] = get_link($list[$uk][0] - 1, $color, $list[$uk][1]);
				++ $uk;							
			}
		}
	}
	make_table($a, $list);
	function swap(&$a, &$b){
		$tmp = $b;
		$b = $a;
		$a = $tmp;
	}
	function create_standart_table(&$a){
		$start = array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5, 6 => 3, 7 => 2, 8 => 1);
		for($i = 1;$i <= 8;++ $i)
			$a[1][$i] = get_link(1, ($i - 1) % 2, $start[$i]);	
		for($i = 1;$i <= 8;++ $i)
			$a[2][$i] = get_link(1, $i % 2, 0);	
		for($i = 3;$i <= 6;++ $i)
			for($j = 1;$j <= 8;++ $j)
				$a[$i][$j] = get_empty_cell(($i + $j) % 2);
		for($i = 1;$i <= 8;++ $i)
			$a[7][$i] = get_link(0, ($i - 1) % 2, 0);	
		for($i = 1;$i <= 8;++ $i)
			$a[8][$i] = get_link(0, $i % 2, $start[$i]);	
	}
	function show_chess_board(&$a){
		echo "<table id = 'bordergo'><tr>";
		echo "<td> </td>";
		for($j = 1;$j <= 8;++ $j){
			echo "<td>";
			echo chr(64 + $j); 
			echo "</td>";
		}
		echo "</tr>";
		for($i = 1;$i <= 8;++ $i){
		    $num = $i;
			echo "<tr> <td> $num </td> ";
			for($j = 1;$j <= 8;++ $j){
				$fig = $a[$i][$j];
			    echo "<td id = 'in'> <img src = '$fig'> </td>";
			}
			echo "</tr>";
		}	
		echo "</table>";
	}
	function get_value($name, &$last_move){
		if($name == "xs")
			return $last_move[0];
		else if($name == "ys")
			return $last_move[1];
		else if($name == "xf")
			return $last_move[2];
		else
			return $last_move[3];
	}
	function x_pos_form($name){
		$last_move = explode(" ", file_get_contents("last.txt"));
		$value = get_value($name, $last_move);
		echo "<select name = '$name'>";
		for($i = 1;$i <= 8;++ $i){
		    if($i == $value)
				echo "<option selected = '$i' value = '$i'> $i </option>";
			else
				echo "<option value = '$i'> $i </option>";
		}
		echo "</select>";
	}
	function y_pos_form($name, $zabei = 0){
		$last_move = explode(" ", file_get_contents("last.txt"));
		if($zabei == 1)
			$value = 'A';
		else
			$value = get_value($name, $last_move);
		echo "<select name = '$name'>";
		for($i = 1;$i <= 8;++ $i){
			$pos = chr(64 + $i);
			if($value == $pos)
				echo "<option selected = '$i' value = '$i'> $pos </option>";
			else 
				echo "<option value = '$i'> $pos </option>";
		}
		echo "</select>";
	}
	function get_empty_cell($color){
		if($color == 0)
			return "images/white_cell.png";
		else 
			return "images/black_cell.png";
	}
	function get_plus_cell($color){
		if($color == 0)
			return "images/from_white_cell.png";
		else
			return "images/from_black_cell.png";
	}
	function get_index($x, $y){
		return ($x - 1) * 8 + $y - 1;
	}
	function clear_all_previous_3(&$list){
		for($i = 0;$i < 64;++ $i)
			if($list[$i] == 3)
				$list[$i] = 0;
	}
	function figure($a){
		if($a == 0 || $a == 3)
			return false;
		return true;
	}
	function is_pawn($fig){
		if($fig == 10 || $fig == 20)
			return true;
		return false;
	}
	function is_choose($f1, $f2, $xf){
	    if(($figure[0] == $f2[0] && figure($f2) == true) || is_pawn($f1) == false)
	    	return false;
		if($f1 == 10 && $xf == 8)
			return true;
		if($f1 == 20 && $xf == 1)
			return true;			
		return false;	
	}
	function make_move($xs, $ys, $xf, $yf, &$list, $no_need = 0, &$is_choose = 0, &$a = 0){
		$last_move = $xs." ";
		$add = chr(64 + $ys);
		$last_move .= $add." ";
		$last_move .= $xf." ";
		$add = chr(64 + $yf);
		$last_move .= $add;
		file_put_contents("last.txt", $last_move);
		$from = get_index($xs, $ys);		
		$to = get_index($xf, $yf);
		$bad = 0;
		if(figure($list[$from]) == false){
			if($no_need != 0)
				$bad = 1;
			else {
		 
				header("Location:http://www.chess.com?pr=2"); 
				exit;		
			}
		}
		if($xs == $xf && $ys == $yf){
			if($no_need != 0)
				$bad = 1;
			else {
		 
				header("Location:http://www.chess.com?pr=0"); 
				exit;
			}
		}	
		if($list[$from][0] == $list[$to][0]){
			if($no_need != 0)
				$bad = 1;
			else {
		 
				header("Location:http://www.chess.com?pr=1"); 
				exit;
			}
		}
		if($bad == 0){
			if(is_choose($list[$from], $list[$to], $xf) == true){
				$is_choose = 1;
				$color = $list[$from][0] - 1;
				$a[$xf][$yf] = "images/question_on_";
				if(($xf + $yf) % 2 == 1)
					$a[$xf][$yf] .= "black.png";
				else
					$a[$xf][$yf] .= "white.png";
				if($no_need != 2){
?>
				<div id = 'choose'>
				    <table>
						<form method = 'post' action = 'index.php'>
					        <tr> <td align = "center"> Choose your figure </td> </tr>
					        <tr> <td>
							   		<input type = 'radio' name = 'choose' value = '1'> <img height = '40px' width = '40px' src = '<?php echo get_link($color, 0, 1); ?>'> 
							   		<input type = 'radio' name = 'choose' value = '2'> <img height = '40px' width = '40px' src = '<?php echo get_link($color, 0, 2); ?>'> 
							   		<input type = 'radio' name = 'choose' value = '3'> <img height = '40px' width = '40px' src = '<?php echo get_link($color, 0, 3); ?>'> 
							   		<input type = 'radio' name = 'choose' value = '4'> <img height = '40px' width = '40px' src = '<?php echo get_link($color, 0, 4); ?>'> 		   			
							   		<input type = 'hidden' name = 'sx' value = '<?php echo $xs;?>'>
							   		<input type = 'hidden' name = 'sy' value = '<?php echo $ys;?>'>
							   		<input type = 'hidden' name = 'x' value = '<?php echo $xf;?>'>
							   		<input type = 'hidden' name = 'y' value = '<?php echo $yf;?>'>
							   		<input type = 'hidden' name = 'color' value = '<?php echo $color;?>'> 
							<td> </tr>
							<tr> <td align = "center"> 
									<input type = "submit" value = "choose"> 
							</td> </tr> 
						</form>
					</table>
				</div> 
<?          	}
			}
			else {
				clear_all_previous_3($list);
				swap($list[$from], $list[$to]);
				$list[$from] = 3;
			}
		}
	}
	function put($x, $y, $color, $type, $list){
		$id = get_index($x, $y);			
		$list[$id] = $color.$type;
		$new_list = implode(" ", $list);
		file_put_contents("input.txt", $new_list);
	}
	if(isset($_POST["choose"])){
	    $xs = $_POST["sx"];
	    $ys = $_POST["sy"];
	    $xf = $_POST["x"];
	    $yf = $_POST["y"];		
		if(figure($list[get_index($xf, $yf)]) == false) 
			$was = ' ';
		else 
			$was = $list[get_index($xf, $yf)][1];
		$move = $xs."-".$ys;
		$move .= $was.$xf."-".$yf.":.";
		$was = file_get_contents("moves.txt");
		$was .= $move;
		file_put_contents("moves.txt", $was);
		make_move($xs, $ys, $xf, $yf, $list, 2, $is_choose, $a);		
		$last_move = $xs." ";
		$add = chr(64 + $ys);
		$last_move .= $add." ";
		$last_move .= $xf." ";
		$add = chr(64 + $yf);
		$last_move .= $add;
		file_put_contents("last.txt", $last_move);
	    $id = get_index($xs, $ys);
	    $list[$id] = 0;
	    put($_POST["x"], $_POST["y"], ($_POST["color"] + 1), $_POST["choose"], $list);
		 
		header("Location:http://www.chess.com");
		exit;
	}
	function get_moves(&$len){				    
		$word = file_get_contents("moves.txt");					
		for($i = 0;$i < strlen($word);++ $i)
			if($word[$i] == '.')
				++ $len;
		$moves = explode(".", file_get_contents("moves.txt"));					
		return $moves;
	}
	function figures($color){
    	for($i = 0;$i <= 5;++ $i){
    		$link = get_link($color - 1, 0, $i);
    		$value = $color.$i;
    		echo "<input type = 'radio' name = 'add' value = '$value'> <img height = '40px' width = '40px' src = '$link'>";
    	}
	}
	function get_coordinates(&$x1, &$y1, &$x2, &$y2, $word){
		$x1 = $word[0];		
		$y1 = $word[2];		
		$x2 = $word[4];		
		$y2 = $word[6];		
	}
	function undo_move($x1, $y1, $x2, $y2, &$list, $type, $was){
		$id1 = get_index($x1, $y1);
		$id2 = get_index($x2, $y2);
		$color = $list[$id2][0];
		if($type == 1){			
		    if($was != ' ')
			    $list[$id2] = ((($color - 1) ^ 1) + 1).$was;		    
			else
				$list[$id2] = 0;
			$list[$id1] = $color."0";
		}		
		else {
		    if($was != ' ')
			    $list[$id1] = ((($color - 1) ^ 1) + 1).$was;		    
			swap($list[$id1], $list[$id2]);
		}                                                
	}                                                     
	if(isset($_POST["undo"])){                            
	    clear_all_previous_3($list);                      
		$len = 0;				
		$moves = get_moves($len);
		if($len > 0){
			$last = $moves[$len - 1];
			$cnt = strlen($last);
			$x1 = $y1 = $x2 = $y2 = -1;
			get_coordinates($x1, $y1, $x2, $y2, $last);
			$left = "";
			for($i = 0;$i < $len - 1;++ $i)
				$left .= $moves[$i].".";
			file_put_contents("moves.txt", $left);
			if($last[$cnt - 1] == ":")
				undo_move($x1, $y1, $x2, $y2, $list, 1, $last[3]);				
			else 
				undo_move($x1, $y1, $x2, $y2, $list, 0, $last[3]);								
			$new_list = implode(" ", $list);
			file_put_contents("input.txt", $new_list);
		 
			header("Location:http://www.chess.com");
			exit;			
		}
	}
	if(isset($_POST["xs"])){
		$xs = $_POST["xs"];	
		$ys = $_POST["ys"];	
		$xf = $_POST["xf"];	
		$yf = $_POST["yf"];
		$is_choose = 0;
		if(figure($list[get_index($xf, $yf)]) == false) 
			$was = ' ';
		else 
			$was = $list[get_index($xf, $yf)][1];
		make_move($xs, $ys, $xf, $yf, $list, 0, $is_choose, $a);
		if($is_choose == 0){
			$move = $xs."-".$ys;
			$move .= $was.$xf."-".$yf.".";
			$was = file_get_contents("moves.txt");
			$was .= $move;
			file_put_contents("moves.txt", $was); 
			$new_list = implode(" ", $list);
			file_put_contents("input.txt", $new_list);
			 
			header("Location:http://www.chess.com");
			exit;
		}
	}
	if(isset($_POST["add"])){
		$x = $_POST["px"];
		$y = $_POST["py"];
		$who = $_POST["add"];
		put($x, $y, $who[0], $who[1], $list);
		 
		header("Location:http://www.chess.com");
		exit;
	}
	if(isset($_POST["check"])){
		exec("a.exe");
		$info = file_get_contents("ai_move.txt");
		if($info != "Impossible"){
			$x = $info[0];
			$y = $info[2];
			$x2 = $info[4];
			$y2 = $info[6];
			if(figure($list[get_index($x2, $y2)]) == false) 
				$was = ' ';
			else 
				$was = $list[get_index($x2, $y2)][1];
			make_move($x, $y, $x2, $y2, &$list, 1);
			$new_list = implode(" ", $list);
			file_put_contents("input.txt", $new_list);
			$move = $x."-".$y.$was.$x2."-".$y2.".";
			$was = file_get_contents("moves.txt");
			$was .= $move;
			file_put_contents("moves.txt", $was);
		 
			header("Location:http://www.chess.com");
			exit;		
		}
	}	
?>
<html>
	<head>
		<title>chess</title>                                                  			   	
		<link rel="stylesheet" type="text/css" href="style/style.css">                 			   	
		<link rel="shortcut icon" href="images/favicon.ico">
	</head>
	<body>
		<div id = "out">
			<span id = "bold">
			    <?php 
//			    	exec("is_checkmate.exe");
/*			    	$now = file_get_contents("checkmate.txt");
			    	if($now == 1)
			    		echo "check!";
			    	else if($now == 2)
			    		echo "checkmate!!";
			    	else if($now == 3)
			    		echo "draw";
*/			    ?>
			</span>
		</div>
		<div id = "moves">
			<span id = "bold">
	        	moves:
			</span>
			<table> 
				<?php
					$len = 0;		
					$moves = get_moves($len);
					for($i = 0;$i < $len;++ $i){
					    $moves[$i][2] = chr(64 + $moves[$i][2]); 
					    $moves[$i][3] = ' ';
					    $moves[$i][6] = chr(64 + $moves[$i][6]); 
					    if($moves[$i][7] == ":")
					    	$moves[$i][7] = '';
					    echo "<tr><td>";
						echo $moves[$i]."<br>";
						echo "</td></tr>";
					}
					if($len > 0){
					?>
						<tr>
							<td>
								<form action = "index.php" method = "post">
									<input type = "submit" name = "undo" value = "undo">
								</form>
							</td>
						</tr>
					<?}															
				?>	
			</table> 
		</div>
	    <div id = "board">
			<?php
			    show_chess_board($a);
			?>
		</div>
		<!--
	    <div id = "add">
			<form action = "index.php" method = "post">
					<table>
						<tr> <td align = "center" colspan = "2"> <span id = "bold"> add figures </span> </td> </tr>
						<tr> <td colspan = "2"> <?php figures(1); ?> </td> </tr>
						<tr> <td colspan = "2"> <?php figures(2); ?> </td> </tr>
						<tr> <td> to:   </td> <td> <?php x_pos_form("px"); y_pos_form("py", 1); ?> </td> </tr>
						<tr> <td align = "left" colspan = "2"> <input type="submit" value="add"> </td> </td>
					</table>
			</form>		
		</div>-->
		<div id = "form">
		    <div id = "move">
				<form action = "index.php" method = "post">
					<table>
						<tr> <td align = "center" colspan = "2"> <span id = "bold"> make move </span> </td> </tr>
						<tr> <td> from: </td> <td> <?php x_pos_form("xs"); y_pos_form("ys"); ?> </td> </tr>
						<tr> <td> to:   </td> <td> <?php x_pos_form("xf"); y_pos_form("yf"); ?> </td> </tr>
						<tr> <td align = "left" colspan = "2"> <input type="submit" value="move"> </td> </td>
					</table>
				</form>		
			</div>								
			<?php 
				if(isset($_GET["pr"])){
					$out = $warnings[$_GET['pr']];
					echo "
						<div id = 'warning1'>
							$out
						</div>
						";
				}
			?>
			<form action = "index.php" method = "post">			   
				<input type = "submit" name = "check" value = "AI move" id = "check">
			</form>		
				<?php
					if(isset($_POST["check"])){
						$info = file_get_contents("ai_move.txt");
						if($info == "Impossible"){
							echo "<div id = 'warning2'>";
							echo "It is impossible to win with no more than 3 moves";
							echo "</div>";
						}
					}					
				?>
			</div>
		</div>
	</body>
</html>