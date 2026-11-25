#!/bin/bash
cd "$(dirname "$0")/.." || exit 1
T=textures
mkdir -p maps/ok maps/bad maps/bad/dir.cub
mk(){ printf "%b" "$2" > "maps/$1"; }
H="NO $T/north.xpm\nSO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\n\nF 220,100,0\nC 225,30,0\n\n"
M="111111\n100101\n101001\n1100N1\n111111\n"
TX="NO $T/north.xpm\nSO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\n"

# ---------- VALIDES ----------
mk ok/simple.cub "$H$M"
mk ok/disorder.cub "\n\nC   0, 0 ,255  \n\n\nEA $T/east.xpm\n   NO   $T/north.xpm   \nF 1,2,3\nWE $T/west.xpm\nSO $T/south.xpm\n\n\n111\n1E1\n111\n\n\n   \n"
mk ok/no_final_nl.cub "${H}111\n1S1\n111"
mk ok/crlf.cub "NO $T/north.xpm\r\nSO $T/south.xpm\r\nWE $T/west.xpm\r\nEA $T/east.xpm\r\nF 1,1,1\r\nC 2,2,2\r\n111\r\n1W1\r\n111\r\n"
mk ok/subject.cub "${H}        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111  1110101  101111010001\n11111111  1111111  111111111111\n"

# ---------- INVALIDES : fichier / header ----------
mk bad/empty.cub ""
mk bad/only_header.cub "$H"
mk bad/missing_NO.cub "SO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\nF 1,1,1\nC 1,1,1\n$M"
mk bad/dup_NO.cub "NO $T/north.xpm\n$H$M"
mk bad/unknown_id.cub "NE $T/north.xpm\n$H$M"
mk bad/tex_extra.cub "NO $T/north.xpm extra\nSO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\nF 1,1,1\nC 1,1,1\n$M"
mk bad/tex_missing_file.cub "NO $T/nope.xpm\nSO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\nF 1,1,1\nC 1,1,1\n$M"
mk bad/tex_not_xpm.cub "NO Makefile\nSO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\nF 1,1,1\nC 1,1,1\n$M"
mk bad/tex_empty.cub "NO\nSO $T/south.xpm\nWE $T/west.xpm\nEA $T/east.xpm\nF 1,1,1\nC 1,1,1\n$M"

# ---------- INVALIDES : couleurs ----------
i=0
for col in "220,100" "220,100,0,5" "220,100," "220,,0" "256,0,0" "-1,0,0" \
           "2a0,0,0" "99999999999,0,0" "" ",1,2" "1 2,3,4" "+5,0,0"; do
	i=$((i+1)); mk "bad/color_$i.cub" "${TX}F $col\nC 1,1,1\n$M"
done

# ---------- INVALIDES : map ----------
mk bad/map_before_header.cub "NO $T/north.xpm\nSO $T/south.xpm\n$M\nWE $T/west.xpm\nEA $T/east.xpm\nF 1,1,1\nC 1,1,1\n"
mk bad/map_not_last.cub "$H${M}F 1,1,1\n"
mk bad/map_empty_line.cub "${H}111111\n100101\n\n101001\n1100N1\n111111\n"
mk bad/open_top.cub "${H}111011\n100101\n101001\n1100N1\n111111\n"
mk bad/open_side.cub "${H}111111\n000101\n101001\n1100N1\n111111\n"
mk bad/open_short_line.cub "${H}111111\n10010\n101001\n1100N1\n111111\n"
mk bad/space_hole.cub "${H}111111\n10 101\n101001\n1100N1\n111111\n"
mk bad/no_player.cub "${H}111\n101\n111\n"
mk bad/two_players.cub "${H}1111\n1NS1\n1111\n"
mk bad/bad_char.cub "${H}1111\n1N21\n1111\n"
mk bad/tab_in_map.cub "${H}1111\n1N01\n1111\t\n"
mk bad/player_on_edge.cub "${H}1N11\n1001\n1111\n"
echo "maps créées"
