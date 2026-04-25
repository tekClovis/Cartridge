# Quick script — paste in terminal
GB_FILE="./pokopie.gb"
SIZE=$(wc -c < "$GB_FILE")
MAX=131072   # 128KB = 0x02 in header — change to match yours

USED=$SIZE
LEFT=$((MAX - USED))
PCT=$((USED * 100 / MAX))

echo "Used:      $USED bytes ($PCT%)"
echo "Remaining: $LEFT bytes"
echo "Total:     $MAX bytes"
