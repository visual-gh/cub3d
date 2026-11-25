#!/bin/bash
cd "$(dirname "$0")/.." || exit 1
fail=0
for f in maps/bad/*; do
	out=$(timeout 2 ./cub3D "$f" 2>&1)
	if echo "$out" | head -1 | grep -q '^Error$'; then
		printf "✅ %-26s %s\n" "$(basename "$f")" "$(echo "$out" | sed -n 2p)"
	else
		printf "❌ %-26s ne renvoie pas Error\n" "$(basename "$f")"; fail=1
	fi
done
[ $fail -eq 0 ] && echo "🎉 toutes les maps invalides sont refusées"
